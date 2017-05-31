#pragma once
#include "IScreen.h"
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkWin32RenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
namespace geronimo_impl
{
	class TelaVR:public IScreen
	{
	private:
		vtkSmartPointer<vtkProp3D> source;
		vtkSmartPointer<vtkRenderer> renderer;
		vtkSmartPointer<vtkWin32OpenGLRenderWindow> renderWindow;
		vtkSmartPointer<vtkWin32RenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle;
		
	public:
		TelaVR();
		void Resize(int w, int h) override;
		void CreateScreen(HWND handle, int w, int h) override;
		void ShowImage(vtkSmartPointer<vtkProp3D> s) override;
		
	};
}
