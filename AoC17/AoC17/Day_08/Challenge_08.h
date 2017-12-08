#pragma once
#include "../Challenge.h"

class Challenge_08 : public Challenge
{
public:
	Challenge_08();
	~Challenge_08();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	struct Registery
	{
		string name;
		int value = 0;
	};

	vector<Registery*> m_Regs;

	Registery* GetRegisteryByName(const string& name)
	{
		auto it = find_if(m_Regs.begin(), m_Regs.end(), [name](Registery* r) {return r->name == name; });
		if (it != m_Regs.end())
			return m_Regs[it - m_Regs.begin()];
		else
			return nullptr;
	}

};

