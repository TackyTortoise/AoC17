#pragma once
#include "../Challenge.h"
class Challenge_01 :public Challenge
{
public:
	Challenge_01();
	~Challenge_01();
	void Run() override;

private:
	void P1();
	void P2();
};

