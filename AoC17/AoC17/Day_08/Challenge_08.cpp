#include "Challenge_08.h"

Challenge_08::Challenge_08() {}
Challenge_08::~Challenge_08() {}

void Challenge_08::Run()
{
	P2();
}

void Challenge_08::P1()
{
	auto lines = TxtFileGetLines("./Day_08/Input_08.txt");
	regex rgx("\\S+");
	smatch sm;
	for (auto l : lines)
	{
		vector<string> splitResults;
		auto cpy = l;
		while (regex_search(cpy, sm, rgx))
		{
			splitResults.push_back(sm[0]);
			cpy = sm.suffix();
		}

		string regName = splitResults[0];
		int op = splitResults[1][0] == 'i' ? 1 : -1;
		int value = stoi(splitResults[2]);
		string checkName = splitResults[4];
		string checkOp = splitResults[5];
		int checkValue = stoi(splitResults[6]);

		Registery* currentReg = GetRegisteryByName(regName);
		//Create reg if it doesn't exit
		if (currentReg == nullptr)
		{
			currentReg = new Registery();
			currentReg->name = regName;
			m_Regs.push_back(currentReg);
		}
		auto other = GetRegisteryByName(checkName);
		if (other == nullptr)
		{
			other = new Registery();
			other->name = checkName;
			m_Regs.push_back(other);
		}

		//Check condition
		bool execute = false;
		if (checkOp == ">")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value > checkValue;
		}
		else if (checkOp == "<")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value < checkValue;
		}
		else if (checkOp == ">=")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value >= checkValue;
		}
		else if (checkOp == "<=")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value <= checkValue;
		}
		else if (checkOp == "==")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value == checkValue;
		}
		else if (checkOp == "!=")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value != checkValue;
		}

		if (execute)
		{
			currentReg->value += op * value;
		}
	}

	auto maxValue = max_element(m_Regs.begin(), m_Regs.end(), [](Registery* r, Registery* o) {return r->value < o->value; });
	cout << "Max value: " << m_Regs[maxValue - m_Regs.begin()]->value << endl;
}

void Challenge_08::P2()
{
	auto lines = TxtFileGetLines("./Day_08/Input_08.txt");
	regex rgx("\\S+");
	smatch sm;
	int maxValue = numeric_limits<int>::min();
	for (auto l : lines)
	{
		vector<string> splitResults;
		auto cpy = l;
		while (regex_search(cpy, sm, rgx))
		{
			splitResults.push_back(sm[0]);
			cpy = sm.suffix();
		}

		string regName = splitResults[0];
		int op = splitResults[1][0] == 'i' ? 1 : -1;
		int value = stoi(splitResults[2]);
		string checkName = splitResults[4];
		string checkOp = splitResults[5];
		int checkValue = stoi(splitResults[6]);

		Registery* currentReg = GetRegisteryByName(regName);
		//Create reg if it doesn't exit
		if (currentReg == nullptr)
		{
			currentReg = new Registery();
			currentReg->name = regName;
			m_Regs.push_back(currentReg);
		}
		auto other = GetRegisteryByName(checkName);
		if (other == nullptr)
		{
			other = new Registery();
			other->name = checkName;
			m_Regs.push_back(other);
		}

		//Check condition
		bool execute = false;
		if (checkOp == ">")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value > checkValue;
		}
		else if (checkOp == "<")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value < checkValue;
		}
		else if (checkOp == ">=")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value >= checkValue;
		}
		else if (checkOp == "<=")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value <= checkValue;
		}
		else if (checkOp == "==")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value == checkValue;
		}
		else if (checkOp == "!=")
		{
			auto reg = GetRegisteryByName(checkName);
			if (reg != nullptr)
				execute = reg->value != checkValue;
		}

		if (execute)
		{
			currentReg->value += op * value;
			if (currentReg->value > maxValue)
				maxValue = currentReg->value;
		}
	}

	cout << "Max value: " << maxValue << endl;
}
