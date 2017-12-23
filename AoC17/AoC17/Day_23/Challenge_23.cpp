#include "Challenge_23.h"

Challenge_23::Challenge_23(){}
Challenge_23::~Challenge_23(){}

void Challenge_23::Run()
{
	P2();
}

void Challenge_23::P1()
{
	auto input = TxtFileGetLines("./Day_23/Input_23.txt");
	vector<Register> regs;
	int mulUsed = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		string line = input[i];
		char reg = line[4];
		string rest = line.size() > 5 ? line.substr(6) : "";
		string instr = line.substr(0, 3);
		 if (instr == "set")
		{
			SetRegisterValue(reg, ValueFromRest(rest, regs), regs);
		}
		else if (instr == "sub")
		{
			auto oldValue = GetRegisterValue(reg, regs);
			SetRegisterValue(reg, oldValue - ValueFromRest(rest, regs), regs);
		}
		else if (instr == "mul")
		{
			++mulUsed;
			auto oldValue = GetRegisterValue(reg, regs);
			SetRegisterValue(reg, oldValue * ValueFromRest(rest, regs), regs);
		}
		else if (instr == "jnz")
		{
			string strReg = "";
			strReg += reg;
			if (ValueFromRest(strReg, regs) != 0)
			{
				auto v = ValueFromRest(rest, regs) - 1;
				i += v;
			}
		}

		 if (i < 0)
			 break;
	}

	cout << mulUsed << endl;
}

void Challenge_23::P2()
{
	long long  b = 0, h = 0;

	for (b = 106700; b < 123701; b += 17)
	{
		for (int i = 2; i < b / 2; ++i)
		{
			if (b % i == 0)
			{
				//b is not prime
				++h;
				break;
			}
		}
	}

	cout << (int)h << endl;
}


long long Challenge_23::GetRegisterValue(const char name, vector<Register>& regs)
{
	auto it = find_if(regs.begin(), regs.end(), [=](Register r) {return r.name == name; });
	//Return reg value if it exists
	if (it != regs.end())
	{
		return regs[it - regs.begin()].value;
	}

	//Create new reg if it does not
	regs.push_back(Register(name, 0));
	return 0;
}

void Challenge_23::SetRegisterValue(const char name, const long long v, vector<Register>& regs)
{
	auto it = find_if(regs.begin(), regs.end(), [=](Register r) {return r.name == name; });
	//Set value if register exists
	if (it != regs.end())
	{
		regs[it - regs.begin()].value = v;
		return;
	}
	//Create new value if it does not
	regs.push_back(Register(name, v));
}

long long Challenge_23::ValueFromRest(const string& rest, vector<Register>& regs)
{
	//rest is a digit
	if (count_if(rest.begin(), rest.end(), [](char c) {return isdigit(c) || c == '-'; }) == rest.size())
	{
		return stoi(rest);
	}
	//rest is a register
	return GetRegisterValue(rest[0], regs);
}
