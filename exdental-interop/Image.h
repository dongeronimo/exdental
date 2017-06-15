#pragma once
#include <Windows.h>
#include <ImageLoader.h>
#include <Pipeline.h>
#include <memory>
#include "ImageNativeData.h"
#include <Windows.h>
#using <WindowsBase.dll>
#using <mscorlib.dll> 
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#include <msclr\marshal_cppstd.h>
#include <ImageLoader.h>
#include <ImageLoader.h>
#include <vector>
#include "Image.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
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
		HWND windowWithTheProgressBarHandle;
	public:
		Image(shared_ptr<imageLoader::LoadedImage> img, HWND windowWithTheProgressBar);
		~Image();
		shared_ptr<pipeline::Pipeline> GetPipeline() { return data->pipe; }
		void AplicarSuavizacao(int iterations, double timestep, double conductance);
		void AplicarSigmoide(int alpha, int beta, float min, float max);
		void SalvarParaOVolview(String^ file);
	};
}