#pragma once
#include <itkImage.h>
#include <ImageLoader.h>
#include <vtkImageImport.h>
#include <vtkSmartPointer.h>
#include <vtkVolume.h>
#include <vtkImageSlice.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageProperty.h>
#include <itkSigmoidImageFilter.h>
#include <itkCastImageFilter.h>

#include <vtkImageSlice.h>
using namespace std;
using namespace imageLoader;


namespace pipeline
{
	class SubPipelinePlanar
	{
	private:
		vtkSmartPointer<vtkImageImport> importedImage;
		vtkSmartPointer<vtkImageResliceMapper> resliceMapper;
		vtkSmartPointer<vtkImageProperty> resliceProperties;
		vtkSmartPointer<vtkImageSlice> resliceActor;

	public:
		SubPipelinePlanar(vtkSmartPointer<vtkImageImport> img);
		vtkSmartPointer<vtkImageSlice> GetActor()
		{
			return resliceActor;
		}
		void Update();
	};

	class SubPipelineVR
	{
	private:
		vtkSmartPointer<vtkImageImport> importedImage;
		vtkSmartPointer<vtkGPUVolumeRayCastMapper> vrMapper;
		vtkSmartPointer<vtkVolumeProperty> vrProperty;
		vtkSmartPointer<vtkVolume> vrActor;
	public:
		SubPipelineVR(vtkSmartPointer<vtkImageImport> img);
		void Update();
		vtkSmartPointer<vtkVolume> GetActor()
		{
			return vrActor;
		}
	};

	class Pipeline
	{
	private:
		typedef itk::CastImageFilter<itk::Image<short, 3>, itk::Image<float, 3>> ShortToFloatImageFilter;
		typedef itk::SigmoidImageFilter<itk::Image<float, 3>, itk::Image<short, 3>> SigmoidFilter;
		typedef itk::CastImageFilter<itk::Image<float, 3>, itk::Image<short, 3>> FloatToShortImageFilter;
		

		typedef  void (_stdcall *GpuAnisotropicFilterDelegate)(itk::Image<short, 3>::Pointer input, 
			int numberOfIterations, double timeStep, double conductanceParameter,
			itk::Image<short, 3>::Pointer output);
		HINSTANCE hDllHandle;
		unique_ptr<SubPipelinePlanar> pipelineDoPlano;
		unique_ptr<SubPipelineVR> pipelineDoVR;
		shared_ptr<LoadedImage> imagem;
		ShortImage::Pointer imagemPosSuavizacao;
		vtkSmartPointer<vtkImageImport> finalImage;
		GpuAnisotropicFilterDelegate GpuAnisotropicDelegate;

		ShortToFloatImageFilter::Pointer shortToFloat;
		SigmoidFilter::Pointer sigmoid;
		FloatToShortImageFilter::Pointer floatToShort;

		void CreateFinalImageFromShort(ShortImage::Pointer src);
	public:
		~Pipeline();
		Pipeline(shared_ptr<LoadedImage> img);
		vtkSmartPointer<vtkImageSlice> GetPlanarActor()
		{
			return pipelineDoPlano->GetActor();
		}
		vtkSmartPointer<vtkVolume> GetVolumeActor()
		{
			return pipelineDoVR->GetActor();
		}
		void Suavizacao(int iterations, double timestep, double conductance);
	};
}
