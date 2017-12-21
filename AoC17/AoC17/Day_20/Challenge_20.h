#pragma once
#include "../Challenge.h"

class Challenge_20 : public Challenge
{
public:
	Challenge_20();
	~Challenge_20();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	struct Vec3
	{
		Vec3(){};
		Vec3(int xP, int yP, int zP):x(xP), y(yP), z(zP){}
		long long x = 0, y = 0, z = 0;

		Vec3 operator+ (Vec3& o)
		{
			return Vec3(x + o.x, y + o.y , z + o.z);
		}

		bool operator==(Vec3&o)
		{
			return x == o.x && y == o.y && z == o.z;
		}
	};

	struct Particle
	{
		Vec3 position;
		Vec3 velocity;
		Vec3 acceleration;

		void Advance()
		{
			velocity = velocity + acceleration;
			position = position + velocity;
		}

		long long GetManhatten()
		{
			return abs(position.x) + abs(position.y) + abs(position.z);
		}
	};
};

