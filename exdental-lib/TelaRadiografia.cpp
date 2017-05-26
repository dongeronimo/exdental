#include "TelaRadiografia.h"
#include <vtkCamera.h>
namespace geronimo_impl
{
	void TelaRadiografia::SetWL(int w, int l)
	{
		pipe->SetWL(w, l);
		renderWindow->Render();
	}

	void TelaRadiografia::CreateScreen(HWND handle, int w, int h)
	{
		renderWindow = vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();
		renderWindow->SetParentId(handle);
		rendererRadiografia = vtkSmartPointer<vtkRenderer>::New();
		renderWindow->AddRenderer(rendererRadiografia);
		renderWindowInteractor = vtkSmartPointer<vtkWin32RenderWindowInteractor>::New();
		renderWindow->SetInteractor(renderWindowInteractor);
		renderWindowInteractor->Initialize();
		renderWindowInteractor->Enable();
		renderWindowInteractor->InstallMessageProcOff();
		this->Resize(w, h);
		interactorStyle = vtkSmartPointer<TelaRadiografiaInteractionStyle>::New();
		renderWindowInteractor->SetInteractorStyle(interactorStyle);
	}

	TelaRadiografia::TelaRadiografia()
	{
		rendererRadiografia = nullptr;
		renderWindow = nullptr;
		renderWindowInteractor = nullptr;
		interactorStyle = nullptr;
	}
	
	void TelaRadiografia::Resize(int w, int h)
	{
		if (!renderWindow)
			return;
		renderWindow->SetSize(w, h);
		renderWindow->Render();
	}

	void TelaRadiografia::ShowImage(std::shared_ptr<Pipeline> pipe)
	{
		assert(renderWindow);
		this->pipe = pipe; //std::make_unique<Pipeline>(imagem->GetImage(), imagem->GetMetadata());
		rendererRadiografia->AddActor(this->pipe->GetResliceActor());
		rendererRadiografia->ResetCamera();
		rendererRadiografia->GetActiveCamera()->ParallelProjectionOn();
		renderWindow->Render();
	}

}