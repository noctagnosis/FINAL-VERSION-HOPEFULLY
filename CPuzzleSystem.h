#pragma once
#include "CEvidence.h"
#include "CUI.h"

class PuzzleSystem
{
	string puzzleType;
	bool puzzleCompleted;
	bool puzzleRunning;
	CEvidence evidence;
	string userAnswer;
	int numberPosition;
	string systemMsg;

public:
	void startPuzzles(string puzzle);
	void renderPuzzles();
	void renderNumber(int num);
	void inputNum(int input);
	void enterNum(int input);
	bool getBool();
	void setBool(bool state);
	void setPuzzle(string puzzle);

	PuzzleSystem();
};

