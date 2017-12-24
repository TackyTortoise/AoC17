#pragma once
#include "../Challenge.h"
#include <list>

class Challenge_24 : public Challenge
{
public:
	Challenge_24();
	~Challenge_24();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	struct Connection
	{
		Connection(int p1, int p2) :pin1(p1), pin2(p2) {}
		int pin1;
		int pin2;

		bool CanConnect(const Connection* o) const
		{
			return pin1 == o->pin1 || pin2 == o->pin1 || pin1 == o->pin2 || pin2 == o->pin2;
		}

		bool CanConnectPin(const int otherPin) const
		{
			return pin1 == otherPin || pin2 == otherPin;
		}

		bool operator<(const Connection* other) const
		{
			if (other->pin1 == pin1 && other->pin2 < pin2)
				return true;
			return other->pin1 < pin1;
		}

		set<Connection*> possibleConnections;

		vector<Connection*> GetChildChain(vector<Connection*> lastIgnore)
		{
			vector<Connection*> r;
			r.push_back(this);
			auto connectPin = pin2;
			vector<Connection*> children;
			std::copy(possibleConnections.begin(), possibleConnections.end(), back_inserter(children));
			sort(children.begin(), children.end(), [](Connection* a, Connection* b) {
				if (a->pin1 == b->pin1 && a->pin2 < b->pin2)
					return true;
				return a->pin1 < b->pin1; });
			for (auto it = children.begin(); it != children.end(); ++it)
			{
				auto c = *it;
				if (find(r.begin(), r.end(), c) == r.end() && c->CanConnectPin(connectPin))
				{
					r.push_back(c);
					connectPin = connectPin == c->pin1 ? c->pin2 : c->pin1;
					it = children.begin();
				}
			}

			auto last = r[r.size() - 1];
			if (find(lastIgnore.begin(), lastIgnore.end(), last) != lastIgnore.end())
			{
				r.pop_back();
				connectPin = connectPin == last->pin1 ? last->pin2 : last->pin1;
				for (auto ch : children)
				{
					if (last == ch || find(r.begin(), r.end(), ch) != r.end() || find(lastIgnore.begin(), lastIgnore.end(), ch) != lastIgnore.end())
						continue;
					if (ch->CanConnectPin(connectPin))
					{
						r.push_back(ch);
						break;
					}
				}
			}

			return r;
		}
	};

	vector<Connection*> m_Connections;
	vector<vector<Connection*>> m_Sums;

	Connection* FindNextConnection(const int prevPin, vector<Connection*> ignoreList, Connection* extraIgnore = nullptr);
	int GetChainScore(const vector<Connection*> chain);

	void GetConnectionChildCount(Connection* c, vector<Connection*>& checked);
	void FindNext(Connection* current, list<Connection*> numbers, std::vector<Connection*> numbersFound, bool ignoreFirst);
};

