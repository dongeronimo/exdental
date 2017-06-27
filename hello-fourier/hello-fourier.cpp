//#define IR_E_VOLTAR

#include <iostream>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkForwardFFTImageFilter.h>
#include <itkInverseFFTImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkImageFileWriter.h>
#include <itkComplexToModulusImageFilter.h>
#include <itkLogImageFilter.h>
#include <itkMinimumMaximumImageFilter.h>
using namespace std;

typedef itk::Image<double, 2> FloatImageType;
typedef itk::ForwardFFTImageFilter<FloatImageType> FFTType;
typedef itk::InverseFFTImageFilter<FFTType::OutputImageType, FloatImageType> IFFTType;
typedef itk::ComplexToModulusImageFilter< FFTType::OutputImageType, FloatImageType> ModulusFilterType;
typedef itk::LogImageFilter < FloatImageType, FloatImageType > LogFilterType;
typedef itk::MinimumMaximumImageFilter<FloatImageType> MinMaxFilterType;

FloatImageType::Pointer LoadImagem();
void SaveImagem(FloatImageType::Pointer img);
void GetMinMax(FloatImageType::Pointer input, float& min, float& max);

void PrintMinMax(float min, float max)
{
	wcout << "Mínimo:" << min << ", Máximo:" << max << endl;
}

int main(int argc, char** argv)
{
	try
	{
		float minValDaImagem, maxValDaImagem;
		//1) Carrega a imagem
		FloatImageType::Pointer image = LoadImagem();
		//Faz a fourier
		FFTType::Pointer fftFilter = FFTType::New();
		fftFilter->SetInput(image);
		fftFilter->Update();
		// Calculo da magnitude		
		ModulusFilterType::Pointer modulusFilter = ModulusFilterType::New();
		modulusFilter->SetInput(fftFilter->GetOutput());
		modulusFilter->Update();
		GetMinMax(modulusFilter->GetOutput(), minValDaImagem, maxValDaImagem);
		PrintMinMax(minValDaImagem, maxValDaImagem);
		//Pelo exemplo da opencv, agora aplico log na imagem
		LogFilterType::Pointer logFilter = LogFilterType::New();
		logFilter->SetInput(modulusFilter->GetOutput());
		logFilter->InPlaceOff();
		logFilter->Update();
		GetMinMax(logFilter->GetOutput(), minValDaImagem, maxValDaImagem);
		PrintMinMax(minValDaImagem, maxValDaImagem);
		//Tentar gravar pra ver o que acontece
		
		//Talvez eu tenha que log intensity rescale pra por em escala logaritminca
#ifdef IR_E_VOLTAR
		//2) Fazer a fourier da imagem e voltar para a imagem
		FFTType::Pointer fftFilter = FFTType::New();
		fftFilter->SetInput(image);
		fftFilter->Update();
		// Compute the IFFT
		IFFTType::Pointer ifftFilter = IFFTType::New();
		ifftFilter->SetInput(fftFilter->GetOutput());
		ifftFilter->Update();
		//3)Salva
		SaveImagem(ifftFilter->GetOutput());
#endif
	}
	catch(itk::ExceptionObject &ex)
	{
		ex.Print(cout);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void GetMinMax(FloatImageType::Pointer input, float& min, float& max)
{
	MinMaxFilterType::Pointer minMax = MinMaxFilterType::New();
	minMax->SetInput(input);
	minMax->Update();
	max = minMax->GetMaximum();
	min = minMax->GetMinimum();
}

void SaveImagem(FloatImageType::Pointer img)
{
	typedef itk::Image<unsigned char, 2> UnsignedCharImageType;
	typedef itk::CastImageFilter< FloatImageType, UnsignedCharImageType > CastFilterType;
	CastFilterType::Pointer castFilter = CastFilterType::New();
	castFilter->SetInput(img);
	castFilter->Update();
	typedef itk::ImageFileWriter<UnsignedCharImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName("C:\\src\\exdental\\ifft.png");
	writer->SetInput(castFilter->GetOutput());
	writer->Update();
}

FloatImageType::Pointer LoadImagem()
{
	typedef itk::ImageFileReader<FloatImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName("C:\\src\\exdental\\black_dot_1_channel.png");
	reader->Update();
	return reader->GetOutput();
}