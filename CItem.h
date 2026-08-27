#pragma once
#include "CObject.h"
#include "CObstacle.h"
#include "CInventory.h"
class CItem :
    public CObject
{
public:
	enum Items
	{
		NOTEBOOK,
		CAR_KEY,
		JACKET,
		MASTER_BEDROOM_KEY,
		NEIGHBOUR_HOUSE_KEY,
		CIGARS,
		CODE_NOTE
	};
private:
	Items Item;
	string ItemDialouge;
	string InventoryDialogue;
	string ItemName;
	int Id;
public:
	CItem* SetItem(CObstacle* Obstacle, Items I);
	void AddToInventory();
	void SetType(Items I);
	CItem();
	string GetItemName();
	string GetInventoryDialogue() { return InventoryDialogue; }
	static string GetItemDialogueByType(Items type);
	int GetId();
};

