#pragma once
#include "../Challenge.h"

class Challenge_21 : public Challenge
{
public:
	Challenge_21();
	~Challenge_21();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	string GetSquare(const string& image, int topLeft);
	string AssembleSquares(const vector<string>& sq);
	string GetRow(const string& in, int row);
	vector<string> FindSquares(const string& in);
	void TransformSquares(vector<string>& squares);
	void PrintSquare(const string& in);
	void UpdateImage(string& in);

	struct Rule
	{
		Rule(string inp, string outp) : output(outp)
		{
			//Calculate rotation and flip
			int size = sqrt(inp.size());
			auto last = inp;
			//Create flip
			for (int i = 0; i < 4; ++i)
			{
				auto rot = Rotate(last);
				auto flip = Flip(rot);
				options.push_back(rot);
				options.push_back(flip);
				last = rot;
			}
		}

		string Rotate(string in)
		{
			int s = sqrt(in.size());
			string t;
			t.resize(in.size());
			int size = sqrt(in.size());
			for (int r = 0; r < size; ++r)
				for (int c = 0; c < size; ++c)
				{
					int index1 = c + size * r;
					int index2 = r + size * c;
					t[index1] = in[index2];
				}

			for (int i = 0; i < t.size(); i += s)
				reverse(t.begin() + i, t.begin() + i + s);
			return t;
		}

		string Flip(string in)
		{
			int s = sqrt(in.size());
			string f = in;
			for (int i = 0; i < f.size(); i += s)
				reverse(f.begin() + i, f.begin() + i + s);

			return f;
		}

		bool IsMatch(string in)
		{
			return find(options.begin(), options.end(), in) != options.end();
		}

		vector<string> options;
		string output;
	};

	vector<Rule*> m_Rules;
};

