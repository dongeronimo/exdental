#include "GpuAnisotropicDiffusion.h"
#include <itkCommand.h>
#include <Windows.h>

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

void _stdcall ExecuteAnistropicDiffusion(itk::Image<short, 3>::Pointer input, 
	int numberOfIterations, double timeStep, double conductanceParameter, 
	itk::Image<short, 3>::Pointer output, HWND progressObserverHandle)
{
	if (numberOfIterations < 1)
		throw std::invalid_argument("interações não podem ser ");
	if (timeStep < 0)
		throw std::invalid_argument("timestep não pode ser menor que 0");
	if (conductanceParameter < 0)
		throw std::invalid_argument("conductante não pode ser menor que 0");
	GPUAnisoDiffFilterType::Pointer GPUFilter = GPUAnisoDiffFilterType::New();
	if(progressObserverHandle)
	{
		MyITKProgressEventSender::Pointer observer = MyITKProgressEventSender::New();
		((MyITKProgressEventSender*)(observer.GetPointer()))->SetHWND(progressObserverHandle);
		GPUFilter->AddObserver(itk::ProgressEvent(), observer);
	}
	GPUFilter->SetInput(input);
	GPUFilter->SetNumberOfIterations(numberOfIterations);
	GPUFilter->SetTimeStep(timeStep);
	GPUFilter->SetConductanceParameter(conductanceParameter);
	GPUFilter->UseImageSpacingOn();
	GPUFilter->Update();
	GPUFilter->GetOutput()->UpdateBuffers(); // synchronization point
	GPUFloatImage::Pointer result = GPUFilter->GetOutput();
	//cópia pro output
	double inSpacingX = input->GetSpacing()[0];
	double inSpacingY = input->GetSpacing()[1];
	double inSpacingZ = input->GetSpacing()[2];
	output->SetRegions(input->GetLargestPossibleRegion());
	output->Allocate();
	itk::ImageRegionConstIterator<GPUFloatImage> inputIterator(result, result->GetLargestPossibleRegion());
	itk::ImageRegionIterator<itk::Image<short, 3>> outputIterator(output, output->GetLargestPossibleRegion());
	const double inSpacing[] = { inSpacingX, inSpacingY, inSpacingZ };
	output->SetSpacing(inSpacing);
	while (!inputIterator.IsAtEnd())
	{
		outputIterator.Set(inputIterator.Get());
		++inputIterator;
		++outputIterator;
	}
}
