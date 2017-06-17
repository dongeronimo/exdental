#include <iostream>
#include <array>
#include <string>
#include <sstream>

#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageData.h>
#include <vtkTransform.h>
#include <vtkImageReslice.h>
#include <vtkPNGWriter.h>
#include <vtkImageInterpolator.h>
using namespace std;

vtkSmartPointer<vtkImageData> LoadImagemOriginal(string filepath);
void SalvarImagem(vtkSmartPointer<vtkImageData> img, string filename);
//Gira a imagem ao redor de seu centro por um angulo tetha (em graus).
vtkSmartPointer<vtkImageData> RotateImage(vtkSmartPointer<vtkImageData>input, double tetha);


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

	//Gira a imagem
	vtkSmartPointer<vtkImageData> rotatedImage = RotateImage(imagem, 0);
	//Cria o interpolador
	vtkSmartPointer<vtkImageInterpolator> rotatedImageInterpolator = vtkSmartPointer<vtkImageInterpolator>::New();
	rotatedImageInterpolator->SetInterpolationModeToLinear();
	rotatedImageInterpolator->SetOutValue(0);
	rotatedImageInterpolator->Initialize(rotatedImage);
	rotatedImageInterpolator->Update();
	//Canvas de teste, só pra eu enxergar o que está acontecendo.
	vtkSmartPointer<vtkImageData> canvasDeTeste = vtkSmartPointer<vtkImageData>::New();
	canvasDeTeste->SetExtent(0, 255, 0, 255, 0, 1);
	canvasDeTeste->SetSpacing(1, 1, 1);
	canvasDeTeste->SetOrigin(0, 0, 0);
	canvasDeTeste->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
	void *buffer = canvasDeTeste->GetScalarPointer();
	memset(buffer, 0, 256 * 256 * 3);
	//Percorre ao longo da horizontal gerando raios e marchando-os fazendo as integrações.
	for(int i=0; i<dimensoesDaImagem[0];i++)
	{
		//seta o vetor e o ponto inicial do raio atual, partindo da parte inferior da imagem
		array<double, 2> r0i = { i*spacingDaImagem[0], 0 };
		array<double, 2> rVeci = { 0,1 };
		array<double, 3> somatorioRaioAtual = { 0,0,0 };
		for(int gamma = 0; gamma < dimensoesDaImagem[0]; gamma++)
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
		cout << somatorioRaioAtual[0] << endl;
		canvasDeTeste->SetScalarComponentFromDouble(i, 128, 0, 0, somatorioRaioAtual[0]);
		canvasDeTeste->SetScalarComponentFromDouble(i, 128, 0, 1, somatorioRaioAtual[1]);
		canvasDeTeste->SetScalarComponentFromDouble(i, 128, 0, 2, somatorioRaioAtual[2]);
	}
	SalvarImagem(rotatedImage, "C:\\src\\exdental\\rotated_image.png");
	SalvarImagem(canvasDeTeste, "C:\\src\\exdental\\somatorio_teste.png");
	return EXIT_SUCCESS;
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