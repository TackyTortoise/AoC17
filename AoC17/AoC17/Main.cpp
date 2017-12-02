#include "./Day_01/Challenge_01.h"
#include "Day_02/Challenge_02.h"

int main()
{
	Challenge* c = new Challenge_02();
	c->Run();
	cin.get();
	delete c;
}
