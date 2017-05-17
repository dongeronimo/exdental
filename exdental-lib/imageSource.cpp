#include "imageSource.h"
#include <itkMetaDataObject.h>
#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <map>
#include <itkResampleImageFilter.h>
#include <itkAffineTransform.h>
#include <itkOrientImageFilter.h>

template<typename TImage> void DeepCopy(typename TImage::Pointer input, typename TImage::Pointer output)
{
	int inSzX = input->GetLargestPossibleRegion().GetSize()[0];
	int inSzY = input->GetLargestPossibleRegion().GetSize()[1];
	int inSzZ = input->GetLargestPossibleRegion().GetSize()[2];
	double inSpacingX = input->GetSpacing()[0];
	double inSpacingY = input->GetSpacing()[1];
	double inSpacingZ = input->GetSpacing()[2];

	output->SetRegions(input->GetLargestPossibleRegion());
	output->Allocate();

	itk::ImageRegionConstIterator<TImage> inputIterator(input, input->GetLargestPossibleRegion());
	itk::ImageRegionIterator<TImage> outputIterator(output, output->GetLargestPossibleRegion());
	const double inSpacing[] = { inSpacingX, inSpacingY, inSpacingZ };
	output->SetSpacing(inSpacing);
	while (!inputIterator.IsAtEnd())
	{
		outputIterator.Set(inputIterator.Get());
		++inputIterator;
		++outputIterator;
	}
}

double datasource::ImageSource::GetGantryTilt(std::map<std::string, std::string> metadata)
{
	int i = metadata.count("0018|1120");
	if (i != 1)
		return 0.0;
	else
	{
		string _gt = metadata.at("0018|1120");
		return stof(_gt);
	}
}

void datasource::ImageSource::CorrectGantryTilt(itk::Image<short, 3>::Pointer source, std::map<std::string, std::string> metadata)
{
	//Pega o angulo;
	const double tilt = GetGantryTilt(metadata);
	if (tilt <= 0.05)
		return;
	//O filtro não é inplace - isso vai gerar uma inevitável duplicacao de memória. Os dados da saída serão copiados pra Source via
	//minha função de deep copy. 
	typedef itk::ResampleImageFilter<itk::Image<short, 3>, itk::Image<short, 3>> FilterType;
	FilterType::Pointer filter = FilterType::New();
	typedef itk::AffineTransform<double, 3> TransformType;
	TransformType::Pointer transform = TransformType::New();
	typedef itk::LinearInterpolateImageFunction<itk::Image<short, 3>, double> InterpolatorType;
	InterpolatorType::Pointer interpolator = InterpolatorType::New();
	filter->SetInterpolator(interpolator);
	filter->SetDefaultPixelValue(-3000);
	//--Os parametros da saida sao obtidos da entrada
	const itk::Image<short, 3>::SpacingType &spacing = source->GetSpacing();
	const itk::Image<short, 3>::PointType  &origin = source->GetOrigin();
	itk::Image<short, 3>::SizeType size = source->GetLargestPossibleRegion().GetSize();
	filter->SetOutputOrigin(origin);
	filter->SetOutputSpacing(spacing);
	filter->SetOutputDirection(source->GetDirection());
	filter->SetSize(size);
	filter->SetInput(source);

	transform->Shear(1, 2, sin(18 * 0.01745329));
	filter->SetTransform(transform);

	filter->Update();
	itk::Image<short, 3>::Pointer _inp = filter->GetOutput();
	DeepCopy<itk::Image<short, 3>>(_inp, source);
	//return 0;	
}

datasource::ImageSource::ImageSource(callbackDeProgressDaCarga callbackExternoDeCarga)
{
	SetCallbackDeProgesso(callbackExternoDeCarga);
}

datasource::ImageSource::ImageSource()
{
	SetCallbackDeProgesso(nullptr);
}

void datasource::ImageSource::SetCallbackDeProgesso(callbackDeProgressDaCarga cbk)
{
	//Inicializa o callback de carga
	void *ptr = cbk;
	if (ptr)
	{
		handleDoCallbackDeCarga = CallbackProgressoDeCarga::New();
		handleDoCallbackDeCarga->SetCallbackDoDelphi(ptr);
	}
	else
	{
		handleDoCallbackDeCarga = nullptr;
	}
}

void datasource::ImageSource::PushFile(string f)
{
	filePaths.push_back(f);
}

void datasource::ImageSource::ClearList()
{
	filePaths.clear();
}

unique_ptr<datasource::LoadedImage>  datasource::ImageSource::Load(string idExame, string idSerie)
{
	assert("TEM FATIAS???"&&filePaths.size() > 0);
	map<string, string> metadata;
	codigoDeErro = SEM_ERRO_DE_CARGA;
	typedef itk::MetaDataDictionary DictionaryType;
	typedef itk::MetaDataObject< std::string > MetaDataStringType;
	typedef short    PixelType;
	const unsigned int      Dimension = 3;
	typedef itk::Image< PixelType, Dimension >         ImageType;
	typedef itk::ImageSeriesReader< ImageType >        ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	typedef itk::GDCMImageIO       ImageIOType;
	ImageIOType::Pointer dicomIO = ImageIOType::New();
	reader->SetImageIO(dicomIO);
	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	//antes de sair abrindo tudo e tomar exceção se algo não for encontrado testar para cada arquivo fornecido
	////se ele existe. Se não existe, tira da lista
	vector<int> indices_zuados;
	for (unsigned int i = 0; i < filePaths.size(); i++)
	{
		string path = filePaths[i];
		WIN32_FIND_DATA FindFileData;
		HANDLE handle = FindFirstFileA(path.c_str(), &FindFileData);
		int found = handle != INVALID_HANDLE_VALUE;
		if (found)
		{
			FindClose(handle);
		}
		else
		{
			indices_zuados.push_back(i);
		}
	}
	if (indices_zuados.size() > 0)
	{
		codigoDeErro = ERROR_CODE_INDICES_ZUADOS;
		return nullptr;
	}

	for (unsigned int i = 0; i < indices_zuados.size(); i++)
	{
		filePaths.erase(filePaths.begin() + indices_zuados[i]);
	}
	//Pega o tamanho em bytes da série a partir das propriedades da 1a fatia. Esse tamanho será usado para ver
	//se a série caberá na memória. Como o sistema está limitado a 4gb devido a ser 32 bits e uma série sendo 
	//renderizada na tela ocupa 2.7 seu tamanho original o sistema se recusará a cerregar algo maior que 900mb
	ReaderType::Pointer singleFileReader = ReaderType::New();
	singleFileReader->SetFileName(filePaths[0]);
	singleFileReader->Update();
	//const DictionaryType& singleImageDictionary = singleFileReader->GetMetaDataDictionary();
	ImageType::Pointer singleImage = singleFileReader->GetOutput();
	int x = singleImage->GetLargestPossibleRegion().GetSize()[0];
	int y = singleImage->GetLargestPossibleRegion().GetSize()[1];
	long sizeInBytes = x * y * filePaths.size() * sizeof(short);
	const long maxMemSizeInBytes = 900 * 1024 * 1024;
	if (sizeInBytes > maxMemSizeInBytes)
	{
		codigoDeErro = ERROR_CODE_OOM;
		return nullptr;
	}
	//Lê a série
	reader->SetFileNames(filePaths);
	try
	{
		//So devo adicionar um listener de progresso se tenho listener e só tenho listener
		//se um callback para a função que trata o progresso for imformada.
		if (handleDoCallbackDeCarga)
		{
			reader->AddObserver(itk::ProgressEvent(), handleDoCallbackDeCarga);
		}
		reader->Update();
	}
	catch (itk::ExceptionObject& ex)
	{
		string erro = ex.GetDescription();
		if (erro == "Cannot read requested file")
		{
			codigoDeErro = ERROR_FALHA_NA_LEITURA;
			return nullptr;
		}
	}
	//ptrImg é o que será retornado.
	itk::Image<short, 3>::Pointer ptrImg = reader->GetOutput();
	const DictionaryType& dictionary = dicomIO->GetMetaDataDictionary();
	DictionaryType::ConstIterator metadataDictionaryIterator = dictionary.Begin();
	DictionaryType::ConstIterator metadataDictionaryEnd = dictionary.End();
	std::cout << "tags dicom" << std::endl;
	typedef itk::MetaDataObject< std::string > MetaDataStringType;

	while (metadataDictionaryIterator != metadataDictionaryEnd)
	{
		itk::MetaDataObjectBase::Pointer entry = metadataDictionaryIterator->second;
		MetaDataStringType::Pointer entryValue = dynamic_cast<MetaDataStringType*>(entry.GetPointer());
		if (entryValue)
		{
			string tagkey = metadataDictionaryIterator->first;
			string labelId;
			string tagvalue = entryValue->GetMetaDataObjectValue();
			std::cout << tagkey << " = " << tagvalue << endl;
			metadata.insert(make_pair(tagkey, tagvalue));
		}
		++metadataDictionaryIterator;
	}
	typedef itk::OrientImageFilter<ImageType, ImageType> TOrientImageFilter;
	TOrientImageFilter::Pointer reorientador = nullptr;
	reorientador = TOrientImageFilter::New();
	reorientador->SetInput(ptrImg);
	reorientador->UseImageDirectionOn();
	reorientador->SetDesiredCoordinateOrientation(itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RIP);
	reorientador->Update();
	DeepCopy<itk::Image<short, 3>>(reorientador->GetOutput(), ptrImg);
	CorrectGantryTilt(ptrImg, metadata);
	return make_unique<LoadedImage>(ptrImg, metadata, dictionary, idExame, idSerie);
}
