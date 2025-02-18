#pragma once
#include "WAVFile.h"
#include "MuteConverter.h"
#include "MixerConverter.h"
#include "EchoConverter.h"

struct ConverterParams {
    std::string configLine;
    int sampleRate;
    std::vector<std::string> streams;
};

class ConverterFactory {
public:
    virtual std::unique_ptr<Converter> createConverter(const ConverterParams& params) = 0;
    virtual ~ConverterFactory() = default;
};

class MuteConverterFactory : public ConverterFactory {
public:
    std::unique_ptr<Converter> createConverter(const ConverterParams& params) override;
};

class MixerConverterFactory : public ConverterFactory {
public:
    std::unique_ptr<Converter> createConverter(const ConverterParams& params) override;
};

class EchoConverterFactory : public ConverterFactory {
public:
    std::unique_ptr<Converter> createConverter(const ConverterParams& params) override;
};
