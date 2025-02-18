#include "ConfigInput.h"

ConfigInput::ConfigInput(const std::string& filename) {
	ParseConfig(filename);
}

void ConfigInput::ParseConfig(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open config file:" + filename);
	}

	std::string line;
	while (std::getline(file, line)) {

		if (line.empty() || line[0] == '#') {
			continue;
		}

		line.erase(0, line.find_first_not_of(' '));
		line.erase(line.find_last_not_of(' ') + 1);

		config.push_back(line);
	}

	file.close();
}

std::vector<std::string> ConfigInput::getConfigLines()
{
	return config;
}
