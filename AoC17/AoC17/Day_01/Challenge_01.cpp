#include "Challenge_01.h"

Challenge_01::Challenge_01(){}
Challenge_01::~Challenge_01(){}

void Challenge_01::Run()
{
	P1();
	P2();
}

void Challenge_01::P1()
{
	string input = TxtFileToString("./Day_01/Input_01.txt");
	int total = 0;
	for (int i = 0; i < input.length(); ++i)
	{
		char next;
		if (i == input.length() - 1)
			next = input[0];
		else
			next = input[i + 1];

		if (input[i] == next)
			total += input[i] - '0';
	}
	cout << total << endl;
}

void Challenge_01::P2()
{
	string input = TxtFileToString("./Day_01/Input_01.txt");
	int total = 0;
	int jump = input.length() / 2;
	for (int i = 0; i < input.length(); ++i)
	{
		char next = input[(i + jump) % input.length()];

		if (input[i] == next)
			total += input[i] - '0';
	}
	cout << total << endl;
}
