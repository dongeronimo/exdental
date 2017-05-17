#ifndef  _____itk_types
#define _____itk_types
#include <itkImage.h>
#include <itkImportImageFilter.h>

#include <itkFlipImageFilter.h>
#include <itkResampleImageFilter.h>
//definição do tipo da imagem
typedef itk::Image<short, 3> ImageType;
//definição do filtro de importação
typedef itk::ImportImageFilter<short, 3> ImageImportFilterType;
typedef itk::FlipImageFilter<ImageType> ImageFlipType;

typedef itk::ResampleImageFilter<ImageType, ImageType> ResamplerType;

template<typename TImage> void DeepCopy(typename TImage::Pointer input, typename TImage::Pointer output)
{
	int inSzX = input->GetLargestPossibleRegion().GetSize()[0];
	int inSzY = input->GetLargestPossibleRegion().GetSize()[1];
	int inSzZ = input->GetLargestPossibleRegion().GetSize()[2];
	double inSpacingX = input->GetSpacing()[0];
	double inSpacingY = input->GetSpacing()[1];
	double inSpacingZ = input->GetSpacing()[2];

	output->SetRegions(input->GetLargestPossibleRegion());
	output->Allocate();

	itk::ImageRegionConstIterator<TImage> inputIterator(input, input->GetLargestPossibleRegion());
	itk::ImageRegionIterator<TImage> outputIterator(output, output->GetLargestPossibleRegion());
	const double inSpacing[] = { inSpacingX, inSpacingY, inSpacingZ };
	output->SetSpacing(inSpacing);
	while (!inputIterator.IsAtEnd())
	{
		outputIterator.Set(inputIterator.Get());
		++inputIterator;
		++outputIterator;
	}
}
#endif
