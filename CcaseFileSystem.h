#pragma once
#include <iostream>
#include <string>
#include "CUI.h"
#include <vector>
#include "CEvidence.h"
#include "CNPC.h"
using namespace std;

class CcaseFileSystem
{
	enum CFSView {
		DOCUMENT,
		EVIDENCE,
		SUSPECT,
		NOTES
	};

	CFSView currentView = CFSView::DOCUMENT;

	vector<CEvidence> discoveredEvidence;
	vector<NPC> discoveredSuspect;
	vector<string> discoveredDocument;

	int currentFiles = 0;
	int currentDocumentFiles = 0;
	int currentEvidenceFiles = 0;
	int currentSuspectFiles = 0;
	bool isCFSOpen = false;
	string notes[5][100] = {{"No notes currently...", ""}, {"No notes currently...", ""}, {"No notes currently...", ""}, {"No notes currently...", ""}, 
	{ "No notes currently...", "" } };
	string documentDescription;
	string evidenceDescription;
	int currentNotes[5] = {1, 1, 1, 1, 1};

public:
	void changeFiles(int input);
	void renderEvidenceFiles();
	void renderSuspectFiles();
	void renderFiles();
	void addEvidence(CEvidence::Evidence type);
	void addSuspect(NPC::People name);
	void addDocument();
	void renderNotes();
	void showFiles(char input);
	bool getCFSState();
	void addNotes();
	void addDescription(string words);
	CcaseFileSystem();

};

