#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <sstream>

#include <vtkImageActor.h>
#include <vtkImageProperty.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkImageViewer2.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageData.h>
#include <vtkTransform.h>
#include <vtkImageReslice.h>
#include <vtkPNGWriter.h>
#include <vtkImageInterpolator.h>

#include <itkForwardFFTImageFilter.h>
#include <itkComplexToRealImageFilter.h>
#include <itkImage.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkImageFileWriter.h>

using namespace std;

typedef array<unsigned int, 3> TuplaRGB;
typedef vector<TuplaRGB> LinhaProjetada;

vtkSmartPointer<vtkImageData> LoadImagemOriginal(string filepath);
void SalvarImagem(vtkSmartPointer<vtkImageData> img, string filename);
//Gira a imagem ao redor de seu centro por um angulo tetha (em graus).
vtkSmartPointer<vtkImageData> RotateImage(vtkSmartPointer<vtkImageData>input, double tetha);
//Projeta a imagem passado raios nela.
LinhaProjetada CalculaProjecaoDaImagem(vtkSmartPointer<vtkImageData> rotatedImage, vtkSmartPointer<vtkImageData> originalImage);
//Monta o sinograma
vtkSmartPointer<vtkImageData> GerarSinograma(vector<LinhaProjetada> linhas);
//Reconstrução da imagem
vtkSmartPointer<vtkImageData> ReconstrucaoSimpleBackprojection(vtkSmartPointer<vtkImageData> sinograma);
//Cria uma tela pra ver a imagem
vtkSmartPointer<vtkImageViewer2> GerarVisualizacao(vtkSmartPointer<vtkImageData> img);
int main(int argc, char** argv)
{
	vtkSmartPointer<vtkImageData> imagem = LoadImagemOriginal("C:\\src\\exdental\\black_dot.png");
	array<double, 3> origemDaImagem;
	imagem->GetOrigin(origemDaImagem.data());
	array<double, 3> spacingDaImagem;
	imagem->GetSpacing(spacingDaImagem.data());
	array<double, 3> centroDaImagem;
	imagem->GetCenter(centroDaImagem.data());
	array<int, 3> dimensoesDaImagem;
	imagem->GetDimensions(dimensoesDaImagem.data());
	//teste de fazer uma fourier transform
	typedef itk::Image<float, 2> ImageType;
	ImageType::Pointer itkImage = ImageType::New();
	ImageType::RegionType region;
	ImageType::IndexType index;
	index[0] = 0; index[1] = 0;
	region.SetIndex(index);
	ImageType::SizeType size;
	size[0] = dimensoesDaImagem[0];
	size[1] = dimensoesDaImagem[1];
	region.SetSize(size);
	itkImage->SetRegions(region);
	itkImage->Allocate();
	//A passagem tem que ser manual pq o fft exige uma entrada de numeros reais.
	unsigned char *sourceBuffer = reinterpret_cast<unsigned char*>(imagem->GetScalarPointer());
	float *destBuffer = itkImage->GetBufferPointer();
	for(auto i=0; i<dimensoesDaImagem[0]*dimensoesDaImagem[1]; i++)
	{
		destBuffer[i] = sourceBuffer[i * 3];
	}
	//A partir daqui, a imagem está na ITK, pra eu ver se consigo fazer a fourier na ITK funcionar, pq 
	//a na VTK ficou uma merda.
	typedef itk::ForwardFFTImageFilter< ImageType > FFTType;//This filter works only for real single-component input image types.
	FFTType::Pointer fftFilter = FFTType::New();
	fftFilter->SetInput(itkImage);
	typedef FFTType::OutputImageType FFTOutputImageType;
	typedef itk::ComplexToRealImageFilter< FFTOutputImageType, ImageType> RealFilterType;
	RealFilterType::Pointer realFilter = RealFilterType::New();
	realFilter->SetInput(fftFilter->GetOutput());
	typedef itk::RescaleIntensityImageFilter< ImageType, itk::Image<unsigned char, 2> > RescaleFilterType;
	//volta de real pra unsigned char pra gravar.
	RescaleFilterType::Pointer realRescaleFilter = RescaleFilterType::New();
	realRescaleFilter->SetInput(realFilter->GetOutput());
	realRescaleFilter->SetOutputMinimum(itk::NumericTraits< unsigned char >::min());
	realRescaleFilter->SetOutputMaximum(itk::NumericTraits< unsigned char >::max());
	//grava
	typedef itk::ImageFileWriter<  itk::Image<unsigned char, 2> > WriterType;
	WriterType::Pointer realWriter = WriterType::New();
	realWriter->SetFileName("C:\\src\\exdental\\eh_a_fourier.png");
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

	//Pega as projeções dos raios fazendo as inclinações da imagem
	vector<LinhaProjetada> linhas;
	for(int i=0; i<=360;i++)
	{
		vtkSmartPointer<vtkImageData> rotatedImage = RotateImage(imagem, i);
		LinhaProjetada linhaAtual = CalculaProjecaoDaImagem(rotatedImage, imagem);
		linhas.push_back(linhaAtual);
	}
	vtkSmartPointer<vtkImageData> sinograma = GerarSinograma(linhas);

	

	vtkSmartPointer<vtkImageViewer2> visualizaçãoDoSinograma = GerarVisualizacao(sinograma);
	//vtkSmartPointer<vtkImageViewer2> visualizaçãoDaFFT = GerarVisualizacao(fft->GetOutput());
	visualizaçãoDoSinograma->GetRenderWindow()->GetInteractor()->Start();
	return EXIT_SUCCESS;
}
vtkSmartPointer<vtkImageData> ReconstrucaoSimpleBackprojection(vtkSmartPointer<vtkImageData> sinograma)
{
	//O X é o ângulo [0,360], o Y é a amostragem
	array<int, 3> dimensoesDoSinograma;
	sinograma->GetDimensions(dimensoesDoSinograma.data());
	//cria a imagem
	vtkSmartPointer<vtkImageData> reconstrucao = vtkSmartPointer<vtkImageData>::New();
	reconstrucao->SetExtent(0, dimensoesDoSinograma[1]-1, 0, dimensoesDoSinograma[1] - 1, 0, 1);
	reconstrucao->SetOrigin(0, 0, 0);
	reconstrucao->SetSpacing(1, 1, 1);
	reconstrucao->AllocateScalars(VTK_FLOAT, 1);
	//para cada coluna do sinograma:
		//1)obtenha os valores da projeção
		//2)rotacione reconstrução 1º
		//3)marche os valores de cada elemento do vetor de valores de projeção, indo de cima para baixo
		//em reconstrução.

	return reconstrucao;
}
vtkSmartPointer<vtkImageData> GerarSinograma(vector<LinhaProjetada> linhas)
{
	vtkSmartPointer<vtkImageData> testeImagem = vtkSmartPointer<vtkImageData>::New();
	testeImagem->SetExtent(0, 359, 0, 255, 0, 1);
	testeImagem->SetOrigin(0, 0, 0);
	testeImagem->SetSpacing(1, 1, 1);
	testeImagem->AllocateScalars(VTK_UNSIGNED_INT, 1);
	//passa os dados
	for (int x = 0; x < 360; x++)
	{
		for (int y = 0; y<256; y++)
		{
			testeImagem->SetScalarComponentFromDouble(x, y, 0, 0, linhas[x][y][0]);
		}
	}
	return testeImagem;
}

vtkSmartPointer<vtkImageViewer2> GerarVisualizacao(vtkSmartPointer<vtkImageData> img)
{
	vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputData(img);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();
	return imageViewer;
}

LinhaProjetada CalculaProjecaoDaImagem(vtkSmartPointer<vtkImageData> rotatedImage, vtkSmartPointer<vtkImageData> originalImage)
{
	array<double, 3> origemDaImagem;
	originalImage->GetOrigin(origemDaImagem.data());
	array<double, 3> spacingDaImagem;
	originalImage->GetSpacing(spacingDaImagem.data());
	array<double, 3> centroDaImagem;
	originalImage->GetCenter(centroDaImagem.data());
	array<int, 3> dimensoesDaImagem;
	originalImage->GetDimensions(dimensoesDaImagem.data());

	//Cria o interpolador
	vtkSmartPointer<vtkImageInterpolator> rotatedImageInterpolator = vtkSmartPointer<vtkImageInterpolator>::New();
	rotatedImageInterpolator->SetInterpolationModeToLinear();
	rotatedImageInterpolator->SetOutValue(0);
	rotatedImageInterpolator->Initialize(rotatedImage);
	rotatedImageInterpolator->Update();
	//Percorre ao longo da horizontal gerando raios e marchando-os fazendo as integrações.
	LinhaProjetada resultado;
	for (int i = 0; i<dimensoesDaImagem[0]; i++)
	{
		//seta o vetor e o ponto inicial do raio atual, partindo da parte inferior da imagem
		array<double, 2> r0i = { i*spacingDaImagem[0], 0 };
		array<double, 2> rVeci = { 0,1 };
		array<double, 3> somatorioRaioAtual = { 0,0,0 };
		for (int gamma = 0; gamma < dimensoesDaImagem[0]; gamma++)
		{
			//calcula o ponto atual da marcha.
			const array<double, 3> pontoAtual = {
				r0i[0] + gamma*spacingDaImagem[1] * rVeci[0],
				r0i[1] + gamma*spacingDaImagem[1] * rVeci[1],
				0
			};
			//Valor da posição atual
			array<double, 3> valorComponentes;
			rotatedImageInterpolator->Interpolate(pontoAtual.data(), valorComponentes.data());
			somatorioRaioAtual[0] += valorComponentes[0];
			somatorioRaioAtual[1] += valorComponentes[1];
			somatorioRaioAtual[2] += valorComponentes[2];
		}
		array<unsigned int, 3> raioAtual = { somatorioRaioAtual[0], somatorioRaioAtual[1], somatorioRaioAtual[2] };
		resultado.push_back(raioAtual);
	}
	return resultado;
}

vtkSmartPointer<vtkImageData> RotateImage(vtkSmartPointer<vtkImageData>input, double tetha)
{
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->Translate(input->GetCenter()[0], input->GetCenter()[1], input->GetCenter()[2]);
	transform->RotateWXYZ(tetha, 0, 0, 1);
	transform->Translate(-input->GetCenter()[0], -input->GetCenter()[1], -input->GetCenter()[2]);
	vtkSmartPointer<vtkImageReslice> reslicer = vtkSmartPointer<vtkImageReslice>::New();
	reslicer->SetInputData(input);
	reslicer->SetResliceTransform(transform);
	reslicer->SetInterpolationModeToLinear();
	reslicer->SetOutputOrigin(input->GetOrigin());
	reslicer->SetOutputSpacing(input->GetSpacing());
	reslicer->Update();
	return reslicer->GetOutput();
}
void SalvarImagem(vtkSmartPointer<vtkImageData> img, string filename)
{
	vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
	writer->SetFileName(filename.c_str());
	writer->SetInputData(img);
	writer->Write();
}
vtkSmartPointer<vtkImageData> LoadImagemOriginal(string filepath)
{
	vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
	reader->SetFileName(filepath.c_str());
	reader->Update();
	vtkSmartPointer<vtkImageData> resultado = reader->GetOutput();
	cout << "Scalar type: " << resultado->GetScalarTypeAsString() << endl;
	cout << "Scalar components: " << resultado->GetNumberOfScalarComponents() << endl;
	return resultado;
}