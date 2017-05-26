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
		//Retorna as série que existem do diretório na forma identifier;numero de fatias.
		System::Collections::Generic::List<String^>^ GetListaDeImagens(String^ dirpath);

		//Carrega a imagem que está no diretorio dado. Essa versão é simples e assume somente uma série no diretório
		void LoadFromDir(String^ dirpath);
		//Carrega a série. É comum ter várias séries no mesmo diretório. Nessa versão do método tem que ser escolhida
		//qual das séries deve ser carregada, segundo a ordem que GetListaDeImagens retorna. Esse método assume que os
		//conteúdos do diretório usado em GetListaDeImagens não mudou entre ele e LoadFromDir.
		void LoadFromDir(String^ dirpath, int qualSerie);

		Imagem^ GetImagemCarregada();

		~ImageLoader();

		void SetProgressBar(ProgressBar^ pb);
	};
}

