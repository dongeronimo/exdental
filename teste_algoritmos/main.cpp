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
#include <itkImportImageFilter.h>

#include <itkForwardFFTImageFilter.h>
#include <itkComplexToRealImageFilter.h>
#include <itkImage.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkImageFileWriter.h>

using namespace std;

typedef array<unsigned int, 3> TuplaRGB;
typedef vector<TuplaRGB> LinhaProjetada;
const unsigned int Dimension = 2;
typedef double                                   FloatPixelType;
typedef itk::Image< FloatPixelType, Dimension > FloatImageType;

vtkSmartPointer<vtkImageData> LoadImagemOriginal(string filepath);
void SalvarImagem(vtkSmartPointer<vtkImageData> img, string filename);
//Gira a imagem ao redor de seu centro por um angulo tetha (em graus).
vtkSmartPointer<vtkImageData> RotateImage(vtkSmartPointer<vtkImageData>input, double tetha);
//Projeta a imagem passado raios nela.
LinhaProjetada CalculaProjecaoDaImagem(vtkSmartPointer<vtkImageData> rotatedImage, vtkSmartPointer<vtkImageData> originalImage);
//Monta o sinograma
vtkSmartPointer<vtkImageData> GerarSinograma(vtkSmartPointer<vtkImageData> imagem);
vtkSmartPointer<vtkImageData> GerarSinogramaMK2(vtkSmartPointer<vtkImageData>imagem);

//Reconstrução da imagem
vtkSmartPointer<vtkImageData> ReconstrucaoSimpleBackprojection(vtkSmartPointer<vtkImageData> sinograma);
//Cria uma tela pra ver a imagem
vtkSmartPointer<vtkImageViewer2> GerarVisualizacao(vtkSmartPointer<vtkImageData> img);

int main(int argc, char** argv)
{
	//black_dot_1_channel.png
	//vtkSmartPointer<vtkImageData> imagem = LoadImagemOriginal("C:\\src\\exdental\\phantom.png");
	vtkSmartPointer<vtkImageData> imagem = LoadImagemOriginal("C:\\src\\exdental\\black_dot_1_channel.png");
	array<double, 3> origemDaImagem;
	imagem->GetOrigin(origemDaImagem.data());
	array<double, 3> spacingDaImagem;
	imagem->GetSpacing(spacingDaImagem.data());
	array<double, 3> centroDaImagem;
	imagem->GetCenter(centroDaImagem.data());
	array<int, 3> dimensoesDaImagem;
	imagem->GetDimensions(dimensoesDaImagem.data());
	//teste de fazer uma fourier transform
	FloatImageType::Pointer itkImage = FloatImageType::New();
	FloatImageType::RegionType region;
	FloatImageType::IndexType index;
	index[0] = 0; index[1] = 0;
	region.SetIndex(index);
	FloatImageType::SizeType size;
	size[0] = dimensoesDaImagem[0];
	size[1] = dimensoesDaImagem[1];
	region.SetSize(size);
	itkImage->SetRegions(region);
	itkImage->Allocate();
	//A passagem tem que ser manual pq o fft exige uma entrada de numeros reais.
	unsigned char *sourceBuffer = reinterpret_cast<unsigned char*>(imagem->GetScalarPointer());
	double *destBuffer = itkImage->GetBufferPointer();
	for(auto i=0; i<dimensoesDaImagem[0]*dimensoesDaImagem[1]; i++)
	{
		destBuffer[i] = sourceBuffer[i];
	}
	vtkSmartPointer<vtkImageData> sinograma = GerarSinogramaMK2(imagem);

	vtkSmartPointer<vtkImageViewer2> visualizaçãoDoSinograma = GerarVisualizacao(sinograma);
	//vtkSmartPointer<vtkImageViewer2> visualizaçãoDaFFT = GerarVisualizacao(fft->GetOutput());
	visualizaçãoDoSinograma->GetRenderWindow()->GetInteractor()->Start();
	return EXIT_SUCCESS;
}

vtkSmartPointer<vtkImageData> GerarSinogramaMK2(vtkSmartPointer<vtkImageData> imagem)
{
//VTK pra ITK
	typedef itk::ImportImageFilter< float, 3 >   ImportFilterType;
	ImportFilterType::Pointer importFilter = ImportFilterType::New();
	ImportFilterType::SizeType  size;
	size[0] = imagem->GetDimensions()[0];
	size[1] = imagem->GetDimensions()[1];
	size[2] = imagem->GetDimensions()[2];
	ImportFilterType::IndexType start;
	start.Fill(0);
	ImportFilterType::RegionType region;
	region.SetIndex(start);
	region.SetSize(size);
	importFilter->SetRegion(region);

	double origin[Dimension];
	origin[0] = 0.0;    // X coordinate
	origin[1] = 0.0;    // Y coordinate
	origin[2] = 0.0;    // Z coordinate

	importFilter->SetOrigin(origin);

	double spacing[Dimension];
	spacing[0] = 1.0;    // along X direction
	spacing[1] = 1.0;    // along Y direction
	spacing[2] = 1.0;    // along Z direction

	importFilter->SetSpacing(spacing);

	const unsigned int numberOfPixels = size[0] * size[1] * size[2];
	PixelType * localBuffer = new PixelType[numberOfPixels];

	const double radius = 80.0;

	const double radius2 = radius * radius;
	PixelType * it = localBuffer;

	for (unsigned int z = 0; z < size[2]; z++)
	{
		const double dz = static_cast<double>(z) - static_cast<double>(size[2]) / 2.0;
		for (unsigned int y = 0; y < size[1]; y++)
		{
			const double dy = static_cast<double>(y) - static_cast<double>(size[1]) / 2.0;
			for (unsigned int x = 0; x < size[0]; x++)
			{
				const double dx = static_cast<double>(x) - static_cast<double>(size[0]) / 2.0;
				const double d2 = dx*dx + dy*dy + dz*dz;
				*it++ = (d2 < radius2) ? 255 : 0;
			}
		}
	}

	const bool importImageFilterWillOwnTheBuffer = true;
	importFilter->SetImportPointer(localBuffer, numberOfPixels,
		importImageFilterWillOwnTheBuffer);
//Fourier da imagem	
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

vtkSmartPointer<vtkImageData> GerarSinograma(vtkSmartPointer<vtkImageData> imagem )
{
	vector<LinhaProjetada> linhas;
	for (int i = 0; i <= 360; i++)
	{
		vtkSmartPointer<vtkImageData> rotatedImage = RotateImage(imagem, i);
		LinhaProjetada linhaAtual = CalculaProjecaoDaImagem(rotatedImage, imagem);
		linhas.push_back(linhaAtual);
	}
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