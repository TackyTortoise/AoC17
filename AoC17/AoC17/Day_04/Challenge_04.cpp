#include "Challenge_04.h"

Challenge_04::Challenge_04() {}

Challenge_04::~Challenge_04() {}

void Challenge_04::Run()
{
	P1();
	P2();
}

void Challenge_04::P1()
{
	auto input = TxtFileGetLines("./Day_04/Input_04.txt");
	int totalValid = 0;
	regex rgx("[\\a+]");
	smatch sm;
	for (int i = 0; i < input.size(); ++i)
	{
		vector<string> found;
		string line = input[i];
		bool valid = true;
		
		auto splits = SplitString(line, ' ');
		for(auto s : splits)
		{
			if (find(found.begin(), found.end(), s) != found.end())
			{
				valid = false;
				break;
			}

			found.push_back(s);
		}

		if (valid)
			++totalValid;
	}

	cout << totalValid << endl;
}

void Challenge_04::P2()
{
	auto input = TxtFileGetLines("./Day_04/Input_04.txt");
	int totalValid = 0;
	regex rgx("[\\a+]");
	smatch sm;
	for (int i = 0; i < input.size(); ++i)
	{
		vector<string> found;
		string line = input[i];
		bool valid = true;

		auto splits = SplitString(line, ' ');
		for (auto s : splits)
		{
			sort(s.begin(), s.end());
			if (find(found.begin(), found.end(), s) != found.end())
			{
				valid = false;
				break;
			}

			found.push_back(s);
		}

		if (valid)
			++totalValid;
	}

	cout << totalValid << endl;
}
