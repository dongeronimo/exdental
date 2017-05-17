#include "loadedImage.h"
#include <itkOrientImageFilter.h>

#include  "itktypes.h"
datasource::LoadedImage::LoadedImage(ImageType::Pointer _image, map<string, string> metadata, itk::MetaDataDictionary rawDictionary, string idExame, string idSerie)
{
	this->idExame = idExame;
	this->idSerie = idSerie;
	this->image = _image;
	this->metadataDictionary = metadata;
	this->rawDictionary = rawDictionary;
	typedef itk::OrientImageFilter<ImageType, ImageType> TOrientImageFilter;


	//Ajeita o que é parte de baixo e o que é parte de cima
	TOrientImageFilter::Pointer reorientador = nullptr;
	reorientador = TOrientImageFilter::New();
	reorientador->SetInput(image);
	reorientador->UseImageDirectionOn();
	reorientador->SetDesiredCoordinateOrientation(itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RIP);
	reorientador->Update();
	DeepCopy<itk::Image<short, 3>>(reorientador->GetOutput(), image);
	//image->DebugOn();
}


