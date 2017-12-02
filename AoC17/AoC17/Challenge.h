#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

class Challenge
{
public:
	Challenge(){}
	virtual ~Challenge(){}
	virtual void Run() = 0;

protected:
	string TxtFileToString(const char* filePath) const;
	vector<string> TxtFileGetLines(const char* filePath) const;

private:
	Challenge(const Challenge& o) = delete;
	Challenge& operator= (const Challenge& o) = delete;
};

inline string Challenge::TxtFileToString(const char* filePath) const
{
	ifstream file(filePath);
	if (!file.is_open())
		return false;
	stringstream r;
	r << file.rdbuf();
	auto s = r.str();
	return s;
}

inline vector<string> Challenge::TxtFileGetLines(const char* filePath) const
{
	vector<string> inputs;
	ifstream input(filePath);
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			inputs.push_back(line);
		}
	}
	else
		cout << "Failed to open " << filePath << endl;

	return inputs;
}
