#pragma once
#include "CMap.h"
#include "Cinventory.h"
#include "CcaseFileSystem.h"
#include "CNPC.h"
#include "CUI.h"
#include "CObstacle.h"
#include "CPuzzleSystem.h" 
#include "CItem.h"
#include <vector>
class CGameManager
{
	struct NodeItems {
		NPC* npc;
		int node;
		string itemName;
		CItem::Items itemType;
	};
	struct NodeEvidence { //new stuff for handing evidence
		NPC* npc;
		int node;
		CEvidence::Evidence evidenceType;
	};
	struct NodeFlags {
		NPC* npc;
		int node;
		bool* flag;
	};
	vector<NodeFlags> nodeFlags;
	void checkNodeFlags(NPC* npc);

	vector<NodeItems> nodeItems;
	void checkNodeItems(NPC* npc);

	vector<NodeEvidence> nodeEvidence;
	void checkNodeEvidence(NPC* npc);

	int static const MAX_MAPS = 15;
	static const int MAX_OBSTACLE = 200;
	CMap map[MAX_MAPS];
	int currentMap;
	int currentUI;
	bool IsGameRunning;
	inventorySystem* inventory = new inventorySystem;
	CcaseFileSystem caseFileSystem;
	PuzzleSystem puzzleSystem;
	NPC* NPCs;
	vector<vector<int>> Connect;
	vector<vector<CObstacle*>> mapObstacles;
	vector<vector<NPC*>> mapNPCs;
	CObstacle* Obstacle[MAX_OBSTACLE];
	int const static MAX_EVIDENCE = 11;
	CObstacle* Evidenceptr[MAX_EVIDENCE];
	CObstacle* ObstacleInteract;
	CEvidence Evidence;
	CGameManager* evidence = nullptr;
	int item = 1;
	CItem Items;
	vector<CItem*> allItems;
	CItem* addItems(CObstacle* obstacle, CItem::Items type);
	bool CanTravel = false;
	bool CanTravel2 = false; //added this
	bool itemExists = false;

	/* is visible/present or unlocked */
	bool IsBedroomkeyPresent = false;
	bool IsMansionAvailable = false;
	bool IsCollinAvailable = false;
	bool IsProsecutorAvailable = false;
	bool IsMainPorchAvailable = false;
	bool IsMainStudyAvailable = false;
	bool IsCollinPorchVisible = false;
	bool IsCaseFileUnlocked = false;

	
	/*Has interact to*/
	bool hasTalkToSilas = false;
	bool hasTalkToBatista = false;
	bool hasShownEmilyEvi1 = false;
	bool hasFinishEmily = false;
	bool hasTalkToSarah1 = false;
	bool hasShownEviToSarah = false;
	bool hasTalkToSarah2 = false;
	bool hasTalkToTrisha = false;
	bool hasShownEmilyGlass = false;
	bool hasTalkToMichael1 = false;
	bool hasTalkToMichael3 = false;
	bool takeAPiss = false;
	bool hasTalkedToMichaelAgain = false;

	/*Has found Evidence*/
	bool candlestickFound = false;
	bool whiskeyGlassFound = false;
	bool gunpowderFound = false;
	bool bankStatementFound = false;
	bool divorcePapersFound = false;
	bool gloveFound = false;
	bool shoeboxFound = false;
	bool whiskeyGlassRptCollected = false;

	/*Has found item*/
	bool NotebookisFound = false;
	bool CarKeysisFound = false;
	bool jacketisFound = false;

	/*has passed to batista */
	bool hasPassCandle = false;
	bool hasPassGlass = false;
	bool hasPassGlove = false;

	/* NPC and node set*/
	NPC* Silas = new NPC;
	NPC* batista2 = nullptr; //added this
	NPC* batista3 = nullptr; //added this
	NPC* emily = nullptr; //adeded this
	NPC* sarah = nullptr; //adeded this
	NPC* michael = nullptr; //added this
	int nB4_1_id = -1; //for batista event stuff
	int nB5_1_candle_id;
	int nB5_1_glass_id;
	int nB5_1_glove_id;

	vector<bool> mapVisited;
	vector<vector<pair<string, string>>> mapIntroDialogue;
	vector<bool> mapRemoved;
public:
	int SelectDestination(vector<int>& options);
	CObstacle* AddObstacle(int mapIndex, CObstacle::Furniture type, int x, int y, bool rotation);
	NPC* AddNPC(int mapIndex, NPC::People type, int x, int y);
	NPC* FindNPC(int mapIndex, int x, int y);
	void displayDialogue(string c, string t);
	void TestDialogue();
	void SetMaps();
	void changeMaps(char input);
	void RunGame();
	CObstacle* FindObstacle(int mapIndex, int x, int y);
	bool IsMapUnlocked(int mapIndex);
	void PlayIntroDialogue(int mapIndex);
	void RemoveRoom(int mapIndex);
	int GetDialogue_Length(CEvidence::Evidence e);
	void checkForAllEvidence(CObstacle* oPtr);
	void checkForEvidence(CObstacle* oPtr, CObstacle*& ptr, CEvidence::Evidence e);
	CGameManager* GetEvidencePtr();


	CGameManager();
	~CGameManager();

};
