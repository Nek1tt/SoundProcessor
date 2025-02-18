#include "EchoConverter.h"

EchoConverter::EchoConverter(int start, int end, int delay, float decay, int sampleRate)
    : startSample_(start * sampleRate),
    endSample_(end * sampleRate),
    delay_(delay),
    decay_(decay) {
    if (startSample_ < 0 || endSample_ < 0 || delay_ <= 0) {
        throw std::invalid_argument("Invalid start, end, or delay values");
    }
    if (decay_ < 0.0f || decay_ > 1.0f) {
        throw std::invalid_argument("Decay must be between 0.0 and 1.0");
    }
}

std::vector<int16_t> EchoConverter::process(const std::vector<int16_t>& input) {
    std::vector<int16_t> output = input;

    size_t effectiveEndSample = std::min(static_cast<int>(endSample_), static_cast<int>(input.size()));

    for (size_t i = startSample_; i < effectiveEndSample; ++i) {
        if (i >= delay_) {
            int32_t value = static_cast<int32_t>(output[i]) +
                static_cast<int32_t>(input[i - delay_]) * decay_;
            output[i] = static_cast<int16_t>(std::clamp(value, -32768, 32767));
        }
    }

    return output;
}


