#include"pipeline.h"
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>

void Pipeline::SetWL(int w, int l)
{
	resliceProperties->SetColorWindow(w);
	resliceProperties->SetColorLevel(l);
	resliceActor->Update();
}

void Pipeline::ExecutePipeline()
{


}

Pipeline::Pipeline(InputImageType::Pointer img, map<string, string> metadataDictionary)
{
	this->inputImage = img;

	SuavizacaoNumberOfIteration = 10;
	suavizacaoTimeSteps = 0.01;
	suavizacaoConductanceParameter = 3.0;
	//De itk::image pra vtkImageData;
	vtkImport = vtkSmartPointer<vtkImageImport>::New();
	int szX = img->GetLargestPossibleRegion().GetSize()[0];
	int szY = img->GetLargestPossibleRegion().GetSize()[1];
	int szZ = img->GetLargestPossibleRegion().GetSize()[2];
	double sX = img->GetSpacing()[0];
	double sY = img->GetSpacing()[1];
	double sZ = img->GetSpacing()[2];
	double oX = img->GetOrigin()[0];
	double oY = img->GetOrigin()[1];
	double oZ = img->GetOrigin()[2];
	vtkImport->SetDataSpacing(sX, sY, sZ);
	vtkImport->SetDataOrigin(oX, oY, oZ);
	vtkImport->SetWholeExtent(0, szX - 1, 0, szY - 1, 0, szZ - 1);
	vtkImport->SetDataExtentToWholeExtent();
	vtkImport->SetDataScalarTypeToShort();
	void* imgPtr = img->GetBufferPointer();
	vtkImport->SetImportVoidPointer(imgPtr, 1);
	vtkImport->Update();

	//Agora a pipeline de radiografia
	resliceMapper = vtkSmartPointer<vtkImageResliceMapper>::New();
	resliceMapper->SetInputData((vtkImageData*)vtkImport->GetOutputDataObject(0));
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


	//A pipeline de VR
	vrMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	vrMapper->SetMaxMemoryFraction(0.9);
	vrMapper->SetInputData((vtkImageData*)vtkImport->GetOutputDataObject(0));
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

vtkSmartPointer<vtkVolume> Pipeline::GetVRActor()
{
	return vrActor;
}


vtkSmartPointer<vtkImageSlice> Pipeline::GetResliceActor()
{
	return resliceActor;
}

