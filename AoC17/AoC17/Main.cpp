#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "Day_01/Challenge_01.h"
#include "Day_02/Challenge_02.h"
#include "Day_03/Challenge_03.h"
#include "Day_04/Challenge_04.h"
#include "Day_05/Challenge_05.h"
#include "Day_06/Challenge_06.h"
#include "Day_07/Challenge_07.h"
#include "Day_08/Challenge_08.h"
#include "Day_09/Challenge_09.h"
#include "Day_10/Challenge_10.h"
#include "Day_11/Challenge_11.h"
#include "Day_12/Challenge_12.h"
#include "Day_13/Challenge_13.h"
#include "Day_14/Challenge_14.h"
#include "Day_15/Challenge_15.h"
#include "Day_16/Challenge_16.h"
#include "Day_17/Challenge_17.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Challenge* c = new Challenge_17();
	c->Run();
	cin.get();
	delete c;
}
