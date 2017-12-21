#include "Challenge_20.h"

Challenge_20::Challenge_20(){}
Challenge_20::~Challenge_20(){}

void Challenge_20::Run()
{
	P2();
}

void Challenge_20::P1()
{
	auto input = TxtFileGetLines("./Day_20/Input_20.txt");
	regex dgtRgx("-?\\d+");
	smatch sm;
	vector<Particle*> particles;

	for (auto line : input)
	{
		auto curParticle = new Particle();
		for (int i = 0; i < 3; ++i)
		{
			Vec3 current;
			regex_search(line, sm, dgtRgx);
			current.x = stoi(sm[0]);
			line = sm.suffix();
			regex_search(line, sm, dgtRgx);
			current.y = stoi(sm[0]);
			line = sm.suffix();
			regex_search(line, sm, dgtRgx);
			current.z = stoi(sm[0]);
			line = sm.suffix();

			if (i == 0)
				curParticle->position = current;
			if (i == 1)
				curParticle->velocity = current;
			if (i == 2)
				curParticle->acceleration = current;
		}
		particles.push_back(curParticle);
	}

	for (int i = 0; i < 10001; i++)
	{
		for_each(particles.begin(), particles.end(), [](Particle* p) {p->Advance(); });
		if (i % 10 == 0)
		{
			int shortD = numeric_limits<int>::max();
			int shortIndex = -1;
			for (int pi = 0; pi < particles.size(); pi++)
			{
				auto dist = particles[pi]->GetManhatten();
				if (dist < shortD)
				{
					shortD = dist;
					shortIndex = pi;
				}
			}

			cout << "Closest particle at iteration " << i << " is: " << shortIndex << endl;
		}
	}
}

void Challenge_20::P2()
{
	auto input = TxtFileGetLines("./Day_20/Input_20.txt");
	regex dgtRgx("-?\\d+");
	smatch sm;
	vector<Particle*> particles;

	for (auto line : input)
	{
		auto curParticle = new Particle();
		for (int i = 0; i < 3; ++i)
		{
			Vec3 current;
			regex_search(line, sm, dgtRgx);
			current.x = stoi(sm[0]);
			line = sm.suffix();
			regex_search(line, sm, dgtRgx);
			current.y = stoi(sm[0]);
			line = sm.suffix();
			regex_search(line, sm, dgtRgx);
			current.z = stoi(sm[0]);
			line = sm.suffix();

			if (i == 0)
				curParticle->position = current;
			if (i == 1)
				curParticle->velocity = current;
			if (i == 2)
				curParticle->acceleration = current;
		}
		particles.push_back(curParticle);
	}

	for (int i = 0; i < 300001; i++)
	{
		//Erase duplicats
		for(int ci = 0; ci < particles.size(); ci++)
		{
			vector<int> removeIndices;
			auto it = find_if(particles.begin() + ci + 1, particles.end(), [&](Particle* p) {return p->position == particles[ci]->position; });
			if (it == particles.end())
				continue;

			removeIndices.push_back(ci);
			while (it != particles.end())
			{
				removeIndices.push_back(it - particles.begin());
				it = find_if(particles.begin() + removeIndices[removeIndices.size() - 1] + 1, particles.end(), [&](Particle* p) {return p->position == particles[ci]->position; });
			}

			for (int ri = 0; ri < removeIndices.size(); ++ri)
			{
				particles.erase(particles.begin() + removeIndices[ri] - ri);
			}
			--ci;
		}

		for_each(particles.begin(), particles.end(), [](Particle* p) {p->Advance(); });
		if (i % 100 == 0)
		{
			cout << "Particles still alive at iteration " << i << " is: " << particles.size() << endl;
		}
	}
}
