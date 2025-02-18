#pragma once
#include "SoundProcessor.h"

class Converter {

public:
	virtual ~Converter() = default;
	virtual std::vector<int16_t> process(const std::vector<int16_t>& input) = 0;
};