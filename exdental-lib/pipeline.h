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

#include "itkOpenCLUtil.h"
#include "itkGPUImage.h"
#include "itkGPUKernelManager.h"
#include "itkGPUContextManager.h"
#include "itkGPUImageToImageFilter.h"
#include "itkGPUGradientAnisotropicDiffusionImageFilter.h"

#include <itkCastImageFilter.h>
//A partir da imagem carregada, bota na tela.
using namespace std;

typedef itk::Image<short, 3> InputImageType;
typedef itk::Image<float, 3> CPUFloatImageType;
typedef itk::GPUImage< float, 3 > GPUFloatImageType;
typedef itk::GPUGradientAnisotropicDiffusionImageFilter< InputImageType, GPUFloatImageType > GPUAnisoDiffFilterType;

class Pipeline
{
private:
	unsigned int SuavizacaoNumberOfIteration;
	float suavizacaoTimeSteps;
	float suavizacaoConductanceParameter;

	InputImageType::Pointer inputImage;
	GPUAnisoDiffFilterType::Pointer GPUFilter;

	vtkSmartPointer<vtkImageImport> vtkImport;
	vtkSmartPointer<vtkImageResliceMapper> resliceMapper;
	vtkSmartPointer<vtkImageProperty> resliceProperties;
	vtkSmartPointer<vtkImageSlice> resliceActor;

	vtkSmartPointer<vtkGPUVolumeRayCastMapper> vrMapper;
	vtkSmartPointer<vtkVolumeProperty> vrProperty;
	vtkSmartPointer<vtkVolume> vrActor;

	void CopyFromGPUImageToCPU(GPUFloatImageType::Pointer input, CPUFloatImageType::Pointer output);
public:
	Pipeline(InputImageType::Pointer img, map<string, string> metadataDictionary);
	vtkSmartPointer<vtkImageSlice> GetResliceActor();
	vtkSmartPointer<vtkVolume> GetVRActor();
	void ExecutePipeline();
	void SetWL(int w, int l);
};