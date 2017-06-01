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
		vtkSmartPointer<vtkVolume> GetActor()
		{
			return vrActor;
		}
	};

	class Pipeline
	{
	private:
		typedef  void (_stdcall *GpuAnisotropicFilterDelegate)(itk::Image<short, 3>::Pointer input, itk::Image<short, 3>::Pointer output);
		HINSTANCE hDllHandle;
		unique_ptr<SubPipelinePlanar> pipelineDoPlano;
		unique_ptr<SubPipelineVR> pipelineDoVR;
		shared_ptr<LoadedImage> imagem;
		ShortImage::Pointer imagemPosSuavizacao;
		vtkSmartPointer<vtkImageImport> finalImage;
		GpuAnisotropicFilterDelegate GpuAnisotropicDelegate;
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
	};
}
