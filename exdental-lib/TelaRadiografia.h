#pragma once
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkWin32RenderWindowInteractor.h>
#include "TelaRadiografiaInteractionStyle.h"
#include "loadedImage.h"
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
		std::shared_ptr<Pipeline> pipe;
	public:
		TelaRadiografia();
		void SetWL(int w, int l);
		void Resize(int w, int h);
		void CreateScreen(HWND handle, int w, int h);
		void ShowImage(std::shared_ptr<Pipeline> pipe)override;
		
	};
}
