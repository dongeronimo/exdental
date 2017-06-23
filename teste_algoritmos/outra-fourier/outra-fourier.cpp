#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkComplexToRealImageFilter.h"
#include "itkComplexToImaginaryImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include <itkMinimumMaximumImageCalculator.h>
#include "itkContinuousIndex.h"
#include "itkLinearInterpolateImageFunction.h"
#include <array>
#include <itkInverseFFTImageFilter.h>
#include <iostream>
//#include "fft_settings.h"
//#include "fft.h"
//

//using namespace simple_fft;
using namespace std;
//
const unsigned int Dimension = 2;
typedef double                                   FloatPixelType;
typedef itk::Image< FloatPixelType, Dimension > FloatImageType;
typedef itk::Image<unsigned char, Dimension> UnsignedCharImageType;
//
FloatImageType::Pointer CarregarImagem()
{
	const char * inputFileName = "C:\\src\\exdental\\black_dot_1_channel.png";
	typedef itk::ImageFileReader< FloatImageType >  ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(inputFileName);
	reader->Update();
	return reader->GetOutput();
}
//
void NormalizaValores(FloatImageType::Pointer img)
{
	itk::ImageRegionIterator<FloatImageType> imageIterator(img, img->GetLargestPossibleRegion());
	while (!imageIterator.IsAtEnd())
	{
		float val = imageIterator.Get();
		imageIterator.Set(val / 255.0);
		++imageIterator;
	}
}
//
FloatImageType::Pointer FourierTransform(FloatImageType::Pointer img)
{
	typedef itk::ForwardFFTImageFilter< FloatImageType > FFTType;
	FFTType::Pointer fftFilter = FFTType::New();
	fftFilter->SetInput(img);
	fftFilter->Update();
	typedef FFTType::OutputImageType FFTOutputImageType;
	typedef itk::ComplexToRealImageFilter< FFTOutputImageType, FloatImageType> RealFilterType;
	RealFilterType::Pointer realFilter = RealFilterType::New();
	realFilter->SetInput(fftFilter->GetOutput());
	realFilter->Update();
	return realFilter->GetOutput();
}

int main(int argc, char** argv)
{
	FloatImageType::Pointer loadedImage = CarregarImagem();
	NormalizaValores(loadedImage);
	FloatImageType::Pointer fourier = FourierTransform(loadedImage);
	//Aqui eu já tenho a imagem normalizada e sua série de fourier. Segundo o livro é só eu pegar uma linha girando centrada
	//no centro da imagem que eu pego o sinograma.
	
	itk::LinearInterpolateImageFunction<FloatImageType, double>::Pointer interpolator = itk::LinearInterpolateImageFunction<FloatImageType, double>::New();
	interpolator->SetInputImage(fourier);
	
	//Eu vou marchar um raio ao longo da imagem, esse raio é determinado por um vetor V e uma posição inicial P0.
	//A posição inicial é o centro da imagem. Eu marcho dois raios opostos.
	
	array<double, 2> V = { cos(0 * 3.14 / 180), sin(0 * 3.14 / 180) };
	array<double, 2> Vinv = { -cos(0 * 3.14 / 180), -sin(0 * 3.14 / 180) };
	array<double, 2> center = { fourier->GetLargestPossibleRegion().GetSize()[0] / 2,fourier->GetLargestPossibleRegion().GetSize()[1] / 2 };
	typedef array<double, 256> Linha;
	vector<Linha> linhas;

	for(int ang=0; ang<1; ang++)//para cada um dos 360 graus faça
	{
		//Atualiza os vetores
		V = { sin(ang * 3.14 / 180), cos(ang * 3.14 / 180) };
		Vinv = { -sin(ang * 3.14 / 180),-cos(ang * 3.14 / 180) };
		Linha ln;
		for(int i=0; i>=-127; i--)
		{
			itk::ContinuousIndex<double, 2> pixel;
			pixel[0] = center[0] + i * Vinv[0];
			pixel[1] = center[1] + i * Vinv[1];
			double val = interpolator->EvaluateAtContinuousIndex(pixel);
			ln[i + 127] = val;
		}
		for (int i = 127; i < 256; i++)
		{
			itk::ContinuousIndex<double, 2> pixel;
			pixel[0] = center[0] + i * V[0];
			pixel[1] = center[1] + i * V[1];
			double val = interpolator->EvaluateAtContinuousIndex(pixel);
			ln[i] = val;
		}
		linhas.push_back(ln);
	}
	typedef itk::Image<double, 1> LinhaAsImage;
	LinhaAsImage::Pointer ln = LinhaAsImage::New();
	LinhaAsImage::RegionType region;
	LinhaAsImage::IndexType index;
	index[0] = 0;
	region.SetIndex(index);
	LinhaAsImage::SizeType size;
	size[0] = 256;
	region.SetSize(size);
	ln->SetRegions(region);
	ln->Allocate();
	memcpy(ln->GetBufferPointer(), linhas[0].data(), 256 * sizeof(double));
	typedef itk::InverseFFTImageFilter<LinhaAsImage, LinhaAsImage> IFFTType;
	IFFTType::Pointer ifftFilter = IFFTType::New();
	ifftFilter->SetInput(ln);
	ifftFilter->Update();
	itk::ImageRegionIterator<LinhaAsImage> imageIterator(ifftFilter->GetOutput(), ifftFilter->GetOutput()->GetLargestPossibleRegion());
	while (!imageIterator.IsAtEnd())
	{
		double val = imageIterator.Get();
		cout << val << endl;
		++imageIterator;
	}

	return EXIT_SUCCESS;
}
//
//int main(int argc, char* argv[])
//{
//	FloatImageType::Pointer loadedImage = CarregarImagem();
//	FloatImageType::Pointer fourier = FourierTransform(loadedImage);
//
//	//FloatImageType::Pointer loadedImage = CarregarImagem();
//	//////Normaliza a imagem
//	////NormalizaValores(loadedImage);
//	////Aplica a série de fourier
//	//FloatImageType::Pointer fourier = FourierTransform(loadedImage);
//	////Pega o valor máximo e mínimo da serie de fourier gerada.
//	//typedef itk::MinimumMaximumImageCalculator <FloatImageType> ImageCalculatorFilterType;
//	//ImageCalculatorFilterType::Pointer imageCalculatorFilter = ImageCalculatorFilterType::New();
//	//imageCalculatorFilter->SetImage(fourier);
//	//imageCalculatorFilter->Compute();
//	//cout << "[" << imageCalculatorFilter->GetMinimum() << "," << imageCalculatorFilter->GetMaximum() << "]" << endl;
//	////grava
//	//typedef itk::ImageFileWriter< FloatImageType > FloatWriterType;
//	//FloatWriterType::Pointer vtkWriter = FloatWriterType::New();
//	//vtkWriter->SetInput(fourier);
//	//vtkWriter->SetFileName("C:\\src\\exdental\\black_dot_1_channel_real.mha");
//	//vtkWriter->Write();
//	//typedef itk::RescaleIntensityImageFilter< FloatImageType, UnsignedCharImageType > RescaleFilterType;
//	//RescaleFilterType::Pointer realRescaleFilter = RescaleFilterType::New();
//	//realRescaleFilter->SetInput(fourier);
//	//realRescaleFilter->SetOutputMinimum(itk::NumericTraits< unsigned char >::min());
//	//realRescaleFilter->SetOutputMaximum(itk::NumericTraits< unsigned char >::max());
//	//typedef itk::ImageFileWriter< UnsignedCharImageType > UnsignedChartWriterType;
//	//UnsignedChartWriterType::Pointer realWriter = UnsignedChartWriterType::New();
//	//realWriter->SetInput(realRescaleFilter->GetOutput());
//	//realWriter->SetFileName("C:\\src\\exdental\\black_dot_1_channel_real.png");
//	//realWriter->Write();
//	//cout << "fim" << endl;
//
//
//
//
//	//typedef itk::ForwardFFTImageFilter< FloatImageType > FFTType;
//	//FFTType::Pointer fftFilter = FFTType::New();
//	//fftFilter->SetInput(reader->GetOutput());
//
//	//typedef FFTType::OutputImageType FFTOutputImageType;
//
//	//// Extract the real part
//	//typedef itk::ComplexToRealImageFilter< FFTOutputImageType, FloatImageType> RealFilterType;
//	//RealFilterType::Pointer realFilter = RealFilterType::New();
//	
//
//	//typedef itk::ImageFileWriter< FloatImageType > FloatWriterType;
//	//FloatWriterType::Pointer vtkWriter = FloatWriterType::New();
//	//vtkWriter->SetFileName("C:\\src\\exdental\\black_dot_1_channel_real.mha");
//	//vtkWriter->SetInput(realFilter->GetOutput());
//	//try
//	//{
//	//	vtkWriter->Update();
//	//}
//	//catch (itk::ExceptionObject & error)
//	//{
//	//	std::cerr << "Error: " << error << std::endl;
//	//	return EXIT_FAILURE;
//	//}
//
//
//
//	//typedef itk::RescaleIntensityImageFilter< FloatImageType, UnsignedCharImageType > RescaleFilterType;
//	//RescaleFilterType::Pointer realRescaleFilter = RescaleFilterType::New();
//	//realRescaleFilter->SetInput(realFilter->GetOutput());
//	//realRescaleFilter->SetOutputMinimum(itk::NumericTraits< UnsignedCharPixelType >::min());
//	//realRescaleFilter->SetOutputMaximum(itk::NumericTraits< UnsignedCharPixelType >::max());
//	
//	//typedef itk::ImageFileWriter< UnsignedCharImageType > WriterType;
//	//WriterType::Pointer realWriter = WriterType::New();
//	//realWriter->SetFileName(realFileName);
//	//realWriter->SetInput(realRescaleFilter->GetOutput());
//	//try
//	//{
//	//	realWriter->Update();
//	//}
//	//catch (itk::ExceptionObject & error)
//	//{
//	//	std::cerr << "Error: " << error << std::endl;
//	//	return EXIT_FAILURE;
//	//}
//
//	//// Extract the imaginary part
//	//typedef itk::ComplexToImaginaryImageFilter< FFTOutputImageType, FloatImageType> ImaginaryFilterType;
//	//ImaginaryFilterType::Pointer imaginaryFilter = ImaginaryFilterType::New();
//	//imaginaryFilter->SetInput(fftFilter->GetOutput());
//
//	//RescaleFilterType::Pointer imaginaryRescaleFilter = RescaleFilterType::New();
//	//imaginaryRescaleFilter->SetInput(imaginaryFilter->GetOutput());
//	//imaginaryRescaleFilter->SetOutputMinimum(itk::NumericTraits< UnsignedCharPixelType >::min());
//	//imaginaryRescaleFilter->SetOutputMaximum(itk::NumericTraits< UnsignedCharPixelType >::max());
//
//	//WriterType::Pointer complexWriter = WriterType::New();
//	//complexWriter->SetFileName(imaginaryFileName);
//	//complexWriter->SetInput(imaginaryRescaleFilter->GetOutput());
//	//try
//	//{
//	//	complexWriter->Update();
//	//}
//	//catch (itk::ExceptionObject & error)
//	//{
//	//	std::cerr << "Error: " << error << std::endl;
//	//	return EXIT_FAILURE;
//	//}
//
//	//// Compute the magnitude
//	//typedef itk::ComplexToModulusImageFilter< FFTOutputImageType, FloatImageType> ModulusFilterType;
//	//ModulusFilterType::Pointer modulusFilter = ModulusFilterType::New();
//	//modulusFilter->SetInput(fftFilter->GetOutput());
//
//	//RescaleFilterType::Pointer magnitudeRescaleFilter = RescaleFilterType::New();
//	//magnitudeRescaleFilter->SetInput(modulusFilter->GetOutput());
//	//magnitudeRescaleFilter->SetOutputMinimum(itk::NumericTraits< UnsignedCharPixelType >::min());
//	//magnitudeRescaleFilter->SetOutputMaximum(itk::NumericTraits< UnsignedCharPixelType >::max());
//
//	//WriterType::Pointer magnitudeWriter = WriterType::New();
//	//magnitudeWriter->SetFileName(modulusFileName);
//	//magnitudeWriter->SetInput(magnitudeRescaleFilter->GetOutput());
//	//try
//	//{
//	//	magnitudeWriter->Update();
//	//}
//	//catch (itk::ExceptionObject & error)
//	//{
//	//	std::cerr << "Error: " << error << std::endl;
//	//	return EXIT_FAILURE;
//	//}
//
//	return EXIT_SUCCESS;
//}