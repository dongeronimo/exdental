#include "Imagem.h"


namespace geronimo
{


	Imagem::Imagem(std::shared_ptr<datasource::LoadedImage> i)
	{
		enc = new StdPtrEncapsulator();
		enc->data = std::move(i);
	}

	Imagem::~Imagem()
	{
		enc->data.reset();
	}

	std::shared_ptr<datasource::LoadedImage> Imagem::GetImagem()
	{
		return enc->data;
	}
}
