#pragma once
#include "../Challenge.h"

class Challenge_15 : public Challenge
{
public:
	Challenge_15();
	~Challenge_15();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	struct Generator
	{
		Generator(long long f):factor(f){}
		long long factor;
		long long GenerateNumber(long long input)
		{
			return long long(input * factor % 2147483647);
		}
	};
};

