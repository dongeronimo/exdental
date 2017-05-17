#pragma once
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkWin32RenderWindowInteractor.h>
#include "TelaRadiografiaInteractionStyle.h"
#include "loadedImage.h"
#include "pipeline.h"
#include <memory>
namespace geronimo_impl
{
	class TelaRadiografia
	{
	private:
		vtkSmartPointer<vtkRenderer> rendererRadiografia;
		vtkSmartPointer<vtkWin32OpenGLRenderWindow> renderWindow;
		vtkSmartPointer<vtkWin32RenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<TelaRadiografiaInteractionStyle> interactorStyle;
		std::unique_ptr<Pipeline> pipe;
		std::shared_ptr<datasource::LoadedImage> imagem;
	public:
		TelaRadiografia();
		void SetWL(int w, int l);
		void Resize(int w, int h);
		void CreateScreen(HWND handle, int w, int h);
		void ShowImage(std::shared_ptr<datasource::LoadedImage> qual);
	};
}