#pragma once
#include <ImageLoader.h>
#include <memory>
using namespace std;
namespace geronimo
{
	class ImageNativeData
	{
	public:
		shared_ptr<imageLoader::LoadedImage> imagem;
	};

	public ref class Image
	{
	private:
		ImageNativeData *data;
	public:
		Image(shared_ptr<imageLoader::LoadedImage> img);
		~Image();
	};
}