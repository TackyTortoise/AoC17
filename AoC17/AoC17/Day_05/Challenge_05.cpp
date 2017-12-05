#include "Challenge_05.h"

Challenge_05::Challenge_05() {}

Challenge_05::~Challenge_05() {}

void Challenge_05::Run()
{
	P1();
	P2();
}

void Challenge_05::P1()
{
	auto strInput = TxtFileGetLines("./Day_05/Input_05.txt");
	vector<int> nums;
	for_each(strInput.begin(), strInput.end(), [&](string x) {nums.push_back(stoi(x)); });
	int index = 0;
	int steps = 0;
	while (index >= 0 && index < nums.size())
	{
		int value = nums[index];
		++nums[index];
		index += value;

		++steps;
	}
	cout << steps << endl;
}

void Challenge_05::P2()
{
	auto strInput = TxtFileGetLines("./Day_05/Input_05.txt");
	vector<int> nums;
	for_each(strInput.begin(), strInput.end(), [&](string x) {nums.push_back(stoi(x)); });
	int index = 0;
	int steps = 0;
	while (index >= 0 && index < nums.size())
	{
		int value = nums[index];
		if (value < 3)
			++nums[index];
		else
			--nums[index];
		index += value;

		++steps;
	}
	cout << steps << endl;
}
