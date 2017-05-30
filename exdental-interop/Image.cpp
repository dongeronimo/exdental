#include "Image.h"

namespace geronimo
{
	Image::Image(shared_ptr<imageLoader::LoadedImage> img)
	{
		data = new ImageNativeData();
		data->imagem = img;
		data->pipe = make_shared<pipeline::Pipeline>(data->imagem);
	}
	Image::~Image()
	{
		delete data;
	}
}