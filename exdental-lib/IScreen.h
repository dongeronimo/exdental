#pragma once
#include <memory>
#include "loadedImage.h"

namespace geronimo_impl
{
	class IScreen
	{
	public:
		virtual ~IScreen(){}
		virtual void Resize(int w, int h) = 0;
		virtual void CreateScreen(HWND handle, int w, int h) = 0;
		virtual void ShowImage(std::shared_ptr < datasource::LoadedImage > qual) = 0;
	};
}
