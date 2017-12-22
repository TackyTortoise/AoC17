#include "Challenge_22.h"

Challenge_22::Challenge_22(){}
Challenge_22::~Challenge_22(){}

void Challenge_22::Run()
{
	P2();
}

void Challenge_22::P1()
{
	auto input = TxtFileToString("./Day_22/Input_22.txt");
	input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	int gridSize = sqrt(input.size());
	int virusIndex = input.size() / 2;
	Node virusNode(virusIndex % gridSize, virusIndex / gridSize);
	vector<Node> infectedNodes;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == '#')
			infectedNodes.push_back(Node(i % gridSize, i / gridSize));
	}

	int currentDirection = 0; // 0 = up, 1 = right, 2 = down, 3 = left
	int infectionCount = 0;
	int bursts = 10000;

	for (int i = 0; i < bursts; ++i)
	{
		auto it = find(infectedNodes.begin(), infectedNodes.end(), virusNode);
		//On infected node
		if (it != infectedNodes.end())
		{
			currentDirection = (currentDirection + 1) % 4;
			infectedNodes.erase(it);
			MoveVirusForward(virusNode, currentDirection);
		}
		//On clean node
		else
		{
			currentDirection -= 1;
			if (currentDirection < 0)
				currentDirection = 4 + currentDirection;
			//Infect current node
			infectedNodes.push_back(virusNode);
			++infectionCount;
			MoveVirusForward(virusNode, currentDirection);
		}
	}

	cout << infectionCount << endl;
}

void Challenge_22::P2()
{
	auto input = TxtFileToString("./Day_22/Input_22.txt");
	input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	int gridSize = sqrt(input.size());
	int virusIndex = input.size() / 2;
	Node virusNode(virusIndex % gridSize, virusIndex / gridSize);
	vector<Node*> infectedNodes;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == '#')
			infectedNodes.push_back(new Node(i % gridSize, i / gridSize, 'I'));
	}

	int currentDirection = 0; // 0 = up, 1 = right, 2 = down, 3 = left
	int infectionCount = 0;
	int bursts = 10000000;

	for (int i = 0; i < bursts; ++i)
	{
		auto it = find_if(infectedNodes.begin(), infectedNodes.end(), [&](Node* n) {return *n == virusNode; });
		//On Special node
		if (it != infectedNodes.end())
		{
			//Weakened node
			if ((*it)->state == 'W')
			{
				(*it)->state = 'I';
				++infectionCount;
				MoveVirusForward(virusNode, currentDirection);
			}
			//Infected node
			else if ((*it)->state == 'I')
			{
				currentDirection = (currentDirection + 1) % 4;
				(*it)->state = 'F';
				MoveVirusForward(virusNode, currentDirection);
			}
			//Flagged node
			else if ((*it)->state == 'F')
			{
				currentDirection = (currentDirection + 2) % 4;
				(*it)->state = 'C';
				MoveVirusForward(virusNode, currentDirection);
			}
			//Clean node
			else if ((*it)->state == 'C')
			{
				currentDirection -= 1;
				if (currentDirection < 0)
					currentDirection = 4 + currentDirection;
				(*it)->state = 'W';
				MoveVirusForward(virusNode, currentDirection);
			}
		}
		//On new clean node
		else
		{
			currentDirection -= 1;
			if (currentDirection < 0)
				currentDirection = 4 + currentDirection;
			//Weaken current node
			infectedNodes.push_back(new Node(virusNode.x, virusNode.y, 'W'));
			MoveVirusForward(virusNode, currentDirection);
		}
	}

	cout << infectionCount << endl;
}

void Challenge_22::MoveVirusForward(Node& n, int direction)
{
	switch (direction)
	{
	case 0://up
		--n.y;
		break;
	case 1://right
		++n.x;
		break;
	case 2://down
		++n.y;
		break;
	case 3://left
		--n.x;
		break;
	}
}
