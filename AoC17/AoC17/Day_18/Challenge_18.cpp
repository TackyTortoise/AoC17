#include "Challenge_18.h"
#include <queue>

Challenge_18::Challenge_18() {}
Challenge_18::~Challenge_18() {}

void Challenge_18::Run()
{
	P2();
}

void Challenge_18::P1()
{
	auto input = TxtFileGetLines("./Day_18/Input_18.txt");
	vector<Register> regs;
	unsigned lastSound = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		string line = input[i];
		char reg = line[4];
		string rest = line.size() > 5 ? line.substr(6) : "";
		string instr = line.substr(0, 3);
		if (instr == "snd")
		{
			lastSound = GetRegisterValue(reg, regs);
		}
		else if (instr == "set")
		{
			SetRegisterValue(reg, ValueFromRest(rest, regs), regs);
		}
		else if (instr == "add")
		{
			auto oldValue = GetRegisterValue(reg, regs);
			SetRegisterValue(reg, oldValue + ValueFromRest(rest, regs), regs);
		}
		else if (instr == "mul")
		{
			auto oldValue = GetRegisterValue(reg, regs);
			SetRegisterValue(reg, oldValue * ValueFromRest(rest, regs), regs);
		}
		else if (instr == "mod")
		{
			auto oldValue = GetRegisterValue(reg, regs);
			SetRegisterValue(reg, oldValue % ValueFromRest(rest, regs), regs);
		}
		else if (instr == "rcv")
		{
			auto v = GetRegisterValue(reg, regs);
			if (v > 0)
			{
				std::cout << "Recovered frequency: " << lastSound << endl;
				return;
			}
		}
		else if (instr == "jgz")
		{
			if (GetRegisterValue(reg, regs) > 0)
			{
				auto v = ValueFromRest(rest, regs) - 1;
				i += v;
			}
		}
	}
}

void Challenge_18::P2()
{
	auto input = TxtFileGetLines("./Day_18/Input_18.txt");
	vector<Register> regs0;
	regs0.push_back(Register('p', 0));
	vector<Register> regs1;
	regs1.push_back(Register('p', 1));

	queue<long long> sendQueue0;
	queue<long long> sendQueue1;

	bool inLock0 = false, inLock1 = false;

	int i0 = 0;
	int i1 = 0;

	int count = 0;

	while (true)
	{
		//Reg0 instructions
		string line = input[i0];
		char reg = line[4];
		string rest = line.size() > 5 ? line.substr(6) : "";
		string instr = line.substr(0, 3);
		if (instr == "snd")
		{
			string strReg = "";
			strReg += reg;
			sendQueue0.push(ValueFromRest(strReg, regs0));
		}
		else if (instr == "set")
		{
			SetRegisterValue(reg, ValueFromRest(rest, regs0), regs0);
		}
		else if (instr == "add")
		{
			auto oldValue = GetRegisterValue(reg, regs0);
			SetRegisterValue(reg, oldValue + ValueFromRest(rest, regs0), regs0);
		}
		else if (instr == "mul")
		{
			auto oldValue = GetRegisterValue(reg, regs0);
			SetRegisterValue(reg, oldValue * ValueFromRest(rest, regs0), regs0);
		}
		else if (instr == "mod")
		{
			auto oldValue = GetRegisterValue(reg, regs0);
			SetRegisterValue(reg, oldValue % ValueFromRest(rest, regs0), regs0);
		}
		else if (instr == "rcv")
		{
			if (sendQueue1.size() == 0)
			{
				--i0;
				inLock0 = true;
				if (inLock0 && inLock1)
					break;
			}
			else
			{
				inLock0 = false;
				long long v = sendQueue1.front();
				sendQueue1.pop();
				SetRegisterValue(reg, v, regs0);
			}
		}
		else if (instr == "jgz")
		{
			string strReg = "";
			strReg += reg;
			if (ValueFromRest(strReg, regs0) > 0)
			{
				auto v = ValueFromRest(rest, regs0) - 1;
				i0 += v;
			}
		}


		//Reg1 instructions
		line = input[i1];
		reg = line[4];
		rest = line.size() > 5 ? line.substr(6) : "";
		instr = line.substr(0, 3);
		if (instr == "snd")
		{
			string strReg = "";
			strReg += reg;
			sendQueue1.push(ValueFromRest(strReg, regs1));
			++count;
		}
		else if (instr == "set")
		{
			SetRegisterValue(reg, ValueFromRest(rest, regs1), regs1);
		}
		else if (instr == "add")
		{
			auto oldValue = GetRegisterValue(reg, regs1);
			SetRegisterValue(reg, oldValue + ValueFromRest(rest, regs1), regs1);
		}
		else if (instr == "mul")
		{
			auto oldValue = GetRegisterValue(reg, regs1);
			SetRegisterValue(reg, oldValue * ValueFromRest(rest, regs1), regs1);
		}
		else if (instr == "mod")
		{
			auto oldValue = GetRegisterValue(reg, regs1);
			SetRegisterValue(reg, oldValue % ValueFromRest(rest, regs1), regs1);
		}
		else if (instr == "rcv")
		{
			if (sendQueue0.size() == 0)
			{
				--i1;
				inLock1 = true;
				if (inLock0 && inLock1)
					break;
			}
			else
			{
				inLock1 = false;
				long long v = sendQueue0.front();
				sendQueue0.pop();
				SetRegisterValue(reg, v, regs1);
			}
		}
		else if (instr == "jgz")
		{
			string strReg = "";
			strReg += reg;
			if (ValueFromRest(strReg, regs1) > 0)
			{
				auto v = ValueFromRest(rest, regs1) - 1;
				i1 += v;
			}
		}
		
		++i0;
		++i1;

		if (i0 >= input.size() && i1 >= input.size())
		{
			break;
		}
	}

	std::cout << count << endl;
}

long long Challenge_18::GetRegisterValue(const char name, vector<Register>& regs)
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

void Challenge_18::SetRegisterValue(const char name, const long long v, vector<Register>& regs)
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

long long Challenge_18::ValueFromRest(const string& rest, vector<Register>& regs)
{
	//rest is a digit
	if (count_if(rest.begin(), rest.end(), [](char c) {return isdigit(c) || c == '-'; }) == rest.size())
	{
		return stoi(rest);
	}
	//rest is a register
	return GetRegisterValue(rest[0], regs);
}
