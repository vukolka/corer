//
// Created by vukolov on 18.02.18.
//

#include <iostream>
#include "CorewarVis.h"

using namespace std;

CorewarVis::CorewarVis(int width, int height)
{
	lasProcessAmmount = 0;
	screenHeight = height;
	screenWidth = width;
	running = true;
}
