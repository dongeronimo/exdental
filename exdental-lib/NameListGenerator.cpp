#include "NameListGenerator.h"
#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImage.h>
namespace datasource
{
	std::vector<NameListGenerator::SliceList> NameListGenerator::CreateList(const char* path, std::vector<std::string>& outSeriesIdentifiers)
	{
		float prog = 0;
		if (cbk) cbk(prog);
		std::vector<SliceList> result;
		const char* source_dir = path;
		typedef itk::Image< short, 3 >         ImageType;
		typedef itk::ImageSeriesReader< ImageType >        ReaderType;
		ReaderType::Pointer reader = ReaderType::New();
		typedef itk::GDCMImageIO       ImageIOType;
		ImageIOType::Pointer dicomIO = ImageIOType::New();
		reader->SetImageIO(dicomIO);
		typedef itk::GDCMSeriesFileNames NamesGeneratorType;
		NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
		nameGenerator->SetUseSeriesDetails(true);
		nameGenerator->SetDirectory(source_dir);
		typedef std::vector< std::string >    SeriesIdContainer;
		const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
		if (cbk) cbk(0.75);
		int i = 0;
		//Gera os arquivos de saída pra cada serie
		SeriesIdContainer::const_iterator seriesListIt = seriesUID.begin();
		SeriesIdContainer::const_iterator seriesListEndId = seriesUID.end();
		while (seriesListIt != seriesListEndId)
		{
			SliceList currentList;
			std::string seriesIdentifier = seriesListIt->c_str();
			outSeriesIdentifiers.push_back(seriesIdentifier);

			typedef std::vector< std::string >   FileNamesContainer;
			FileNamesContainer fileNames = nameGenerator->GetFileNames(seriesIdentifier);
			reader->SetFileNames(fileNames);
			for (int i = 0; i < fileNames.size(); i++)
			{
				std::string _s = fileNames[i];
				currentList.push_back(_s);
			}
			++seriesListIt;
			result.push_back(currentList);
			i++;
			

		}
		if (cbk) cbk(1.0);
		return result;
	}
}