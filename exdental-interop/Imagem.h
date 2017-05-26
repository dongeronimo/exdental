#pragma once
#include <Windows.h>
#include <memory>
#include <loadedImage.h>
#include <pipeline.h>
namespace geronimo
{
	class StdPtrEncapsulator
	{
	public:		
		std::unique_ptr<datasource::LoadedImage> data;
		std::shared_ptr<Pipeline> pipeline;
	};

	public ref class Imagem
	{
	private:
		StdPtrEncapsulator* enc;
	public:
		Imagem(std::unique_ptr<datasource::LoadedImage> i);
		~Imagem();
		datasource::LoadedImage* GetImagem();
		std::shared_ptr<Pipeline> GetPipeline();
	};
}

