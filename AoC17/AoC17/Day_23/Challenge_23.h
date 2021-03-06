#pragma once
#include "../Challenge.h"

class Challenge_23 : public Challenge
{
public:
	Challenge_23();
	~Challenge_23();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

	struct Register
	{
		Register(char n, unsigned v) :name(n), value(v) {}
		char name;
		long long value;
	};

	long long GetRegisterValue(const char name, vector<Register>& regs);
	void SetRegisterValue(const char name, const long long v, vector<Register>& regs);
	long long ValueFromRest(const string& rest, vector<Register>& regs);
};

