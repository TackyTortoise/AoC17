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

private:
	struct Program
	{
		Program(string n, int w, const vector<string> c, Program* p) : name(n), weight(w), children(c), parent(p) {}
		string name;
		int weight;
		vector<string> children;
		Program* parent;
		int GetChildrenWeight(const vector<Program*> programs, bool findDifference = false, int otherw = 0, int diffToFind = 0)
		{
			int total = 0;
			for (auto c : children)
			{
				auto it = find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == c; });
				if (it != programs.end())
				{
					auto ind = it - programs.begin();
					total += programs[ind]->GetChildrenWeight(programs);
				}
			}
			if (findDifference)
			{
				if (total + weight != otherw)
				{
					auto o = GetOddInChildren(this, programs, otherw);
					auto last = o;
					while (o != nullptr)
					{
						last = o;
						o = GetOddInChildren(o, programs, otherw);
					}

					for (auto child : last->children)
					{
						auto prog = GetProgramByName(child, programs);
						cout << prog->GetChildrenWeight(programs) << endl;
					}
					cout << "should be: " << last->weight - diffToFind << endl;
				}
			}

			return total + weight;
		}

		Program* GetProgramByName(string name, const vector<Program*>& programs)
		{
			return programs[find_if(programs.begin(), programs.end(), [=](Program* p) {return p->name == name; }) - programs.begin()];
		}

		vector<Program*> NameToProgramChildren(const vector<string>& names, const vector<Program*>& programs)
		{
			vector<Program*> result;
			for(auto n : names)
			{
				result.push_back(GetProgramByName(n, programs));
			}
			return result;
		}

		Program* GetOddInChildren(Program* p, const vector<Program*>& programs, const int otherw)
		{
			auto childPrograms = NameToProgramChildren(p->children, programs);
			int weight1 = -1;
			int weight2 = -1;
			Program* p1 = nullptr;
			Program* p2 = nullptr;

			for (auto c : childPrograms)
			{
				if (c->GetChildrenWeight(programs)!= weight1)
				{
					weight1 = c->GetChildrenWeight(programs);
					p1 = c;
					if (weight2 < 0)
					{
						weight2 = c->GetChildrenWeight(programs);
						p2 = c;
					}
				}
				if (weight1 != weight2)
				{
					int w1c = count_if(childPrograms.begin(), childPrograms.end(), [=](Program* pr) {return pr->GetChildrenWeight(programs) == weight1; });
					int w2c = count_if(childPrograms.begin(), childPrograms.end(), [=](Program* pr) {return pr->GetChildrenWeight(programs) == weight2; });
					if (w1c < w2c)
					{
						return p1;
					}
					else
					{
						return p2;
					}
				}
			}

			return nullptr;
		}
	};
};

