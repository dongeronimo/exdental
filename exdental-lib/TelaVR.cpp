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
	void TelaVR::ShowImage(vtkSmartPointer<vtkProp3D> s)
	{
		assert(renderWindow);
		this->source = s;
		renderer->AddActor(source);
		renderer->ResetCamera();
		renderer->GetActiveCamera()->ParallelProjectionOn();
		renderer->Render();
	}

}