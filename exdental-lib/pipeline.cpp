#include "Pipeline.h"
#include <Windows.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>

pipeline::SubPipelinePlanar::SubPipelinePlanar(vtkSmartPointer<vtkImageImport> img)
{
	this->importedImage = img;
	resliceMapper = vtkSmartPointer<vtkImageResliceMapper>::New();
	resliceMapper->SetInputConnection(img->GetOutputPort());
	resliceMapper->SliceFacesCameraOn();
	resliceMapper->SliceAtFocalPointOn();

	resliceProperties = vtkSmartPointer<vtkImageProperty>::New();
	resliceProperties->SetColorWindow(256);
	resliceProperties->SetColorLevel(1200);
	resliceProperties->SetAmbient(0);
	resliceProperties->SetDiffuse(1);
	resliceProperties->SetOpacity(1);

	resliceActor = vtkSmartPointer<vtkImageSlice>::New();
	resliceActor->SetMapper(resliceMapper);
	resliceActor->SetProperty(resliceProperties);
}

void pipeline::SubPipelinePlanar::Update()
{
	importedImage->Update();
	//resliceMapper->Update();
	resliceActor->Update();
}

pipeline::SubPipelineVR::SubPipelineVR(vtkSmartPointer<vtkImageImport> img)
{
	this->importedImage = img;
	vrMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	vrMapper->SetMaxMemoryFraction(0.9);
	vrMapper->SetInputConnection(img->GetOutputPort());
	vrProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
	opacityFunction->AddSegment(0, 0, 200, 0.2);
	opacityFunction->AddSegment(201, 0.2, 600, 0.8);
	opacityFunction->AddSegment(601, 0.8, 1000, 1);
	vrProperty->SetScalarOpacity(opacityFunction);
	vtkSmartPointer<vtkColorTransferFunction> colorFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
	colorFunction->AddRGBSegment(0, 0, 0, 0, 200, 1, 0, 0);
	colorFunction->AddRGBSegment(201, 1, 0, 0, 600, 1, 1, 0);
	colorFunction->AddRGBSegment(601, 1, 1, 0, 1000, 1, 1, 1);
	vrProperty->SetColor(colorFunction);
	vrProperty->ShadeOn();
	//Propriedades definindas
	vrActor = vtkSmartPointer<vtkVolume>::New();
	vrActor->SetProperty(vrProperty);
	vrActor->SetMapper(vrMapper);
}

void pipeline::SubPipelineVR::Update()
{
	importedImage->Update();
	vrMapper->Update();
	vrActor->Update();
}

void pipeline::Pipeline::CreateFinalImageFromShort(ShortImage::Pointer src)
{
	if (!finalImage)
		finalImage = vtkSmartPointer<vtkImageImport>::New();

	int szX = src->GetLargestPossibleRegion().GetSize()[0];
	int szY = src->GetLargestPossibleRegion().GetSize()[1];
	int szZ = src->GetLargestPossibleRegion().GetSize()[2];
	double sX = src->GetSpacing()[0];
	double sY = src->GetSpacing()[1];
	double sZ = src->GetSpacing()[2];
	double oX = src->GetOrigin()[0];
	double oY = src->GetOrigin()[1];
	double oZ = src->GetOrigin()[2];
	finalImage->SetDataSpacing(sX, sY, sZ);
	finalImage->SetDataOrigin(oX, oY, oZ);
	finalImage->SetWholeExtent(0, szX - 1, 0, szY - 1, 0, szZ - 1);
	finalImage->SetDataExtentToWholeExtent();
	finalImage->SetDataScalarTypeToShort();
	void* srcPtr = src->GetBufferPointer();
	finalImage->SetImportVoidPointer(srcPtr, 1);
	finalImage->Modified();
	finalImage->Update();
}

pipeline::Pipeline::~Pipeline()
{
	FreeLibrary(hDllHandle);
}



pipeline::Pipeline::Pipeline(shared_ptr<LoadedImage> img, HWND progressBarWindow)
{
	sigmoidAlpha = 409;
	sigmoidBeta = 1392;
	sigmoidMin = 0.0;
	sigmoidMax = 100.0;
	this->progressBarWindowHandle = progressBarWindow;
	myITKProgressObserver = MyITKProgressEventSender::New();
	((MyITKProgressEventSender*)(myITKProgressObserver.GetPointer()))->SetHWND(progressBarWindow);

	hDllHandle = LoadLibrary("exdental-opencl-module.dll");
	if (!hDllHandle)
		throw std::exception("dll não encontrada.");
	GpuAnisotropicDelegate = (GpuAnisotropicFilterDelegate)GetProcAddress(hDllHandle, "ExecuteAnistropicDiffusion");
	if(!GpuAnisotropicDelegate)
		throw std::exception("ExecuteAnistropicDiffusion() não encontrada.");
	finalImage = nullptr;
	this->imagem = img;
	//Filtro de suavização via GPU
	imagemPosSuavizacao = ShortImage::New();
	GpuAnisotropicDelegate(imagem->GetImage(),5,0.0125,3, imagemPosSuavizacao, progressBarWindowHandle);
	//Sigmóide
	shortToFloat = ShortToFloatImageFilter::New();
	shortToFloat->AddObserver(itk::ProgressEvent(), myITKProgressObserver);
	sigmoid = SigmoidFilter::New();
	sigmoid->AddObserver(itk::ProgressEvent(), myITKProgressObserver);
	thresholder = OtsuThresholdFilter::New();
	thresholder->AddObserver(itk::ProgressEvent(), myITKProgressObserver);
	thresholder->DebugOn();
	thresholder->SetInsideValue(0);
	thresholder->SetOutsideValue(100);
	floatToShort = FloatToShortImageFilter::New();
	floatToShort->AddObserver(itk::ProgressEvent(), myITKProgressObserver);
	
	SetSigmoid(sigmoidAlpha, sigmoidBeta, sigmoidMin, sigmoidMax);
	LinkFiltersAfterGPUSmooth();

	CreateFinalImageFromShort(floatToShort->GetOutput());
	pipelineDoPlano = make_unique<SubPipelinePlanar>(finalImage);
	pipelineDoVR = make_unique<SubPipelineVR>(finalImage);
	pipelineDoPlano->SetWL(50, 50);
}

void pipeline::Pipeline::LinkFiltersAfterGPUSmooth()
{
	shortToFloat->SetInput(imagemPosSuavizacao);
	sigmoid->SetInput(shortToFloat->GetOutput());
	thresholder->SetInput(sigmoid->GetOutput());
	floatToShort->SetInput(thresholder->GetOutput());
	floatToShort->Update();
}

void pipeline::Pipeline::SetSigmoid(short alpha, short beta, float min, float max)
{
	sigmoid->SetAlpha(alpha);
	sigmoid->SetBeta(beta);
	sigmoid->SetOutputMinimum(min);
	sigmoid->SetOutputMaximum(max);
}

void pipeline::Pipeline::Sigmoide(short alpha, short beta, float min, float max)
{
	this->sigmoidAlpha = alpha;
	this->sigmoidBeta = beta;
	this->sigmoidMin = min;
	this->sigmoidMax = max;
	SetSigmoid(alpha, beta, min, max);
	LinkFiltersAfterGPUSmooth();
	CreateFinalImageFromShort(floatToShort->GetOutput());
	pipelineDoPlano->Update();
	pipelineDoVR->Update();
}

void pipeline::Pipeline::SalvarSigmoide(string file)
{
	imageLoader::SaveAsXML(sigmoid->GetOutput(), file);
}

void pipeline::Pipeline::SalvarOtsu(string file)
{
	imageLoader::SaveAsXML(thresholder->GetOutput(), file);
}

void pipeline::Pipeline::Suavizacao(int iterations, double timestep, double conductance)
{
	GpuAnisotropicDelegate(imagem->GetImage(), iterations, timestep, conductance, imagemPosSuavizacao, progressBarWindowHandle);
	SetSigmoid(sigmoidAlpha, sigmoidBeta, sigmoidMin, sigmoidMax);
	LinkFiltersAfterGPUSmooth();
	CreateFinalImageFromShort(floatToShort->GetOutput());
	pipelineDoPlano->Update();
	pipelineDoVR->Update();
}
