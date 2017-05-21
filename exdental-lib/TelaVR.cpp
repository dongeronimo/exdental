#include "TelaVR.h"
#include <vtkCamera.h>
namespace geronimo_impl
{
	TelaVR::TelaVR()
	{
		renderer = nullptr;
		renderWindow = nullptr;
		renderWindowInteractor = nullptr;
		interactorStyle = nullptr;
		pipe = nullptr;
	}
	void TelaVR::Resize(int w, int h)
	{
		if (!renderWindow)
			return;
		renderWindow->SetSize(w, h);
		renderWindow->Render();
	}
	void TelaVR::CreateScreen(HWND handle, int w, int h)
	{
		renderWindow = vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();
		renderWindow->SetParentId(handle);
		renderer = vtkSmartPointer<vtkRenderer>::New();
		renderWindow->AddRenderer(renderer);
		renderWindowInteractor = vtkSmartPointer<vtkWin32RenderWindowInteractor>::New();
		renderWindow->SetInteractor(renderWindowInteractor);
		renderWindowInteractor->Initialize();
		renderWindowInteractor->Enable();
		renderWindowInteractor->InstallMessageProcOff();
		this->Resize(w, h);
		interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
		renderWindowInteractor->SetInteractorStyle(interactorStyle);

	}
	void TelaVR::ShowImage(std::shared_ptr < datasource::LoadedImage > qual)
	{
		assert(renderWindow);
		imagem = qual;
		pipe = std::make_unique<Pipeline>(imagem->GetImage(), imagem->GetMetadata());
		renderer->AddActor(pipe->GetVRActor());
		renderer->ResetCamera();
		renderer->GetActiveCamera()->ParallelProjectionOn();
		renderer->Render();
	}

}