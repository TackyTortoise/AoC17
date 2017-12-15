#include "Challenge_15.h"

Challenge_15::Challenge_15() {}
Challenge_15::~Challenge_15() {}

void Challenge_15::Run()
{
	P2();
}

void Challenge_15::P1()
{
	long long valueA = 699;
	long long valueB = 124;
	Generator genA(16807);
	Generator genB(48271);

	unsigned matchCount = 0;

	for (int i = 0; i < 40000000; ++i)
	{
		valueA = genA.GenerateNumber(valueA);
		valueB = genB.GenerateNumber(valueB);
		unsigned lowA = valueA & 0xFFFF;
		unsigned lowB = valueB & 0xFFFF;
		if (lowA == lowB)
			++matchCount;
	}

	cout << matchCount << endl;
}

void Challenge_15::P2()
{
	long long valueA = 699;
	long long valueB = 124;
	Generator genA(16807);
	Generator genB(48271);

	unsigned matchCount = 0;

	for (int i = 0; i < 5000000; ++i)
	{
		do
		{
			valueA = genA.GenerateNumber(valueA);
		} while (valueA % 4 != 0);
		do
		{
				valueB = genB.GenerateNumber(valueB);
		} while (long long(valueB % 8) != 0);
		unsigned lowA = valueA & 0xFFFF;
		unsigned lowB = valueB & 0xFFFF;
		if (lowA == lowB)
			++matchCount;
	}
	
	cout << matchCount << endl;
}
