#pragma once
#include "CObject.h"
class CEvidence :
    public CObject
{

public:
    enum Evidence {
        Brass_Candlestick,
        Broken_Whiskey_Glass,
        Gunpowder_Ziploc,
        Suspicious_Glove,
        BrokenWhiskey_Glass_Report,
        Brass_Candlestick_Report,
        Suspicious_Glove_Report,
        Picture_of_Muddy_shoeprint,
        Shoebox_of_property_Photos,
        Bank_Statement,
        Divorce_Papers,
    };
    void SetEvidence(Evidence E);
    Evidence getEvidence();
    string GetDialogue(int num);
    void placeEvidence(int x, int y);
    bool GetFound();
    void SetFound(bool find);
    void SetName(string namegive);
    string GetName();
    int GetDialogueLength();
    int GetLength();
    int GetId();
    string GetDescription();
    CEvidence(string Name);
    CEvidence();

private:

    string description;
    int id;
    int length;
    string Dialogue[10];
    Evidence type;
    string name;
    bool found;

};
