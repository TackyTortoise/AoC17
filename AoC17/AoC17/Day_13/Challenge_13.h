#pragma once
#include "../Challenge.h"

class Challenge_13 : public Challenge
{
public:
	Challenge_13();
	~Challenge_13();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	struct Layer
	{
		int range;
		int currentScanPosition = 0;
		int currentDirection = 1;

		void UpdatePosition()
		{
			if (range == 0)
			{
				currentScanPosition = -1;
				return;
			}
			currentScanPosition += currentDirection;
			if (currentScanPosition >= range - 1)
				currentDirection = -1;
			else if (currentScanPosition <= 0)
				currentDirection = 1;
		}

		bool IsScanningTop() const
		{
			return currentScanPosition == 0;
		}
	};

	vector<Layer*> m_FireWallLayers;
	vector<vector<Layer*>> m_Configs;

	vector<Layer*> CreateNewFireWallCopy(vector<Layer*> original);
	void CreateFireWallCopy(vector<Layer*>& destination, const vector<Layer*>& original);
};

