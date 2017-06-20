#include <string>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>
#include <itkImage.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkPNGReader.h>
using namespace std;

vtkSmartPointer<vtkImageData> LoadImagemOriginal(string filepath);

int main(int argc, char* argv[])
{
	string inPath = argv[1];
	string outPath = argv[2];
	vtkSmartPointer<vtkImageData> input = LoadImagemOriginal(inPath);

	typedef itk::Image<unsigned char, 2> ImageType;
	ImageType::Pointer itkImage = ImageType::New();
	ImageType::RegionType region;
	ImageType::IndexType index;
	index[0] = 0; index[1] = 0;
	region.SetIndex(index);
	ImageType::SizeType size;
	size[0] = input->GetDimensions()[0];
	size[1] = input->GetDimensions()[1];
	region.SetSize(size);
	itkImage->SetRegions(region);
	itkImage->Allocate();
	//A passagem tem que ser manual pq o fft exige uma entrada de numeros reais.
	unsigned char *sourceBuffer = reinterpret_cast<unsigned char*>(input->GetScalarPointer());
	unsigned char *destBuffer = itkImage->GetBufferPointer();
	for (auto i = 0; i<size[0] * size[1]; i++)
	{
		destBuffer[i] = sourceBuffer[i * 3];
	}
	itk::ImageFileWriter<itk::Image<unsigned char, 2>>::Pointer writer = itk::ImageFileWriter<itk::Image<unsigned char, 2>>::New();
	writer->SetInput(itkImage);
	writer->SetFileName(outPath.c_str());
	try
	{
		writer->Write();
	}
	catch(itk::ExceptionObject &ex)
	{
		cout << ex << endl;
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