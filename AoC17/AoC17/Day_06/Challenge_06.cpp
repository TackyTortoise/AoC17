#include "Challenge_06.h"

Challenge_06::Challenge_06(){}

Challenge_06::~Challenge_06(){}

void Challenge_06::Run()
{
	P1();
	P2();
}

void Challenge_06::P1()
{
	auto strInput = SplitString(TxtFileToString("./Day_06/Input_06.txt"), '\t');
	vector<int> nums;
	for_each(strInput.begin(), strInput.end(), [&](string x) {nums.push_back(stoi(x)); });
	
	vector<string> permutations;
	string perm = "";
	for (auto num : nums)
	{
		perm += to_string(num) + " ";
	}

	int biggestValue = *max_element(nums.begin(), nums.end());
	int biggestIndex = find(nums.begin(), nums.end(), biggestValue) - nums.begin();
	
	do 
	{
		permutations.push_back(perm);
		nums[biggestIndex] = 0;
		for(int i = 0; i < biggestValue; ++i)
		{
			++nums[(i + biggestIndex + 1) % nums.size()];
		}

		biggestValue = *max_element(nums.begin(), nums.end());
		biggestIndex = find(nums.begin(), nums.end(), biggestValue) - nums.begin();

		perm.clear();
		for (auto num : nums)
		{
			perm += to_string(num) + " ";
		}
	} while (find(permutations.begin(), permutations.end(), perm) == permutations.end());
	cout << permutations.size() << endl;
}

void Challenge_06::P2()
{
	auto strInput = SplitString(TxtFileToString("./Day_06/Input_06.txt"), '\t');
	vector<int> nums;
	for_each(strInput.begin(), strInput.end(), [&](string x) {nums.push_back(stoi(x)); });

	vector<string> permutations;
	string perm = "";
	for (auto num : nums)
	{
		perm += to_string(num) + " ";
	}

	int biggestValue = *max_element(nums.begin(), nums.end());
	int biggestIndex = find(nums.begin(), nums.end(), biggestValue) - nums.begin();

	do
	{
		permutations.push_back(perm);
		nums[biggestIndex] = 0;
		for (int i = 0; i < biggestValue; ++i)
		{
			++nums[(i + biggestIndex + 1) % nums.size()];
		}

		biggestValue = *max_element(nums.begin(), nums.end());
		biggestIndex = find(nums.begin(), nums.end(), biggestValue) - nums.begin();

		perm.clear();
		for (auto num : nums)
		{
			perm += to_string(num) + " ";
		}
	} while (find(permutations.begin(), permutations.end(), perm) == permutations.end());

	auto target = perm;
	perm.pop_back();
	auto newInput = SplitString(perm, ' ');
	nums.clear();
	for_each(newInput.begin(), newInput.end(), [&](string x) {nums.push_back(stoi(x)); });
	biggestValue = *max_element(nums.begin(), nums.end());
	biggestIndex = find(nums.begin(), nums.end(), biggestValue) - nums.begin();
	int steps = 0;
	do
	{
		++steps;
		nums[biggestIndex] = 0;
		for (int i = 0; i < biggestValue; ++i)
		{
			++nums[(i + biggestIndex + 1) % nums.size()];
		}

		biggestValue = *max_element(nums.begin(), nums.end());
		biggestIndex = find(nums.begin(), nums.end(), biggestValue) - nums.begin();

		perm.clear();
		for (auto num : nums)
		{
			perm += to_string(num) + " ";
		}
	} while (perm != target);

	cout << steps << endl;
}
