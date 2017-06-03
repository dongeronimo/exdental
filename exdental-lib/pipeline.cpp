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
	resliceMapper->Update();
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
	opacityFunction->AddSegment(0, 0, 300, 0.2);
	opacityFunction->AddSegment(301, 0.2, 800, 0.8);
	opacityFunction->AddSegment(801, 0.8, 1200, 1);
	vrProperty->SetScalarOpacity(opacityFunction);
	vtkSmartPointer<vtkColorTransferFunction> colorFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
	colorFunction->AddRGBSegment(0, 0, 0, 0, 300, 1, 0, 0);
	colorFunction->AddRGBSegment(301, 1, 0, 0, 800, 1, 1, 0);
	colorFunction->AddRGBSegment(801, 1, 1, 0, 1200, 1, 1, 1);
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



pipeline::Pipeline::Pipeline(shared_ptr<LoadedImage> img)
{
	hDllHandle = LoadLibrary("exdental-opencl-module.dll");
	if (!hDllHandle)
		throw std::exception("dll não encontrada.");
	GpuAnisotropicDelegate = (GpuAnisotropicFilterDelegate)GetProcAddress(hDllHandle, "ExecuteAnistropicDiffusion");
	if(!GpuAnisotropicDelegate)
		throw std::exception("ExecuteAnistropicDiffusion() não encontrada.");
	finalImage = nullptr;
	this->imagem = img;
	imagemPosSuavizacao = ShortImage::New();
	GpuAnisotropicDelegate(imagem->GetImage(),5,0.0125,3, imagemPosSuavizacao);
	CreateFinalImageFromShort(imagemPosSuavizacao);
	pipelineDoPlano = make_unique<SubPipelinePlanar>(finalImage);
	pipelineDoVR = make_unique<SubPipelineVR>(finalImage);
}

void pipeline::Pipeline::Suavizacao(int iterations, double timestep, double conductance)
{
	GpuAnisotropicDelegate(imagem->GetImage(), iterations, timestep, conductance, imagemPosSuavizacao);
	CreateFinalImageFromShort(imagemPosSuavizacao);
	pipelineDoPlano->Update();
	pipelineDoVR->Update();
}
