#pragma once
#include "SoundProcessor.h"

class ConfigInput
{
public:
	ConfigInput(const std::string& filename);
	std::vector<std::string> getConfigLines();
private:
	std::vector<std::string> config;
	void ParseConfig(const std::string& filename);
};

