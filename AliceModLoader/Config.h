#pragma once


class Config
{
public:
	static std::string configPath;

	static void GetAliceFolder();
	static void LoadConfig();
};
