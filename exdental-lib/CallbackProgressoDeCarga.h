#pragma once

#include<itkCommand.h>
#include <itkSmartPointer.h>
#include <itkImageSeriesReader.h>
#include <itkImage.h>

typedef void(__stdcall *callbackDeProgressDaCarga)(float prog);


class CallbackProgressoDeCarga :public itk::Command
{
public:
	typedef CallbackProgressoDeCarga Self;
	typedef itk::SmartPointer<Self> Pointer;
	itkNewMacro(CallbackProgressoDeCarga);
	void* callback;
public:
	void SetCallbackDoDelphi(void* fnptr)
	{
		this->callback = fnptr;
	}
	void Execute(itk::Object* caller, const itk::EventObject & ev)
	{
		itk::ImageSeriesReader<itk::Image<short, 3>>* _caller = (itk::ImageSeriesReader<itk::Image<short, 3>>*)(caller);
		const float progress = _caller->GetProgress();
		typedef void(__stdcall *callback_do_delphi)(float progress); //caller do tipo itkImageSeriesReader. ev do tipo itk::ProgressEvent
		callback_do_delphi fn = nullptr;
		fn = (callback_do_delphi)callback;
		fn(progress);
	}

	void Execute(const itk::Object* caller, const itk::EventObject & ev)
	{
		itk::ImageSeriesReader<itk::Image<short, 3>>* _caller = (itk::ImageSeriesReader<itk::Image<short, 3>>*)(caller);
		const float progress = _caller->GetProgress();
		typedef void(*callback_do_delphi)(float progress); //caller do tipo itkImageSeriesReader. ev do tipo itk::ProgressEvent
		callback_do_delphi fn = nullptr;
		fn = (callback_do_delphi)callback;
		fn(progress);
	}
};