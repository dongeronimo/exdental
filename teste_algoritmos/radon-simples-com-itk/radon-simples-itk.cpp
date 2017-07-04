#include <Windows.h>
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
typedef itk::Image<float, 1> RayAccumulatorImage;
FloatImage::Pointer LoadMyImage();
FloatImage::Pointer CreateEmptyITKImage(int width, int height);
FloatImage::Pointer MakeSinogram(FloatImage::Pointer input);
FloatImage::Pointer RotateImage(FloatImage::Pointer input, float angleInDegrees);
void SaveAsPng(FloatImage::Pointer input, string filepath);
RayAccumulatorImage::Pointer MarchRay(FloatImage::Pointer input);

int main(int argc, char** argv)
{
	//Load the image, rescaling it's scalar range to between 0 and 1.
	FloatImage::Pointer input = LoadMyImage();
	FloatImage::Pointer sinogram = MakeSinogram(input);
	return EXIT_SUCCESS;
}


FloatImage::Pointer MakeSinogram(FloatImage::Pointer input)
{
	long t0 = GetCurrentTime();
	FloatImage::Pointer sinogramImage = CreateEmptyITKImage(360, input->GetLargestPossibleRegion().GetSize()[0]);
	for(int i=0; i<360; i++)
	{
		//Rotate image
		FloatImage::Pointer rotationResult = RotateImage(input, i);
		//March ray
		RayAccumulatorImage::Pointer accumulatedImage = MarchRay(rotationResult);
		for(unsigned int y=0; y<accumulatedImage->GetLargestPossibleRegion().GetSize()[0]; y++)
		{
			RayAccumulatorImage::IndexType srcPos;
			srcPos[0] = y;

			FloatImage::IndexType destPos;
			destPos[0] = i;
			destPos[1] = y;
			sinogramImage->SetPixel(destPos, accumulatedImage->GetPixel(srcPos));
		}
	}
	long t1 = GetCurrentTime();
	cout << "Tempo = " << (t1 - t0) << endl;
	SaveAsPng(sinogramImage, "c:\\src\\foo.png");
	string s;
	cin >> s;
	//Accumulate in sinogramImage
	return sinogramImage;
}

RayAccumulatorImage::Pointer MarchRay(FloatImage::Pointer input)
{
	RayAccumulatorImage::Pointer result = RayAccumulatorImage::New();
	RayAccumulatorImage::RegionType region;
	RayAccumulatorImage::RegionType::SizeType size;
	size[0] = input->GetLargestPossibleRegion().GetSize()[0];
	region.SetSize(size);
	result->SetSpacing(input->GetSpacing()[0]);
	result->SetOrigin(0.0);
	result->SetRegions(region);
	result->Allocate();
	itk::LinearInterpolateImageFunction<FloatImage, double>::Pointer interpolator = itk::LinearInterpolateImageFunction<FloatImage, double>::New();
	interpolator->SetInputImage(input);
	typedef itk::LinearInterpolateImageFunction<FloatImage, double>::PointType PointType;

	//O raio vai de baixo pra cima, da esquerda pra direita.
	for (unsigned int x = 0; x<input->GetLargestPossibleRegion().GetSize()[0]; x++)
	{
		PointType rayOrigin;
		rayOrigin[0] = input->GetOrigin()[0] + x * input->GetSpacing()[0];
		rayOrigin[1] = input->GetOrigin()[1];
		float sum = 0.0;
		for (unsigned int y = 0; y<input->GetLargestPossibleRegion().GetSize()[1]; y++)
		{
			PointType currentPoint;
			currentPoint[0] = rayOrigin[0];
			currentPoint[1] = rayOrigin[1] + y * input->GetSpacing()[1];
			float evaluation = interpolator->Evaluate(currentPoint);
			sum = sum + evaluation;
		}
		RayAccumulatorImage::IndexType resultPos;
		resultPos[0] = x;
		result->SetPixel(resultPos, sum);
		//cout << sum << endl;
	}
	return result;
}

void SaveAsPng(FloatImage::Pointer input, string filepath)
{
	typedef itk::Image<unsigned char, 2> UCharImage;
	typedef itk::RescaleIntensityImageFilter<FloatImage, UCharImage> RescaleBackFilter;
	typedef itk::ImageFileWriter<UCharImage> PNGWriterType;
	RescaleBackFilter::Pointer rb = RescaleBackFilter::New();
	rb->SetInput(input);
	rb->SetOutputMinimum(0);
	rb->SetOutputMaximum(255);
	PNGWriterType::Pointer writer = PNGWriterType::New();
	writer->SetInput(rb->GetOutput());
	writer->SetFileName(filepath.c_str());
	writer->Write();
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
	centerOfRotation[0] = input->GetLargestPossibleRegion().GetSize()[0] * input->GetSpacing()[0] / 2 + input->GetOrigin()[0];
	centerOfRotation[1] = input->GetLargestPossibleRegion().GetSize()[1] * input->GetSpacing()[1] / 2 + input->GetOrigin()[0];
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
