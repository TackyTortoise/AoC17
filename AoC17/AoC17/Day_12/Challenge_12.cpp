#include "Challenge_12.h"

Challenge_12::Challenge_12(){}
Challenge_12::~Challenge_12(){}

void Challenge_12::Run()
{
	P1();
	P2();
}

void Challenge_12::P1()
{
	auto input = TxtFileGetLines("./Day_12/Input_12.txt");

	for(size_t i = 0; i < input.size(); ++i)
	{
		m_Pipes.push_back(new Pipe(i));
	}
	
	regex dgtRgx("\\d+");
	smatch sm;
	for (auto l : input)
	{
		regex_search(l, sm, dgtRgx);
		int id = stoi(sm[0]);
		l = sm.suffix();
		while (regex_search(l, sm, dgtRgx))
		{
			int connection = stoi(sm[0]);
			m_Pipes[id]->connectedPipes.push_back(m_Pipes[connection]);
			l = sm.suffix();
		}
	}

	vector<const Pipe*> checked;
	GetPipeChildCount(m_Pipes[0], checked);
	cout << checked.size() << endl;
}

void Challenge_12::P2()
{
	auto input = TxtFileGetLines("./Day_12/Input_12.txt");

	m_Pipes.clear();
	for (size_t i = 0; i < input.size(); ++i)
	{
		m_Pipes.push_back(new Pipe(i));
	}

	regex dgtRgx("\\d+");
	smatch sm;
	for (auto l : input)
	{
		regex_search(l, sm, dgtRgx);
		int id = stoi(sm[0]);
		l = sm.suffix();
		while (regex_search(l, sm, dgtRgx))
		{
			int connection = stoi(sm[0]);
			m_Pipes[id]->connectedPipes.push_back(m_Pipes[connection]);
			l = sm.suffix();
		}
	}
		
	int groups = 0;
	vector<const Pipe*> checked;
	do
	{
		checked.clear();
		GetPipeChildCount(m_Pipes[0], checked);
		++groups;
		
		for(int i = 0; i < checked.size(); ++i)
		{
			auto it = find_if(m_Pipes.begin(), m_Pipes.end(), [&](Pipe* p) {return p->pipeId == checked[i]->pipeId; });
			m_Pipes.erase(it);
		}

	} while (m_Pipes.size() > 0);

	cout << groups << endl;
}

void Challenge_12::GetPipeChildCount(const Pipe* pipe, vector<const Pipe*>& checked)
{
	checked.push_back(pipe);
	for (auto p : pipe->connectedPipes)
	{
		if (find(checked.begin(), checked.end(), p) != checked.end())
			continue;
		GetPipeChildCount(p, checked);
	}
}
