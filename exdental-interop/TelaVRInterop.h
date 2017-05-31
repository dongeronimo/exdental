#pragma once
#include <Windows.h>
#using <WindowsBase.dll>
#using <mscorlib.dll> 
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#include <TelaVR.h>
#include "Image.h"
using namespace System::Windows::Forms;
namespace geronimo
{
	public ref class TelaVR
	{
	private:
		geronimo_impl::TelaVR* telaVR;
	public:
		TelaVR();
		~TelaVR();
		void CreateScreen(Panel^ targetPanel);
		void SetImagem(Image^ im);
		void Resize(int w, int h);

	};
}