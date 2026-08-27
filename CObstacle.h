#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
using namespace std;
#include "CGameObject.h"
#include "CEvidence.h"

class CItem;
class CObstacle :
    public CGameObject
{
public:
    enum Furniture
    {
        Table,
        Desk,
        Small_Shelf,
        Long_Shelf,
        Sofa,
        Chair,
        Door,
        Window,
        Flower,
        Tree,
        Bed,
        ToiletBowl,
        BathTub,
        Sink,
        Tape
    };
    void SetType(Furniture f);
    void Rotate();
    int GetWidth();
    int GetHeight();
    int GetEvidenceId(); //added this
    char GetSymbol();
    Furniture GetType();
    string GetNextDialouge();
    void SetDialogue(int index, const string text);
    string runDialogue(CEvidence::Evidence, int num);
    string GetEvidenceName(CEvidence::Evidence e);
    void SetItemPtr(CItem* i);
    CItem* GetItemPtr();
    CObstacle();

private:
    Furniture type;
    int width, height;
    char symbol;
    string IDialouge[3];
    int dialougeidx;
    CEvidence EvidenceIdx;
    int EvidenceDialogueIdx;
    CItem* item = nullptr;
    


    //Placeholders for later;
    bool isKeyObject = false;
    void SetKeyObject(bool val);
    bool IsKeyObject();
};

