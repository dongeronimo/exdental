#pragma once
#include <Windows.h>
#using <WindowsBase.dll>
#using <mscorlib.dll> 
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#include <TelaRadiografia.h>
#include "Image.h"
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
		void SetImagem(Image^ im);
		void Resize(int w, int h);
		void SetWL(int w, int l);
	};
}