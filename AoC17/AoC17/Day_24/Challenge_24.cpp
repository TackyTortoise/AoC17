#include "Challenge_24.h"

Challenge_24::Challenge_24() {}
Challenge_24::~Challenge_24() {}

void Challenge_24::Run()
{
	P2();
}

void Challenge_24::P1()
{
	auto input = TxtFileGetLines("./Day_24/Input_24.txt");
	for (auto l : input)
	{
		auto slashPos = l.find('/');
		int pin1 = stoi(l.substr(0, slashPos));
		int pin2 = stoi(l.substr(slashPos + 1));
		m_Connections.push_back(new Connection(min(pin1, pin2), max(pin1, pin2)));
	}

	//ATTEMPT 1
	/*vector<vector<Connection*>> allChains;
	for (auto c : m_Connections)
	{
		if (c->pin1 == 0)
		{
			vector<Connection*> chain;
			chain.push_back(c);
			allChains.push_back(chain);
			for (auto c2 : m_Connections)
			{
				if (c == c2 || !c2->CanConnectPin(c->pin2))
					continue;

				chain.clear();
				chain.push_back(c);
				chain.push_back(c2);
				vector<Connection*>  ignore;
				ignore.push_back(c);
				ignore.push_back(c2);
				auto lastConnectedPin = c2->pin1 == c->pin2 ? c2->pin2 : c2->pin1;
				auto next = FindNextConnection(lastConnectedPin, ignore);
				while (next != nullptr)
				{
					if (next->pin1 == lastConnectedPin)
						lastConnectedPin = next->pin2;
					else
						lastConnectedPin = next->pin1;
					chain.push_back(next);
					ignore.push_back(next);
					next = FindNextConnection(lastConnectedPin, ignore);
				}

				allChains.push_back(chain);

				auto lastIngore = ignore[ignore.size() - 1];
				ignore.pop_back();
				while (chain.size() > 2 && find_if(m_Connections.begin(), m_Connections.end(), [&](Connection* con) {return con->CanConnect(chain[chain.size() - 2]); }) != m_Connections.end())
				{
					//Check back one step
					lastConnectedPin = chain[chain.size() - 1]->pin1 == lastConnectedPin ? chain[chain.size() - 1]->pin2 : chain[chain.size() - 1]->pin1;
					next = FindNextConnection(lastConnectedPin, ignore, lastIngore);
					chain.pop_back();
					while (next != nullptr)
					{
						lastConnectedPin = next->pin1 == lastConnectedPin ? next->pin2 : next->pin1;
						chain.push_back(next);
						ignore.push_back(next);
						next = FindNextConnection(lastConnectedPin, ignore);
					}

					lastIngore = ignore[ignore.size() - 1];

					allChains.push_back(chain);
				}

			}
		}
	}

	int highestScore = numeric_limits<int>::min();
	for (auto ch : allChains)
	{
		auto chainScore = GetChainScore(ch);
		if (chainScore > highestScore)
			highestScore = chainScore;
	}

	cout << highestScore << endl;*/

	//ATTEMPT 2
	/*sort(m_Connections.begin(), m_Connections.end(), [](Connection* a, Connection* b) {
		if (a->pin1 == b->pin1 && a->pin2 < b->pin2)
			return true;
		return a->pin1 < b->pin1; });

	for (auto c : m_Connections)
	{
		for (auto c2 : m_Connections)
		{
			if (c2->pin1 == 0)
				continue;
			c->possibleConnections.emplace(c2);
			c2->possibleConnections.emplace(c);
			for (auto c3 : m_Connections)
			{
				if (find(c3->possibleConnections.begin(), c3->possibleConnections.end(), c) != c3->possibleConnections.end())
				{
					c3->possibleConnections.emplace(c2);
					c2->possibleConnections.emplace(c3);
				}
				if (find(c3->possibleConnections.begin(), c3->possibleConnections.end(), c2) != c3->possibleConnections.end())
				{
					c3->possibleConnections.emplace(c2);
					c2->possibleConnections.emplace(c3);
				}
			}
		}
	}


	m_Connections.erase(remove_if(m_Connections.begin(), m_Connections.end(), [](Connection* c) {return c->pin1 != 0; }), m_Connections.end());
	vector<vector<Connection*>> allChains;
	for (auto con : m_Connections)
	{
		vector<Connection*> lastIgnores;
		auto chain = con->GetChildChain(lastIgnores);
		lastIgnores.push_back(chain[chain.size() - 1]);
		auto bigChainSize = chain.size();
		while (chain.size() >= bigChainSize)
		{
			allChains.push_back(chain);
			chain = con->GetChildChain(lastIgnores);
			lastIgnores.push_back(chain[chain.size() - 1]);
		}
	}


	int maxChainScore = 0;
	for (auto c : allChains)
	{
		auto cs = GetChainScore(c);
		if (cs > maxChainScore)
			maxChainScore = cs;
	}

	cout << maxChainScore << endl;*/

	//ATTEMPT 3
	list<Connection*> connectionList;
	copy(m_Connections.begin(), m_Connections.end(), back_inserter(connectionList));
	for (auto c : m_Connections)
	{
		if (c->pin1 == 0)
		{
			vector<Connection*> found;
			FindNext(c, connectionList, found, false);
		}
	}

	int maxChainScore = 0;
	for (auto c : m_Sums)
	{
		auto cs = GetChainScore(c);
		if (cs > maxChainScore)
			maxChainScore = cs;
	}

	cout << maxChainScore << endl;
}

void Challenge_24::P2()
{
	auto input = TxtFileGetLines("./Day_24/Input_24.txt");
	for (auto l : input)
	{
		auto slashPos = l.find('/');
		int pin1 = stoi(l.substr(0, slashPos));
		int pin2 = stoi(l.substr(slashPos + 1));
		m_Connections.push_back(new Connection(min(pin1, pin2), max(pin1, pin2)));
	}

	list<Connection*> connectionList;
	copy(m_Connections.begin(), m_Connections.end(), back_inserter(connectionList));
	for (auto c : m_Connections)
	{
		if (c->pin1 == 0)
		{
			vector<Connection*> found;
			FindNext(c, connectionList, found, false);
		}
	}

	vector<vector<Connection*>> longChains;
	auto maxSize = 0;
	for (auto c : m_Sums)
	{
		if (c.size() > maxSize)
		{
			maxSize = c.size();
			longChains.clear();
		}

		if (c.size() == maxSize)
		{
			longChains.push_back(c);
		}
	}

	int maxChainScore = 0;
	for (auto c : longChains)
	{
		auto cs = GetChainScore(c);
		if (cs > maxChainScore)
			maxChainScore = cs;
	}

	cout << maxChainScore << endl;
}

Challenge_24::Connection* Challenge_24::FindNextConnection(const int prevPin, vector<Connection*> ignoreList, Connection* extraIgnore)
{
	if (extraIgnore != nullptr)
		ignoreList.push_back(extraIgnore);
	auto it = find_if(m_Connections.begin(), m_Connections.end(), [&](Connection* c) {return find(ignoreList.begin(), ignoreList.end(), c) == ignoreList.end() && c->CanConnectPin(prevPin); });
	if (it == m_Connections.end())
		return nullptr;

	return *it;
}

int Challenge_24::GetChainScore(const vector<Connection*> chain)
{
	int score = 0;
	for (auto l : chain)
	{
		score += l->pin1;
		score += l->pin2;
	}

	return score;
}

void Challenge_24::GetConnectionChildCount(Connection* c, vector<Connection*>& checked)
{
	checked.push_back(c);
	for (auto p : c->possibleConnections)
	{
		if (find(checked.begin(), checked.end(), p) != checked.end())
			continue;
		GetConnectionChildCount(p, checked);
	}
}

void Challenge_24::FindNext(Connection* current, list<Connection*> numbers, std::vector<Connection*> numbersFound, bool ignoreFirst)
{
	// current = current number to check
	// numbers to check if found a number that is equal to current 
	// numbers found is a list of all the numbers that are store after each other to make a sum later 
	// If ignoreFirstis true only check the second number


	//Check if there is a number found.
	bool foundOne = false;
	for (auto b : numbers)
	{
		if (ignoreFirst)
		{

			//check number one and if found do recursive
			if (current->pin2 == b->pin1)
			{
				auto next = numbers;
				auto nf = numbersFound;
				nf.push_back(b);
				//int localSum = sum += b.number1 + b.number2;
				next.remove(b);
				FindNext(b, next, nf, true);
				foundOne = true;
			}
			else if (current->pin2 == b->pin2)
			{
				auto next = numbers;
				auto nf = numbersFound;
				nf.push_back(b);
				//int localSum = sum += b.number1 + b.number2;
				next.remove(b);
				FindNext(b, next, nf, false);
				foundOne = true;
			}
		}
		else
		{

			//check number one and if found do recursive
			if (current->pin1 == b->pin1)
			{


				auto next = numbers;
				auto nf = numbersFound;
				nf.push_back(b);
				//int localSum = sum += b.number1 + b.number2;
				next.remove(b);
				FindNext(b, next, nf, true);
				foundOne = true;
			}
			if (current->pin1 == b->pin2)
			{


				auto next = numbers;
				auto nf = numbersFound;
				nf.push_back(b);
				//int localSum = sum += b.number1 + b.number2;
				next.remove(b);
				FindNext(b, next, nf, false);
				foundOne = true;
			}
		}

	}

	//if there is nu number, push back the list to make a sum later
	if (!foundOne)
	{
		m_Sums.push_back(numbersFound);
	}
}
