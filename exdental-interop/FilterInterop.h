#pragma once
#include <Windows.h>
#include "Imagem.h"
#using <WindowsBase.dll>
#using <mscorlib.dll> 
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#include <TelaVR.h>
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
		void SetImagem(Imagem^ imgCarregada);
		void Resize(int w, int h);

	};
}