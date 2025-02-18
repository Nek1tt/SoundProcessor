#pragma once
#include "Converter.h"


class EchoConverter : public Converter {
public:
	EchoConverter(int start, int end, int delay, float decay, int sampleRate);

	std::vector<int16_t> process(const std::vector<int16_t>& input) override;

private:
	size_t startSample_;
	size_t endSample_;
	int delay_;
	float decay_;
};