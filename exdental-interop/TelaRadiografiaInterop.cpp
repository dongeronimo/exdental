#include "TelaRadiografiaInterop.h"

namespace geronimo
{
	void TelaRadiografia::SetWL(int w, int l)
	{
		telaRadio->SetWL(w, l);
	}

	TelaRadiografia::TelaRadiografia()
	{
		telaRadio = new geronimo_impl::TelaRadiografia();
	}

	void TelaRadiografia::CreateScreen(Panel^ targetPanel)
	{
		HWND h = reinterpret_cast<HWND>( targetPanel->Handle.ToPointer() );
		telaRadio->CreateScreen(h, targetPanel->Width, targetPanel->Height);
	}

	void TelaRadiografia::SetImagem(Imagem^ imgCarregada)
	{
		telaRadio->ShowImage(imgCarregada->GetImagem());
	}

	void TelaRadiografia::Resize(int w, int h)
	{
		telaRadio->Resize(w, h);
	}

	TelaRadiografia::~TelaRadiografia()
	{
		if (telaRadio)
			delete telaRadio;
	}
}