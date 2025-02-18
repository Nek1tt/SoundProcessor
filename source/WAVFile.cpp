#include "WAVFile.h"

WAVFile::WAVFile(const std::string& filename)
{
	read(filename);
}

void WAVFile::read(const std::string& filename)
{
	std::ifstream inFile(filename, std::ios::binary);

	if (!inFile.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	inFile.read(reinterpret_cast<char*>(&header), 7 * sizeof(uint32_t) + 4 * sizeof(uint16_t));

	sampleRate = header.sampleRate;
	NumChannels = header.numChannels;
	BitsPerSample = header.bitsPerSample;

	while (true)
	{
		char chunkID[4];
		uint32_t chunkSize;
		inFile.read(chunkID, sizeof(uint32_t));
		inFile.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));
		if (chunkID[0] == 'd' || chunkID[1] == 'a' || chunkID[2] == 't' || chunkID[3] == 'a')
		{
			header.subchunk2Id[0] = chunkID[0];
			header.subchunk2Id[1] = chunkID[1];
			header.subchunk2Id[2] = chunkID[2];
			header.subchunk2Id[3] = chunkID[3];
			header.subchunk2Size = chunkSize;
			break;
		}
		else
		{
			inFile.seekg(chunkSize, std::ios::cur);
		}
	}

	data.resize(header.subchunk2Size / sizeof(int16_t));
	inFile.read(reinterpret_cast<char*>(data.data()), header.subchunk2Size);

	inFile.close();
}
void WAVFile::write(const std::string& filename)
{
	std::ofstream outFile(filename, std::ios::binary);

	if (!outFile.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + filename);
	}

	header.subchunk2Size = data.size() * sizeof(int16_t);
	outFile.write(reinterpret_cast<char*>(&header), sizeof(header));
	outFile.write(reinterpret_cast<char*>(data.data()), header.subchunk2Size);

	outFile.close();
}

std::vector<int16_t> WAVFile::getData()
{
	return data;
}

void WAVFile::setData(const std::vector<int16_t>& newData)
{
	data = newData;
	header.subchunk2Size = data.size() * sizeof(int16_t);
	header.chunkSize = sizeof(header) + header.subchunk2Size - 8;
}

int WAVFile::getSampleRate()
{
	return sampleRate;
}

int WAVFile::getNumChannels()
{
	return NumChannels;
}

int WAVFile::getBitsPerSample()
{
	return BitsPerSample;
}