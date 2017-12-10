#include "Challenge_10.h"

Challenge_10::Challenge_10(){}
Challenge_10::~Challenge_10(){}

void Challenge_10::Run()
{
	P1();
	P2();
}

void Challenge_10::P1()
{
	const int elementCount = 256;
	vector<int> numbers;
	numbers.resize(elementCount);
	for (int i = 0; i < elementCount;++i)
	{
		numbers[i] = i;
	}

	string lengths = TxtFileToString("./Day_10/Input_10.txt");
	int currPos = 0;
	int skipSize = 0;

	regex digitRgx("\\d+");
	smatch sm;
	while (regex_search(lengths, sm, digitRgx))
	{
		auto currLength = stoi(sm[0]);
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

		lengths = sm.suffix();
	}

	int check = numbers[0] * numbers[1];
	cout << check << endl;
}

void Challenge_10::P2()
{
	const int elementCount = 256;
	vector<int> numbers;
	numbers.resize(elementCount);
	for (int i = 0; i < elementCount; ++i)
	{
		numbers[i] = i;
	}
	
	string lengthstring = TxtFileToString("./Day_10/Input_10.txt");
	vector<int> lengths;
	ConvertASCIIToBytes(lengthstring, lengths);

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

	cout << hash << endl;
}

void Challenge_10::ConvertASCIIToBytes(const string& input, vector<int>& output)
{
	output.resize(input.size());
	for (int i = 0; i < input.size(); ++i)
	{
		output[i] = (int)input[i];
	}
}
