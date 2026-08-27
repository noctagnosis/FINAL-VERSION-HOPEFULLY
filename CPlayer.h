#pragma once
#include "CGameObject.h"
class CPlayer :
    public CGameObject
{
    char lastInput;
public:
    void SetlastInput(char input);
    char GetlastInput();
    void Move(char map[100][100], int map_size_x, int map_size_y);
    CPlayer();
};

