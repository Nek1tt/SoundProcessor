#include "ConverterFactory.h"

std::unique_ptr<Converter> MuteConverterFactory::createConverter(const ConverterParams& params) {
    std::istringstream iss(params.configLine);
    std::string type;
    int start, end;

    iss >> type;
    if (type != "mute") {
        throw std::runtime_error("Invalid config line for MuteConverter: " + params.configLine);
    }

    iss >> start >> end;

    if (!iss) {
        throw std::runtime_error("Invalid parameters in config line: " + params.configLine);
    }

    return std::make_unique<MuteConverter>(start, end, params.sampleRate);
}

std::unique_ptr<Converter> MixerConverterFactory::createConverter(const ConverterParams& params) {
    std::istringstream iss(params.configLine);
    std::string streamRef;
    std::string type;
    int insertPosition;

    iss >> type;
    if (type != "mix") {
        throw std::runtime_error("Invalid config line for MixConverter: " + params.configLine);
    }

    iss >> streamRef >> insertPosition;
    int streamIndex = std::stoi(streamRef.substr(1));

    if (streamIndex < 0 || streamIndex > params.streams.size())
    {
        throw std::runtime_error("Invalid index of mix file");
    }

    WAVFile addStream(params.streams[streamIndex]);
    std::vector<int16_t> addData = addStream.getData();

    return std::make_unique<MixerConverter>(addData, insertPosition, params.sampleRate);
}

std::unique_ptr<Converter> EchoConverterFactory::createConverter(const ConverterParams& params) 
{
    std::istringstream iss(params.configLine);
    std::string type;
    int start, end;

    iss >> type;
    if (type != "echo") {
        throw std::runtime_error("Invalid config line for EchoConverter: " + params.configLine);
    }

    iss >> start >> end;

    if (!iss) {
        throw std::runtime_error("Invalid parameters in config line: " + params.configLine);
    }

    return std::make_unique<EchoConverter>(start, end, 44100, 0.5, params.sampleRate);
}