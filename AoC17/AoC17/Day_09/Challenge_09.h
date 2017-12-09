#pragma once
#include "../Challenge.h"

class Challenge_09 : public Challenge
{
public:
	Challenge_09();
	~Challenge_09();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
private:
	string RemoveGarbage(const string& group) const;
	int GetGroupScore(const string& group, int parentScore) const;
	int GetGarbageSize(const string& group) const;
};

