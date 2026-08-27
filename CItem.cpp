#include "CItem.h"
void CItem::SetType(Items I) {
	Item = I;
	switch (I) {
	case NOTEBOOK:
		ItemName = "Notebook";
		ItemDialouge = "You found Detective Black's Notebook";
		InventoryDialogue = "A worn Notebook. This Notebook holds years of notes on different cases.";
		Id = 1001;
		break;
	case CAR_KEY:
		ItemName = "Car Keys";
		ItemDialouge = "You found Silas's Car Keys";
		InventoryDialogue = "A 2025 Honda City Facelift's Car key.";
		Id = 1002;
		break;
	case JACKET:
		ItemName = "Jacket";
		ItemDialouge = "You found Detective Black's Jacket";
		InventoryDialogue = "A worn brown leather jacket that Rowan has for many years.";
		Id = 1003;
		break;
	case MASTER_BEDROOM_KEY:
		ItemName = "Master Bedroom Key";
		ItemDialouge = "";
		InventoryDialogue = "A Master Bedroom Key";
		Id = 1005;
		break;
	case NEIGHBOUR_HOUSE_KEY:
		ItemName = "Neighbour House Key";
		ItemDialouge = "";
		InventoryDialogue = "The Collin's House Key";
		Id = 1006;
		break;
	case CIGARS:
		ItemName = "Cigar";
		ItemDialouge = "You found a box of cigars, you sneakily took one out and put it in your pocket";
		InventoryDialogue = "A Cohiba brand Cigar";
		Id = 1007;
		break;
	case CODE_NOTE:
		ItemName = "Note with a Number";
		ItemDialouge = "You found a note with the number '180905' written on it";
		InventoryDialogue = "A note with the number -180905- written on it";
		Id = 1008;
		break;
	}
}
CItem* CItem::SetItem(CObstacle* obstacle, Items I) {
	SetType(I);
	obstacle->SetDialogue(0, ItemDialouge);
	return this;
}
string CItem::GetItemName() {
	return ItemName; 
}
int CItem::GetId() {
	return Id; 
}

string CItem::GetItemDialogueByType(Items type) {
	CItem tItem;
	tItem.SetType(type);
	return tItem.GetInventoryDialogue();

}

CItem::CItem() {

}