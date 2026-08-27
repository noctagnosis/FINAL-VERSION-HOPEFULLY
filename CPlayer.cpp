#include "CPlayer.h"
void CPlayer::SetlastInput(char input) {
	lastInput = input;
}
char CPlayer::GetlastInput() {
    return lastInput;
}
void CPlayer::Move(char map[100][100], int map_size_x, int map_size_y) {
	int NewY = GetPosY();
	int NewX = GetPosX();
	switch (lastInput) {
    case 'w':
        if (GetPosY() > 0)
            NewY = NewY - 1;
        break;
    case 's':
        if (GetPosY() < map_size_y - 1)
            NewY = NewY + 1;
        break;
    case 'a':
        if (GetPosX() > 0)
            NewX = NewX - 1;
        break;
    case 'd':
        if (GetPosX() < map_size_x - 1)
            NewX = NewX + 1;
        break;
	}
    if (NewX >= 0 && NewX <= map_size_x - 1 && NewY >= 0 && NewY <= map_size_y - 1 && map[NewY][NewX] == '\0') {
        SetPosX(NewX);
        SetPosY(NewY);
        }
}

CPlayer::CPlayer() {
	lastInput = '\0';
	SetPosX(0);
	SetPosY(0);
}