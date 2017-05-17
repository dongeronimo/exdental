#pragma warning(disable:4996)
#pragma warning(disable:4049)
#ifndef __loaded_image_h
#define __loaded_image_h
#include <itkImage.h>
#include <string>
#include <map>
#include <itkMetaDataDictionary.h>

using namespace std;

namespace datasource
{
	typedef itk::Image<short, 3> ImageType;
	//Uma imagem carregada, pronta pra ser usada pelas pipelines.
	class LoadedImage
	{
	private:
		//a string do exame e da série
		string idExame, idSerie;
		//A imagem. 
		ImageType::Pointer image;
		//A metadata numa forma inteligível.
		map<string, string> metadataDictionary;
		//O dicionário de metadata na forma crua da itk
		itk::MetaDataDictionary rawDictionary;
	public:
		string GetIdExame(){ return idExame; }
		string GetIdSerie(){ return idSerie; }

		short valueOffset;
		LoadedImage(ImageType::Pointer _image, map<string, string> metadata, itk::MetaDataDictionary rawDictionary, string idExame, string idSerie);
		ImageType::Pointer GetImage(){ return image; }
		map<string, string> GetMetadata(){ return metadataDictionary; };
	};
}


#endif