#include <iostream>
#include <string>
#include <sstream>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkForwardFFTImageFilter.h>
#include <itkResampleImageFilter.h>
#include <itkAffineTransform.h>
#include <itkLinearInterpolateImageFunction.h>
#include <vtkMath.h>
#include <itkCastImageFilter.h>
#include <itkRigid2DTransform.h>
#include <itkImageFileWriter.h>

using namespace std;
typedef itk::Image<float, 2> FloatImage;
FloatImage::Pointer LoadMyImage();
FloatImage::Pointer CreateEmptyITKImage(int width, int height);
FloatImage::Pointer MakeSinogram(FloatImage::Pointer input);
int main(int argc, char** argv)
{
	//Load the image, rescaling it's scalar range to between 0 and 1.
	FloatImage::Pointer input = LoadMyImage();
	FloatImage::Pointer sinogram = MakeSinogram(input);
	return EXIT_SUCCESS;
}

FloatImage::Pointer RotateImage(FloatImage::Pointer input, float angleInDegrees)
{
	typedef itk::ResampleImageFilter<FloatImage, FloatImage> RotatorFilterType;
	RotatorFilterType::Pointer rotator = RotatorFilterType::New();
	rotator->SetInput(input);
	typedef itk::Rigid2DTransform<double> TransformType; //Typedef do transform
	TransformType::Pointer transform = TransformType::New();
	transform->SetAngleInDegrees(angleInDegrees);
	TransformType::InputPointType centerOfRotation;
	centerOfRotation[0] = 128;
	centerOfRotation[1] = 128;
	transform->SetCenter(centerOfRotation);
	TransformType::OutputVectorType _t;
	_t[0] = 0;
	_t[1] = 0;
	transform->SetTranslation(_t);
	rotator->SetTransform(transform);
	typedef itk::LinearInterpolateImageFunction<FloatImage> LinearInterpolatorType;
	LinearInterpolatorType::Pointer li = LinearInterpolatorType::New();
	rotator->SetInterpolator(li);
	rotator->SetDefaultPixelValue(0);
	rotator->SetOutputSpacing(input->GetSpacing());
	rotator->SetOutputOrigin(input->GetOrigin());
	rotator->SetSize(input->GetLargestPossibleRegion().GetSize());
	rotator->Update();
	return rotator->GetOutput();
}

FloatImage::Pointer MakeSinogram(FloatImage::Pointer input)
{
	FloatImage::Pointer sinogramImage = CreateEmptyITKImage(360, input->GetLargestPossibleRegion().GetSize()[0]);
	//Rotate image
	for(int i=0; i<360; i++)
	{
		FloatImage::Pointer rotationResulto = RotateImage(input, i);
		typedef itk::Image<unsigned char, 2> UCharImage;
		typedef itk::RescaleIntensityImageFilter<FloatImage, UCharImage> RescaleBackFilter;
		typedef itk::ImageFileWriter<UCharImage> PNGWriterType;
		RescaleBackFilter::Pointer rb = RescaleBackFilter::New();
		rb->SetInput(rotationResulto);
		rb->SetOutputMinimum(0);
		rb->SetOutputMaximum(255);
		PNGWriterType::Pointer writer = PNGWriterType::New();
		writer->SetInput(rb->GetOutput());
		stringstream ss;
		ss << "c:\\src\\teste_" << i << ".png";
		writer->SetFileName(ss.str().c_str());
		writer->Write();
		
	}
	//March ray
	//Accumulate in sinogramImage
	return sinogramImage;
}


FloatImage::Pointer CreateEmptyITKImage(int width, int height)
{
	FloatImage::Pointer image = FloatImage::New();
	FloatImage::RegionType region;
	FloatImage::IndexType start;
	start[0] = 0;
	start[1] = 0;
	FloatImage::SizeType size;
	size[0] = width;
	size[1] = height;
	region.SetSize(size);
	region.SetIndex(start);
	image->SetRegions(region);
	image->Allocate();
	memset(
		image->GetBufferPointer(),
		0,
		width * height * sizeof(float));
	return image;
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
