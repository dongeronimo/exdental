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
#include <vtkImageFFT.h>
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
	//Pega as projeções dos raios fazendo as inclinações da imagem
	vector<LinhaProjetada> linhas;
	for(int i=0; i<=360;i++)
	{
		vtkSmartPointer<vtkImageData> rotatedImage = RotateImage(imagem, i);
		LinhaProjetada linhaAtual = CalculaProjecaoDaImagem(rotatedImage, imagem);
		linhas.push_back(linhaAtual);
	}
	vtkSmartPointer<vtkImageData> sinograma = GerarSinograma(linhas);
	
	vtkSmartPointer<vtkImageFFT> fft = vtkSmartPointer<vtkImageFFT>::New();
	fft->SetDimensionality(2);
	fft->SetInputData(imagem);
	fft->Update();
	vtkImageData* minhaFFT = fft->GetOutput();
	cout<<minhaFFT->GetScalarTypeAsString()<<endl;
	SalvarImagem(fft->GetOutput(), "C:\\src\\exdental\\fft.png");
	

	vtkSmartPointer<vtkImageViewer2> visualizaçãoDoSinograma = GerarVisualizacao(sinograma);
	vtkSmartPointer<vtkImageViewer2> visualizaçãoDaFFT = GerarVisualizacao(fft->GetOutput());
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