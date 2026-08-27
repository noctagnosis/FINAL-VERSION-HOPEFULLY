#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "CUI.h"
using namespace std;

class inventorySystem
{
	int static const MAX_ITEMS = 15;
	int InventoryIDS[MAX_ITEMS] = {0};
	//string inventorySpace[MAX_ITEMS] = {"it worrks"};
	string inventorySpace[MAX_ITEMS];
	int ItemCount = 0; //change 1 to 0
	int itemPosition = 0;
	bool isInventoryOpen = false;
	string InventoryDialogues[20];
public:
	void renderInventory();
	void showInventory(char input);
	void addToInventory(string item, int id, string invDialogue = "");
	void removeFromInventory(int index); //added this
	void switchItem(int input);
	bool getInventoryState();
	int GetItemCount();
	string GetInventory(int index);
	int GetInventoryID(int index);
	string GetInventoryDialogue(int index) { return InventoryDialogues[index]; }
	int getItemPosition() { return itemPosition; }
};