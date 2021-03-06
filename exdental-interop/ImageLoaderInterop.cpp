#include "ImageLoaderInterop.h"
#include <ImageLoader.h>
#include <vector>
#include <string>
#include <msclr\marshal_cppstd.h>

using namespace std;

namespace geronimo
{
	void ImageLoader::LoadVTI(String^ filename)
	{
		std::string arq = msclr::interop::marshal_as<std::string>(filename);
		std::string n = "noexam";
		imageLoader::ImageLoader loader(windowHandle);
		imagem = gcnew Image(loader.LoadVTI(arq, n, n),windowHandle);
	}

	ImageLoader::ImageLoader(IntPtr progressEventTarget)
	{
		data = new ImageLoaderNativeData();
		windowHandle = reinterpret_cast<HWND>(progressEventTarget.ToPointer());
	}

	ImageLoader::~ImageLoader()
	{
		delete data;
	}
	
	void ImageLoader::Load()
	{
		StringList slices = data->fatiasDasImagens[0];
		imageLoader::ImageLoader loader(windowHandle);
		imagem = gcnew Image(loader.Load(slices, "noexam", "noseries"), windowHandle);
	}

	void ImageLoader::Load(int index)
	{
		StringList slices = data->fatiasDasImagens[index];
		imageLoader::ImageLoader loader(windowHandle);
		imagem = gcnew Image(loader.Load(slices, "noexam", "noseries"), windowHandle);
	}

	System::Collections::Generic::List<String^>^ ImageLoader::GetListaDeImagens(String^ dirpath)
	{
		System::Collections::Generic::List<String^>^ result = gcnew System::Collections::Generic::List<String^>();
		imageLoader::NameListGenerator lstGenerator;
		StringList identifiers;
		vector<StringList> listas = lstGenerator.CreateList(msclr::interop::marshal_as<std::string>(dirpath).c_str(), identifiers);
		//aqui est� a lista de listas - cada sublista deve ser mapeada pra um nome e valor
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