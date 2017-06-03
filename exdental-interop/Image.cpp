#include "Image.h"

namespace geronimo
{
	void Image::AplicarSuavizacao(int iterations, double timestep, double conductance)
	{
		//Suavizacao(int iterations, double timestep, double conductance)
		data->pipe->Suavizacao(iterations, timestep, conductance);
	}
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