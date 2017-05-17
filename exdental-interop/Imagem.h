#pragma once
#include <Windows.h>
#include <memory>
#include <loadedImage.h>
namespace geronimo
{
	class StdPtrEncapsulator
	{
	public:		
		std::shared_ptr<datasource::LoadedImage> data;
	};

	public ref class Imagem
	{
	private:
		StdPtrEncapsulator* enc;
	public:
		Imagem(std::shared_ptr<datasource::LoadedImage> i);
		~Imagem();
		std::shared_ptr<datasource::LoadedImage> GetImagem();
	};
}

