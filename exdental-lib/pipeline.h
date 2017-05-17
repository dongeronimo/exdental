#pragma once
#include <itkImage.h>
#include <string>
#include <map>
#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageProperty.h>
#include <vtkImageSlice.h>
//A partir da imagem carregada, bota na tela.
using namespace std;
class Pipeline
{
private:

	vtkSmartPointer<vtkImageImport> vtkImport;
	vtkSmartPointer<vtkImageResliceMapper> resliceMapper;
	vtkSmartPointer<vtkImageProperty> resliceProperties;
	vtkSmartPointer<vtkImageSlice> resliceActor;
public:
	Pipeline(itk::Image<short, 3>::Pointer img, map<string, string> metadataDictionary);
	vtkSmartPointer<vtkImageSlice> GetResliceActor();
	void SetWL(int w, int l);
};