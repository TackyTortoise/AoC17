#include "Challenge_25.h"

Challenge_25::Challenge_25(){}
Challenge_25::~Challenge_25(){}

void Challenge_25::Run()
{
	P1();
}

void Challenge_25::P1()
{
	auto input = TxtFileGetLines("./Day_25/Input_25.txt");
	vector<Instruction*> instructions;
	char currentState;
	for (int i = 3; i < input.size(); ++i)
	{
		if (input[i].find("In state") != string::npos)
			currentState = input[i][input[i].size() - 2];
		else 
			continue;

		auto instr = new Instruction();
		instr->state = currentState;
		instr->checkValue = 0;
		instr->writeValue = input[i + 2][input[i + 2].size() - 2] - '0';
		instr->moveValue = input[i + 3].find("right") != string::npos ? 1 : -1;
		instr->nextState = input[i + 4][input[i + 4].size() - 2];
		instructions.push_back(instr);

		instr = new Instruction();
		instr->state = currentState;
		instr->checkValue = 1;
		instr->writeValue = input[i + 6][input[i + 6].size() - 2] - '0';
		instr->moveValue = input[i + 7].find("right") != string::npos ? 1 : -1;
		instr->nextState = input[i + 8][input[i + 8].size() - 2];
		instructions.push_back(instr);

		i += 9;
	}

	string tape = "0";
	int cursor = 0;
	regex dgt("\\d+");
	smatch sm;
	regex_search(input[1], sm, dgt);
	int steps = stoi(sm[0]);
	char state = 'A';
	for (int i = 0; i < steps; ++i)
	{
		if (cursor < 0)
		{
			cursor = 0;
			tape.insert(tape.begin(), '0');
		}
		else if (cursor >= tape.size())
		{
			auto diff = cursor - (tape.size() - 1);
			for (int d = 0; d < diff; ++d)
				tape.push_back('0');
		}

		int cursorValue = tape[cursor] - '0';
		auto it = find_if(instructions.begin(), instructions.end(), [&](Instruction* ins) {return ins->Match(state, cursorValue); });
		Instruction* rule = *it;
		tape[cursor] = rule->writeValue + '0';
		cursor += rule->moveValue;
		state = rule->nextState;
	}

	cout << count_if(tape.begin(), tape.end(), [](char c) {return c == '1'; }) << endl;
}

void Challenge_25::P2()
{
	//Yay
}
