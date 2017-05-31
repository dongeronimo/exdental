#include "TelaVRInterop.h"

namespace geronimo
{


	TelaVR::TelaVR()
	{
		telaVR = new geronimo_impl::TelaVR();
	}

	void TelaVR::CreateScreen(Panel^ targetPanel)
	{
		HWND h = reinterpret_cast<HWND>(targetPanel->Handle.ToPointer());
		telaVR->CreateScreen(h, targetPanel->Width, targetPanel->Height);
	}

	void TelaVR::SetImagem(Image^ im)
	{
		telaVR->ShowImage(im->GetPipeline()->GetVolumeActor());
	}

	void TelaVR::Resize(int w, int h)
	{
		telaVR->Resize(w, h);
	}

	TelaVR::~TelaVR()
	{
		if (telaVR)
			delete telaVR;
	}
}