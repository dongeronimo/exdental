#include "Image.h"
#include <ImageLoader.h>
namespace geronimo
{
	void Image::SalvarParaOVolview(String^ file)
	{
		std::string stdFile = msclr::interop::marshal_as<std::string>(file);
		imageLoader::SaveAsXML(data->imagem->GetImage(), stdFile);
	}

	void Image::AplicarSuavizacao(int iterations, double timestep, double conductance)
	{
		data->pipe->Suavizacao(iterations, timestep, conductance);
	}

	Image::Image(shared_ptr<imageLoader::LoadedImage> img, HWND windowWithTheProgressBar)
	{
		data = new ImageNativeData();
		data->imagem = img;
		data->pipe = make_shared<pipeline::Pipeline>(data->imagem, windowWithTheProgressBar);
	}

	Image::~Image()
	{
		delete data;
	}

	void Image::AplicarSigmoide(int alpha, int beta, float min, float max)
	{
		data->pipe->Sigmoide(alpha, beta, min, max);
	}

	void Image::SalvarSigmoide(String^ file)
	{
		std::string stdFile = msclr::interop::marshal_as<std::string>(file);
		data->pipe->SalvarSigmoide(stdFile);
	}
}