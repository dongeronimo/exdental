#pragma once
#include "Imagem.h"
#include <Windows.h>
#using <WindowsBase.dll>
#using <mscorlib.dll> 
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#include <imageSource.h>
#include <NameListGenerator.h>
#include <loadedImage.h>
#include "Imagem.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

namespace geronimo
{
	public ref class ImageLoader
	{
	private:
		datasource::ImageSource* imageSource;
		datasource::LoadedImage* loadedImage;
		Imagem^ managedImg;
		ProgressBar^ progressBar;
	public:
		static ImageLoader^ gambiarra;
		ProgressBar^ GetProgressBar()
		{
			return progressBar;
		}

		ImageLoader();
		//Retorna as s�rie que existem do diret�rio na forma identifier;numero de fatias.
		System::Collections::Generic::List<String^>^ GetListaDeImagens(String^ dirpath);

		//Carrega a imagem que est� no diretorio dado. Essa vers�o � simples e assume somente uma s�rie no diret�rio
		void LoadFromDir(String^ dirpath);
		//Carrega a s�rie. � comum ter v�rias s�ries no mesmo diret�rio. Nessa vers�o do m�todo tem que ser escolhida
		//qual das s�ries deve ser carregada, segundo a ordem que GetListaDeImagens retorna. Esse m�todo assume que os
		//conte�dos do diret�rio usado em GetListaDeImagens n�o mudou entre ele e LoadFromDir.
		void LoadFromDir(String^ dirpath, int qualSerie);

		Imagem^ GetImagemCarregada();

		~ImageLoader();

		void SetProgressBar(ProgressBar^ pb);
	};
}

