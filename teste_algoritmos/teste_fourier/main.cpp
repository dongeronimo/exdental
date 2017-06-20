#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkComplexToRealImageFilter.h"
#include "itkComplexToImaginaryImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main(int argc, char* argv[])
{

	const char * inputFileName = "C:\\src\\exdental\\black_dot_1_channel.png";
	const char * realFileName = "C:\\src\\exdental\\black_dot_1_channel_real.png";
	const char * imaginaryFileName = "C:\\src\\exdental\\black_dot_1_channel_imaginary.png";
	const char * modulusFileName = "C:\\src\\exdental\\black_dot_1_channel_modulus.png";

	const unsigned int Dimension = 2;

	typedef float                                   FloatPixelType;
	typedef itk::Image< FloatPixelType, Dimension > FloatImageType;

	typedef itk::ImageFileReader< FloatImageType >  ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(inputFileName);

	typedef unsigned char UnsignedCharPixelType;
	typedef itk::Image< UnsignedCharPixelType, Dimension > UnsignedCharImageType;


	
	typedef itk::ForwardFFTImageFilter< FloatImageType > FFTType;
	FFTType::Pointer fftFilter = FFTType::New();
	fftFilter->SetInput(reader->GetOutput());

	typedef FFTType::OutputImageType FFTOutputImageType;

	// Extract the real part
	typedef itk::ComplexToRealImageFilter< FFTOutputImageType, FloatImageType> RealFilterType;
	RealFilterType::Pointer realFilter = RealFilterType::New();
	realFilter->SetInput(fftFilter->GetOutput());

	typedef itk::ImageFileWriter< FloatImageType > FloatWriterType;
	FloatWriterType::Pointer vtkWriter = FloatWriterType::New();
	vtkWriter->SetFileName("C:\\src\\exdental\\black_dot_1_channel_real.mha");
	vtkWriter->SetInput(realFilter->GetOutput());
	try
	{
		vtkWriter->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		return EXIT_FAILURE;
	}



	typedef itk::RescaleIntensityImageFilter< FloatImageType, UnsignedCharImageType > RescaleFilterType;
	RescaleFilterType::Pointer realRescaleFilter = RescaleFilterType::New();
	realRescaleFilter->SetInput(realFilter->GetOutput());
	realRescaleFilter->SetOutputMinimum(itk::NumericTraits< UnsignedCharPixelType >::min());
	realRescaleFilter->SetOutputMaximum(itk::NumericTraits< UnsignedCharPixelType >::max());

	typedef itk::ImageFileWriter< UnsignedCharImageType > WriterType;
	WriterType::Pointer realWriter = WriterType::New();
	realWriter->SetFileName(realFileName);
	realWriter->SetInput(realRescaleFilter->GetOutput());
	try
	{
		realWriter->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		return EXIT_FAILURE;
	}

	// Extract the imaginary part
	typedef itk::ComplexToImaginaryImageFilter< FFTOutputImageType, FloatImageType> ImaginaryFilterType;
	ImaginaryFilterType::Pointer imaginaryFilter = ImaginaryFilterType::New();
	imaginaryFilter->SetInput(fftFilter->GetOutput());

	RescaleFilterType::Pointer imaginaryRescaleFilter = RescaleFilterType::New();
	imaginaryRescaleFilter->SetInput(imaginaryFilter->GetOutput());
	imaginaryRescaleFilter->SetOutputMinimum(itk::NumericTraits< UnsignedCharPixelType >::min());
	imaginaryRescaleFilter->SetOutputMaximum(itk::NumericTraits< UnsignedCharPixelType >::max());

	WriterType::Pointer complexWriter = WriterType::New();
	complexWriter->SetFileName(imaginaryFileName);
	complexWriter->SetInput(imaginaryRescaleFilter->GetOutput());
	try
	{
		complexWriter->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		return EXIT_FAILURE;
	}

	// Compute the magnitude
	typedef itk::ComplexToModulusImageFilter< FFTOutputImageType, FloatImageType> ModulusFilterType;
	ModulusFilterType::Pointer modulusFilter = ModulusFilterType::New();
	modulusFilter->SetInput(fftFilter->GetOutput());

	RescaleFilterType::Pointer magnitudeRescaleFilter = RescaleFilterType::New();
	magnitudeRescaleFilter->SetInput(modulusFilter->GetOutput());
	magnitudeRescaleFilter->SetOutputMinimum(itk::NumericTraits< UnsignedCharPixelType >::min());
	magnitudeRescaleFilter->SetOutputMaximum(itk::NumericTraits< UnsignedCharPixelType >::max());

	WriterType::Pointer magnitudeWriter = WriterType::New();
	magnitudeWriter->SetFileName(modulusFileName);
	magnitudeWriter->SetInput(magnitudeRescaleFilter->GetOutput());
	try
	{
		magnitudeWriter->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}