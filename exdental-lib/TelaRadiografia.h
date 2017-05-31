#pragma once
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkWin32RenderWindowInteractor.h>
#include "TelaRadiografiaInteractionStyle.h"
#include <vtkImageImport.h>
#include "pipeline.h"
#include <memory>
#include "IScreen.h"

namespace geronimo_impl
{
	class TelaRadiografia : public IScreen
	{
	private:
		vtkSmartPointer<vtkRenderer> rendererRadiografia;
		vtkSmartPointer<vtkWin32OpenGLRenderWindow> renderWindow;
		vtkSmartPointer<vtkWin32RenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<TelaRadiografiaInteractionStyle> interactorStyle;
		vtkSmartPointer<vtkProp3D> source;
	public:
		TelaRadiografia();
		void SetWL(int w, int l);
		void Resize(int w, int h);
		void CreateScreen(HWND handle, int w, int h);
		void ShowImage(vtkSmartPointer<vtkProp3D> s)override;
		
	};
}
