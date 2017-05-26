#include "Imagem.h"
#include <map>
#include <string>

namespace geronimo
{
	Imagem::Imagem(std::unique_ptr<datasource::LoadedImage> i)
	{
		enc = new StdPtrEncapsulator();
		enc->data = std::move(i);
		std::map<std::string, std::string> metadata;//HACK: To jogando fora a metadata
//		enc->pipeline = std::make_shared<Pipeline>(enc->data, metadata);
	}

	Imagem::~Imagem()
	{
		enc->data.reset();
	}

	datasource::LoadedImage* Imagem::GetImagem()
	{
		return enc->data.get();
	}

	std::shared_ptr<Pipeline> Imagem::GetPipeline()
	{
		return enc->pipeline;
	}
}
