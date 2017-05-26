#include "ImageLoader.h"
#include <msclr\marshal_cppstd.h>
#include <NameListGenerator.h>
#include <CallbackProgressoDeCarga.h>
namespace geronimo
{


	void __stdcall FnDoCallbackDeCarga(const float prog)
	{
		if(ImageLoader::gambiarra->GetProgressBar()!=nullptr)
			ImageLoader::gambiarra->GetProgressBar()->Value = prog * 100;
	}

	void ImageLoader::SetProgressBar(ProgressBar^ pb)
	{
		this->progressBar = pb;
	}

	ImageLoader::ImageLoader()
	{
		CallbackProgressoDeCarga::Pointer cbk = CallbackProgressoDeCarga::New();
		cbk->SetCallbackDoDelphi(FnDoCallbackDeCarga);
		imageSource = new datasource::ImageSource();//o objeto de callback da itk vai entrar aqui
		loadedImage = nullptr;
		progressBar = nullptr;
		ImageLoader::gambiarra = this;
	}

	ImageLoader::~ImageLoader()
	{
		delete imageSource;
		ImageLoader::gambiarra = nullptr;
		if (loadedImage)
			delete loadedImage;
	}
	//Retorna as s�rie que existem do diret�rio na forma identifier;numero de fatias.
	System::Collections::Generic::List<String^>^ ImageLoader::GetListaDeImagens(String^ dirpath)
	{
		
		System::Collections::Generic::List<String^>^ result = gcnew System::Collections::Generic::List<String^>();
		datasource::NameListGenerator lstGenerator;
		lstGenerator.SetCallbackDeProgresso(FnDoCallbackDeCarga);
		std::vector<std::string> identifiers;
		std::vector<datasource::NameListGenerator::SliceList> listas = lstGenerator.CreateList(msclr::interop::marshal_as<std::string>(dirpath).c_str(), identifiers);
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
		return result;
	}
	//Carrega a imagem que est� no diretorio dado. Essa vers�o � simples e assume somente uma s�rie no diret�rio
	void ImageLoader::LoadFromDir(String^ dirpath)
	{
		this->LoadFromDir(dirpath, 0);
	}
	//Carrega a s�rie. � comum ter v�rias s�ries no mesmo diret�rio. Nessa vers�o do m�todo tem que ser escolhida
	//qual das s�ries deve ser carregada, segundo a ordem que GetListaDeImagens retorna. Esse m�todo assume que os
	//conte�dos do diret�rio usado em GetListaDeImagens n�o mudou entre ele e LoadFromDir.
	void ImageLoader::LoadFromDir(String^ dirpath, int qualSerie)
	{
		datasource::NameListGenerator lstGenerator;
		lstGenerator.SetCallbackDeProgresso(FnDoCallbackDeCarga);
		std::vector<std::string> identifiers;
		std::vector<datasource::NameListGenerator::SliceList> listas = lstGenerator.CreateList(msclr::interop::marshal_as<std::string>(dirpath).c_str(), identifiers);
		std::vector<std::string> chosenLista = listas[qualSerie];
		std::unique_ptr<datasource::ImageSource> imageSource = std::make_unique<datasource::ImageSource>();
		imageSource->SetCallbackDeProgesso(FnDoCallbackDeCarga);
		imageSource->ClearList();
		for (std::string s : chosenLista)
		{
			imageSource->PushFile(s);
		}
		std::unique_ptr<datasource::LoadedImage> nativeImage = imageSource->Load("exame", identifiers[qualSerie]);
		managedImg = gcnew Imagem(std::move( nativeImage));
	}

	Imagem^ ImageLoader::GetImagemCarregada()
	{
		return  managedImg;
	}

}