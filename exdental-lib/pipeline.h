#pragma once
#include <itkImage.h>
#include <string>
#include <map>
#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageProperty.h>
#include <vtkImageSlice.h>



#include <itkCastImageFilter.h>
//A partir da imagem carregada, bota na tela.
using namespace std;

typedef itk::Image<short, 3> InputImageType;
typedef itk::Image<float, 3> CPUFloatImageType;

//TODO: No momento existe uma instância de pipeline pra cada tela. Fazer a pipeline existir independente da tela.
class Pipeline
{
private:
	unsigned int SuavizacaoNumberOfIteration;
	float suavizacaoTimeSteps;
	float suavizacaoConductanceParameter;

	InputImageType::Pointer inputImage;


	vtkSmartPointer<vtkImageImport> vtkImport;
	vtkSmartPointer<vtkImageResliceMapper> resliceMapper;
	vtkSmartPointer<vtkImageProperty> resliceProperties;
	vtkSmartPointer<vtkImageSlice> resliceActor;

	vtkSmartPointer<vtkGPUVolumeRayCastMapper> vrMapper;
	vtkSmartPointer<vtkVolumeProperty> vrProperty;
	vtkSmartPointer<vtkVolume> vrActor;


public:
	Pipeline(InputImageType::Pointer img, map<string, string> metadataDictionary);
	vtkSmartPointer<vtkImageSlice> GetResliceActor();
	vtkSmartPointer<vtkVolume> GetVRActor();
	void ExecutePipeline();
	void SetWL(int w, int l);
};