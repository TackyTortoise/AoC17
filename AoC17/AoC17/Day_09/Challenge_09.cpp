#include "Challenge_09.h"

Challenge_09::Challenge_09() {}
Challenge_09::~Challenge_09() {}

void Challenge_09::Run()
{
	P1();
	P2();
}

void Challenge_09::P1()
{
	auto input = TxtFileToString("./Day_09/Input_09.txt");
	input = RemoveGarbage(input);
	cout << input << endl;
	cout << GetGroupScore(input, 0) << endl;
}

void Challenge_09::P2()
{
	auto input = TxtFileToString("./Day_09/Input_09.txt");
	cout << GetGarbageSize(input) << endl;
}

string Challenge_09::RemoveGarbage(const string& group) const
{
	auto str = group;
	auto garbageStart = str.find('<');
	while (garbageStart != string::npos)
	{
		auto garbageEnd = str.find('>', garbageStart);
		//See if '>' is valid
		while (garbageEnd != string::npos)
		{
			bool inValid = false;
			int prevIndex = garbageEnd - 1;
			while (str[prevIndex] == '!')
			{
				inValid = !inValid;
				--prevIndex;
			}

			//Find next '>' if not valid
			if (inValid)
				garbageEnd = str.find('>', garbageEnd + 1);
			else
				break;
		}

		//Found garbage end
		//Remove piece of garbage
		str.erase(garbageStart, garbageEnd - garbageStart + 1);
		//Look for possible other garbage
		garbageStart = str.find('<');
	}

	return str;
}

int Challenge_09::GetGroupScore(const string& group, int parentScore) const
{
	auto str = group;
	auto open = str.find('{');
	auto firstClose = str.find('}');
	auto nextOpen = str.rfind('{', firstClose);
	//Found group in group
	int childScores = 0;
	while (nextOpen > open)
	{
		string depthCheckStr = str.substr(open + 1, nextOpen - open - 1);
		int extraDepth = count_if(depthCheckStr.begin(), depthCheckStr.end(), [](char c) {return c == '{'; });

		auto child = str.substr(nextOpen + 1, firstClose - nextOpen - 1);
		childScores += GetGroupScore(child, parentScore + 1 + extraDepth);

		//Recheck after child manipulation
		firstClose = str.find('}');
		nextOpen = str.rfind('{', firstClose);
		str.erase(nextOpen, firstClose - nextOpen + 1);

		firstClose = str.find('}');
		nextOpen = str.rfind('{', firstClose);
	}
	return childScores + parentScore + 1;
}

int Challenge_09::GetGarbageSize(const string& group) const
{
	auto str = group;
	auto garbageStart = str.find('<');
	vector<string> garbagePieces;
	while (garbageStart != string::npos)
	{
		auto garbageEnd = str.find('>', garbageStart);
		//Invalid end
		while (garbageEnd != string::npos)
		{
			bool inValid = false;
			int prevIndex = garbageEnd - 1;
			while (str[prevIndex] == '!')
			{
				inValid = !inValid;
				--prevIndex;
			}

			//Find next '>'
			if (inValid)
				garbageEnd = str.find('>', garbageEnd + 1);
			else
				break;
		}

		//Found garbage end
		garbagePieces.push_back(str.substr(garbageStart + 1, garbageEnd - garbageStart - 1));
		str.erase(garbageStart, garbageEnd - garbageStart + 1);
		garbageStart = str.find('<');
	}

	int tgs = 0;
	for (string gp : garbagePieces)
	{
		for (int i = 0; i < gp.size(); ++i)
		{
			if (gp[i] == '!')
			{
				++i;
				continue;
			}

			++tgs;
		}
	}

	return tgs;
}
