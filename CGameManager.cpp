#include "CGameManager.h"
#include <iostream>


CObstacle* CGameManager::AddObstacle(int mapIndex, CObstacle::Furniture type, int x, int y, bool rotation)
{
    CObstacle* Furniture = new CObstacle();
    Furniture->SetType(type);
    Furniture->SetPosX(x);
    Furniture->SetPosY(y);
    if (rotation) {
        Furniture->Rotate();
    }
    mapObstacles[mapIndex].push_back(Furniture);
    return Furniture;
}

NPC* CGameManager::AddNPC(int mapIndex, NPC::People type, int x, int y)
{
    NPC* People = new NPC();
    People->setPerson(type);
    People->SetPosX(x);
    People->SetPosY(y);

    mapNPCs[mapIndex].push_back(People);
    return People;
}

CObstacle* CGameManager::FindObstacle(int mapIndex, int x, int y) {
    for (int i = 0; i < (int)(mapObstacles[mapIndex].size()); i++) {
        CObstacle* O = mapObstacles[mapIndex][i];

        int OX = O->GetPosX();
        int OY = O->GetPosY();
        int OWidth = O->GetWidth();
        int OHeight = O->GetHeight();

        if (x >= OX && x < OX + OWidth && y >= OY && y < OY + OHeight) {
            return O;
        }
    }
    return nullptr;
}

NPC* CGameManager::FindNPC(int mapIndex, int x, int y) {
    for (int i = 0; i < (int)(mapNPCs[mapIndex].size()); i++) {
        NPC* npc = mapNPCs[mapIndex][i];

        if (npc->GetPosX() == x && npc->GetPosY() == y) {
            return npc;
        }
    }
    return nullptr;
}
CItem* CGameManager::addItems(CObstacle* obstacle, CItem::Items type) {
    CItem* newItem = new CItem();
    newItem->SetItem(obstacle, type);
    obstacle->SetItemPtr(newItem);
    allItems.push_back(newItem);
    return newItem;
}

void CGameManager::RemoveRoom(int mapIndex) {
    if (mapIndex < 0 || mapIndex >= MAX_MAPS) return;
    if (mapRemoved[mapIndex]) return;
    for (CObstacle* o : mapObstacles[mapIndex]) {
        delete o;
    }
    mapObstacles[mapIndex].clear();
    for (NPC* n : mapNPCs[mapIndex]) {
        nodeItems.erase(
            std::remove_if(nodeItems.begin(), nodeItems.end(),
                [n](const NodeItems& r) { return r.npc == n; }),
            nodeItems.end());

        nodeFlags.erase(
            std::remove_if(nodeFlags.begin(), nodeFlags.end(),
                [n](const NodeFlags& r) { return r.npc == n; }),
            nodeFlags.end());

        if (n == Silas) Silas = nullptr;
        delete n;
    }
    mapNPCs[mapIndex].clear();
    map[mapIndex].DeleteRoom();
    mapRemoved[mapIndex] = true;
}

bool CGameManager::IsMapUnlocked(int mapIndex) {
    if (mapRemoved[mapIndex]) return false;
    switch (mapIndex) {
    case 3: // Master Bedroom
        return IsBedroomkeyPresent;

    case 12:
        return IsCollinAvailable;

    case 11: //mansion
        return IsMansionAvailable;

    case 10: // Prosecutor's Office
        return IsProsecutorAvailable;

    case 13: // Main Porch
        return IsMainPorchAvailable;

    case 14: // Main Studyroom
        return IsMainStudyAvailable;


    default:
        return true;
    }
}
int CGameManager::GetDialogue_Length(CEvidence::Evidence e) {
    Evidence.SetEvidence(e);
    int length = Evidence.GetLength();
    return length;
}

void CGameManager::checkForAllEvidence(CObstacle* oPtr)
{
    for (int i = 0; i < MAX_EVIDENCE; i++) {
        checkForEvidence(oPtr, Evidenceptr[i], static_cast<CEvidence::Evidence>(i));
    }
}

// CGameManager.cpp
void CGameManager::checkForEvidence(CObstacle* oPtr, CObstacle*& ptr, CEvidence::Evidence e)
{
    if (oPtr != nullptr && oPtr == ptr) {
        Evidence.SetEvidence(e);
        for (int i = 0; i < GetDialogue_Length(e); i++) {
            displayDialogue("Narrator", oPtr->runDialogue(e, i));
        }
        inventory->addToInventory(oPtr->GetEvidenceName(e), oPtr->GetEvidenceId(), ""); 
        caseFileSystem.addEvidence(e);
        caseFileSystem.addDescription(Evidence.GetDescription());
        Evidence.SetFound(true);
        ptr = nullptr; 
    }
}

CGameManager* CGameManager::GetEvidencePtr()
{
    return evidence;
}
void CGameManager::EmilyEndingDialogue()
{
    displayDialogue("Narrator", "After further investigation...");
    displayDialogue("Narrator", "And the court trial...");
    displayDialogue("Narrator", "Emily was found guilty");
    displayDialogue("Narrator", "however...");
    displayDialogue("Narrator", "she was not the killer");
    displayDialogue("Narrator", "The killer is still yet to be found");
    displayDialogue("Narrator", "Lurking in the shadows...");
    displayDialogue("Narrator", "He/she managed to escape this time...");
    displayDialogue("Narrator", "Will there be a next time?...");
    displayDialogue("Narrator", "THE END");
    IsGameRunning = false;
}
void CGameManager::MichaelEndingDialogue()
{
    displayDialogue("Narrator", "After further investigation...");
    displayDialogue("Narrator", "And the court trial...");
    displayDialogue("Narrator", "Michael was found...");
    displayDialogue("Narrator", "GUILTY");
    displayDialogue("Narrator", "Sentenced to jail for life");
    displayDialogue("Narrator", "With no friend or family to visit him");
    displayDialogue("Narrator", "Repaying for his sins in Willow Creaks bad people prison");
    displayDialogue("Narrator", "THE END");
    IsGameRunning = false;

}
void CGameManager::SarahEndingDialogue()
{
    displayDialogue("Narrator", "After further investigation...");
    displayDialogue("Narrator", "And the court trial...");
    displayDialogue("Narrator", "Sarah was found guilty");
    displayDialogue("Narrator", "however...");
    displayDialogue("Narrator", "she was not the killer");
    displayDialogue("Narrator", "The killer is still yet to be found");
    displayDialogue("Narrator", "Lurking in the shadows...");
    displayDialogue("Narrator", "He/she managed to escape this time...");
    displayDialogue("Narrator", "Will there be a next time?...");
    displayDialogue("Narrator", "THE END");
    IsGameRunning = false;
}
void CGameManager::checkNodeFlags(NPC* npc) {
    for (int i = 0; i < (int)nodeFlags.size(); i++) {
        NodeFlags r = nodeFlags[i];
        if (r.npc == npc && npc->getCurrentNode() == r.node) {
            *r.flag = true;
        }
    }
}
void CGameManager::PlayIntroDialogue(int mapIndex) {
    for (auto& line : mapIntroDialogue[mapIndex]) {
        displayDialogue(line.first, line.second);
    }
}

void CGameManager::SetMaps() {

    mapRemoved.resize(MAX_MAPS, false);
    mapVisited.resize(MAX_MAPS, false);
    mapIntroDialogue.resize(MAX_MAPS);
    mapVisited[0] = true;
    mapObstacles.resize(MAX_MAPS);



    // Adding NPCs to the map
    NPC* narrator = new NPC();
    narrator->setPerson(NPC::Narrator);

    mapNPCs.resize(MAX_MAPS);



    /*---- Mr SIlas Reed ----*/
    Silas = AddNPC(0, NPC::Silias_Reeds, 5, 3);
    //nSR1_0: n = "node", SR = SILAS REED, 0 = EventState, _1 = node number.
    int nSR0_1 = Silas->AddDialougeNode("The call's from your friend, Detective Batista... you know? the funky one");
    int nSR0_2 = Silas->AddDialougeNode("yeah your friend from back in the academy");
    int nSR0_3 = Silas->AddDialougeNode("i got no cash to bet rowan.. flat broke, we really need more cases. this isn't a freebie remember.");
    int nSR0_4 = Silas->AddDialougeNode("He needs help, some rich guy found dead, in his own mansion.");
    int nSR0_5 = Silas->AddDialougeNode("um Batista said it was further from the city some mansion down in Willow's Creek. ill drive.");
    int nSR0_6 = Silas->AddDialougeNode("not sure, he says just look for the mansion surrounded by police.");
    int nSR0_7 = Silas->AddDialougeNode("Right...lets go (You unlocked The Movement to the Mansion)");
    Silas->AddNodeOption(nSR0_1, 0, nSR0_2, "Batista huh?");
    Silas->AddNodeOption(nSR0_2, 0, nSR0_3, "Right right, i wonder if he has gone bald now...wanna bet?");
    Silas->AddNodeOption(nSR0_3, 0, nSR0_4, "Aah, just a small bet nothing harmful. Anyways, why did he call?");
    Silas->AddNodeOption(nSR0_4, 0, nSR0_5, "I see, where is it?");
    Silas->AddNodeOption(nSR0_5, 0, nSR0_6, "Willow's Creek? Mansion? could be the Smiths? the Collins? or the Addams?");
    Silas->AddNodeOption(nSR0_6, 0, -1, "Hmmm");

    Silas->AddNodeOption(nSR0_1, 1, nSR0_7, "aight let's go, we finally getting something good hehehe.");
    Silas->AddNodeOption(nSR0_7, 1, -1, "Let me grab my stuff first...");

    Silas->AddNodeOption(nSR0_1, 0, -1, "Nevermind");
    nodeFlags.push_back({ Silas, nSR0_7, &IsMansionAvailable });
    nodeFlags.push_back({ Silas, nSR0_7, &CanTravel });

   
    /*--------------------------------------------------------------------------------------------------------------------------------------*/
    /*---- Mrs Emily Smith ----*/
    ///* Event 1 (First Interaction) */
    emily = AddNPC(1, NPC::Emily_Smith, 7, 4);



    int nE1_1 = emily->AddDialougeNode("...Yes?"); //nE1_1: n = "node", E = Emily, 1 = EventState, _1 = node number.
    int nE1_2 = emily->AddDialougeNode("Yes, I was in my room reading. My Maid, Trisha, ran in to told me about it. I-I couldn't believe it.");
    int nE1_3 = emily->AddDialougeNode("* Sobs *");
    int nE1_4 = emily->AddDialougeNode("Emily sat back down on the couch", narrator->getName());

    emily->AddNodeOption(nE1_1, 0, nE1_2, "It says here, you were upstair reading during the time of murder correct?");
    emily->AddNodeOption(nE1_1, 0, -1, "Never mind.");

    emily->AddNodeOption(nE1_2, 0, nE1_3, "I See, Thanks for confirming");  // eventFlag = 1

    emily->AddNodeOption(nE1_3, 0, nE1_4, "...?");

    emily->AddNodeOption(nE1_4, 0, -1, "...");


    /* Event 2 (Need Masterbedroom key) */


    int nE2_1 = emily->AddDialougeNode("...Yes?");
    int nE2_2 = emily->AddDialougeNode("Why? It has nothing to do with what happened in the study.");
    int nE2_3 = emily->AddDialougeNode("...Rule me out? ...Fine here (You received a Bedroom Key)");
    nodeItems.push_back({ emily, nE2_3, "Master Bedroom Key", CItem::MASTER_BEDROOM_KEY });
    int nE2_4 = emily->AddDialougeNode("...Fine. I don't need this looking worse than it already does. (You received a Bedroom Key)");
    nodeItems.push_back({ emily, nE2_4, "Master Bedroom Key", CItem::MASTER_BEDROOM_KEY });
    int nE2_5 = emily->AddDialougeNode("Excuse me?");
    int nE2_6 = emily->AddDialougeNode("My husband is dead! And you're already accusing me in my own home?");

    emily->AddNodeOption(nE2_1, 1, nE2_2, "Mrs. Smith, we need access to the master bedroom,");
    emily->AddNodeOption(nE2_1, 1, -1, "Never mind.");

    emily->AddNodeOption(nE2_2, 1, nE2_3, "We're not here to invade your life. We're here to rule you out");

    emily->AddNodeOption(nE2_2, 1, nE2_4, "If there's nothing in there, this takes two minutes. If you keep stalling, it doesn't look good.");

    emily->AddNodeOption(nE2_2, 1, nE2_5, "What are you hiding in there, Mrs. Smith?");

    emily->AddNodeOption(nE2_3, 1, -1, "...");
    emily->AddNodeOption(nE2_4, 1, -1, "...");
    emily->AddNodeOption(nE2_5, 1, nE2_6, "...");
    emily->AddNodeOption(nE2_6, 1, -1, "...");

    emily->SetEventStartNode(1, nE2_1);

    /* Event 3 (Evidence presenting 1) */


    int nE3_1 = emily->AddDialougeNode("...Yes?");
    int nE3_2 = emily->AddDialougeNode("Emily straigtens, composing herself", narrator->getName());
    int nE3_3 = emily->AddDialougeNode("Our marriage was fine, Detective. We had our disagreements, like any couple...");
    int nE3_4 = emily->AddDialougeNode("But nothing serious. Nothing that would make me want him gone, if that's what you're getting at.");
    int nE3_5 = emily->AddDialougeNode("I don't know what you think you're going to find, but there's nothing there.");
    /*correfct*/
    int nE1_correct = emily->AddDialougeNode("Black sets the envelope down on the table between them.", narrator->getName());
    int nE2_correct = emily->AddDialougeNode("Emily's eyes drop to it. The color drains from her face, and for a moment she says nothing at all.", narrator->getName());
    int nE3_correct = emily->AddDialougeNode("...Where did you find that ?");
    int nE4_correct = emily->AddDialougeNode("Okay.It wasn't- it wasn't fine. Not really.I just... didn't want it to be true.");
    /*Wrong*/
    int nE1_wrong = emily->AddDialougeNode("What's that? what does that have to do with me?");
    /*Avoid*/
    int nE1_avoid = emily->AddDialougeNode("We will show that later...", Silas->getName());

    emily->AddNodeOption(nE3_1, 2, nE3_2, "Mrs. Smith...I have to ask. How was your marriage, really?");
    emily->AddNodeOption(nE3_1, 2, -1, "Never mind.");

    emily->AddNodeOption(nE3_2, 2, nE3_3, "...");
    emily->AddNodeOption(nE3_3, 2, nE3_4, "...");
    emily->AddNodeOption(nE3_4, 2, nE3_5, "...");

    emily->AddNodeOption(nE3_5, 2, NPC::PRESENT_EVIDENCE, "LIE DETECTED! [Present Evidence]");
    emily->SetEvidenceRequest(nE3_5, 3011, nE1_correct, nE1_wrong);
    emily->SetEvidenceRequest(nE3_5, 3010, nE1_avoid, nE1_wrong);
    emily->AddNodeOption(nE3_5, 2, -1, "Never mind.");

    emily->AddNodeOption(nE1_correct, 2, nE2_correct, "Then what's this?");
    emily->AddNodeOption(nE2_correct, 2, nE3_correct, "...");
    emily->AddNodeOption(nE3_correct, 2, nE4_correct, "* sigh *");
    emily->AddNodeOption(nE4_correct, 2, -1, "...");
    nodeFlags.push_back({ emily, nE4_correct, &hasShownEmilyEvi1 });

    emily->AddNodeOption(nE1_avoid, 2, nE3_5, "...");

    emily->AddNodeOption(nE1_wrong, 2, nE3_5, "...");


    emily->SetEventStartNode(2, nE3_1);


    /* Event 4 (Evidence presenting 2) */

    int nE4_1 = emily->AddDialougeNode("...");
    int nE4_2 = emily->AddDialougeNode("We can't write you off the suspect list if you lie to us again, Mrs. Smith,", Silas->getName());
    int nE4_3 = emily->AddDialougeNode("Emily wraps her arms around herself, eyes fixed on the envelope.", narrator->getName());
    int nE4_4 = emily->AddDialougeNode("Money...It started with money.");
    int nE4_5 = emily->AddDialougeNode("Jonathan started pulling cash out of our accounts months ago. Large amounts.When I asked, he'd brush it off");
    int nE4_6 = emily->AddDialougeNode("'business expenses' he'd say. Never any details...We used to talk about everything.");
    int nE4_7 = emily->AddDialougeNode("Then suddenly I'm finding out about our own finances from bank statements he thought I wasn't looking at.");
    int nE4_8 = emily->AddDialougeNode("No. I asked. He got angry every time I brought it up...angrier than I'd ever seen him over money before. ");
    int nE4_9 = emily->AddDialougeNode("That's when I did the divorce paper. Not because I stopped loving him. Because I didn't know who he was anymore. ");
    /*correfct*/
    int nE1_correct2 = emily->AddDialougeNode("Black pulls out the statement, laying it beside the envelope.", narrator->getName());
    int nE2_correct2 = emily->AddDialougeNode("Yes. Exactly like that. Over and over, no explanation.");
    int nE3_correct2 = emily->AddDialougeNode("No...");
    int nE4_correct2 = emily->AddDialougeNode("But if I had to guess... I'd start with Michael , his business partner.");
    /*Wrong*/
    int nE1_wrong2 = emily->AddDialougeNode("Don't think that matters in this situation...", Silas->getName());

    emily->AddNodeOption(nE4_1, 3, nE4_2, "Tell me what the issue was between you and Mr. Smith,");
    emily->AddNodeOption(nE4_1, 3, -1, "Never mind.");

    emily->AddNodeOption(nE4_2, 3, nE4_3, "...");
    emily->AddNodeOption(nE4_3, 3, nE4_4, "...");
    emily->AddNodeOption(nE4_4, 3, nE4_5, "Go On");
    emily->AddNodeOption(nE4_6, 3, nE4_6, "...");
    emily->AddNodeOption(nE4_5, 3, nE4_7, "...");
    emily->AddNodeOption(nE4_7, 3, nE4_8, "Did you ever find out where the money was going?");
    emily->AddNodeOption(nE4_8, 3, nE4_9, "...");

    emily->AddNodeOption(nE4_9, 3, NPC::PRESENT_EVIDENCE, "[Present Evidence?]");
    emily->SetEvidenceRequest(nE4_9, 3010, nE1_correct2, nE1_wrong2);
    emily->AddNodeOption(nE4_9, 3, -1, "I see...");


    emily->AddNodeOption(nE1_correct2, 3, nE2_correct2, "This is the kind of withdrawal you mean?");
    emily->AddNodeOption(nE2_correct2, 3, nE3_correct2, "Any idea who he might've been paying?");
    emily->AddNodeOption(nE3_correct2, 3, nE4_correct2, "...");
    emily->AddNodeOption(nE4_correct2, 3, -1, "Thank you...");
    nodeFlags.push_back({ emily, nE4_correct2, &hasFinishEmily });

    emily->AddNodeOption(nE1_wrong2, 3, nE4_9, "Whoops");


    emily->SetEventStartNode(3, nE4_1);

    /* Event 5 (Default from now on) */

    int nE5_1 = emily->AddDialougeNode("Please just...leave me be...");
    int nE5_2 = emily->AddDialougeNode("...");
    /*correfct*/
    int nE1_correct3 = emily->AddDialougeNode("Whats this?...Johnathan doesn't drink Whiskey tho, he despise it's taste.");
    /*Wrong*/
    int nE1_wrong3 = emily->AddDialougeNode("...What's this for?");

    emily->AddNodeOption(nE5_1, 4, nE5_2, "...Sorry about this");
    emily->AddNodeOption(nE5_1, 4, NPC::PRESENT_EVIDENCE, "[Present Evidence?]");
    emily->SetEvidenceRequest(nE5_1, 3002, nE1_correct3, nE1_wrong3);
    emily->SetEvidenceRequest(nE5_1, 3005, nE1_correct3, nE1_wrong3);
    emily->AddNodeOption(nE5_1, 4, -1, "Never mind.");

    emily->AddNodeOption(nE1_correct3, 4, -1, "Hmmm... interesting");
    nodeFlags.push_back({ emily, nE1_correct3, &hasShownEmilyGlass });
 

    emily->AddNodeOption(nE1_wrong3, 4, nE5_1, "Sorry");

    emily->AddNodeOption(nE5_2, 4, -1, "...");


    emily->SetEventStartNode(4, nE5_1);



    /*--------------------------------------------------------------------------------------------------------------------------------------*/
    /*---- Mrs Sarah Collins ----*/
    /* Event 1 (first convo) */
     sarah = AddNPC(1, NPC::Sarah_Collins, 3, 3);
    
     int nS1_1 = sarah->AddDialougeNode("Sarah Seems to be deep in thought while trembling", narrator->getName());
     int nS1_2 = sarah->AddDialougeNode("Huh? Err, y-yes,");
     int nS1_3 = sarah->AddDialougeNode("I-I didn't know, I didn't know he was murdered. I was just baking bread, and all of a sudden police kn-");
     int nS1_4 = sarah->AddDialougeNode("Black, let me handle this", Silas->getName());
     int nS1_5 = sarah->AddDialougeNode("Take your time Sarah. Nobody thinks you did anything...", Silas->getName());
     int nS1_6 = sarah->AddDialougeNode("We just need to understand what you saw", Silas->getName());
     int nS1_7 = sarah->AddDialougeNode("O-Okay...");
     int nS1_8 = sarah->AddDialougeNode("[How should Detective Black Reply]", narrator->getName());

     sarah->AddNodeOption(nS1_1, 0, nS1_2, "Sarah Collins, right?");
     sarah->AddNodeOption(nS1_1, 0, -1, "Never mind.");

     sarah->AddNodeOption(nS1_2, 0, nS1_3, "Can you explain why you were in Mr Smith's Property around the time of his murder?");

     sarah->AddNodeOption(nS1_3, 0, nS1_4, "Calm down, Sarah, you are not answering my question");

     sarah->AddNodeOption(nS1_4, 0, nS1_5, "...fine");

     sarah->AddNodeOption(nS1_5, 0, nS1_6, "...");

     sarah->AddNodeOption(nS1_6, 0, nS1_7, "...");

     sarah->AddNodeOption(nS1_7, 0, nS1_8, "...");

     /*choice but same event*/

     /*failed*/
     int nS1_8w1 = sarah->AddDialougeNode("Sarah's face crumples, panic flooding back in.", narrator->getName());
     int nS1_8w2 = sarah->AddDialougeNode("Not what we agreed on, Rowan...", Silas->getName());

     /*pass*/
     int nS1_9 = sarah->AddDialougeNode("Sarah nods slowly, some tension leaving her shoulders.", narrator->getName());
     int nS1_10 = sarah->AddDialougeNode("I...I ran out of sugar. I was baking bread, so as neighbours...");
     int nS1_11 = sarah->AddDialougeNode("I-I came over to borrow sugar from them...");
     int nS1_12 = sarah->AddDialougeNode("I was knocking on their backdoor, i notice the back sliding door was ajar, so it wasnt lock...");
     int nS1_13 = sarah->AddDialougeNode("..b-but of course it would be rude to just enter.");
     int nS1_14 = sarah->AddDialougeNode("That's when i here quarreling, i got scared and went back");

     sarah->AddNodeOption(nS1_8, 0, nS1_8w1, "You were seen leaving later than you're admitting. Why?");
     sarah->AddNodeOption(nS1_8w1, 0, nS1_8w2, "...damn");
     sarah->AddNodeOption(nS1_8w2, 0, nS1_8, "my bad... [retry]");

     sarah->AddNodeOption(nS1_8, 0, nS1_9, "Just start from the beginning. What made you go over there that day?");
     sarah->AddNodeOption(nS1_9, 0, nS1_10, "...");
     sarah->AddNodeOption(nS1_10, 0, nS1_11, "...");
     sarah->AddNodeOption(nS1_11, 0, nS1_12, "What happened when you got there?");
     sarah->AddNodeOption(nS1_12, 0, nS1_13, "...");
     sarah->AddNodeOption(nS1_13, 0, nS1_14, "...");
     sarah->AddNodeOption(nS1_14, 0, -1, "...I see");
     nodeFlags.push_back({ sarah, nS1_14, &hasTalkToSarah1 });



     /* Event 2 (present evidence or go to house)*/
     int nS2_1 = sarah->AddDialougeNode("...y-yes?");
     int nS2_2 = sarah->AddDialougeNode("What, why?");
     int nS2_3 = sarah->AddDialougeNode("Sarah paused for a second", narrator->getName());
     int nS2_4 = sarah->AddDialougeNode("O-Okay, here");
     nodeItems.push_back({ sarah, nS2_4, "Neighbour's House Key", CItem::NEIGHBOUR_HOUSE_KEY });

     /* correct */
     int nS2_correct1 = sarah->AddDialougeNode("Silas raises a picture of a muddy footprint", narrator->getName());
     int nS2_correct2 = sarah->AddDialougeNode("Are you sure you went back home after hearing the quarrel?", Silas->getName());
     int nS2_correct3 = sarah->AddDialougeNode("...");
     int nS2_correct4 = sarah->AddDialougeNode("We found this mud shoe print of a Nike shoe, INSIDE of the house...", Silas->getName());
     int nS2_correct5 = sarah->AddDialougeNode("...by the backdoor.", Silas->getName());
     int nS2_correct6 = sarah->AddDialougeNode("Okay...I did enter, but only a few step to check on them");
     int nS2_correct7 = sarah->AddDialougeNode("But the noise got louder, so i took off as i got scared");
     int nS2_correct8 = sarah->AddDialougeNode("Black looks at Silas, He seems a little suspicious of the answer but satisfied for now...", narrator->getName());

     /* wrong */
     int nS2_wrong1 = sarah->AddDialougeNode("w-what is that?");

     sarah->AddNodeOption(nS2_1, 1, nS2_2, "Sorry, but is it possible for me to check your house?");
     sarah->AddNodeOption(nS2_1, 1, NPC::PRESENT_EVIDENCE, "[Present Evidence?]");
     sarah->SetEvidenceRequest(nS2_1, 3008, nS2_correct1, nS2_wrong1);
     sarah->AddNodeOption(nS2_1, 0, -1, "Never mind.");

     sarah->AddNodeOption(nS2_2, 1, nS2_3, "We need to confirm your claims, if you are clear, we can cross your name off");
     sarah->AddNodeOption(nS2_3, 1, nS2_4, "...");
     sarah->AddNodeOption(nS2_4, 1, -1, "Thank you");

     sarah->AddNodeOption(nS2_correct1, 1, nS2_correct2, "...");
     sarah->AddNodeOption(nS2_correct2, 1, nS2_correct3, "...");
     sarah->AddNodeOption(nS2_correct3, 1, nS2_correct4, "Come clean now, Sarah. Why were you inside.");
     sarah->AddNodeOption(nS2_correct4, 1, nS2_correct5, "...");
     sarah->AddNodeOption(nS2_correct5, 1, nS2_correct6, "...");
     sarah->AddNodeOption(nS2_correct6, 1, nS2_correct7, "...");
     sarah->AddNodeOption(nS2_correct7, 1, nS2_correct8, "...");
     sarah->AddNodeOption(nS2_correct8, 1, -1, "...");
     nodeFlags.push_back({ sarah, nS1_14, &hasShownEviToSarah });


     sarah->SetEventStartNode(1, nS2_1);
     

     /* Event 3 (Present shoebox evidence)*/
     int nS3_1 = sarah->AddDialougeNode("...Y-Yes?");
     int nS3_2 = sarah->AddDialougeNode("N-No, We..We were pretty nice to each other...");

     /*correct*/
     int nS3_correct1 = sarah->AddDialougeNode("Sarah gasped and took a small step back.", narrator->getName());
     int nS3_correct2 = sarah->AddDialougeNode("Sarah stared at the box of photos, hands trembling", narrator->getName());
     int nS3_correct3 = sarah->AddDialougeNode("She presses a hand to her mouth for a second, trying to steady her breathing.", narrator->getName());
     int nS3_correct4 = sarah->AddDialougeNode("The second I heard he was murdered, I knew...");
     int nS3_correct5 = sarah->AddDialougeNode(" I knew how this would look. Years of complaints, photos, letters...");
     int nS3_correct6 = sarah->AddDialougeNode("Yes...I didn't think it through. I just panicked.");
     int nS3_correct7 = sarah->AddDialougeNode("I didn't know what to say, so I said 'no' and hoped it would be enough");
     int nS3_correct8 = sarah->AddDialougeNode("I was angry about the fence.About the tree. ");
     int nS3_correct9 = sarah->AddDialougeNode("About six years of him treating it like it didn't matter...");
     int nS3_correct10 = sarah->AddDialougeNode("But angry isn't the same as...I didn't do this.");

     int nS3_wrong1 = sarah->AddDialougeNode("pick the shoebox of pictures breh...", Silas->getName());


     sarah->AddNodeOption(nS3_1, 2, nS3_2, "Do you and the Smiths have any altercation before?");
     sarah->AddNodeOption(nS3_2, 2, NPC::PRESENT_EVIDENCE, "LIE DETECTED! [Present Evidence]");
     sarah->SetEvidenceRequest(nS3_2, 3009, nS3_correct1, nS3_wrong1);
     sarah->AddNodeOption(nS3_2, 2, -1, "Never mind then...");

     sarah->AddNodeOption(nS3_correct1, 2, nS3_correct2, "You were angry with the Smiths over property, correct? Why did you lie?");
     sarah->AddNodeOption(nS3_correct2, 2, nS3_correct3, "...");
     sarah->AddNodeOption(nS3_correct3, 2, nS3_correct4, "...");
     sarah->AddNodeOption(nS3_correct4, 2, nS3_correct5, "...");
     sarah->AddNodeOption(nS3_correct5, 2, nS3_correct6, "So you lied to protect yourself,");
     sarah->AddNodeOption(nS3_correct6, 2, nS3_correct7, "...");
     sarah->AddNodeOption(nS3_correct7, 2, nS3_correct8, "...");
     sarah->AddNodeOption(nS3_correct8, 2, nS3_correct9, "...");
     sarah->AddNodeOption(nS3_correct9, 2, nS3_correct10, "...");
     sarah->AddNodeOption(nS3_correct10, 2, -1, "I see...");
     nodeFlags.push_back({ sarah, nS3_correct10, &hasTalkToSarah2 });
     

     sarah->AddNodeOption(nS3_wrong1, 1, nS3_2, "My bad...");

     sarah->SetEventStartNode(2, nS3_1);

     /* Event 4 (Default from now on)*/
     int nS4_1 = sarah->AddDialougeNode("...Y-Yes?");
     sarah->AddNodeOption(nS4_1, 3, -1, "nothing");

     sarah->SetEventStartNode(3, nS4_1);
    /*---- Mr Michael Turner -----*/
/* Event 0 (first convo) */
     michael = AddNPC(5, NPC::Michael_Turner, 10, 8);

     int nM0_1 = michael->AddDialougeNode("Hey...");
     int nM0_2 = michael->AddDialougeNode("Yes, I am. W-Well I would say i'm more of the founder and he is the Co Founder.");
     int nM0_3 = michael->AddDialougeNode("Claim? CLAIM? It's a fact, Detective. The maid saw me leave, ask her yourself.");
     int nM0_4 = michael->AddDialougeNode("Michael points to the direction of the kitchen, where the maid is.", narrator->getName());

     michael->AddNodeOption(nM0_1, 0, nM0_2, "You are Mr Turner right? You're the business partner of Mr Smith?");
     michael->AddNodeOption(nM0_1, 0, -1, "Never mind");

     michael->AddNodeOption(nM0_2, 0, nM0_3, "Right... It says here, you claim you left the Smith mansion at 16:15pm. Correct?");
     michael->AddNodeOption(nM0_3, 0, nM0_4, "...");
     michael->AddNodeOption(nM0_4, 0, -1, "... Ok, we will.");

     /* Event 1 (second convo - more detailed) */
     int nM1_1 = michael->AddDialougeNode("Hey...");
     int nM1_2 = michael->AddDialougeNode("Yes, I am. W-Well I would say i'm more of the founder and he is the Co Founder.");
     int nM1_3 = michael->AddDialougeNode("Claim? CLAIM? It's a fact, Detective. The maid saw me leave, ask her yourself.");
     int nM1_4 = michael->AddDialougeNode("Michael points to the direction of the kitchen, where the maid is.", narrator->getName());
     int nM1_5 = michael->AddDialougeNode("Turner's jaw loosens slightly, though his hand doesn't stop turning the watch", narrator->getName());
     int nM1_6 = michael->AddDialougeNode("...Right. Of course.");
     int nM1_7 = michael->AddDialougeNode("We were talking about the business, The consulting firm. I proposed something");
     int nM1_8 = michael->AddDialougeNode("a way to cover our capital shortfall without waiting on a slow investor pipeline.");
     int nM1_9 = michael->AddDialougeNode("...Restructuring some of the client funds. Temporarily. Just to bridge the gap until new capital came in.");
     int nM1_10 = michael->AddDialougeNode("It was temporary...but, Jonathan didn't see it that way. He refused.");
     int nM1_11 = michael->AddDialougeNode("Said it crossed a line he wasn't willing to cross, no matter how bad things got.");
     int nM1_12 = michael->AddDialougeNode("We argued. Loudly, probably, I won't pretend otherwise. Then I left.");
     int nM1_13 = michael->AddDialougeNode("About 16:15. Like i said, the maid saw me out.");

     michael->AddNodeOption(nM1_1, 1, nM1_2, "You are Mr Turner right? You're the business partner of Mr Smith?");
     michael->AddNodeOption(nM1_1, 1, -1, "Never mind");
     michael->AddNodeOption(nM1_2, 1, nM1_3, "Right... It says here, you claim you left the Smith mansion at 16:15pm. Correct?");
     michael->AddNodeOption(nM1_3, 1, nM1_4, "...");
     michael->AddNodeOption(nM1_4, 1, nM1_5, "It's not personal, Mr. Turner. We're confirming everyone's timeline");
     michael->AddNodeOption(nM1_5, 1, nM1_6, "...");
     michael->AddNodeOption(nM1_6, 1, nM1_7, "...");
     michael->AddNodeOption(nM1_7, 1, nM1_8, "...");
     michael->AddNodeOption(nM1_8, 1, nM1_9, "...");
     michael->AddNodeOption(nM1_9, 1, nM1_10, "That's not restructuring, Mr. Turner. That's moving client money without their knowledge.");
     michael->AddNodeOption(nM1_10, 1, nM1_11, "...");
     michael->AddNodeOption(nM1_11, 1, nM1_12, "...");
     michael->AddNodeOption(nM1_12, 1, nM1_13, "Just to triple check, What time was it?");
     michael->AddNodeOption(nM1_13, 1, -1, "Thanks Mr Turner");
     nodeFlags.push_back({ michael, nM1_13, &hasTalkToMichael1 });

     michael->SetEventStartNode(1, nM1_1);

     /* Event 2 (Confronting about whiskey glass) */
     int nM2_1 = michael->AddDialougeNode("Hey...");
     int nM2_2 = michael->AddDialougeNode("Turner pauses — just half a second too long.", narrator->getName());
     int nM2_3 = michael->AddDialougeNode("...Sometimes. Socially. Why?");
     int nM2_4 = michael->AddDialougeNode("Funny thing is, Jonathan didn't drink. Hated the stuff, according to his wife.", Silas->getName());
     int nM2_5 = michael->AddDialougeNode("Something flickers across Turner's face, quick, involuntary.", narrator->getName());
     int nM2_6 = michael->AddDialougeNode("...I didn't know that.");
     int nM2_7 = michael->AddDialougeNode("We talked business, Detective. Not exactly a habit of ours to compare drink orders.");
     int nM2_8 = michael->AddDialougeNode("I already told you — I don't know anything about a glass.");

     /*correct1 - fingerprint on glass*/
     int nM2_correct1_1 = michael->AddDialougeNode("We had a forensic team run a fingerprint test on it…", Silas->getName());
     int nM2_correct1_2 = michael->AddDialougeNode("And it matches your fingerprint", Silas->getName());
     int nM2_correct1_3 = michael->AddDialougeNode("Turner's eyes open wide. For a moment, he says nothing", narrator->getName());
     int nM2_correct1_4 = michael->AddDialougeNode("...Okay...Okay. I lied. I came back");
     int nM2_correct1_5 = michael->AddDialougeNode("That night. After I left.");
     int nM2_correct1_6 = michael->AddDialougeNode("And we talked. It didn't go anywhere. So I left again.");
     int nM2_correct1_7 = michael->AddDialougeNode("That's it. That's all that happened");
     int nM2_correct1_8 = michael->AddDialougeNode("Suddenly his eyes lit up, and turn towards Detective Black.", narrator->getName());
     int nM2_correct1_9 = michael->AddDialougeNode("Wait, as I was leaving, I recall hearing someone walking to the study room at around 17.00 pm");

     /*correct2 - glove evidence*/
     int nM2_correct2_1 = michael->AddDialougeNode("That's from the study. Jonathan kept a pair on the shelf, I think");
     int nM2_correct2_2 = michael->AddDialougeNode("Never touched it myself.");
     int nM2_correct2_3 = michael->AddDialougeNode("Not exactly the kind of thing you pick up during a business meeting.");

     /*wrong*/
     int nM2_wrong = michael->AddDialougeNode("Wha…What does this have to do with me?");

     michael->AddNodeOption(nM2_1, 2, nM2_2, "One more thing, Mr. Turner. Do you drink whiskey?");
     michael->AddNodeOption(nM2_2, 2, nM2_3, "...");
     michael->AddNodeOption(nM2_3, 2, nM2_4, "Because we found a broken whiskey glass in the study.");
     michael->AddNodeOption(nM2_4, 2, nM2_5, "...");
     michael->AddNodeOption(nM2_5, 2, nM2_6, "...");
     michael->AddNodeOption(nM2_6, 2, nM2_7, "No? You've been business partners for years, yet you didn't know he doesn't drink whiskey?");
     michael->AddNodeOption(nM2_7, 2, nM2_8, "Fair enough,...So if he didn't drink, and you say you left before anyone else came by...");
     michael->AddNodeOption(nM2_8, 2, NPC::PRESENT_EVIDENCE, "[Present Evidence?]");
     michael->SetEvidenceRequest(nM2_8, 3005, nM2_correct1_1, nM2_wrong); // Broken Whiskey Glass
     michael->SetEvidenceRequest(nM2_8, 3006, nM2_correct2_1, nM2_wrong); // Suspicious Glove

     /*correct1*/
     michael->AddNodeOption(nM2_correct1_1, 2, nM2_correct1_2, "...");
     michael->AddNodeOption(nM2_correct1_2, 2, nM2_correct1_3, "...");
     michael->AddNodeOption(nM2_correct1_3, 2, nM2_correct1_4, "...");
     michael->AddNodeOption(nM2_correct1_4, 2, nM2_correct1_5, "...");
     michael->AddNodeOption(nM2_correct1_5, 2, nM2_correct1_6, "And?");
     michael->AddNodeOption(nM2_correct1_6, 2, nM2_correct1_7, "...");
     michael->AddNodeOption(nM2_correct1_7, 2, nM2_correct1_8, "...");
     michael->AddNodeOption(nM2_correct1_8, 2, nM2_correct1_9, "...");
     michael->AddNodeOption(nM2_correct1_9, 2, -1, "*nods head");
     nodeFlags.push_back({ michael, nM2_correct1_9, &hasTalkToMichael3 });

     /*correct2 - glove path (goes back to nM2_8) */
     michael->AddNodeOption(nM2_correct2_1, 2, nM2_correct2_2, "...");
     michael->AddNodeOption(nM2_correct2_2, 2, nM2_correct2_3, "...");
     michael->AddNodeOption(nM2_correct2_3, 2, nM2_8, "*nods head");

     /*wrong*/
     michael->AddNodeOption(nM2_wrong, 2, nM2_8, "*nods head");

     michael->SetEventStartNode(2, nM2_1);

     /* Event 3 (default from then on) */
     int nM3_1 = michael->AddDialougeNode("Hey...");
     michael->AddNodeOption(nM3_1, 3, -1, "Hey...");

     michael->SetEventStartNode(3, nM3_1);



     /* Event 5 (default from then on) */
     int nM5_1 = michael->AddDialougeNode("Hey...");
     michael->AddNodeOption(nM5_1, 4, -1, "Hey...");

     michael->SetEventStartNode(4, nM5_1);
     /*--------------------------------------------------------------------------------------------------------------------------------------*/
    /*---- Trisha Lopez (The Maid) ----*/
     NPC* trisha = AddNPC(7, NPC::Trisha_Lopez, 10, 6);

     int nT1_1 = trisha->AddDialougeNode("Yes?");
     int nT1_2 = trisha->AddDialougeNode("About 5 years");
     int nT1_3 = trisha->AddDialougeNode("I was in the young master's bedroom, folding his clothes,");
     int nT1_4 = trisha->AddDialougeNode("I heard a quarrel — from the study. Mr. Smith and... someone. I think it was Mrs. Smith.");
     int nT1_5 = trisha->AddDialougeNode("I then went down to grab a drink, which i saw Mr Turner Leaving, i think it was 4pm or so");
     int nT1_6 = trisha->AddDialougeNode("I went back to young master’s room to continue folding the clothes");
     int nT1_7 = trisha->AddDialougeNode("She wrings her hands, eyes downcast.", narrator->getName());
     int nT1_8 = trisha->AddDialougeNode("Then I heard a loud thud. I told myself it was nothing");
     int nT1_9 = trisha->AddDialougeNode("I didn't want to believe something was happening between them.");
     int nT1_10 = trisha->AddDialougeNode("But I couldn't shake the feeling, so I went to the study, quietly, to check.");
     int nT1_11 = trisha->AddDialougeNode("T-T-That's when I saw Mr. Smith's body. I... I was terrified");

     trisha->AddNodeOption(nT1_1, 0, nT1_2, "Trisha right? How long have you been working in the Smith’s Mansion?");
     trisha->AddNodeOption(nT1_1, 0, -1, "Never mind");
     trisha->AddNodeOption(nT1_2, 0, nT1_3, "Where were you before you found Mr Smith’s body?");
     trisha->AddNodeOption(nT1_3, 0, nT1_4, "...");
     trisha->AddNodeOption(nT1_4, 0, nT1_5, "...");
     trisha->AddNodeOption(nT1_5, 0, nT1_6, "...");
     trisha->AddNodeOption(nT1_6, 0, nT1_7, "...");
     trisha->AddNodeOption(nT1_7, 0, nT1_8, "...");
     trisha->AddNodeOption(nT1_8, 0, nT1_9, "...");
     trisha->AddNodeOption(nT1_9, 0, nT1_10, "...");
     trisha->AddNodeOption(nT1_10, 0, nT1_11, "...");
     trisha->AddNodeOption(nT1_11, 0, -1, "I see, im sorry");
     nodeFlags.push_back({ trisha, nT1_11, &hasTalkToTrisha });


     /*--------------------------------------------------------------------------------------------------------------------------------------*/
     /*---- Detective Batista ----*/

     NPC* batista1 = AddNPC(11, NPC::Angelo_Batista, 1, 4);
     int nB1_1 = batista1->AddDialougeNode("It's a closed-room murder, domestic. The owner of this mansion, Mr. Jonathan Smith...");
     int nB1_2 = batista1->AddDialougeNode("...was found dead, El Pobre has a deep wound to the back of the neck");
     int nB1_3 = batista1->AddDialougeNode("Vamanos Viejo, The body is in the study room");
     batista1->AddNodeOption(nB1_1, 0, nB1_2, "...");
     batista1->AddNodeOption(nB1_2, 0, nB1_3, "...");
     batista1->AddNodeOption(nB1_3, 0, -1, "...");


     /* --Event 2 (in study room) */

     batista2 = AddNPC(6, NPC::Angelo_Batista, 3, 1);
     int nB2_1 = batista2->AddDialougeNode("Take a look around see if you find anything...");
     batista2->AddNodeOption(nB2_1, 0, -1, "Got it...");

     /* --Event 3 (in study room after collecting evidence) */
     int nB3_1 = batista2->AddDialougeNode("Done?");
     int nB3_2 = batista2->AddDialougeNode("From what I've gathered, four people had contact with Mr. Smith around the time of death...");
     int nB3_3 = batista2->AddDialougeNode("...His wife, Emily Smith; his business partner, Michael Turner; his maid, Trisha Lopez; and the neighbour, Sarah Collins");
     int nB3_4 = batista2->AddDialougeNode("They should be downstairs, OH and here is the Case files on the suspects and victim");
     int nB3_5 = batista2->AddDialougeNode("Detective Batista hands you a Case Folder (Case Folder Unlocked Press 'C'), Batista then heads down to the Kitchen ", narrator->getName());
     batista2->AddNodeOption(nB2_1, 1, nB3_2, "Im done, by the way, Who was present at the time of the crime?");
     batista2->AddNodeOption(nB3_2, 1, nB3_3, "...");
     batista2->AddNodeOption(nB3_3, 1, nB3_4, "...");
     batista2->AddNodeOption(nB3_4, 1, nB3_5, "Thanks");
     batista2->AddNodeOption(nB3_5, 1, -1, "...");
     nodeFlags.push_back({ batista2, nB3_5, &hasTalkToBatista });//added this
     nodeFlags.push_back({ batista2, nB3_5, &IsCollinPorchVisible });//added this
     nodeFlags.push_back({ batista2, nB3_5, &IsCaseFileUnlocked });//added this
     nodeFlags.push_back({ batista2, nB3_5, &IsProsecutorAvailable });//added this

     /* --Event 4 (in Kitchen) */
     batista3 = AddNPC(7, NPC::Angelo_Batista, 12, 4);
     int nB4_1 = batista3->AddDialougeNode("Anything I'll be here...");
     batista3->AddNodeOption(nB4_1, 0, -1, "Ok Cabron...");

     /* --Event 5 (in Kitchen if there is report) */ //add if there is report condition
     //int nB5_1 = batista3->AddDialougeNode("Oh hey, the reports from the forensics came back, here you go");
     int nB5_1_candle = batista3->AddDialougeNode("Oh hey, the reports from the forensics came back, here you go (You Recieved a Brass Candlestick Report)");
     int nB5_1_glass = batista3->AddDialougeNode("Oh hey, the reports from the forensics came back, here you go (You Recieved a Broken Whiskey Glass Report)");
     int nB5_1_glove = batista3->AddDialougeNode("Oh hey, the reports from the forensics came back, here you go (You Recieved a Suspicious Glove Report)");
     nodeEvidence.push_back({ batista3, nB5_1_candle, CEvidence::Brass_Candlestick_Report });
     nodeEvidence.push_back({ batista3, nB5_1_glass, CEvidence::BrokenWhiskey_Glass_Report });
     nodeEvidence.push_back({ batista3, nB5_1_glove, CEvidence::Suspicious_Glove_Report });
     batista3->AddNodeOption(nB5_1_candle, 0, -1, "Take Brass Candlestick Report");
     batista3->AddNodeOption(nB5_1_glass, 0, -1, "Take Broken Whiskey Glass Report");
     batista3->AddNodeOption(nB5_1_glove, 0, -1, "Take Broken Whiskey Glass Report");

     nB4_1_id = nB4_1;
     //nB5_1_id = nB5_1;
     
     nB5_1_candle_id = nB5_1_candle;
     nB5_1_glass_id = nB5_1_glass;
     nB5_1_glove_id = nB5_1_glove;


     /*--------------------------------------------------------------------------------------------------------------------------------------*/
     /*Forensics*/
     NPC* forensics1 = AddNPC(6, NPC::Forensics, 2, 6);
     int nF1 = forensics1->AddDialougeNode("Sorry, a little busy now, come back later...");
     forensics1->AddNodeOption(nF1, 0, -1, "...");

     NPC* forensics2 = AddNPC(14, NPC::Forensics, 2, 6);
     int nF2_1 = forensics2->AddDialougeNode("Hi, What do you need me for?");
     int nF2_2 = forensics2->AddDialougeNode("Sure thing, just pass it to me");
     /*correct node*/
     int nF2_correct = forensics2->AddDialougeNode("...Got it, i'll pass the report to you afterwards.");
     int nF2_3 = forensics2->AddDialougeNode("Will do, Detective Black.");
     /*wrong node*/
     int nF2_wrong = forensics2->AddDialougeNode("Don't think we will need the forensics for this", Silas->getName());


     forensics2->AddNodeOption(nF2_1, 0, nF2_2, "Hi, Can you help me run a few test on these stuff?...");
     forensics2->AddNodeOption(nF2_1, 0, -1, "Never Mind");

     forensics2->AddNodeOption(nF2_2, 0, NPC::PRESENT_EVIDENCE, "[Give Evidence]");
     forensics2->SetEvidenceRequest(nF2_2, 3001, nF2_correct, nF2_wrong);
     forensics2->SetEvidenceRequest(nF2_2, 3002, nF2_correct, nF2_wrong);
     forensics2->SetEvidenceRequest(nF2_2, 3004, nF2_correct, nF2_wrong);
     forensics2->AddNodeOption(nF2_2, 0, nF2_1, "Back");

     forensics2->AddNodeOption(nF2_correct, 0, nF2_3, "No need, just pass it to Detective Batista.");
     forensics2->AddNodeOption(nF2_3, 0, -1, "...");

     forensics2->AddNodeOption(nF2_wrong, 0, nF2_2, "Back");



    /* Policia*/
     NPC* police = AddNPC(11, NPC::Police, 3, 3);
     int nP1 = police->AddDialougeNode("Keep it moving...");
     police->AddNodeOption(nP1, 0, -1, "...");

     NPC* police2 = AddNPC(11, NPC::Police, 5, 7);
     int nP2 = police2->AddDialougeNode("Keep it moving man");
     police2->AddNodeOption(nP2, 0, -1, "...");

     NPC* police3 = AddNPC(11, NPC::Police, 4, 10);
     int nP3 = police3->AddDialougeNode("Just keeping a look out");
     police3->AddNodeOption(nP3, 0, -1, "...");

     NPC* police4 = AddNPC(11, NPC::Police, 10, 7);
     int nP4 = police4->AddDialougeNode("Just keeping a look out");
     police4->AddNodeOption(nP4, 0, -1, "...");


     NPC* police5 = AddNPC(13, NPC::Police, 3, 3);
     int nP5 = police5->AddDialougeNode("Keep it moving...");
     police5->AddNodeOption(nP5, 0, -1, "...");

     NPC* police6 = AddNPC(13, NPC::Police, 5, 7);
     int nP6 = police6->AddDialougeNode("Keep it moving man");
     police6->AddNodeOption(nP6, 0, -1, "...");

     NPC* police7 = AddNPC(13, NPC::Police, 4, 10);
     int nP7 = police7->AddDialougeNode("Just keeping a look out");
     police7->AddNodeOption(nP7, 0, -1, "...");

     NPC* police8 = AddNPC(13, NPC::Police, 10, 7);
     int nP8 = police8->AddDialougeNode("Just keeping a look out");
     police8->AddNodeOption(nP8, 0, -1, "...");


     /* Johnathan the victim*/
     NPC* johnathan = AddNPC(6, NPC::Jonathan_Smith, 4, 5);
     int nJ1 = johnathan->AddDialougeNode("A deep wound can be seen at the back of his head, blunt force trauma.", narrator->getName());
     johnathan->AddNodeOption(nJ1, 0, -1, "...");

     NPC* johnathan2 = AddNPC(14, NPC::Jonathan_Smith, 4, 5);
     int nJ2 = johnathan2->AddDialougeNode("A deep wound can be seen at the back of his head, blunt force trauma.", narrator->getName());
     johnathan2->AddNodeOption(nJ2, 0, -1, "...");

     /*--------------------------------------------------------------------------------------------------------------------------------------*/
     /*---- Mr Harvey Denn (prosecutor) ----*/
     harvey = AddNPC(10, NPC::Harvey_Denn, 3, 5);

     int nH0 = harvey->AddDialougeNode("what up dawg");
     int nH1 = harvey->AddDialougeNode("No problems, gentlemen.");
     int nH2 = harvey->AddDialougeNode("I see... , so who do you think is the murderer?");
     int nH3 = harvey->AddDialougeNode("Could you show me the evidence you collected?");
     int nH4 = harvey->AddDialougeNode("Could you show me the evidence you collected?");
     int nH5 = harvey->AddDialougeNode("Could you show me the evidence you collected?");
     int nH6 = harvey->AddDialougeNode("Seriously?...");

     harvey->AddNodeOption(nH0, 0, nH2, "Submit Report and Evidence");
     harvey->AddNodeOption(nH0, 0, nH1, "Ah, nothing, just checking in on you. We will come back later to submit the report.");
     harvey->AddNodeOption(nH1, 0, -1, "leave");
     harvey->AddNodeOption(nH2, 0, nH3, "Emily Smith (the wife)");
     harvey->AddNodeOption(nH2, 0, nH4, "Michael Turner (business partner)");
     harvey->AddNodeOption(nH2, 0, nH5, "Sarah Collins (neighbor)");
     harvey->AddNodeOption(nH2, 0, nH6, "Trisha Lopez (maid)");
     harvey->AddNodeOption(nH6, 0, nH2, "hehe");
     harvey->AddNodeOption(nH3, 0, NPC::PRESENT_EVIDENCE, "[Present Evidence]");
     harvey->AddNodeOption(nH4, 0, NPC::PRESENT_EVIDENCE, "[Present Evidence]");
     harvey->AddNodeOption(nH5, 0, NPC::PRESENT_EVIDENCE, "[Present Evidence]");
     harvey->AddNodeOption(nH3, 0, -1, "leave");
     harvey->AddNodeOption(nH4, 0, -1, "leave");
     harvey->AddNodeOption(nH5, 0, -1, "leave");

     int nH1_correct = harvey->AddDialougeNode("I need more evidence");
     int nH1_wrong = harvey->AddDialougeNode("NIL"); // nothing here just to ensure the function can run

     for (int j = 1; j < 12; j++) {
         harvey->SetEvidenceRequest(nH3, 3000 + j, nH1_correct, nH1_wrong);
     }
     for (int j = 1; j < 12; j++) {
         harvey->SetEvidenceRequest(nH4, 3000 + j, nH1_correct, nH1_wrong);
     }
     for (int j = 1; j < 12; j++) {
         harvey->SetEvidenceRequest(nH5, 3000 + j, nH1_correct, nH1_wrong);
     }
     harvey->AddNodeOption(nH1_correct, 0, nH3, "sure");

       /*ROOMS AND MAPS*/

   /*Detective Black's office ROOM 0*/
   {
        map[0].SetRoom(11, 6, 5, 1);//office
        map[0].SetName("Detective Black's Office");
        AddObstacle(0, CObstacle::Long_Shelf, 0, 0, 0)->SetDialogue(0, "a picture of you and Silas at the play ground..... why? well why not");
        CObstacle* carKey = AddObstacle(0, CObstacle::Long_Shelf, 7, 0, 0);
        /*HERE IS BRANDON EVIDENCE V*/
        AddObstacle(0, CObstacle::Table, 8, 2, 1);
        AddObstacle(0, CObstacle::Table, 2, 2, 1)->SetDialogue(0, "you find a twenty that Silas left on the table as you look around before pocketing it");
        CObstacle* jacket = AddObstacle(0, CObstacle::Sofa, 7, 5, 0);
        AddObstacle(0, CObstacle::Sofa, 2, 5, 0)->SetDialogue(0, "its messy from all the times you slept here like your homeless... oh wait you are");
        CObstacle* notebook = AddObstacle(0, CObstacle::Desk, 5, 2, 0);
        AddObstacle(0, CObstacle::Window, 5, 0, 0)->SetDialogue(0, "a beautiful Scenery Of... the neighbouring buildings red wall... truly to die for");
        AddObstacle(0, CObstacle::Door, 5, 5, 0);
        addItems(notebook, CItem::NOTEBOOK);
        addItems(jacket, CItem::JACKET);
        addItems(carKey, CItem::CAR_KEY);


   }

   /*The Mansion's Living room ROOM 1*/
   {
       map[1].SetRoom(14, 10, 0, 2);//Mansion living room
       map[1].SetName("The Mansion's Living room");
       AddObstacle(1, CObstacle::Long_Shelf, 13, 0, 1)->SetDialogue(0, "A bunch of trophies and medals, the name Colin is written on each and every one of it");
       AddObstacle(1, CObstacle::Long_Shelf, 13, 6, 1)->SetDialogue(0, "Books, a bunch of them. OMG IS THAT THE VOLUME 1 FIRST PRINTED COPY OF ONE PIECE???!!");
       AddObstacle(1, CObstacle::Sofa, 8, 2, 0);
       AddObstacle(1, CObstacle::Sofa, 6, 4, 1);
       AddObstacle(1, CObstacle::Sofa, 8, 7, 0);
       AddObstacle(1, CObstacle::Table, 9, 4, 1)->SetDialogue(0, "A basket of fruits sat on top of the Marble Table, I think someone bit into the faux Lemon, poor guy");
       AddObstacle(1, CObstacle::Table, 12, 4, 1)->SetDialogue(0, "A 2.5 Mil Stuart Hughes Prestige HD Supreme Rose Edition TV, This luxury 55-inch TV is wrapped in 28 kilograms of 18k rose gold");
       CObstacle* cigarbox = AddObstacle(1, CObstacle::Small_Shelf, 0, 4, 1);
       AddObstacle(1, CObstacle::Table, 0, 7, 1);
       AddObstacle(1, CObstacle::Flower, 0, 3, 1)->SetDialogue(0, "A Potted Plant, Nothing much");
       AddObstacle(1, CObstacle::Flower, 7, 0, 1)->SetDialogue(0, "Did you know? Tulips were once more valuable than gold");
       AddObstacle(1, CObstacle::Door, 0, 0, 0)->SetDialogue(0, "Door Back to the Porch");
       Evidenceptr[CEvidence::Picture_of_Muddy_shoeprint] = AddObstacle(1, CObstacle::Door, 4, 9, 0);
       AddObstacle(1, CObstacle::Window, 6, 9, 0)->SetDialogue(0, "A window with a stunning view to the flower ocean in the garden");
       AddObstacle(1, CObstacle::Window, 7, 9, 0)->SetDialogue(0, "A window with a stunning view to the flower ocean in the garden");
       AddObstacle(1, CObstacle::Window, 8, 9, 0)->SetDialogue(0, "A window with a stunning view to the flower ocean in the garden");
       addItems(cigarbox, CItem::CIGARS);

       mapIntroDialogue[1] = {
        {"Black", "This is gonna be a long night...Let's get this started"},
        {"Game", "(You are now able to roam freely to collect evidence and talk to Suspects)"}
       };
   }

   /*The Mansion's Toilet ROOM 2*/
   {
       map[2].SetRoom(6, 6, 2, 0);//Mansion toilet
       map[2].SetName("The Mansion's toilet");
       AddObstacle(2, CObstacle::Door, 3, 0, 0);
       AddObstacle(2, CObstacle::Sink, 5, 2, 0)->SetDialogue(0, "A sink and a mirror, Still looking sharp Black");
       AddObstacle(2, CObstacle::ToiletBowl, 5, 4, 0)->SetDialogue(0, "A Toilet bowl, Is that a s*** stain?");
       AddObstacle(2, CObstacle::BathTub, 0, 4, 1)->SetDialogue(0, "A big ahh bath tub, a rubber duck sits inside it");
       AddObstacle(2, CObstacle::Flower, 0, 2, 1)->SetDialogue(0, "A Potted Plant, Nothing much");




   }

   /*The Mansion's Master Bedroom ROOM 3*/
   {
       map[3].SetRoom(10, 10, 0, 2);//Mansion master bedroom
       map[3].SetName("The Mansion's Master bedroom");
       AddObstacle(3, CObstacle::Table, 5, 0, 0);
       CObstacle* note = AddObstacle(3, CObstacle::Long_Shelf, 9, 6, 1);
       AddObstacle(3, CObstacle::Long_Shelf, 0, 6, 1)->SetDialogue(0, "Just a shelf with personal belongings and picture");
       AddObstacle(3, CObstacle::Bed, 4, 7, 0)->SetDialogue(0, "A Queen-size Bed, Floral Blanket seems disturbed, seems like someone was lying down here before");
       Evidenceptr[CEvidence::Divorce_Papers] = AddObstacle(3, CObstacle::Desk, 6, 9, 0);
       AddObstacle(3, CObstacle::Desk, 3, 9, 0)->SetDialogue(0, "A 50 shades of grey book on the desk, kinky");
       AddObstacle(3, CObstacle::Flower, 7, 0, 0)->SetDialogue(0, "A Potted Plant, Nothing much");
       AddObstacle(3, CObstacle::Flower, 4, 0, 0)->SetDialogue(0, "A Potted Plant, Nothing much");
       AddObstacle(3, CObstacle::Door, 0, 3, 0);
       addItems(note, CItem::CODE_NOTE);

   }

   /*The Mansion's Bedroom ROOM 4*/
   {
       map[4].SetRoom(7, 5, 2, 0);//Mansion bedroom
       map[4].SetName("The Mansion's Child's bedroom");
       AddObstacle(4, CObstacle::Bed, 0, 3, 1)->SetDialogue(0, "A King-size bed with a few unfolded clothes and another pile of folded clothes on it.");
       AddObstacle(4, CObstacle::Desk, 0, 2, 1);
       AddObstacle(4, CObstacle::Small_Shelf, 6, 2, 1);
       AddObstacle(2, CObstacle::Door, 3, 0, 0);


   }

   /*The Mansion garden ROOM 5*/
   {

       map[5].SetRoom(20, 20, 0, 2);//Mansion garden
       map[5].SetName("The Mansion's Garden");
       for (int y = 3; y < 16; y++) // left flower bed 
       {
           for (int x = 3; x < 8; x++)
           {
               AddObstacle(5, CObstacle::Flower, x, y, 0);
           }
       }

       for (int y = 3; y < 16; y++)// right flower bed 
       {
           for (int x = 11; x < 16; x++)
           {
               AddObstacle(5, CObstacle::Flower, x, y, 0);
           }
       }

       for (int x = 0; x < 20; x += 2)// top tree row
       {
           AddObstacle(5, CObstacle::Tree, x, 0, 0);
       }

       for (int x = 0; x < 20; x += 2)// bottom tree row
       {
           AddObstacle(5, CObstacle::Tree, x, 19, 0);
       }

       for (int x = 4; x < 7; x++) // top left chairs
       {
           AddObstacle(5, CObstacle::Chair, x, 2, 0);
       }

       for (int x = 4; x < 7; x++)// bottom left chairs
       {
           AddObstacle(5, CObstacle::Chair, x, 16, 0);
       }

       for (int x = 12; x < 15; x++)// top right chairs
       {
           AddObstacle(5, CObstacle::Chair, x, 2, 0);
       }

       for (int x = 12; x < 15; x++)// bottom left chairs
       {
           AddObstacle(5, CObstacle::Chair, x, 16, 0);
       }

       AddObstacle(5, CObstacle::Door, 0, 7, 0);
       AddObstacle(5, CObstacle::Door, 7, 0, 0);
       AddObstacle(5, CObstacle::Window, 0, 5, 0)->SetDialogue(0, "A window with a stunning view to the living room sofa...");
       AddObstacle(5, CObstacle::Window, 0, 4, 0)->SetDialogue(0, "A window with a stunning view to the living room sofa...");
       AddObstacle(5, CObstacle::Window, 0, 3, 0)->SetDialogue(0, "A window with a stunning view to the living room sofa...");

   }

   /*The Mansion study room story ROOM 6*/
   {
       map[6].SetRoom(6, 7, 2, 0);//Mansion study room STORY
       map[6].SetName("The Mansion's Study room");
       AddObstacle(6, CObstacle::Door, 3, 0, 0);
       Evidenceptr[CEvidence::Gunpowder_Ziploc] = AddObstacle(6, CObstacle::Chair, 5, 5, 0);
       Evidenceptr[CEvidence::Broken_Whiskey_Glass] = AddObstacle(6, CObstacle::Table, 3, 4, 1);
       Evidenceptr[CEvidence::Brass_Candlestick] = AddObstacle(6, CObstacle::Long_Shelf, 0, 3, 1);
       AddObstacle(6, CObstacle::Small_Shelf, 0, 0, 0);

       mapIntroDialogue[6] = {
         {"Batista", "Here he is. Dead. Cold. Ay, and a waste of good whiskey too,"},
         {"Narrator", "Batista pointed at the body, a broken whiskey glass can be seen on the floor beside the table."},
         {"Narrator", "Black scans the room briefly."},
         {"Narrator", "He catches a faint smell of gunpowder in the air. He walks to the window - no sign of forced entry."}
       };
   }

   /*The Mansion kitchen ROOM 7*/
   {
       map[7].SetRoom(17, 10, 0, 2);//Mansion kitchen
       map[7].SetName("The Mansion's Kitchen");
       for (int x = 2; x < 8; x++)// table
       {
           AddObstacle(7, CObstacle::Table, x, 4, 1)->SetDialogue(0, "Table with a candle in the middle");
       }
       for (int x = 2; x < 8; x += 2)// chairs top
       {
           AddObstacle(7, CObstacle::Chair, x, 3, 0)->SetDialogue(0, "You sat down...then you stand up");
       }
       for (int x = 2; x < 8; x += 2)// chairs bottom
       {
           AddObstacle(7, CObstacle::Chair, x, 6, 0)->SetDialogue(0, "You sat down...then you stand up");
       }
       AddObstacle(7, CObstacle::Chair, 1, 4, 0)->SetDialogue(0, "You sat down...then you stand up");
       AddObstacle(7, CObstacle::Chair, 8, 5, 0)->SetDialogue(0, "You sat down...then you stand up");

       AddObstacle(7, CObstacle::Table, 11, 4, 1);

       for (int y = 1; y < 6; y += 2)// cooking area
       {
           AddObstacle(7, CObstacle::Table, 15, y, 1);
       }
       AddObstacle(7, CObstacle::Sink, 15, 7, 0);
       AddObstacle(7, CObstacle::Sink, 15, 8, 0);

       for (int y = 0; y < 9; y += 2)// top shelf
       {
           AddObstacle(7, CObstacle::Small_Shelf, 16, y, 1);
       }

       AddObstacle(7, CObstacle::Long_Shelf, 13, 0, 0)->SetDialogue(0, "Just bunch of Kitchen Appliance");
       AddObstacle(7, CObstacle::Long_Shelf, 13, 9, 0)->SetDialogue(0, "Just bunch of Kitchen Appliance");

       AddObstacle(7, CObstacle::Window, 7, 0, 0);
       AddObstacle(7, CObstacle::Window, 8, 0, 0);

       AddObstacle(7, CObstacle::Window, 7, 9, 0)->SetDialogue(0, "Stunning view to the garden");
       AddObstacle(7, CObstacle::Window, 8, 9, 0)->SetDialogue(0, "There is a mold stain on this window, someone ain't doing their job");

       AddObstacle(7, CObstacle::Door, 5, 9, 0)->SetDialogue(0, "Door to the garden");

   }

   /*The Neighbour hse living rm ROOM 8*/
   {
       map[8].SetRoom(10, 15, 2, 0);//Neighbour hse living rm
       map[8].SetName("The Collins' Living room");

       AddObstacle(8, CObstacle::Door, 3, 0, 0);
       AddObstacle(8, CObstacle::Door, 5, 14, 0)->SetDialogue(0, "Locked Door, with about 45 chained padlock");
       AddObstacle(8, CObstacle::Window, 5, 0, 0);
       AddObstacle(8, CObstacle::Window, 6, 0, 0);

       AddObstacle(8, CObstacle::Table , 0, 7, 1)->SetDialogue(0, "Is that a Samsung UN110S9VFXZA 4K Ultra High Definition TV, that has a 240 Hz refresh rate and 110-inch screen?");
       AddObstacle(8, CObstacle::Long_Shelf, 0, 3, 1)->SetDialogue(0, "A few Pictures of the Collins Family");
       AddObstacle(8, CObstacle::Small_Shelf, 0, 9, 1)->SetDialogue(0, "CDs of mulitple Movies: The Shining, Mean girls, Tom & Jerry...");
       Evidenceptr[CEvidence::Shoebox_of_property_Photos] = AddObstacle(8, CObstacle::Table, 2, 7, 1);
       AddObstacle(8, CObstacle::Sofa, 4, 7, 1);
       AddObstacle(8, CObstacle::Sofa, 2, 5, 0);
       AddObstacle(8, CObstacle::Sofa, 2, 10, 0);

       AddObstacle(8, CObstacle::Small_Shelf, 9, 3, 1)->SetDialogue(0, "A few Pictures of the Collins Family");
       AddObstacle(8, CObstacle::Small_Shelf, 9, 10, 1)->SetDialogue(0, "An Ischia Rising Stars Trophy with the name Lily Collins");

   }

   /*The Neighbour hse kitchen rm ROOM 9*/
   {
       map[9].SetRoom(10, 10, 0, 2);//Neighbour hse Kitchen
       map[9].SetName("The Collins' Kitchen");
       AddObstacle(9, CObstacle::Long_Shelf, 9, 6, 1)->SetDialogue(0, "A bunch of kitchen stuff");
       AddObstacle(9, CObstacle::Long_Shelf, 5, 9, 0)->SetDialogue(0, "A bunch of kitchen stuff");
       AddObstacle(9, CObstacle::Table, 6, 8, 0)->SetDialogue(0, "A Bread, wrapped in plastic, multiple baking tools on the table");
       AddObstacle(9, CObstacle::Table, 8, 7, 1)->SetDialogue(0, "A Bread, wrapped in plastic, multiple baking tools on the table");
       AddObstacle(9, CObstacle::Desk, 8, 6, 1)->SetDialogue(0, "A cutting board");
       AddObstacle(9, CObstacle::Sink, 5, 8, 1);

       AddObstacle(9, CObstacle::Table, 3, 3, 1);
       AddObstacle(9, CObstacle::Table, 4, 3, 1);
       AddObstacle(9, CObstacle::Chair, 3, 2, 1);
       AddObstacle(9, CObstacle::Chair, 2, 4, 1);
       AddObstacle(9, CObstacle::Chair, 4, 5, 1);

       AddObstacle(9, CObstacle::Flower, 9, 2, 1);
       AddObstacle(9, CObstacle::Door, 0, 3, 1);

       mapIntroDialogue[9] = {
          {"Black", "Woah, Smells like freshly baked bread"},
          {"Silas", "Of course, the bread is right there."},
          {"Black", "So what she say about baking bread was true"},
          {"Narrator", "Detective Black stares at the bread"},
          {"Black", "Do you think she will notice if i take a little bite?"},
          {"Silas", "Bro..." }
       };
   }


   /*The Prosecutor office rm ROOM 10*/
   {
       map[10].SetRoom(15, 10, 2, 0);//Prosecutor office
       map[10].SetName("The Prosecutors' Office");
       AddObstacle(10, CObstacle::Door, 3, 0, 0);;
       AddObstacle(10, CObstacle::Sofa, 4, 3, 0);
       AddObstacle(10, CObstacle::Sofa, 4, 7, 0);
       AddObstacle(10, CObstacle::Chair, 7, 5, 0);
       AddObstacle(10, CObstacle::Table, 4, 5, 0);
       AddObstacle(10, CObstacle::Table, 11, 4, 1);
       AddObstacle(10, CObstacle::Chair, 13, 4, 1);
       AddObstacle(10, CObstacle::Long_Shelf, 11, 0, 0);
       AddObstacle(10, CObstacle::Long_Shelf, 11, 9, 0);
       AddObstacle(10, CObstacle::Long_Shelf, 0, 5, 1);
       AddObstacle(10, CObstacle::Flower, 5, 9, 0);
       AddObstacle(10, CObstacle::Window, 5, 0, 0);
       AddObstacle(10, CObstacle::Window, 6, 0, 0);
   }


   {
       map[11].SetRoom(20, 15, 0, 2);//mansion Porch STORY
       map[11].SetName("Mansion Porch");
       for (int y = 0; y < 14; y += 3)//  tree col
       {
           AddObstacle(11, CObstacle::Tree, 5, y, 0);
       }

       for (int y = 1; y < 3; y++)//  cordon1
       {
           AddObstacle(11, CObstacle::Tape, 5, y, 0);
       }
       for (int y = 4; y < 6; y++)//  cordon2
       {
           AddObstacle(11, CObstacle::Tape, 5, y, 0);
       }
       for (int y = 10; y < 12; y++)//  cordon3
       {
           AddObstacle(11, CObstacle::Tape, 5, y, 0);
       }
       for (int y = 13; y < 15; y++)//  cordon4
       {
           AddObstacle(11, CObstacle::Tape, 5, y, 0);
       }

       for (int y = 0; y < 6; y++)// top flower bed
       {
           for (int x = 7; x < 19; x++)
           {
               AddObstacle(11, CObstacle::Flower, x, y, 0);
           }
       }

       for (int y = 9; y < 15; y++)// bottom flower bed
       {
           for (int x = 7; x < 19; x++)
           {
               AddObstacle(11, CObstacle::Flower, x, y, 0);
           }
       }

       AddObstacle(11, CObstacle::Door, 19, 7, 0);

       mapIntroDialogue[11] = {
            {"Narrator", "Black and reed arrive at the crime screne"},
            {"Narrator", "They can see multiple officers cordoning off the area."},
            {"Silas", "Rich people, huh. Bet the maid dusts more than we make in a month."},
            {"Silas", "Maybe we can sneak a bit of loot out"},
            {"Black", "We are detectives Silas not theives.... tho if they do have smt they wont notice or care losing maybe"},
            {"Narrator", "Black and reed walk up the the officers as the officer stops them"},
            {"Officer", "Sorry, We cant allow entry unless you are permitted"},
            {"???", "Its Ok their with me!"},
            {"Narrator", "A big bald man walks towards them with a fedora, a well maintained mustache and goatee, floral shirt, cargo shorts, grinning"},
            {"Black", "Detective Batista! After all these years, can't believe this is how we reunite!"},
            {"Barista", "Ay Cabron Ha Ha Ha"},
            {"Narrator", "Detective Batista laughed as he went in for an embrace with Detective Black."},
            {"Silas", "Damn it. that was all of it"},
            {"Narrator", "Silas Hands over his last 20 bucks"},
       };

   }


   /*The Collin's Porch ROOM 12*/
   {
       map[12].SetRoom(15, 10, 2, 0);//collin Porch
       map[12].SetName("Collin Porch");
       for (int y = 0; y < 14; y += 3)//  tree col
       {
           AddObstacle(12, CObstacle::Tree, 5, y, 0);
       }
       for (int y = 0; y < 6; y++)// top flower bed
       {
           for (int x = 7; x < 19; x++)
           {
               AddObstacle(12, CObstacle::Flower, x, y, 0);
           }
       }

       for (int y = 9; y < 15; y++)// bottom flower bed
       {
           for (int x = 7; x < 19; x++)
           {
               AddObstacle(12, CObstacle::Flower, x, y, 0);
           }
       }

       mapIntroDialogue[12] = {
         {"Black", "Dang, their porch looks the same"},
         {"Silas", "fr"}
       };
   }


   /*The Main mansion Porch ROOM 13*/
   {
       map[13].SetRoom(20, 15, 0, 2);// Main mansion Porch
       map[13].SetName("Mansion Porch");
       for (int y = 0; y < 14; y += 3)//  tree col
       {
           AddObstacle(13, CObstacle::Tree, 5, y, 0);
       }

       for (int y = 1; y < 3; y++)//  cordon1
       {
           AddObstacle(13, CObstacle::Tape, 5, y, 0);
       }
       for (int y = 4; y < 6; y++)//  cordon2
       {
           AddObstacle(13, CObstacle::Tape, 5, y, 0);
       }
       for (int y = 10; y < 12; y++)//  cordon3
       {
           AddObstacle(13, CObstacle::Tape, 5, y, 0);
       }
       for (int y = 13; y < 15; y++)//  cordon4
       {
           AddObstacle(13, CObstacle::Tape, 5, y, 0);
       }

       for (int y = 0; y < 6; y++)// top flower bed
       {
           for (int x = 7; x < 19; x++)
           {
               AddObstacle(13, CObstacle::Flower, x, y, 0);
           }
       }

       for (int y = 9; y < 15; y++)// bottom flower bed
       {
           for (int x = 7; x < 19; x++)
           {
               AddObstacle(13, CObstacle::Flower, x, y, 0);
           }
       }

       AddObstacle(13, CObstacle::Door, 19, 7, 0);
   }

   /*The Main Mansion study room  ROOM 14*/
   {
       map[14].SetRoom(6, 7, 2, 0);//Mansion study room 
       map[14].SetName("The Mansion's Study room");
       AddObstacle(14, CObstacle::Door, 3, 0, 0);
       AddObstacle(14, CObstacle::Chair, 5, 5, 0);
       AddObstacle(14, CObstacle::Table, 3, 4, 1);
       AddObstacle(14, CObstacle::Long_Shelf, 0, 3, 1);
       Evidenceptr[CEvidence::Bank_Statement] = AddObstacle(14, CObstacle::Small_Shelf, 0, 0, 0);
   }




   /*To place The Objects with height and symbol*/
   for (int i = 0; i < MAX_MAPS; i++) {
       for (int j = 0; j < mapObstacles[i].size(); j++) {
           CObstacle* o = mapObstacles[i][j];
           map[i].SetObstacle(o->GetWidth(), o->GetHeight(),
               o->GetSymbol(), o->GetPosX(), o->GetPosY());
       }
   }

   // Placing the NPC's symbol
   for (int i = 0; i < MAX_MAPS; i++) {
       for (int j = 0; j < mapNPCs[i].size(); j++) {
           NPC* n = mapNPCs[i][j];
           map[i].SetNPC(n->getSymbol(), n->GetPosX(), n->GetPosY());
       }
   }


    /*To place The Objects with height and symbol*/
    for (int i = 0; i < MAX_MAPS; i++) {
        for (int j = 0; j < mapObstacles[i].size(); j++) {
            CObstacle* o = mapObstacles[i][j];
            map[i].SetObstacle(o->GetWidth(), o->GetHeight(),
                o->GetSymbol(), o->GetPosX(), o->GetPosY());
        }
    }

    // Placing the NPC's symbol
    for (int i = 0; i < MAX_MAPS; i++) {
        for (int j = 0; j < mapNPCs[i].size(); j++) {
            NPC* n = mapNPCs[i][j];
            map[i].SetNPC(n->getSymbol(), n->GetPosX(), n->GetPosY());
        }
    }










    Connect.resize(15);
    Connect[0] = { 10, 12 ,11, 13};
    Connect[1] = { 2, 3, 4, 5, 6, 7, 10, 13, 14 };
    Connect[2] = { 1 };
    Connect[3] = { 1, 2, 4, 14 };
    Connect[4] = { 1, 2, 3, 14 };
    Connect[5] = { 1, 7 };
    Connect[6] = { 1 };
    Connect[7] = { 1, 5 };
    Connect[8] = { 9, 12 };
    Connect[9] = { 8 };
    Connect[10] = { 0, 1 };
    Connect[11] = { 0, 6 };
    Connect[12] = { 0, 8, 13 };
    Connect[13] = { 0, 1, 12 };
    Connect[14] = { 1, 2, 3, 4 };

}
int CGameManager::SelectDestination(vector<int>& options) {
    int pos = 0;
    bool selecting = true;
    int destination = -1;

    while (selecting) {
        CUI::GetInstance().Clear();
        cout << "\n      [Where do you want to go now, Mr Black?]\n";
        cout << "+====Current Location: " << map[currentMap].GetName() << "====+" << endl << endl;

        for (int i = 0; i < (int)options.size(); i++) {
            if (i == pos) {
                cout << "      ~> " << "[" << map[options[i]].GetName() << "]" << endl;
            }
            else {
                cout << "         " << "[" << map[options[i]].GetName() << "]" << endl;
            }
        }

        int input = _getch();

        if (input == 0 || input == 224) {
            input = _getch();
            if (input == 72 && pos > 0) {
                pos -= 1;
            }
            else if (input == 80 && pos < (int)options.size() - 1) {
                pos += 1;
            }
        }
        else if (input == 13) {
            destination = options[pos];
            selecting = false;
        }
        else if (input == 27) {
            selecting = false;
        }
    }

    return destination;
}

void CGameManager::changeMaps(char input)
{
    if (input == 'm') {
        if (!CanTravel) {
            displayDialogue("Silas", "We're not going anywhere till we know what we're dealing with.");
            return;
        }
        if (currentMap == 6 && (!CanTravel2 || !hasTalkToBatista)) { //added this for study room
            displayDialogue("Silas", "Lets look around a little more...");
            return;
        }
        vector<int> available;
        for (int m : Connect[currentMap]) {
            if (m == 3) {
                available.push_back(m); // added this
            }
            else if (m == 12) {
                if (IsCollinPorchVisible) {
                    available.push_back(m); // added this too
                }
            }
            else if (IsMapUnlocked(m)) {
                available.push_back(m);
            }
        }
        int destination = SelectDestination(available);

        if (destination == 3 && !IsBedroomkeyPresent) {
            displayDialogue("Silas", "This room is locked, we need something to get in first.");
            displayDialogue("Black", "Let's talk to Mrs Smith for this.");
            if (emily->getCurrentEvent() == 0)
            {
                emily->Addeventflag();
            }
            return;
        }
        if (destination == 12 && !IsCollinAvailable) {
            displayDialogue("Silas", "This House is locked, we need something to get in first.");
            return;
        }

        if (destination != -1) {
            map[currentMap].removePosition(
                map[currentMap].GetPlayer()->GetPosY(),
                map[currentMap].GetPlayer()->GetPosX()
            );

            currentMap = destination;
            if (destination == 0) {
                map[currentMap].GetPlayer()->SetPosX(5);
                map[currentMap].GetPlayer()->SetPosY(1);
                map[currentMap].SetPosition();
                map[currentMap].RenderMap();
            }
            else if (destination == 6){
                map[currentMap].GetPlayer()->SetPosX(0);
                map[currentMap].GetPlayer()->SetPosY(2);
                map[currentMap].SetPosition();
                map[currentMap].RenderMap();
                RemoveRoom(11);
                IsMainPorchAvailable = true;
            }
            else if (destination == 1){
                map[currentMap].GetPlayer()->SetPosX(0);
                map[currentMap].GetPlayer()->SetPosY(2);
                map[currentMap].SetPosition();
                map[currentMap].RenderMap();
                RemoveRoom(6);
                IsMainStudyAvailable = true;
            }
            else if (destination%2 != 0 && destination != 0){
                map[currentMap].GetPlayer()->SetPosX(0);
                map[currentMap].GetPlayer()->SetPosY(2);
                map[currentMap].SetPosition();
                map[currentMap].RenderMap();
            }
            else {
                map[currentMap].GetPlayer()->SetPosX(2);
                map[currentMap].GetPlayer()->SetPosY(0);
                map[currentMap].SetPosition();
                map[currentMap].RenderMap();
            }

            if (currentMap == 4 && hasTalkToTrisha)
            {
                mapIntroDialogue[4] = {
                    {"Narrator", "Black walks in, a stack of folded clothes and a pile of unfolded clothes is seen on the bed."},
                    {"Black", "I guess she really was here folding clothes"},
                };

                PlayIntroDialogue(currentMap);
                hasTalkToTrisha = false;
            }

            if (currentMap == 1 && hasTalkedToMichaelAgain)
            {
                mapIntroDialogue[1] = {
                    {"Narrator", "Black winces, pressing a hand to his stomach."},
                    {"Black", "Ah shucks... too much coffee just now."},
                    {"Black", "Do you know where the toilet is?"},
                    {"Silas", "Just around the corner beside the living room."},
                    {"Game", "[Head to the toilet, Black has to take a piss.]"}
                };

                PlayIntroDialogue(currentMap);

                hasTalkedToMichaelAgain = false;
                takeAPiss = true;
            }

            if (currentMap == 2 && takeAPiss)
            {
                mapIntroDialogue[2] = {
                    {"Narrator", "Black locks the door behind him, relieving himself with a quiet sigh."},
                    {"Narrator", "As he finishes, his eyes land on something in the trash can"},
                    {"Narrator", "a glove, a dark tint staining the palm."},
                    {"Narrator", "He zips up, buckles his belt, then crouches down..."},
                    {"Narrator", "using a wad of toilet paper to pick it up without touching it directly."},
                    {"Narrator", "The stain isn't part of the glove's design — dark red, flaking at the edges where it's dried."},
                    {"Narrator", "Black brings it closer, catching a faint metallic scent."},
                    {"Black", "Smells like iron"},
                    {"Game", "[Suspicious glove added to your evidence inventory]"}
                };

                PlayIntroDialogue(currentMap);

                Evidence.SetEvidence(CEvidence::Suspicious_Glove);
                inventory->addToInventory(
                    Evidence.GetName(),
                    Evidence.GetId(),
                    Evidence.GetDescription()
                );
                caseFileSystem.addEvidence(CEvidence::Suspicious_Glove);
                caseFileSystem.addDescription(Evidence.GetDescription());

                takeAPiss = false;
            }

            if (!mapVisited[currentMap])
            {
                PlayIntroDialogue(currentMap);
                mapVisited[currentMap] = true;
            }


            CUI::GetInstance().typeText("You are now at "); CUI::GetInstance().typeText(map[currentMap].GetName()); CUI::GetInstance().typeText(".\n");
        }
        else {
            map[currentMap].RenderMap();
        }
    }


    /*Interaction Code*/
    else if (input == 'e') {

        CPlayer* player = map[currentMap].GetPlayer();
        int tx = player->GetPosX();
        int ty = player->GetPosY();

        switch (player->GetlastInput()) {
        case 'w':
            ty--;
            break;
        case 'a':
            tx--;
            break;
        case 's':
            ty++;
            break;
        case 'd':
            tx++;
            break;
        }

        NPC* NPCInteract = FindNPC(currentMap, tx, ty);
        CObstacle* ObstacleInteract = FindObstacle(currentMap, tx, ty);

        if (NPCInteract != nullptr) {
            if (NPCInteract->isSuspect() == true) {
                caseFileSystem.addSuspect(NPCInteract->getPerson());
            }

            if (NPCInteract == batista3) 
            {

                if (hasPassCandle) {
                    batista3->SetEventStartNode(0, nB5_1_candle_id);
                    hasPassCandle = false;
                }

                else if (hasPassGlass) {
                    batista3->SetEventStartNode(0, nB5_1_glass_id);
                    hasPassGlass = false;
                }

                else if (hasPassGlove) {
                    batista3->SetEventStartNode(0, nB5_1_glove_id);
                    hasPassGlove = false;
                }

                else {
                    batista3->SetEventStartNode(0, nB4_1_id);
                }
            }

            NPCInteract->dialougesystem(&map[currentMap], inventory);
            if (harvey->getIsEvidenceValid() == true) {
                switch (harvey->getPath()) {
                case 3:
                    EmilyEndingDialogue();
                    break;
                case 4:
                    MichaelEndingDialogue();
                    break;
                case 5:
                    SarahEndingDialogue();
                    break;
                }
            }
            else if (harvey->getNumOfWrongEvidence() != 0) {
                int num = harvey->getNumOfWrongEvidence();
                string text = "I need more evidence, you got " + std::to_string(num) + " evidence wrong";
                displayDialogue("Harvey", text);
                harvey->setEvidenceCounter(0);
            }
            checkNodeItems(NPCInteract);
            checkNodeEvidence(NPCInteract);

            if (whiskeyGlassRptCollected && hasShownEmilyGlass && michael->getCurrentEvent() == 2)
            {
                michael->Addeventflag();
                whiskeyGlassRptCollected = false;
            }

            checkNodeFlags(NPCInteract);

            if (hasShownEmilyEvi1) {
                emily->Addeventflag();
                hasShownEmilyEvi1 = false; // added this to make sure it dont add again
            }
            if (hasFinishEmily) {
                emily->Addeventflag();
                hasFinishEmily = false; // added this to make sure it dont add again
            }
            if (hasTalkToSarah1) {
                sarah->Addeventflag();
                hasTalkToSarah1 = false; // added this to make sure it dont add again
            }
            if (hasTalkToSarah2) {
                sarah->Addeventflag();
                hasTalkToSarah2 = false; // added this to make sure it dont add again
            }
            if (hasTalkToTrisha) {
                michael->Addeventflag();
                hasTalkToTrisha = false;
            }
            if (hasTalkToMichael1) {
                michael->Addeventflag();  // This advances from event 0 to event 1
                hasTalkToMichael1 = false;
            }
            if (hasTalkToMichael3) {
                michael->Addeventflag();
                hasTalkedToMichaelAgain = true;
                takeAPiss = true;
                hasTalkToMichael3 = false;
            }
            int removedID = NPCInteract->getLastRemovedEvidenceID();
            switch (removedID) {
            case 3001:
                hasPassCandle = true;
                break;
            case 3002:
                hasPassGlass = true; // adjust name to whatever you actually called it
                break;
            case 3004:
                hasPassGlove = true; // adjust name to whatever you actually called it
                break;
            }
            map[currentMap].RenderMap();




        }
        else if (ObstacleInteract != nullptr) {
            bool isEvidenceTile = false;
            bool puzzleActivated = false;
            int evidenceIndex = -1;
            for (int i = 0; i < MAX_EVIDENCE; i++) {
                if (ObstacleInteract == Evidenceptr[i]) {
                    if (i == 9) {
                        if (puzzleSystem.getCompletion()) {
                            isEvidenceTile = true;
                        }
                        else {
                            puzzleSystem.setBool(true);
                            puzzleSystem.setPuzzle("lock");
                            puzzleActivated = true;

                            // NEW: override with custom dialogue instead of the obstacle's default line
                            displayDialogue("Narrator", "A peculiar safe catches your eye... looks like it needs solving.");
                            puzzleSystem.renderPuzzles();
                        }
                    }
                    else {
                        isEvidenceTile = true;
                        evidenceIndex = i;
                        break;
                    }
                }
            }

            if (isEvidenceTile) {
                checkForAllEvidence(ObstacleInteract);

                switch (ObstacleInteract->GetEvidenceId()) { // adjust if the getter name differs
                case 3001:
                    candlestickFound = true;
                    break;
                case 3002:
                    whiskeyGlassFound = true;
                    break;
                case 3003:
                    gunpowderFound = true;
                    break;
                case 3004:
                    gloveFound = true;
                    break;
                case 3010:
                    bankStatementFound = true;
                    break;
                case 3011:
                    divorcePapersFound = true;
                    break;
                case 3009:
                    shoeboxFound = true;
                    break;
                }
                if (candlestickFound && whiskeyGlassFound && gunpowderFound) 
                {
                    CanTravel2 = true;
                    batista2->Addeventflag();
                }
                if (bankStatementFound && divorcePapersFound) 
                {
                    emily->Addeventflag();
                }
                if (shoeboxFound)
                {
                    sarah->Addeventflag();
                }

            }
            else if (!puzzleActivated) {
                CItem* foundItem = ObstacleInteract->GetItemPtr();
                if (foundItem != nullptr) {
                    inventory->addToInventory(foundItem->GetItemName(), foundItem->GetId(), foundItem->GetInventoryDialogue());
                    displayDialogue("Narrator", ObstacleInteract->GetNextDialouge());
                    ObstacleInteract->SetItemPtr(nullptr);
                    switch (foundItem->GetId()) {
                    case 1001:
                        NotebookisFound = true;
                        break;
                    case 1002:
                        CarKeysisFound = true;
                        break;
                    case 1003:
                        jacketisFound = true;
                        break;
                    }
                    if (NotebookisFound && CarKeysisFound && jacketisFound) {
                        Silas->Addeventflag();
                    }
                }
                else {
                    displayDialogue("Narrator", ObstacleInteract->GetNextDialouge());
                }
            }
            }
        else {
            displayDialogue("Silas", "theres nothing there... might be losing it pal");
        }

    }



    else if (input == 'f') {
        char npc;
        npc = map[0].GetItem(map[currentMap].GetPlayer()->GetPosX(), map[currentMap].GetPlayer()->GetPosY());
    }
    else {
        map[currentMap].Movement(input);
    }
}

void CGameManager::checkNodeItems(NPC* npc) {
    for (int i = 0; i < (int)nodeItems.size(); i++) {
        NodeItems r = nodeItems[i];
        if (r.npc == npc && npc->getCurrentNode() == r.node) {
            bool itemExists = false;
            for (int j = 0; j < inventory->GetItemCount(); j++) {
                if (inventory->GetInventoryID(j) == r.itemType) {
                    itemExists = true;
                    break;
                }
            }
            if (itemExists) {
                continue; // check of player alr has item
            }
            string dialogue = CItem::GetItemDialogueByType(r.itemType);
            inventory->addToInventory(r.itemName, r.itemType, dialogue);
            if (r.itemType == CItem::MASTER_BEDROOM_KEY) {
                IsBedroomkeyPresent = true;
            }
            if (r.itemType == CItem::NEIGHBOUR_HOUSE_KEY) {   
                IsCollinAvailable = true;
            }
        }
    }
}

void CGameManager::checkNodeEvidence(NPC* npc) {
    for (int i = 0; i < (int)nodeEvidence.size(); i++) {
        NodeEvidence r = nodeEvidence[i];
        if (r.npc == npc && npc->getCurrentNode() == r.node) {
            Evidence.SetEvidence(r.evidenceType);
            bool alreadyHas = false;
            for (int j = 0; j < inventory->GetItemCount(); j++) {
                if (inventory->GetInventoryID(j) == Evidence.GetId()) {
                    alreadyHas = true;
                    break;
                }
            }
            if (alreadyHas) {
                continue;
            }
            inventory->addToInventory(Evidence.GetName(), Evidence.GetId(), Evidence.GetDescription());
            caseFileSystem.addEvidence(r.evidenceType);
            caseFileSystem.addDescription(Evidence.GetDescription());
            if (r.evidenceType == CEvidence::BrokenWhiskey_Glass_Report) {
                whiskeyGlassRptCollected = true;
            }
        }
    }
}

void CGameManager::displayDialogue(string c, string t) {
    CUI::GetInstance().RenderDialougeBox(c, t);
    map[currentMap].RenderMap();
}

void CGameManager::TestDialogue() {
    displayDialogue("Narrator", "It's Thursday night, 18:34. Detective Black sits in his office, smoking a cigar. A knock sounds at the door.");
    displayDialogue("Black", "Come in.");
    displayDialogue("Narrator", "He stubs out the cigar in the ashtray as the door opens.");
    displayDialogue("Narrator", "In comes a tall, leanly built man, hair side-parted, a visible eye bag under each eye.");
    displayDialogue("Narrator", "It's Silas Reed, Black's partner and assistant.");
    displayDialogue("Silas", "We just got a call");
    displayDialogue("Silas", "Sounds like a murder down in Willow's Creek. We're up.");
}

void CGameManager::RunGame() {
    map[currentMap].RenderMap();
    TestDialogue();
    while (IsGameRunning) {
        char input = _getch();

        if (input == 27) {
            bool keepPlaying = CUI::GetInstance().PauseMenu();
            if (!keepPlaying) {
                IsGameRunning = false;
            }
            else {
                map[currentMap].RenderMap();
            }
            continue;
        }

        else if (input == 'i' && caseFileSystem.getCFSState() == false) {
            inventory->showInventory(input);
            if (!inventory->getInventoryState()) {
                map[currentMap].RenderMap();
            }
            continue;
        }

        else if (input == 'c' && inventory->getInventoryState() == false) {
            if (!IsCaseFileUnlocked)
            {
                displayDialogue("Game", "You have not unlock this feature yet...");
                continue;
            }
            caseFileSystem.showFiles(input); //added this
            if (!caseFileSystem.getCFSState())
            {
                map[currentMap].RenderMap();
            }
            continue;
        }

        else if (puzzleSystem.getBool() == true) {
            puzzleSystem.inputNum(input);
            if (input == 'b') {
                puzzleSystem.setBool(false);
                map[currentMap].RenderMap();
            }
            else {
                puzzleSystem.renderPuzzles();
                if (puzzleSystem.getActivateDialogue()) {
                    map[currentMap].RenderMap();
                    displayDialogue("Narrator", "The safe has been unlocked!");
                    puzzleSystem.setActivateDialogue(false);

                }
            }
        }

        else if (inventory->getInventoryState() == false) {
            if (caseFileSystem.getCFSState() == false) {
                changeMaps(input);
            }
            else {
                caseFileSystem.changeFiles(input);
                caseFileSystem.renderFiles();
            }
        }
        else {
            if (input == 13) { // Enter key
                if (inventory->GetItemCount() > 0) {
                    int pos = inventory->getItemPosition();
                    string dialogue = inventory->GetInventoryDialogue(pos);
                    if (!dialogue.empty()) {
                        displayDialogue("Narrator", dialogue);
                    }
                }
                inventory->renderInventory();
            }
            else {
                inventory->switchItem(input);
                inventory->renderInventory();
            }
        }
    }
}

CGameManager::CGameManager() {
    hasTalkedToMichaelAgain = false;
    currentMap = 0;
    currentUI = 0;
    SetMaps();
    CUI::GetInstance().Run();
    if (CUI::GetInstance().GetGameStart()){
        IsGameRunning = true;
    }
    else {
        IsGameRunning = false;
    }
    if (IsGameRunning) {
        RunGame();
    }
    else {
        return;
    }
}

CGameManager::~CGameManager() {
    for (auto& obstacleList : mapObstacles) {
        for (CObstacle* Obstacles : obstacleList) {
            delete Obstacles;
        }
    }
    for (auto& npcList : mapNPCs) {
        for (NPC* npcs : npcList) {
            delete npcs;
        }
    }

}