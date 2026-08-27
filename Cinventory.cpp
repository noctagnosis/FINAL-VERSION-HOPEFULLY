#include "Cinventory.h"


void inventorySystem::renderInventory() {
	CUI::GetInstance().Clear();
	cout << "       [Inventory]\n";
	cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
	for (int i = 0; i < ItemCount; i++) {
		if (i == itemPosition) {
			cout << "~> " << inventorySpace[i] << endl;
		}
		else {
			cout << "   " << inventorySpace[i] << endl;
		}
	}
	cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
}

void inventorySystem::showInventory(char input) {
	if (input == 'i') {
		isInventoryOpen = !isInventoryOpen;
	}
	if (isInventoryOpen) {
		renderInventory();
	}
}

void inventorySystem::addToInventory(string item, int id, string invDialogue) {
	inventorySpace[ItemCount] = item;
	InventoryIDS[ItemCount] = id;
	InventoryDialogues[ItemCount] = invDialogue;
	ItemCount++;
}

void inventorySystem::removeFromInventory(int index) { //added this
	if (index < 0 || index >= ItemCount) return;
	for (int i = index; i < ItemCount - 1; i++) {
		inventorySpace[i] = inventorySpace[i + 1];
		InventoryIDS[i] = InventoryIDS[i + 1];
	}
	ItemCount--;
}

void inventorySystem::switchItem(int input) {
	if (input == 72) {
		if (itemPosition > 0) {
			itemPosition -= 1;
		}
	}
	else if (input == 80) {
		if (itemPosition < ItemCount - 1) {
			itemPosition += 1;
		}
	}
}


int inventorySystem::GetItemCount() {
	return ItemCount;
}
string inventorySystem::GetInventory(int index) {
	return inventorySpace[index];
}
int inventorySystem::GetInventoryID(int index) {
	return InventoryIDS[index];
}

bool inventorySystem::getInventoryState() {
	return isInventoryOpen;
}
