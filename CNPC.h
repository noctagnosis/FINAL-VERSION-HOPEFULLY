#pragma once
#include "CGameObject.h"
#include "CUI.h"
#include "CMAP.h"
#include "CInventory.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;

class NPC :
	public CGameObject
{
	string name;
	char symbol;
	int age;
	string occupation;
	bool killerStatus;
	string description;
	string dialogue;
	struct DialogueOption {
		string text;
		int nextNode;
		int Eventflag = 0;
	};
	struct DialogueNode {
		string speaker; //added speaker 
		string npcLine;
		vector<DialogueOption> options;
	};
	vector<DialogueNode> DialougeTree;
	int currentNode = 0;
	int selectedOption = 0;
	int Eventstate;
	int PresentPosition = 0;
	int lastRemovedEvidenceID = -1;
	bool isPresentEvidenceOpen = false;
	bool evidenceCorrect = false;
	int matchedIndex = -1; // added this
	struct IsEvidenceCorrect {
		vector<int> ExpectedIDs; //turned this to a list
		vector<int> CorrectNode; //same for this
		int incorrectNode;
	};
	unordered_map<int, IsEvidenceCorrect> evidenceRequests;
	int path;
	int storeEvidenceId[4];
	int evidenceCounter = 0;
	bool isEvidenceValid;
	int numOfWrongEvidence;

public:
	enum People
	{
		Sarah_Collins,
		Emily_Smith,
		Michael_Turner,
		Trisha_Lopez,
		Angelo_Batista,
		Harvey_Denn,
		Forensics,
		Jonathan_Smith,
		Silias_Reeds,
		Police,
		Narrator //added narrator
	};

	void setPerson(People p);
	People getPerson();
	string getName();
	char getSymbol();
	int getAge();
	string getOccupation();
	bool getKillerStatus();
	bool isSuspect();
	string getDialogue();
	string setDialogue(string text);
	int getCurrentNode();//for items
	int getCurrentEvent();//for items
	int getLastRemovedEvidenceID();
	void setIsEvidenceValid(bool input);
	bool getIsEvidenceValid();
	int getPath();
	int getNumOfWrongEvidence();
	void setEvidenceCounter(int reset);


	void ResetDialogueTree();
	void RenderDialougeSystem(bool typetext, CMap* map);
	void dialougesystem(CMap* map, inventorySystem* inventory);
	int AddDialougeNode(string npcDialouge, string ovrdSpeaker = ""); //ovrdSpeaker = overide speaker for Narrator
	void AddNodeOption(int nodeIndex, int eventState, int Go_To_Node_Index, string text);
	void Addeventflag();
	vector<int> GetVisibleOptions(const DialogueNode& node);
	void presentEvidence(inventorySystem* Inventory, vector<int>& ids, char input); //change id to vector
	void RenderPresentEvidence(inventorySystem* Inventory);
	void SwitchEvidence(char input, inventorySystem* inventory);
	void showPresentEvidence(inventorySystem* inventory);
	bool GetisPresentOpen();
	string GetDescription();
	static const int PRESENT_EVIDENCE = -2;
	int checkEvidence(int evidenceCounter, int currentNode, const set<int>& evidenceInput);

	void SetEvidenceRequest(int nodeIndex, int expectedItemID, int correctNode, int incorrectNode);
	void SetEventStartNode(int eventState, int nodeIndex); //added this
	NPC();

	struct EvidenceCheck {
		int expectedItemID;
		int correctNode;
		int incorrectNode;
	};
private:

	People person;
	vector<int> eventStartNodes; //for storingg the cur event starting node

};

