#include "Challenge_02.h"

Challenge_02::Challenge_02() {}

Challenge_02::~Challenge_02() {}

void Challenge_02::Run()
{
	P1();
	P2();
}

void Challenge_02::P1()
{
	auto lines = TxtFileGetLines("./Day_02/Input_02.txt");

	regex rgxDigit("[\\d]+");
	smatch sm;
	int checkSum = 0;
	for (auto line : lines)
	{
		int maxV = numeric_limits<int>::min();
		int minV = numeric_limits<int>::max();
		while (regex_search(line, sm, rgxDigit))
		{
			auto num = stoi(sm[0]);
			maxV = max(maxV, num);
			minV = min(minV, num);
			line = sm.suffix();
		}
		checkSum += maxV - minV;
	}

	cout << checkSum << endl;
}

void Challenge_02::P2()
{
	auto lines = TxtFileGetLines("./Day_02/Input_02.txt");

	regex rgxDigit("[\\d]+");
	smatch sm;
	int checkSum = 0;
	for (auto line : lines)
	{
		int lineResult = 0;
		vector<int> numbers;
		while (regex_search(line, sm, rgxDigit))
		{
			numbers.push_back(stoi(sm[0]));
			line = sm.suffix();
		}

		for (int i = 0; i < numbers.size() - 1; ++i)
		{
			auto num = numbers[i];
			for (int j = i + 1; j < numbers.size(); ++j)
			{
				auto other = numbers[j];
				float remainder = fmod((float)num, other);
				if (remainder < 1e-5)
				{
					lineResult = num / other;
					break;
				}

				remainder = fmod(other, num);
				if (remainder < 1e-5)
				{
					lineResult = other / num;
					break;
				}
			}
			if (lineResult != 0)
				break;
		}

		checkSum += lineResult;
	}

	cout << checkSum << endl;
}
