#include "Image.h"

namespace geronimo
{
	Image::Image(shared_ptr<imageLoader::LoadedImage> img)
	{
		data = new ImageNativeData();
		data->imagem = img;
	}
	Image::~Image()
	{
		delete data;
	}
}