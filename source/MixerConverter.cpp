#include "MixerConverter.h"

MixerConverter::MixerConverter(const std::vector<int16_t>& additionalStream, int insertPosition, int sampleRate) : additionalStream_(additionalStream), insertSample_(insertPosition * sampleRate) {}

std::vector<int16_t> MixerConverter::process(const std::vector<int16_t>& input)
{
	std::vector<int16_t> output = input;
    size_t additionalStreamLength = std::min(additionalStream_.size(), input.size() - insertSample_);

    for (size_t i = 0; i < additionalStreamLength; ++i) {
        if (insertSample_ + i < output.size()) {
            output[insertSample_ + i] = (output[insertSample_ + i] + additionalStream_[i]) / 2;
        }
    }

    return output;
}

