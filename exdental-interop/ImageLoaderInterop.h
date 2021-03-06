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
		HWND windowHandle;
		Image ^imagem;
	public:
		//Retorna as s�rie que existem do diret�rio na forma identifier;numero de fatias.
		System::Collections::Generic::List<String^>^ ImageLoader::GetListaDeImagens(String^ dirpath);
		void Load();
		void Load(int index);
		ImageLoader(IntPtr progressEventTarget);
		~ImageLoader();
		Image^ GetImage() { return imagem; }
		void LoadVTI(String^ filename);

		void TesteEnvioDeEventoDeVoltaPraTela(IntPtr myHWND)
		{
			HWND hwnd = (HWND)myHWND.ToPointer();
			unsigned int msg = WM_USER + 1000;
			WPARAM wParam = 10;
			LPARAM lParam = 0;
			SendMessage(hwnd, msg, wParam, lParam);
		}
	};
}