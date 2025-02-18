#pragma once
#include "SoundProcessor.h"

class WAVFile {
public:

	WAVFile(const std::string& filename);
	void write(const std::string& filename);
	std::vector<int16_t> getData();
	void setData(const std::vector<int16_t>& data);
	int getSampleRate();
	int getNumChannels();
	int getBitsPerSample();

private:
	void read(const std::string& filename);
	std::vector<int16_t> data;
	uint32_t sampleRate;
	uint16_t NumChannels;
	uint16_t BitsPerSample;
	struct WAVheader
	{
		char chunkId[4];
		uint32_t chunkSize{ 0 };
		char format[4];
		char subchunk1Id[4];
		uint32_t subchunk1Size{ 0 };
		uint16_t audioFormat{ 0 };
		uint16_t numChannels{ 0 };
		uint32_t sampleRate{ 0 };
		uint32_t byteRate{ 0 };
		uint16_t blockAlign{ 0 };
		uint16_t bitsPerSample{ 0 };
		char subchunk2Id[4];
		uint32_t subchunk2Size{ 0 };
	};
	WAVheader header;
};