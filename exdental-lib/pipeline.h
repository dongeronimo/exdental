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
	class MyITKProgressEventSender : public itk::Command
	{
	private:
		HWND targetWindow;
	protected:
		MyITKProgressEventSender()
		{
			targetWindow = 0;
		}
	public:
		static MyITKProgressEventSender *New()
		{
			return new MyITKProgressEventSender();
		}

		void SetHWND(HWND alvo)
		{
			targetWindow = alvo;
		}

		void Execute(itk::Object * caller, const itk::EventObject & event) override
		{
			Execute((const itk::Object *)caller, event);
		}

		void Execute(const itk::Object * caller, const itk::EventObject & event) override
		{
			if (!itk::ProgressEvent().CheckEvent(&event))
			{
				return;
			}
			const itk::ProcessObject * processObject = dynamic_cast< const itk::ProcessObject * >(caller);
			if (!processObject)
			{
				return;
			}
			HWND hwnd = targetWindow;
			unsigned int msg = WM_USER + 1000;
			WPARAM wParam = processObject->GetProgress() * 100;
			LPARAM lParam = 0;
			SendMessage(hwnd, msg, wParam, lParam);
		}
	};


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
		void SetWL(float window, float level)
		{
			resliceProperties->SetColorWindow(window);
			resliceProperties->SetColorLevel(level);
			Update();
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
		typedef itk::SigmoidImageFilter<itk::Image<float, 3>, itk::Image<float, 3>> SigmoidFilter;
		typedef itk::CastImageFilter<itk::Image<float, 3>, itk::Image<short, 3>> FloatToShortImageFilter;
		

		typedef  void (_stdcall *GpuAnisotropicFilterDelegate)(itk::Image<short, 3>::Pointer input, 
			int numberOfIterations, double timeStep, double conductanceParameter,
			itk::Image<short, 3>::Pointer output, HWND progressObserverHandle);
		HINSTANCE hDllHandle;
		MyITKProgressEventSender::Pointer myITKProgressObserver;
		unique_ptr<SubPipelinePlanar> pipelineDoPlano;
		unique_ptr<SubPipelineVR> pipelineDoVR;
		shared_ptr<LoadedImage> imagem;
		ShortImage::Pointer imagemPosSuavizacao;
		vtkSmartPointer<vtkImageImport> finalImage;
		GpuAnisotropicFilterDelegate GpuAnisotropicDelegate;

		ShortToFloatImageFilter::Pointer shortToFloat;
		SigmoidFilter::Pointer sigmoid;
		FloatToShortImageFilter::Pointer floatToShort;
		HWND progressBarWindowHandle;
		short sigmoidAlpha;
		short sigmoidBeta;
		float sigmoidMin;
		float sigmoidMax;

		void CreateFinalImageFromShort(ShortImage::Pointer src);
		void LinkFiltersAfterGPUSmooth();
		void SetSigmoid(short alpha, short beta, float min, float max);
	public:
		~Pipeline();
		Pipeline(shared_ptr<LoadedImage> img, HWND progressBarWindow);
		vtkSmartPointer<vtkImageSlice> GetPlanarActor()
		{
			return pipelineDoPlano->GetActor();
		}
		vtkSmartPointer<vtkVolume> GetVolumeActor()
		{
			return pipelineDoVR->GetActor();
		}
		void Suavizacao(int iterations, double timestep, double conductance);
		void Sigmoide(short alpha, short beta, float min, float max);
		void SalvarSigmoide(string file);
	};
}
