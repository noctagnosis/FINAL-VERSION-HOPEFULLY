 #include "CNPC.h"

void NPC::setPerson(People p) {

	person = p;
	switch (p) 
	{
	case Sarah_Collins:
		name = "Sarah Collins";
		symbol = 'S';
		age = 39;
		occupation = "Neighbour / Freelance Interior Designer";
		description = "Lives alone in the property adjoining the Smith estate. Soft-spoken "
			"and quick to smile, though it rarely reaches her eyes. Claims no alibi "
			"for the night of the murder - she says she was home, but no one can "
			"confirm it. A years-long property dispute with the Smiths over a "
			"shared fence line has left more bad blood between the households than "
			"she initially let on.";
		killerStatus = false;
		break;
	case Emily_Smith:
		name = "Emily Smith";
		symbol = 'E';
		age = 47;
		occupation = "Homemaker (formerly Corporate Lawyer)";
		description = "Jonathan Smith's wife of eighteen years. Composed in front of "
			"officers, but the composure cracks under pressure. Claims she was "
			"upstairs reading at the time of the murder. Unsigned divorce papers "
			"found hidden in her bedroom suggest the marriage was far less stable "
			"than she's willing to admit, and recent unexplained withdrawals from "
			"the couple's shared accounts have only deepened the questions around "
			"her husband's finances.";
		killerStatus = false;
		break;
	case Michael_Turner:
		name = "Michael Turner";
		symbol = 'M';
		age = 50;
		occupation = "Co-Founder, Smith Holdings";
		description = "Jonathan Smith's longtime business partner, and by most accounts "
			"the one who actually built the company from the ground up. Defensive "
			"and quick-tempered when questioned, particularly about the exact time "
			"he left the mansion. Insists the maid can confirm his alibi. A "
			"fingerprint lifted from a broken whiskey glass at the scene places him "
			"in the study far more recently than he's admitted.";
		killerStatus = true;
		break;
	case Trisha_Lopez:
		name = "Trisha Lopez";
		symbol = 'T';
		occupation = "Live-in Housekeeper";
		description = "Has worked for the Smith household for just under three years. "
			"Quiet, observant, and the first person to discover something was "
			"wrong on the night of the murder. Says little unless asked directly, "
			"and even then, chooses her words carefully - as someone who works in "
			"a house full of secrets tends to learn to do.";
		killerStatus = false;
		break;
	case Angelo_Batista:
		name = "Angelo Batista";
		symbol = 'B';
		age = 5;
		occupation = "";
		killerStatus = false;
		break;
	case Harvey_Denn:
		name = "Harvey Denn";
		symbol = 'H';
		age = 6;
		occupation = "";
		killerStatus = false;
		break;
	case Forensics:
		name = "Forensics";
		symbol = 'F';
		age = 7;
		occupation = "";
		killerStatus = false;
		break;
	case Jonathan_Smith:
		name = "Jonathan Smith";
		symbol = 'J';
		age = 8;
		occupation = "";
		killerStatus = false;
		break;
	case Police:
		name = "Police";
		symbol = 'P';
		age = 9;
		occupation = "";
		killerStatus = false;
		break;
	case Silias_Reeds:
		name = "Silias Reeds";
		symbol = '$';
		age = 10;
		occupation = "";
		killerStatus = false;
		break;
	case Narrator: //added narrator
		name = "Narrator";
		symbol = 'n';
		age = 11;
		occupation = "";
		killerStatus = false;
		break;
	}
}

NPC::People NPC::getPerson()
{
	return person;
}

vector<int> NPC::GetVisibleOptions(const DialogueNode& node) {
	vector<int> visible;
	for (int i = 0; i < (int)node.options.size(); i++) {
		if (node.options[i].Eventflag <= Eventstate) {
			visible.push_back(i);
		}
	}
	return visible;
}

void NPC::ResetDialogueTree() {
	DialougeTree.clear();
	currentNode = 0;
	selectedOption = 0;
	Eventstate = 0;
}

int NPC::AddDialougeNode(string npcDialouge, string ovrdSpeaker) {
	DialogueNode node;
	node.npcLine = npcDialouge;
	if (ovrdSpeaker.empty()) {
		node.speaker = name;
	}
	else {
		node.speaker = ovrdSpeaker;
	}
	DialougeTree.push_back(node);
	return (int)DialougeTree.size() - 1;
}

void NPC::AddNodeOption(int nodeIndex, int eventState, int Go_To_Node_Index, string text) {
	DialogueNode node;
	if (nodeIndex >= 0 && nodeIndex < (int)DialougeTree.size()) {
		DialougeTree[nodeIndex].options.push_back({ text, Go_To_Node_Index, eventState });
	}
}
string NPC::GetDescription(){
	return description;
}

int NPC::checkEvidence(int evidenceCounter, int currentNode, const set<int>& evidenceInput) {
	int NumOFIncorrect = 0;
	static const map<int, set<int>> evidenceSet = {
		{3, {3010, 3011}},
		{4, {3008, 3009}},
		{5, {3001, 3005, 3006, 3007}}
	};
	auto evidenceRequired = evidenceSet.at(currentNode);
	if (evidenceCounter == static_cast<int>(evidenceRequired.size()) && evidenceInput == evidenceRequired) {
		setIsEvidenceValid(true);
		path = currentNode;
	}
	else {
		for (int requiredID : evidenceRequired) {
			if (evidenceInput.find(requiredID) == evidenceInput.end()) {
				NumOFIncorrect++;
			}
		}
		setIsEvidenceValid(false);
		return NumOFIncorrect;
	}
}

string NPC::getName() {
	return name;
}

char NPC::getSymbol() {
	return symbol;
}

int NPC::getAge() {
	return age;
}

string NPC::getOccupation() {
	return occupation;
}

bool NPC::getKillerStatus() {
	return killerStatus;
}


bool NPC::isSuspect()
{
	switch (person) {
	case Emily_Smith:
	case Sarah_Collins:
	case Michael_Turner:
	case Trisha_Lopez:
		return true;
	}
	return false;
}

string NPC::getDialogue() {
	return dialogue;
}
void NPC::RenderDialougeSystem(bool typetext, CMap* map) {
	CUI::GetInstance().Clear();
	map->RenderMap();
	bool dialougePrintoutFinished = false;
	const DialogueNode& node = DialougeTree[currentNode]; 
	string fullLine = "\033[32m" + node.speaker + "\033[0m" + ": " + node.npcLine; //change name to node.speaker
	int boxWidth = (int)fullLine.length() - 9 + 6;

	cout << "+" << std::string(boxWidth - 2, '-') << "+\n";
	cout << "|  ";
	if (typetext) {
		CUI::GetInstance().typeText(fullLine);
	}
	else if(!typetext){
		cout << fullLine;
	}
	cout << "  |\n";
	cout << "+" << std::string(boxWidth - 2, '-') << "+\n";
	vector<int> visible = GetVisibleOptions(node);
	for (int i = 0; i < (int)visible.size(); i++) {
		int optIdx = visible[i];
		if (i == selectedOption)
			cout << "   ~> " << node.options[optIdx].text << endl;
		else
			cout << "      " << node.options[optIdx].text << endl;
	}
}
void NPC::dialougesystem(CMap* map, inventorySystem* inventory) {
	if (Eventstate >= 0 && Eventstate < (int)eventStartNodes.size() && eventStartNodes[Eventstate] != -1) {
		currentNode = eventStartNodes[Eventstate];
	}
	else {
		currentNode = 0;
	}
	selectedOption = 0;
	int lastnode = -1;
	bool talking = true;

	while (talking) {
		bool typetext = (currentNode != lastnode);
		RenderDialougeSystem(typetext, map);
		lastnode = currentNode;
		const DialogueNode& node = DialougeTree[currentNode];
		vector<int> visible = GetVisibleOptions(node);

		int input = _getch();

		if (input == 0 || input == 224) {
			input = _getch();

			if (input == 72 && selectedOption > 0) {
				selectedOption--;
			}
			else if (input == 80 && selectedOption < (int)visible.size() - 1) {
				selectedOption++;
			}
		}
		else if (input == 13) {
			if (visible.empty()) {
				continue;
			}

			int actualOptIdx = visible[selectedOption];
			int next = node.options[actualOptIdx].nextNode;

			if (next == PRESENT_EVIDENCE) {
				auto it = evidenceRequests.find(currentNode);
				vector<int> expectedIDs;
				if (it != evidenceRequests.end()) {
					expectedIDs = it->second.ExpectedIDs;
				}

				isPresentEvidenceOpen = true;
				PresentPosition = 0;

				while (isPresentEvidenceOpen) {
					RenderPresentEvidence(inventory);
					int evInput = _getch();

					if (evInput == 0 || evInput == 224) {
						evInput = _getch();
						SwitchEvidence((char)evInput, inventory);
					}
					else {
						presentEvidence(inventory, expectedIDs, (char)evInput);
					}
				}
				 
				if (it != evidenceRequests.end()) { //change and added these
					if (evidenceCorrect && matchedIndex >= 0 && matchedIndex < (int)it->second.CorrectNode.size()) {
						int whichNPC = currentNode;
						currentNode = it->second.CorrectNode[matchedIndex];
						if (person == Forensics) {
							lastRemovedEvidenceID = expectedIDs[matchedIndex];
							inventory->removeFromInventory(PresentPosition);
						}
						else if (person == Harvey_Denn) {
							int id;
							storeEvidenceId[evidenceCounter] = id = inventory->GetInventoryID(PresentPosition);
							evidenceCounter++;

							if (evidenceCounter == 2) {
								if (whichNPC == 3) {
									int EviID1 = storeEvidenceId[0];
									int EviID2 = storeEvidenceId[1];
									set<int> givenEvidence = { EviID1, EviID2 };
									numOfWrongEvidence = checkEvidence(2, 3, givenEvidence);
									talking = false;
								}
								else if (whichNPC == 5) {
									int EviID1 = storeEvidenceId[0];
									int EviID2 = storeEvidenceId[1];
									set<int> givenEvidence = { EviID1, EviID2 };
									numOfWrongEvidence = checkEvidence(2, 5, givenEvidence);
									talking = false;

								}
							}

							else if (evidenceCounter == 4) {
								if (whichNPC == 4) {
									int EviID1 = storeEvidenceId[0];
									int EviID2 = storeEvidenceId[1];
									int EviID3 = storeEvidenceId[2];
									int EviID4 = storeEvidenceId[3];
									set<int> givenEvidence = { EviID1, EviID2, EviID3, EviID4 };
									numOfWrongEvidence = checkEvidence(4, 4, givenEvidence);
									talking = false;
								}
							}
						}

					}

					else {
						currentNode = it->second.incorrectNode;
					}
				}

				selectedOption = 0;
				map->RenderMap();
			}
			else if (next == -1) {
				talking = false;
			}
			else {
				currentNode = next;
				selectedOption = 0;
			}
		}
		else if (input == 27) {
			talking = false;
		}
	}
}

void NPC::Addeventflag() {
	Eventstate++;
}

int NPC::getCurrentNode() {
	return currentNode;
}

int NPC::getCurrentEvent() { //added this to get event
	return Eventstate;
}

void NPC::SetEvidenceRequest(int nodeIndex, int expectedItemID, int correctNode, int incorrectNode) {
	evidenceRequests[nodeIndex].ExpectedIDs.push_back(expectedItemID);
	evidenceRequests[nodeIndex].CorrectNode.push_back(correctNode);
	evidenceRequests[nodeIndex].incorrectNode = incorrectNode;
}

void NPC::RenderPresentEvidence(inventorySystem* Inventory) {
	CUI::GetInstance().Clear();
	cout << "       [Present Evidence]\n";
	cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
	for (int i = 0; i < Inventory->GetItemCount(); i++) {
		if (i == PresentPosition) {
			cout << "~> " << Inventory->GetInventory(i) << endl;
		}
		else {
			cout << "   " << Inventory->GetInventory(i) << endl;
		}
	}
	cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
}

void NPC::SwitchEvidence(char input, inventorySystem* inventory) {
	if (input == 72) {
		if (PresentPosition > 0) {
			PresentPosition -= 1;
		}
	}
	else if (input == 80) {
		if (PresentPosition < inventory->GetItemCount() - 1) {
			PresentPosition += 1;
		}
	}
}

void NPC::presentEvidence(inventorySystem* Inventory, vector<int>& ids, char input) {
	if (input == 0 || input == (char)224) {
		SwitchEvidence(input, Inventory);
	}
	else if (input == 13) {
		matchedIndex = -1;
		if (Inventory->GetItemCount() > 0) {
			int chosenID = Inventory->GetInventoryID(PresentPosition);
			for (int i = 0; i < (int)ids.size(); i++) {
				if (chosenID == ids[i]) {
					matchedIndex = i;
					break;
				}
			}
		}
		evidenceCorrect = (matchedIndex != -1);
		isPresentEvidenceOpen = false;
	}
	else if (input == 27) {
		evidenceCorrect = false;
		isPresentEvidenceOpen = false;
	}
}

void NPC::showPresentEvidence(inventorySystem* inventory) {
	if (isPresentEvidenceOpen) {
		RenderPresentEvidence(inventory);
	}
}

bool NPC::GetisPresentOpen() {
	return isPresentEvidenceOpen;
}

int NPC::getLastRemovedEvidenceID() {
	return lastRemovedEvidenceID;
}

void NPC::setIsEvidenceValid(bool input)
{
	isEvidenceValid = input;
}

bool NPC::getIsEvidenceValid()
{
	return isEvidenceValid;
}

int NPC::getPath()
{
	return path;
}

int NPC::getNumOfWrongEvidence()
{
	return numOfWrongEvidence;
}

void NPC::setEvidenceCounter(int reset)
{
	evidenceCounter = reset;
}

NPC::NPC() {
	ResetDialogueTree();
	Eventstate = 0;
	person = Sarah_Collins;
	name = "";
	symbol = '\0';
	age = 0;
	occupation = "";
	killerStatus = false;
	SetPosX(0);
	SetPosY(0);
	eventStartNodes.resize(10, -1); // added this, event states 0 through 9
}

void NPC::SetEventStartNode(int eventState, int nodeIndex) { //added this
	if (eventState >= 0 && eventState < (int)eventStartNodes.size()) {
		eventStartNodes[eventState] = nodeIndex;
	}
}
