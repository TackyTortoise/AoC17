#pragma once
#include "../Challenge.h"

class Challenge_05 : public Challenge
{
public:
	Challenge_05();
	~Challenge_05();
	void Run() override;

private:
	void P1() override;
	void P2() override;
};

