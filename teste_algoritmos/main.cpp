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
using namespace std;

vtkSmartPointer<vtkImageData> LoadImagemOriginal(string filepath);

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

int main(int argc, char** argv)
{
	vtkSmartPointer<vtkImageData> imagem = LoadImagemOriginal("C:\\src\\black_dot.png");
	array<double, 3> origemDaImagem;
	imagem->GetOrigin(origemDaImagem.data());
	array<double, 3> spacingDaImagem;
	imagem->GetSpacing(spacingDaImagem.data());
	array<double, 3> centroDaImagem;
	imagem->GetCenter(centroDaImagem.data());
	array<int, 3> dimensoesDaImagem;
	imagem->GetDimensions(dimensoesDaImagem.data());
	//Teste da rotação da imagem
	for(int i=0;i<=180; i++)
	{
		vtkSmartPointer<vtkImageData> img = RotateImage(imagem, i);
		vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
		stringstream ss;
		ss << "C:\\src\\teste_rotacao_" << i << ".png";
		writer->SetFileName(ss.str().c_str());
		writer->SetInputData(img);
		writer->Write();
	}
	return EXIT_SUCCESS;
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