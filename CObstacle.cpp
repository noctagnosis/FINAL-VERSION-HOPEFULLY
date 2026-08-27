#include "CObstacle.h"

void CObstacle::SetType(Furniture f)
{
	type = f;
	switch (f)
	{
	case Table:
		width = 2; height = 1; symbol = '#';
		IDialouge[0] = "A table. Sturdy. Unremarkable... kinda like people named lucas";
		IDialouge[1] = "Still very much a table, With a picture of what seems to be a cat or a dog";
		IDialouge[2] = "you straigten the files on the table";
		break;
	case Desk:
		width = 1; height = 1; symbol = '#';
		IDialouge[0] = "A normal desk made out of wood. doesnt seem to be any evidence here";
		IDialouge[1] = "there's a few scratches on the wood. the table has been throughly used";
		IDialouge[2] = "still just a desk.";
		break;
	case Small_Shelf:
		width = 3; height = 1; symbol = '=';
		IDialouge[0] = "A small shelf, there are items on it.";
		IDialouge[1] = "You swabbed your hands on the shelf, kinda dusty.";
		IDialouge[2] = "you stared at the shelf, it stares back at you.";
		break;
	case Long_Shelf:
		width = 4; height = 1; symbol = '=';
		IDialouge[0] = "Books, trophies, most of them fake just to trick the clients";
		IDialouge[1] = "you straigten the book that is crooked";
		IDialouge[2] = "you avoid your job as you continue to reorganise the shelf. slias looks mildly annoyed";
		break;
	case Sofa:
		width = 2; height = 1; symbol = 'L';
		IDialouge[0] = "A sofa, nothing much to see apart from the weird stain you and silas agree not to talk about";;
		IDialouge[1] = "You sit. You get up. You sit again. Nothing about this helps the case.";
		IDialouge[2] = "You lay on the sofa as you stare at the ceiling... maybe it knows why you dont have any money";
		break;
	case Chair:
		width = 1; height = 1; symbol = 'L';
		IDialouge[0] = "A Chair, You took a sit and stand back up";
		break;
	case Door:
		width = 1; height = 1; symbol = '/';
		IDialouge[0] = "Door";
		IDialouge[1] = "Press M to switch location, The Door dont work, Blame the programmer (us basically) ";
		IDialouge[2] = "Press M to switch location bro, dont make me repeat. >:( ";
		break;
	case Window:
		width = 1; height = 1; symbol = '+';
		IDialouge[0] = "a clear window with a nice veiw of the sky";
		IDialouge[1] = "you breathe on the window as you make a smiley face from the fog";
		IDialouge[2] = "you contine to stare outside as you think to yourself to maybe do your job";
		break;
	case Flower:
		width = 1; height = 1; symbol = '*';
		IDialouge[0] = "Did you know, young sunflowers slowly turn to follow the Sun.";
		IDialouge[1] = "Did you know, Flowers can communicate by releasing scents and chemicals to each other.";
		IDialouge[2] = "Did you know, Some flowers can imitate insects, like the Orchids.";
		break;
	case Tree:
		width = 1; height = 1; symbol = '@';
		IDialouge[0] = "A Strong tall tree";
		IDialouge[1] = "You can see a Squirrel at the side of the tree. It is throwing nuts at you.";
		IDialouge[2] = "You climbed up the tree and smacked the Squirrel. They shall fear the name Rowan Black.";
		break;
	case Bed:
		width = 2; height = 3; symbol = 'X';
		IDialouge[0] = "A Bed";
		IDialouge[1] = "You started to feel tired, the bed is tempting you";
		IDialouge[2] = "*Snore* *Snore* Hu-Huh? Dang i fell asleep";
		break;
	case ToiletBowl:
		width = 1; height = 1; symbol = 'O';
		IDialouge[0] = "A Toilet Bowl";
		IDialouge[1] = "You unbuckled your pants and took a piss";
		IDialouge[2] = "You unbuckled your pants and took a s***";
		break;
	case BathTub:
		width = 2; height = 1; symbol = 'H';
		IDialouge[0] = "A BathTub";
		IDialouge[1] = "You turn on the faucet, it burns your hand";
		IDialouge[2] = "Disgusting, they didnt even clear the drain hole, there is a bunch of hair";
		break;
	case Sink:
		width = 1; height = 1; symbol = 'a';
		IDialouge[0] = "A Sink";
		IDialouge[1] = "You washed your hand";
		IDialouge[2] = "The Sink briefly malfunctioned and sprays at you, you punched it";
		break;
	case Tape:
		width = 1; height = 1; symbol = '|';
		IDialouge[0] = "A Police Tape";
		IDialouge[1] = "You tried to push your way through, the police shouted at you, you backed off";
		IDialouge[2] = "You tried to push your way through again, you got entangled in the tape.";
		break;
	}

}
string CObstacle::GetNextDialouge() {
	if (dialougeidx < 0) dialougeidx = 0;
	if (dialougeidx > 2) dialougeidx = 2;
	string line = IDialouge[dialougeidx];
	if (dialougeidx < 2) dialougeidx++;
	return line;
}

// CObstacle.cpp
void CObstacle::SetDialogue(int index, const string text) {
	if (index >= 0 && index <= 2) {
		IDialouge[index] = text;
	}
}

string CObstacle::runDialogue(CEvidence::Evidence e, int num) {
	EvidenceIdx.SetEvidence(e);
	string text = EvidenceIdx.GetDialogue(num);

	return text;
}

string CObstacle::GetEvidenceName(CEvidence::Evidence e) {
	EvidenceIdx.SetEvidence(e);
	string name = EvidenceIdx.GetName();
	return name;
}

int CObstacle::GetEvidenceId() {
	return EvidenceIdx.GetId();
}

void CObstacle::Rotate()
{
	int temp = width;
	width = height;
	height = temp;
}

int CObstacle::GetWidth()
{
	return width;
}
int CObstacle::GetHeight()
{
	return height;
}
char CObstacle::GetSymbol()
{
	return symbol;
}
CObstacle::Furniture CObstacle::GetType()
{
	return type;
}
void CObstacle::SetItemPtr(CItem* i) {
	item = i;
}
CItem* CObstacle::GetItemPtr() {
	return item;
}

CObstacle::CObstacle()
{
	dialougeidx = 0;
	type = Table;
	width = 0;
	height = 0;
	symbol = '\0';
	SetPosX(0);
	SetPosY(0);
}