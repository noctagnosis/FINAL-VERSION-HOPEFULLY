#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class CUI
{
	int textSpeed;
	int A_SkipSpeed = 1000;
	int PlayerColor;
	bool isSettingsOpen;
	bool isSpeedSettingOpen;
	int SettingPos;
	int const static MaxSetting = 3;
	int const static MaxStartOptions = 4;
	string Settings[MaxSetting] = { "TEXT SPEED", "BACK TO START MENU", "EXIT TO DESKTOP" };
	bool GameStart;
	bool isRunning = true;
	void HandleArrow(int input);
	void HandleEnter();
	int StartMenuPos;
	string StartMenuOptions[MaxStartOptions] = { "START", "CONTROLS ", "SETTINGS", "LEAVE" };
	bool isStartMenuOpen = true;
	bool isSkipPressed = false;

	int const static MaxPauseOptions = 4;
	string PauseMenuOptions[MaxPauseOptions] = { "CONTINUE", "CONTROLS ", "SETTINGS", "EXIT" };
	int PauseMenuPos;
	bool GetSkip();
	void SkipReset();
	bool isPauseMenuOpen;
	bool isPauseLoopActive;
	bool PausedFromGame;
	bool ExitToDesktop;
	bool autoSkip = false;

	bool isControlsOpen = false;
	bool controlsFromPause = false;


public:
	void RenderStartMenu();
	void SwitchStartMenuOption(int input);
	bool GetGameStart();
	static void delayMs(int ms);
	void SetTextSpeed(int speed);
	void typeText(const string text);
	void NextDialouge();
	void RenderDialougeBox(const string character, const string text);
	void RenderDialougeBoxNPC(const string character, const string text);
	void RenderSettings();
	void DisplayTextSpeedSettings();
	void ChangeSpeed(char input);
	void SwitchSetting(int input);
	void Run();
	void Clear();
	void RenderControls();


	void RenderPauseMenu();
	void SwitchPauseMenuOption(int input);
	bool PauseMenu();

	static CUI& GetInstance() {
		static CUI instance;
		return instance;
	}
	CUI(const CUI&) = delete;
	CUI& operator=(const CUI&) = delete;

	CUI();

};