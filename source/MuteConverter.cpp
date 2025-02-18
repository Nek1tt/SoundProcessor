#include "MuteConverter.h"

MuteConverter::MuteConverter(int start, int end, int sampleRate) : startSample_(start * sampleRate), endSample_(end * sampleRate) {}

std::vector<int16_t> MuteConverter::process(const std::vector<int16_t>& input)
{
	std::vector<int16_t> output = input;
	size_t startIndex = std::min(startSample_, output.size());
	size_t endIndex = std::min(endSample_, output.size());
	for (size_t i = startIndex; i < endIndex; ++i)
	{
		output[i] = 0;
	}
	return output;
}