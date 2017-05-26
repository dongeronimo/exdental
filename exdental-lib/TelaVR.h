#pragma once
#include "IScreen.h"
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkWin32RenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include "pipeline.h"
namespace geronimo_impl
{
	class TelaVR:public IScreen
	{
	private:
		std::shared_ptr<Pipeline> pipe;
		vtkSmartPointer<vtkRenderer> renderer;
		vtkSmartPointer<vtkWin32OpenGLRenderWindow> renderWindow;
		vtkSmartPointer<vtkWin32RenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle;
		
	public:
		TelaVR();
		void Resize(int w, int h) override;
		void CreateScreen(HWND handle, int w, int h) override;
		void ShowImage(std::shared_ptr<Pipeline> pipe) override;
		
	};
}
