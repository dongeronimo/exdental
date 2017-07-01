#include <iostream>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkForwardFFTImageFilter.h>
#include <itkComplexToModulusImageFilter.h>
#include <itkMinimumMaximumImageCalculator.h>
using namespace std;

typedef itk::Image<float, 2> FloatImage;
typedef itk::ForwardFFTImageFilter<FloatImage> FourierTransformType;
typedef itk::ComplexToModulusImageFilter<FourierTransformType::OutputImageType, FloatImage> ModulusImageFilter;

//Loads and changes the intensity levels to be between [0,1].
FloatImage::Pointer LoadMyImage();

void ShowScalarRange(FloatImage::Pointer img);

int main(int argc, char** argv)
{
	FloatImage::Pointer originalImage = LoadMyImage();
	//Now, transform the image using the fourier transform
	FourierTransformType::Pointer fourier = FourierTransformType::New();
	fourier->SetInput(originalImage);
	//Modulus of fourier
	ModulusImageFilter::Pointer modulus_image_filter = ModulusImageFilter::New();
	modulus_image_filter->SetInput(fourier->GetOutput());
	modulus_image_filter->Update();

	return EXIT_SUCCESS;
}

FloatImage::Pointer LoadMyImage()
{
	typedef itk::ImageFileReader<FloatImage> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName("C:\\src\\exdental\\black_dot_1_channel.png");
	typedef itk::RescaleIntensityImageFilter<FloatImage, FloatImage> RescalerType;
	RescalerType::Pointer rescaler = RescalerType::New();
	rescaler->SetInput(reader->GetOutput());
	rescaler->SetOutputMaximum(1.0);
	rescaler->SetOutputMinimum(0.0);
	rescaler->Update();
	ShowScalarRange(rescaler->GetOutput());
	return rescaler->GetOutput();
}

void ShowScalarRange(FloatImage::Pointer img)
{
	typedef itk::MinimumMaximumImageCalculator <FloatImage> ImageCalculatorFilterType;
	ImageCalculatorFilterType::Pointer minMax = ImageCalculatorFilterType::New();
	minMax->SetImage(img);
	minMax->ComputeMaximum();
	minMax->ComputeMinimum();
	float min = minMax->GetMinimum();
	float max = minMax->GetMaximum();
	cout << "Minimo " << min << " Maximo " << max;
}