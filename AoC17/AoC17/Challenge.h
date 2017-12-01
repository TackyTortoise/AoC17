#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Challenge
{
public:
	Challenge(){}
	virtual ~Challenge(){}
	virtual void Run() = 0;

protected:
	std::string TxtFileToString(const char* filePath);

private:
	Challenge(const Challenge& o) = delete;
	Challenge& operator= (const Challenge& o) = delete;
};

inline std::string Challenge::TxtFileToString(const char* filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
		return false;
	std::stringstream r;
	r << file.rdbuf();
	auto s = r.str();
	return s;
}
