#include "Challenge_14.h"
#include <bitset>
#include <stack>

Challenge_14::Challenge_14() {}
Challenge_14::~Challenge_14() {}

void Challenge_14::Run()
{
	P2();
}

void Challenge_14::P1()
{
	string input = "oundnydw";
	int usedBits = 0;
	for (int i = 0; i < 128; ++i)
	{
		auto curStr = input + "-";
		stack<int> sd;
		auto number = i;

		if (i == 0)
			curStr += '0';
		else
		{
			while (number > 0)
			{
				int digit = number % 10;
				number /= 10;
				sd.push(digit);
			}

			while (!sd.empty())
			{
				int digit = sd.top();
				sd.pop();

				curStr += digit + '0';
			}
		}

		string hash = GetHash(curStr);
		string binHash = HexStringToBinString(hash);
		int used = count_if(binHash.begin(), binHash.end(), [](char c) {return c == '1'; });
		usedBits += used;
	}

	cout << usedBits << endl;
}

void Challenge_14::P2()
{
	string input = "oundnydw";
	vector<char> grid;
	int lastInd = 0;
	for (int i = 0; i < 128; ++i)
	{
		auto curStr = input + "-";
		stack<int> sd;
		auto number = i;

		if (i == 0)
			curStr += '0';
		else
		{
			while (number > 0)
			{
				int digit = number % 10;
				number /= 10;
				sd.push(digit);
			}

			while (!sd.empty())
			{
				int digit = sd.top();
				sd.pop();

				curStr += digit + '0';
			}
		}

		string hash = GetHash(curStr);
		string binHash = HexStringToBinString(hash);
		grid.resize(grid.size() + binHash.size());
		for (int j = 0; j < binHash.size(); ++j)
		{
			grid[lastInd + j] = binHash[j];
		}
		lastInd = grid.size();
	}

	int count = 0;
	int lastFound = 0;
	while(true)
	{
		auto it = find(grid.begin() + lastFound, grid.end(), '1');
		if (it == grid.end())
			break;
		lastFound = it - grid.begin();
		ClearNeighbours(lastFound, grid);
		++count;
	}
	cout << count << endl;
}

string Challenge_14::HexStringToBinString(const string& hexStr)
{
	string r;
	int value;
	for (int i = 0; i < hexStr.size(); i += 2)
	{
		string hs = hexStr.substr(i, 2);
		istringstream ost(hs);
		ost >> hex >> value;
		bitset<8> bits(value);
		r += bits.to_string();
	}
	return r;
}

void Challenge_14::ConvertASCIIToBytes(const string& input, vector<int>& output)
{
	output.resize(input.size());
	for (int i = 0; i < input.size(); ++i)
	{
		output[i] = (int)input[i];
	}
}

string Challenge_14::GetHash(const string& input)
{
	const int elementCount = 256;
	vector<int> numbers;
	numbers.resize(elementCount);
	for (int i = 0; i < elementCount; ++i)
	{
		numbers[i] = i;
	}

	vector<int> lengths;
	ConvertASCIIToBytes(input, lengths);

	//Extra end salt
	lengths.push_back(17);
	lengths.push_back(31);
	lengths.push_back(73);
	lengths.push_back(47);
	lengths.push_back(23);

	int currPos = 0;
	int skipSize = 0;

	//DO 64 rounds
	for (int r = 0; r < 64; ++r)
	{
		for (int li = 0; li < lengths.size(); ++li)
		{
			auto currLength = lengths[li];
			//SubPart in range
			if (currLength + currPos < elementCount)
			{
				reverse(numbers.begin() + currPos, numbers.begin() + currPos + currLength);
			}
			//SubPart goes out of range
			else
			{
				vector<int> sub(currLength);
				for (int i = 0; i < currLength; ++i)
				{
					sub[i] = numbers[(currPos + i) % elementCount];
				}
				reverse(sub.begin(), sub.end());
				for (int i = 0; i < currLength; ++i)
				{
					numbers[(currPos + i) % elementCount] = sub[i];
				}
			}

			currPos += currLength + skipSize;
			currPos %= elementCount;
			++skipSize;
		}
	}

	//Go from sparse to dense hash
	string hash = "";
	for (int i = 0; i < elementCount; i += 16)
	{
		int dense = 0;
		for (int b = 0; b < 16; ++b)
		{
			dense ^= numbers[b + i];
		}
		stringstream stream;
		stream << std::hex << dense;
		string result(stream.str());
		if (result.size() < 2)
			hash += '0';
		hash += result;
	}

	return hash;
}

vector<int> Challenge_14::GetActiveNeighbourIndices(const int ind, vector<char>& grid)
{
	vector<int> nb;
	int s = 128;
	int c = ind % s;
	int r = ind / s;
	//Up
	if (r > 0)
		if (grid[ind - s] == '1')
			nb.push_back(ind - s);
	//Down
	if (r < s - 1)
		if (grid[ind + s] == '1')
			nb.push_back(ind + s);
	//Left
	if (c > 0)
		if (grid[ind - 1] == '1')
			nb.push_back(ind - 1);
	//right
	if (c < s - 1)
		if (grid[ind + 1] == '1')
			nb.push_back(ind + 1);

	return nb;
}

void Challenge_14::ClearNeighbours(const int ind, vector<char>& grid)
{
	auto anb = GetActiveNeighbourIndices(ind, grid);
	grid[ind] = '0';
	while (anb.size() > 0)
	{
		for (auto nbi : anb)
		{
			grid[nbi] = '0';
		}

		vector<int> nn;
		for (auto nbi : anb)
		{
			auto ianb = GetActiveNeighbourIndices(nbi, grid);
			for (auto nb : ianb)
				nn.push_back(nb);
		}

		anb = nn;
	}
}
