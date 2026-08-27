#define _HAS_STD_BYTE 0
#include "CUI.h"
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void CUI::delayMs(int ms) {
    clock_t start = std::clock();
    while ((std::clock() - start) * 1000 / CLOCKS_PER_SEC < ms) {}
}

void CUI::typeText(const string text) {
    isSkipPressed = false;

    for (size_t i = 0; i < text.length(); i++) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 13 || key == 32) {
                isSkipPressed = true;
            }
            else if (key == 9 && autoSkip) {
                autoSkip = false;
            }
            else if (key == 9) {
                autoSkip = true;
            }
        }

        if (isSkipPressed) {
            cout << text.substr(i) << std::flush;
            break;
        }

        cout << text[i] << std::flush;
        delayMs(textSpeed);
    }

    while (_kbhit()) {
        (void)_getch();
    }
}


void CUI::RenderSettings() {
    Clear();
    cout << "       [SETTINGS]\n";
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
    for (int i = 0; i < MaxSetting; i++) {
        if (i == SettingPos) {
            cout << "-> " << Settings[i] << endl << endl;
        }
        else {
            cout << "   " << Settings[i] << endl << endl;
        }
    }
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
}

void CUI::SwitchSetting(int input) {
    if (input == 72) {
        if (SettingPos > 0) {
            SettingPos -= 1;
        }
    }
    else if (input == 80) {
        if (SettingPos < MaxSetting - 1) {
            SettingPos += 1;
        }
    }
}
bool CUI::GetSkip() {
    return isSkipPressed;
}
void CUI::SkipReset() {
    isSkipPressed = false;
}

void CUI::RenderDialougeBox(const string character, const string text) {
    string fullLine = "\033[32m" + character + "\033[0m" + ": " + text;
    int boxWidth = (int)fullLine.length() - 9 + 6;

    cout << "+" << std::string(boxWidth - 2, '-') << "+\n";
    cout << "|  ";
    typeText(fullLine);
    cout << "  |\n";
    cout << "+" << std::string(boxWidth - 2, '-') << "+\n";
    if (!autoSkip) {
        cout << "\n   [Press Enter to continue or Press Tab for Auto-Skip]";
    }
    else if (autoSkip) {
        cout << "\n   [Auto Skip Is enabled]";
        delayMs(A_SkipSpeed);
        return;
    }
    int skip;
    do {
        skip = _getch();
        if (skip == 9) {
            autoSkip = !autoSkip;
            if (autoSkip) return;
        }
    } while (skip != 13 && skip != 32);
}

void CUI::RenderDialougeBoxNPC(const string character, const string text) {
    string fullLine = "\033[32m" + character + "\033[0m" + ": " + text;
    int boxWidth = (int)fullLine.length() - 9 + 6;

    cout << "+" << std::string(boxWidth - 2, '-') << "+\n";
    cout << "|  ";
    typeText(fullLine);
    cout << "  |\n";
    cout << "+" << std::string(boxWidth - 2, '-') << "+\n";
}

void CUI::NextDialouge() {
    cout << "\n[ Continue... ]";
    while (true) {
        int input = _getch();
        if (input == 13 || input == 32) {
            break;
        }
    }
}

void CUI::SetTextSpeed(int speed) {
    textSpeed = speed;
}

void CUI::DisplayTextSpeedSettings() {
    Clear();
    cout << "       [Text Speed]\n";
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
    cout << "          < " << textSpeed << " >\n";
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
}

void CUI::ChangeSpeed(char input) {
    if (input == 77 && textSpeed < 50) {
        textSpeed += 5;
    }
    else if (input == 75 && textSpeed > 10) {
        textSpeed -= 5;
    }
}

void CUI::HandleArrow(int input) {
    if (isSpeedSettingOpen) {
        ChangeSpeed((char)input);
        DisplayTextSpeedSettings();
    }
    else if (isPauseMenuOpen) {
        SwitchPauseMenuOption(input);
        RenderPauseMenu();
    }
    else if (isSettingsOpen) {
        SwitchSetting(input);
        RenderSettings();
    }
    else if (isStartMenuOpen) {
        SwitchStartMenuOption(input);
        RenderStartMenu();
    }
}

void CUI::HandleEnter() {
    if (isControlsOpen) {
        isControlsOpen = false;
        if (controlsFromPause) {
            isPauseMenuOpen = true;
            RenderPauseMenu();
        }
        else {
            isStartMenuOpen = true;
            RenderStartMenu();
        }
        return;
    }

    if (isSpeedSettingOpen) {
        isSpeedSettingOpen = false;
        isSettingsOpen = true;
        RenderSettings();
        return;
    }

    if (isPauseMenuOpen) {
        switch (PauseMenuPos) {
        case 0:
            isPauseMenuOpen = false;
            isPauseLoopActive = false;
            break;
        case 1:
            isPauseMenuOpen = false;
            isControlsOpen = true;
            controlsFromPause = true;
            RenderControls();
            break;
        case 2:
            isPauseMenuOpen = false;
            isSettingsOpen = true;
            Settings[1] = "RETURN TO PAUSE MENU";
            RenderSettings();
            break;
        case 3:
            isPauseMenuOpen = false;
            isPauseLoopActive = false;
            ExitToDesktop = true;
            break;
        }
        return;
    }

    if (isStartMenuOpen) {
        switch (StartMenuPos) {
        case 0:
            isStartMenuOpen = false;
            Settings[MaxSetting - 1] = "RESUME";
            isRunning = false;
            GameStart = true;
            break;
        case 1:
            isStartMenuOpen = false;
            isControlsOpen = true;
            controlsFromPause = false;
            RenderControls();
            break;
        case 2:
            isStartMenuOpen = false;
            isSettingsOpen = true;
            RenderSettings();
            break;
        case 3:
            GameStart = false;
            isRunning = false;
            break;
        }
        return;
    }

    if (isSettingsOpen) {
        switch (SettingPos) {
        case 0:
            isSettingsOpen = false;
            isSpeedSettingOpen = true;
            DisplayTextSpeedSettings();
            break;
        case 1:
            isSettingsOpen = false;
            if (PausedFromGame) {
                Settings[1] = "RESUME TO PAUSE MENU";
                PausedFromGame = false;
                isPauseMenuOpen = true;
                RenderPauseMenu();
            }
            else {
                isStartMenuOpen = true;
                RenderStartMenu();
            }
            break;
        case 2:
            isPauseLoopActive = false;
            GameStart = false;
            isRunning = false;
            break;
        }
    }
}

void CUI::RenderStartMenu() {
    Clear();
    string title = "A Liar's Paradox";
    int boxWidth = (int)title.length() + 6;
    cout << "+" << std::string(boxWidth - 2, '~') << "+\n";
    cout << "|  ";
    cout << title;
    cout << "  |\n";
    cout << "+" << std::string(boxWidth - 2, '~') << "+\n";


    for (int i = 0; i < MaxStartOptions; i++) {
        if (i == StartMenuPos) {
            cout << "   ~> " << StartMenuOptions[i] << endl << endl;
        }
        else {
            cout << "      " << StartMenuOptions[i] << endl << endl;
        }
    }
}

void CUI::SwitchStartMenuOption(int input) {
    if (input == 72) {
        if (StartMenuPos > 0) {
            StartMenuPos -= 1;
        }
    }
    else if (input == 80) {
        if (StartMenuPos < MaxStartOptions - 1) {
            StartMenuPos += 1;
        }
    }
}
bool CUI::GetGameStart() {
    return GameStart;
}


void CUI::RenderPauseMenu() {
    Clear();
    cout << "       [PAUSED]\n";
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
    for (int i = 0; i < MaxPauseOptions; i++) {
        if (i == PauseMenuPos) {
            cout << "-> " << PauseMenuOptions[i] << endl << endl;
        }
        else {
            cout << "   " << PauseMenuOptions[i] << endl << endl;
        }
    }
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
}

void CUI::SwitchPauseMenuOption(int input) {
    if (input == 72) {
        if (PauseMenuPos > 0) {
            PauseMenuPos -= 1;
        }
    }
    else if (input == 80) {
        if (PauseMenuPos < MaxPauseOptions - 1) {
            PauseMenuPos += 1;
        }
    }
}

bool CUI::PauseMenu() {
    isPauseMenuOpen = true;
    isSettingsOpen = false;
    isSpeedSettingOpen = false;
    isStartMenuOpen = false;
    PausedFromGame = true;
    ExitToDesktop = false;
    PauseMenuPos = 0;

    RenderPauseMenu();
    isPauseLoopActive = true;
    while (isPauseLoopActive) {
        int input = _getch();

        if (input == 0 || input == 224) {
            input = _getch();
            HandleArrow(input);
        }
        else if (input == 13) {
            HandleEnter();
        }
    }

    return !ExitToDesktop;
}


void CUI::Run() {
    while (isRunning) {
        int input = _getch();

        if (input == 0 || input == 224) {
            input = _getch();
            HandleArrow(input);
        }
        else if (input == 13) {
            HandleEnter();
        }
    }
}

void  CUI::Clear() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    COORD homeCoords = { 0, 0 };
    DWORD count;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hConsole, homeCoords);
}
void CUI::RenderControls() {
    Clear();
    cout << "       [CONTROLS]\n";
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
    cout << "   W / A / S / D    - Move\n\n";
    cout << "   E                - Interact\n\n";
    cout << "   I                - Inventory\n\n";
    cout << "   C                - Case File\n\n";
    cout << "   M                - Map Navigation\n\n";
    cout << "   Enter / Space    - Confirm / Continue\n\n";
    cout << "   Tab              - Toggle Auto-Skip Dialogue\n\n";
    cout << "   Esc              - Pause\n\n";
    cout << "   Arrow Keys       - To select Option\n";
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~+\n";
    cout << "\n   [Press Enter to go back]";
}

CUI::CUI() {
    SetTextSpeed(35);
    SettingPos = 0;
    StartMenuPos = 0;
    isStartMenuOpen = true;
    isSettingsOpen = false;
    isSpeedSettingOpen = false;
    RenderStartMenu();
}