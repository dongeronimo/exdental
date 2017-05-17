#pragma once
#include <Windows.h>
#include "Imagem.h"
#using <WindowsBase.dll>
#using <mscorlib.dll> 
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#include <TelaRadiografia.h>
using namespace System::Windows::Forms;
namespace geronimo
{
	public ref class TelaRadiografia
	{
	private:
		geronimo_impl::TelaRadiografia* telaRadio;
	public:
		TelaRadiografia();
		~TelaRadiografia();
		void CreateScreen(Panel^ targetPanel);
		void SetImagem(Imagem^ imgCarregada);
		void Resize(int w, int h);
		void SetWL(int w, int l);
	};
}