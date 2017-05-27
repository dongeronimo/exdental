#include "ImageLoaderInterop.h"
#include <ImageLoader.h>
#include <vector>
#include <string>
#include <msclr\marshal_cppstd.h>

using namespace std;

namespace geronimo
{
	ImageLoader::ImageLoader()
	{
		data = new ImageLoaderNativeData();
	}

	ImageLoader::~ImageLoader()
	{
		delete data;
	}
	
	void ImageLoader::Load()
	{
		StringList slices = data->fatiasDasImagens[0];
		imageLoader::ImageLoader loader;
		imagem = gcnew Image(loader.Load(slices, "noexam", "noseries"));		
	}

	void ImageLoader::Load(int index)
	{
		StringList slices = data->fatiasDasImagens[index];
		imageLoader::ImageLoader loader;
		imagem = gcnew Image(loader.Load(slices, "noexam", "noseries"));
	}

	System::Collections::Generic::List<String^>^ ImageLoader::GetListaDeImagens(String^ dirpath)
	{
		System::Collections::Generic::List<String^>^ result = gcnew System::Collections::Generic::List<String^>();
		imageLoader::NameListGenerator lstGenerator;
		StringList identifiers;
		vector<StringList> listas = lstGenerator.CreateList(msclr::interop::marshal_as<std::string>(dirpath).c_str(), identifiers);
		//aqui está a lista de listas - cada sublista deve ser mapeada pra um nome e valor
		for (int i = 0; i<identifiers.size(); i++)
		{
			std::string name = identifiers[i];
			int size = listas[i].size();
			String^ currData = gcnew String(name.c_str());
			currData += ";";
			currData += size;
			result->Add(currData);
		}
		data->fatiasDasImagens = listas;
		data->imagens = identifiers;
		return result;
	}
}