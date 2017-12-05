#include "./Day_01/Challenge_01.h"
#include "Day_02/Challenge_02.h"
#include "Day_03/Challenge_03.h"
#include "Day_04/Challenge_04.h"
#include "Day_05/Challenge_05.h"

int main()
{
	Challenge* c = new Challenge_05();
	c->Run();
	cin.get();
	delete c;
}
