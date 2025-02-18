#pragma once
#include "Converter.h"

class MixerConverter : public Converter {
public:

	MixerConverter(const std::vector<int16_t>& additionalStream, int insertPosition, int sampleRate);

	std::vector<int16_t> process(const std::vector<int16_t>& input) override;

private:
	std::vector<int16_t> additionalStream_;
	size_t insertSample_;
};

