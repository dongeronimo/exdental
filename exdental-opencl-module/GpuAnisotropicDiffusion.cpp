#include "GpuAnisotropicDiffusion.h"

void _stdcall ExecuteAnistropicDiffusion(itk::Image<short, 3>::Pointer input, 
	int numberOfIterations, double timeStep, double conductanceParameter, 
	itk::Image<short, 3>::Pointer output)
{
	if (numberOfIterations < 1)
		throw std::invalid_argument("interações não podem ser ");
	if (timeStep < 0)
		throw std::invalid_argument("timestep não pode ser menor que 0");
	if (conductanceParameter < 0)
		throw std::invalid_argument("conductante não pode ser menor que 0");
	GPUAnisoDiffFilterType::Pointer GPUFilter = GPUAnisoDiffFilterType::New();
	//GPUFilter->DebugOn();
	GPUFilter->SetInput(input);
	GPUFilter->SetNumberOfIterations(numberOfIterations);
	GPUFilter->SetTimeStep(timeStep);
	GPUFilter->SetConductanceParameter(conductanceParameter);
	GPUFilter->UseImageSpacingOn();
	GPUFilter->Update();
	GPUFilter->GetOutput()->UpdateBuffers(); // synchronization point
	GPUFloatImage::Pointer result = GPUFilter->GetOutput();
	//cópia pro output
	int inSzX = input->GetLargestPossibleRegion().GetSize()[0];
	int inSzY = input->GetLargestPossibleRegion().GetSize()[1];
	int inSzZ = input->GetLargestPossibleRegion().GetSize()[2];
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
