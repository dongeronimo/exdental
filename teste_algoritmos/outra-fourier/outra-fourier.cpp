#include <iostream>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkRescaleIntensityImageFilter.h>
using namespace std;

typedef itk::Image<float, 2> FloatImage;

//Loads and changes the intensity levels to be between [0,1].
FloatImage::Pointer LoadMyImage();

int main(int argc, char** argv)
{
	FloatImage::Pointer originalImage = LoadMyImage();
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
	return rescaler->GetOutput();
}