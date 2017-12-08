#include "Challenge_07.h"

Challenge_07::Challenge_07(){}

Challenge_07::~Challenge_07(){}

void Challenge_07::Run()
{
	P2();
}

void Challenge_07::P1()
{
	auto input = TxtFileGetLines("./Day_07/Input_07.txt");
	vector<Program*> programs;
	for (auto l : input)
	{
		regex wordRgx("[a-z]+");
		smatch sm;
		vector<string> names;
		string lineCopy = l;
		while (regex_search(lineCopy, sm, wordRgx))
		{
			names.push_back(sm[0]);
			lineCopy = sm.suffix();
		}
		regex digitRgx("\\d+");
		regex_search(l, sm, digitRgx);

		string name = names[0];
		names.erase(names.begin());
		int weight = stoi(sm[0]);
		Program* p = nullptr;
		auto it = find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == name; });
		if (it != programs.end())
		{
			auto ind = it - programs.begin();
			programs[ind]->weight = weight;
			programs[ind]->children = names;
			p = programs[ind];
		}
		else
		{
			p = new Program(name, weight, names, nullptr);
			programs.push_back(p);
		}

		for (auto n : names)
		{
			auto it = find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == n; });
			if (it != programs.end())
			{
				//Set parent
				auto ind = it - programs.begin();
				programs[ind]->parent = p;
			}
			else
			{
				//Create entry for parent
				vector<string> empty;
				auto prog = new Program(n, 0, empty, nullptr);
				prog->parent = p;
				programs.push_back(prog);
			}
		}		
	}
	auto it = find_if(programs.begin(), programs.end(), [](Program* p) {return p->parent == nullptr; });
	auto ind = it - programs.begin();
	cout << programs[ind]->name << endl;

	for (auto& p : programs)
	{
		delete p;
		p = nullptr;
	}
	programs.clear();
}

void Challenge_07::P2()
{
	auto input = TxtFileGetLines("./Day_07/Input_07.txt");
	vector<Program*> programs;
	for (auto l : input)
	{
		regex wordRgx("[a-z]+");
		smatch sm;
		vector<string> names;
		string lineCopy = l;
		while (regex_search(lineCopy, sm, wordRgx))
		{
			names.push_back(sm[0]);
			lineCopy = sm.suffix();
		}
		regex digitRgx("\\d+");
		regex_search(l, sm, digitRgx);

		string name = names[0];
		names.erase(names.begin());
		int weight = stoi(sm[0]);
		Program* p = nullptr;
		auto it = find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == name; });
		if (it != programs.end())
		{
			auto ind = it - programs.begin();
			programs[ind]->weight = weight;
			programs[ind]->children = names;
			p = programs[ind];
		}
		else
		{
			p = new Program(name, weight, names, nullptr);
			programs.push_back(p);
		}

		for (auto n : names)
		{
			auto it = find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == n; });
			if (it != programs.end())
			{
				//Set parent
				auto ind = it - programs.begin();
				programs[ind]->parent = p;
			}
			else
			{
				//Create entry for parent
				vector<string> empty;
				auto prog = new Program(n, 0, empty, nullptr);
				prog->parent = p;
				programs.push_back(prog);
			}
		}
	}
	auto it = find_if(programs.begin(), programs.end(), [](Program* p) {return p->parent == nullptr; });
	auto ind = it - programs.begin();
	int save1 = -1;
	int save2 = -1;
	Program* p1 = nullptr;
	Program* p2 = nullptr;
	for (int i = 0; i < programs[ind]->children.size(); ++i)
	{
		auto c = programs[ind]->children[i];
		auto itc = find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == c; });
		if (itc != programs.end())
		{
			auto indc = itc - programs.begin();
			int w = programs[indc]->GetChildrenWeight(programs);
			if (w != save1)
			{
				save1 = w;
				p1 = programs[indc];
				if (save2 < 0)
				{
					save2 = w;
					p2 = programs[indc];
				}
			}
			if (save1 != save2)
			{
				//cout << "Weight difference: " + to_string(abs(save1 - save2)) << endl;
				auto  itNextName = find_if(programs[ind]->children.begin(), programs[ind]->children.end(), [=](string s) {return s != p1->name && s != p2->name; });
				auto indNextName = itNextName - programs[ind]->children.begin();
				auto itn = find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == programs[ind]->children[indNextName]; });
				if (itn != programs.end())
				{
					auto indn = itn - programs.begin();
					Program* next = programs[indn];
					auto nextWeight = next->GetChildrenWeight(programs);

					if (save1 != nextWeight)
						p1->GetChildrenWeight(programs, true, save2, abs(save2 - save1));
					else
						p2->GetChildrenWeight(programs, true, save1, abs(save2 - save1));
					i = -1;
					break;
				}
			}
		}
	}
	cout << programs[ind]->name << endl;
	for (auto& p : programs)
	{
		delete p;
		p = nullptr;
	}
	programs.clear();
}
