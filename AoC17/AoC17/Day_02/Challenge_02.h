#pragma once
#include "../Challenge.h"

class Challenge_02 :
	public Challenge
{
public:
	Challenge_02();
	~Challenge_02();
	void Run() override;

private:
	void P1() override;
	void P2() override;
};

