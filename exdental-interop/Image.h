#pragma once
#include <ImageLoader.h>
#include <Pipeline.h>
#include <memory>
using namespace std;
namespace geronimo
{
	class ImageNativeData
	{
	public:
		shared_ptr<imageLoader::LoadedImage> imagem;
		shared_ptr<pipeline::Pipeline> pipe;
	};

	public ref class Image
	{
	private:
		ImageNativeData *data;
	public:
		Image(shared_ptr<imageLoader::LoadedImage> img);
		~Image();
		shared_ptr<pipeline::Pipeline> GetPipeline() { return data->pipe; }
	};
}