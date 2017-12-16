#include "Challenge_16.h"

Challenge_16::Challenge_16(){}
Challenge_16::~Challenge_16(){}

void Challenge_16::Run()
{
	P2();
}

void Challenge_16::P1()
{
	string programs = "abcdefghijklmnop";
	auto input = TxtFileToString("./Day_16/Input_16.txt");
	auto instructions = SplitString(input, ',');
	for (auto instr : instructions)
	{
		auto iType = instr[0];
		//Spin
		if (iType == 's')
		{
			int size = stoi(instr.substr(1));
			auto first = programs.substr(0, programs.size() - size);
			auto second = programs.substr(programs.size() - size);
			programs = second + first;
		}
		//Exchange
		else if (iType == 'x')
		{
			int slashPos = instr.find('/');
			int ind1 = stoi(instr.substr(1, slashPos - 1));
			int ind2 = stoi(instr.substr(slashPos + 1));
			auto save = programs[ind1];
			programs[ind1] = programs[ind2];
			programs[ind2] = save;
		}
		//Partner
		else if (iType == 'p')
		{
			char char1 = instr[1];
			char char2 = instr[3];
			int ind1 = programs.find(char1);
			int ind2 = programs.find(char2);
			auto save = programs[ind1];
			programs[ind1] = programs[ind2];
			programs[ind2] = save;
		}
	}

	cout << programs << endl;
}

void Challenge_16::P2()
{
	string programs = "abcdefghijklmnop";
	string original = programs;
	auto input = TxtFileToString("./Day_16/Input_16.txt");
	auto instructions = SplitString(input, ',');
	for (int i = 0; i < 1000000000; ++i)
	{
		for (auto instr : instructions)
		{
			auto iType = instr[0];
			//Spin
			if (iType == 's')
			{
				int size = stoi(instr.substr(1));
				auto first = programs.substr(0, programs.size() - size);
				auto second = programs.substr(programs.size() - size);
				programs = second + first;
			}
			//Exchange
			else if (iType == 'x')
			{
				int slashPos = instr.find('/');
				int ind1 = stoi(instr.substr(1, slashPos - 1));
				int ind2 = stoi(instr.substr(slashPos + 1));
				auto save = programs[ind1];
				programs[ind1] = programs[ind2];
				programs[ind2] = save;
			}
			//Partner
			else if (iType == 'p')
			{
				char char1 = instr[1];
				char char2 = instr[3];
				int ind1 = programs.find(char1);
				int ind2 = programs.find(char2);
				auto save = programs[ind1];
				programs[ind1] = programs[ind2];
				programs[ind2] = save;
			}
		}

		if (programs == original)
		{
			int left = 1000000000 / (i + 1);
			i += (left - 1) * (i + 1);
		}
	}

	cout << programs << endl;
}
