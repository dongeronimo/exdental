#pragma once
#include <Windows.h>
#using <WindowsBase.dll>
#using <mscorlib.dll> 
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#include <msclr\marshal_cppstd.h>
#include <ImageLoader.h>
#include <ImageLoader.h>
#include <vector>
#include "Image.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace std;

namespace geronimo
{
	class ImageLoaderNativeData
	{
	public:
		vector<StringList> fatiasDasImagens;
		StringList imagens;
	};

	public ref class ImageLoader
	{
	private:
		ImageLoaderNativeData *data;
		Image ^imagem;
	public:
		//Retorna as série que existem do diretório na forma identifier;numero de fatias.
		System::Collections::Generic::List<String^>^ ImageLoader::GetListaDeImagens(String^ dirpath);
		void Load();
		void Load(int index);
		ImageLoader();
		~ImageLoader();
		Image^ GetImage() { return imagem; }
		void LoadVTI(String^ filename);
	};
}