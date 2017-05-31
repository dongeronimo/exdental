#pragma once
#include <memory>
#include <vtkProp3D.h>
#include <vtkSmartPointer.h>
#include "pipeline.h"

namespace geronimo_impl
{
	class IScreen
	{
	public:
		virtual ~IScreen(){}
		virtual void Resize(int w, int h) = 0;
		virtual void CreateScreen(HWND handle, int w, int h) = 0;
		virtual void ShowImage(vtkSmartPointer<vtkProp3D> s) = 0;
	};
}
