#pragma once
#include "../Challenge.h"

class Challenge_25 : public Challenge
{
public:
	Challenge_25();
	~Challenge_25();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

	struct Instruction
	{
		char state = 'A';
		int checkValue = 0;
		int writeValue = 0;
		int moveValue = 0;
		char nextState = 'A';

		bool Match(const char s, const int value) const
		{
			return state == s && checkValue == value;
		}
	};
};

