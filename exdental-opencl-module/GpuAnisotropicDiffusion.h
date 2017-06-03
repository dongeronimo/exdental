#include <itkGPUGradientAnisotropicDiffusionImageFilter.h>
#include <itkGPUImage.h>
#include <itkImage.h>

typedef itk::GPUImage< float, 3 > GPUFloatImage;
typedef itk::GPUGradientAnisotropicDiffusionImageFilter< itk::Image<short, 3>, GPUFloatImage > GPUAnisoDiffFilterType;

#define LIBRARY_API __declspec(dllexport) 
extern "C"
{
	LIBRARY_API void _stdcall ExecuteAnistropicDiffusion(itk::Image<short, 3>::Pointer input, 
		int numberOfIterations, double timeStep, double conductanceParameter,
		itk::Image<short, 3>::Pointer output);
}