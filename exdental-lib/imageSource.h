#pragma warning(disable:4996)
#pragma warning(disable:4049)
#ifndef __image_source_h
#define __image_source_h
#include <vector>
#include <string>
#include "loadedImage.h"
#include "CallbackProgressoDeCarga.h"
using namespace std;
namespace datasource
{
	class ImageSource
	{
	private:
		//A lista de arquivos fontes.
		vector<string> filePaths;
		//O callback pra barrinha de carga
		CallbackProgressoDeCarga::Pointer handleDoCallbackDeCarga;

		int codigoDeErro;
		void CorrectGantryTilt(itk::Image<short, 3>::Pointer source, std::map<std::string, std::string> metadata);
		double GetGantryTilt(std::map<std::string, std::string> metadata);
	public:
		const int SEM_ERRO_DE_CARGA = 0;
		const int ERROR_CODE_INDICES_ZUADOS = 10;
		const int ERROR_CODE_OOM = 2;
		const int ERROR_FALHA_NA_LEITURA = 1;

		ImageSource(callbackDeProgressDaCarga callbackExternoDeCarga);
		ImageSource();

		
		void SetCallbackDeProgesso(callbackDeProgressDaCarga cbk);
		//Adiciona um arquivo ao fim da lista.
		void PushFile(string f);
		//Limpa a lista de fatias.
		void ClearList();
		unique_ptr<LoadedImage> Load(string idExame, string idSerie);
		int GetCodigoDeErro(){ return codigoDeErro; }
	};
}
#endif