#pragma once
#include <vector>
#include <string>
#include "CallbackProgressoDeCarga.h"

namespace datasource
{
	class NameListGenerator
	{
	private:
		callbackDeProgressDaCarga cbk;
	public:
		typedef std::vector<std::string> SliceList;
		NameListGenerator()
		{
			cbk = nullptr;
		}
		void SetCallbackDeProgresso(callbackDeProgressDaCarga cbk)
		{
			this->cbk = cbk;
		}
		std::vector<SliceList> CreateList(const char* path, std::vector<std::string>& outSeriesIdentifiers);
	};
}
