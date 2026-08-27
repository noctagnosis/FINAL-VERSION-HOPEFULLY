#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include "CPlayer.h"
#include "CUI.h"
using namespace std;
class CMap
{
	static const int MAX_SIZE = 100;
	int MAP_SIZE_X;
	int MAP_SIZE_Y;
	char MAP[MAX_SIZE][MAX_SIZE];
	CPlayer* player;
	std::string name;

public:
	char GetItem(int x, int y);
	void SetMap();
	void SetPlayerPOS(int x, int y);
	void SetPosition();
	void removePosition(int x, int y);
	void RenderMap();
	void SetMAP_SIZE(int size_x, int size_y);
	void SetRoom(int map_size_x, int map_size_y, int playerSpawnX, int playerSpawnY);
	void DeleteRoom();
	void SetName(const std::string& n);
	std::string GetName() const;
	void Movement(char input);
	char GetMap();
	CPlayer* GetPlayer();
	void SetObstacle(int width, int height, char symbol, int x, int y);
	void SetNPC(char symbol, int x, int y);

	~CMap();
	CMap();
};

