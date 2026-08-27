#pragma once
#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
using namespace std;
#include "CGameObject.h"
class CObject :
    public CGameObject
{
    string name;
    string details;
};

