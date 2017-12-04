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
	vector<string> SplitString(const string& str, char splitChar) const;
	vector<string> SplitStringRgx(const string& str) const;

	virtual void P1() {}
	virtual void P2() {}

private:
	Challenge(const Challenge& o) = delete;
	Challenge& operator= (const Challenge& o) = delete;
};

inline string Challenge::TxtFileToString(const char* filePath) const
{
	ifstream file(filePath);
	if (!file.is_open())
		return nullptr;
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

inline vector<string> Challenge::SplitString(const string& str, char splitChar) const
{
	vector<string> result;
	string copyStr = str;
	auto pos = copyStr.find(splitChar);
	int prevPos = 0;
	while (pos != string::npos)
	{
		result.push_back(copyStr.substr(prevPos, pos - prevPos));
		copyStr = copyStr.substr(pos + 1);
		pos = copyStr.find(splitChar);
	}
	result.push_back(copyStr);
	return result;
}

inline vector<string> Challenge::SplitStringRgx(const string& str) const
{
	vector<string> result;
	string copyStr = str;
	regex rgx("\\b\\w+\\b");
	smatch sm;
	while (regex_search(copyStr, sm, rgx))
	{
		result.push_back(sm[0].str());
		copyStr = sm.suffix();
	}
	return result;
}


