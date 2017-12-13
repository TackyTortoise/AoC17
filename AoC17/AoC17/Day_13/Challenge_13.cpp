#include "Challenge_13.h"

Challenge_13::Challenge_13(){}
Challenge_13::~Challenge_13(){}

void Challenge_13::Run()
{
	P1();
	P2();
}

void Challenge_13::P1()
{
	auto input = TxtFileGetLines("./Day_13/Input_13.txt");
	regex dgtRgx("\\d+");
	smatch sm;
	regex_search(input[input.size() - 1], sm, dgtRgx);
	int size = stoi(sm[0]) + 1;

	for (int i = 0; i < size; ++i)
	{
		m_FireWallLayers.push_back(new Layer());
	}

	for (auto l : input)
	{
		regex_search(l, sm, dgtRgx);
		auto layer = m_FireWallLayers[stoi(sm[0])];
		l = sm.suffix();
		regex_search(l, sm, dgtRgx);
		layer->range = stoi(sm[0]);
	}

	int severity = 0;
	for (int i = 0; i < size; ++i)
	{
		if (m_FireWallLayers[i]->IsScanningTop())
		{
			severity += i * m_FireWallLayers[i]->range;
		}
		for (auto fwl : m_FireWallLayers)
			fwl->UpdatePosition();
	}

	cout << severity << endl;

	for (auto f : m_FireWallLayers)
	{
		delete f;
		f = nullptr;
	}
	m_FireWallLayers.clear();
}

void Challenge_13::P2()
{
	auto input = TxtFileGetLines("./Day_13/Input_13.txt");
	regex dgtRgx("\\d+");
	smatch sm;
	regex_search(input[input.size() - 1], sm, dgtRgx);
	int size = stoi(sm[0]) + 1;

	for (int i = 0; i < size; ++i)
	{
		m_FireWallLayers.push_back(new Layer());
	}

	for (auto l : input)
	{
		regex_search(l, sm, dgtRgx);
		auto layer = m_FireWallLayers[stoi(sm[0])];
		l = sm.suffix();
		regex_search(l, sm, dgtRgx);
		layer->range = stoi(sm[0]);
	}

	int currentPosition = 0;
	int checkPos = 0;
	auto fwc = CreateNewFireWallCopy(m_FireWallLayers);
	auto lastConfig = CreateNewFireWallCopy(fwc);
	for (int i = 0; i < size; ++i)
	{
		if (currentPosition >= 0 && fwc[i]->IsScanningTop())
		{
			--checkPos;
			currentPosition = 0;
			i = -1;

			for (auto fwl : lastConfig)
				fwl->UpdatePosition();

			CreateFireWallCopy(fwc, lastConfig);

			continue;
		}
		for (auto fwl : fwc)
			fwl->UpdatePosition();

		++currentPosition;
	}

	cout << checkPos << endl;

	for (auto f : m_FireWallLayers)
	{
		delete f;
		f = nullptr;
	}
	m_FireWallLayers.clear();

	for (auto f : fwc)
	{
		delete f;
		f = nullptr;
	}
	fwc.clear();

	for (auto f : lastConfig)
	{
		delete f;
		f = nullptr;
	}
	lastConfig.clear();
}

vector<Challenge_13::Layer*> Challenge_13::CreateNewFireWallCopy(vector<Layer*> original)
{
	vector<Layer*> result;
	for (auto l : original)
	{
		Layer* ly = new Layer();
		ly->currentDirection = l->currentDirection;
		ly->currentScanPosition = l->currentScanPosition;
		ly->range = l->range;
		result.push_back(ly);
	}
	return result;
}

void Challenge_13::CreateFireWallCopy(vector<Layer*>& destination, const vector<Layer*>& original)
{
	for (int i = 0; i < original.size(); ++i)
	{
		destination[i]->currentDirection = original[i]->currentDirection;
		destination[i]->currentScanPosition = original[i]->currentScanPosition;
		destination[i]->range = original[i]->range;
	}
}
