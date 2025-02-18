#include "ConfigInput.h"
#include "ConverterFactory.h"

void printHelp()
{
	std::cout << "[-h] - print help" << std::endl;
	std::cout << "[-c] + <path> - path to config file" << std::endl;
	std::cout << "After config file goes output file in WAV format" << std::endl;
	std::cout << "After output file goes input files in WAV format" << std::endl;
	std::cout << "Example: SoundProcessor.exe -c config.txt output.wav input1.wav input2.wav" << std::endl;
	std::cout << "For more documentation visit https://github.com/Nek1tt/SoundProcessor" << std::endl;
}

int main(int argc, char** argv)
{
	std::vector<std::string> config;
	std::vector<std::string> Streams;
	if (std::string(argv[1]) == "-h")
	{
		printHelp();
		return 0;
	}
	else if (std::string(argv[1]) == "-c")
	{
		ConfigInput configParser(argv[2]);
		config = configParser.getConfigLines();
		for (int i = 3; i < argc; i++)
		{
			Streams.push_back(argv[i]);
		}
	}
	else
	{
		throw std::runtime_error("No config file given");
	}

	const std::string file = Streams[1];
	WAVFile main(file);
	std::vector <int16_t> mainStream = main.getData();

	std::vector<std::unique_ptr<Converter>> converters;

	for (const auto& configLine : config)
	{
		std::istringstream iss(configLine);
		std::string converterType;
		iss >> converterType;

		if (converterType == "mute")
		{
			ConverterParams muteParams{ configLine, main.getSampleRate(), Streams };
			MuteConverterFactory factory;
			converters.push_back(factory.createConverter(muteParams));
		}
		else if (converterType == "mix")
		{
			ConverterParams mixParams{ configLine, main.getSampleRate(), Streams };
			MixerConverterFactory factory;
			converters.push_back(factory.createConverter(mixParams));
		}
		else if (converterType == "echo")
		{
			ConverterParams echoParams{ configLine, main.getSampleRate(), Streams };
			EchoConverterFactory factory;
			converters.push_back(factory.createConverter(echoParams));
		}
		else
		{
			throw std::runtime_error("Unknown converter type: " + converterType);
		}
	}

	for (const auto& converter : converters)
	{
		std::vector<int16_t> newStream = converter->process(main.getData());
		main.setData(newStream);
	}

	main.write(Streams[0]);

	return 0;
}