#include "Challenge_17.h"

Challenge_17::Challenge_17() {}
Challenge_17::~Challenge_17() {}

void Challenge_17::Run()
{
	P2();
}

void Challenge_17::P1()
{
	int steps = 376;
	vector<int> spinLock;
	spinLock.push_back(0);
	int currentPos = 0;
	for (int i = 0; i < 2017; ++i)
	{
		int insertPos = (currentPos + steps) % spinLock.size();
		spinLock.insert(spinLock.begin() + insertPos + 1, i+1);
		currentPos = insertPos + 1;
	}

	cout << spinLock[currentPos + 1] << endl;
}

void Challenge_17::P2()
{
	int steps = 376;
	int currentPos = 0;
	int spinLockSize = 1;
	int value = 0;
	for (int i = 0; i < 50000000; ++i)
	{
		int insertPos = (currentPos + steps) % spinLockSize;
		currentPos = insertPos + 1;
		if (insertPos == 0)
			value = i + 1;

		++spinLockSize;
	}

	cout << value << endl;
}
