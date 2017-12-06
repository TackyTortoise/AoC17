#pragma once
#include "../Challenge.h"

class Challenge_07 : public Challenge
{
public:
	Challenge_07();
	~Challenge_07();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

