#pragma once
#include "Converter.h"

class MuteConverter : public Converter {

public:
	MuteConverter(int start, int end, int sampleRate);
	std::vector<int16_t> process(const std::vector<int16_t>& input) override;

private:
	size_t startSample_ = 0;
	size_t endSample_ = 0;
};