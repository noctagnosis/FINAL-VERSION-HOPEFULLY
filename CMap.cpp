#include "CMap.h"

void CMap::SetMAP_SIZE(int size_x, int size_y) {
	MAP_SIZE_X = size_x;
	MAP_SIZE_Y = size_y;
}
CPlayer* CMap::GetPlayer(){
    return player;
}
void CMap::SetPlayerPOS(int x, int y) {
    player->SetPosX(x);
    player->SetPosY(y);
}

char CMap::GetItem(int x, int y) {
    char item;

    if (MAP[x][y + 1] != ' ') {
        item = MAP[x][y + 1];
        MAP[x][y + 1] = '\0';
    }
    else if (MAP[x + 1][y] != ' ') {
        item = MAP[x + 1][y];
        MAP[x + 1][y] = '\0';
    }
    else if (MAP[x][y - 1] != ' ') {
        item = MAP[x][y - 1];
        MAP[x][y - 1] = '\0';
    }
    else if (MAP[x - 1][y] != ' ') {
        item = MAP[x - 1][y];
        MAP[x - 1][y] = '\0';
    }
    else {
        item = ' ';
    }
    return item;
}

void CMap::SetMap() {
	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			MAP[i][j] = '\0';
		}
	}
}
void CMap::SetPosition() {
    MAP[player->GetPosY()][player->GetPosX()] = 'd';
}

void CMap::SetObstacle(int width, int height, char symbol, int x, int y) {
    for (int i = y; i < y + height; i++) {
        for (int j = x; j <x + width; j++) {
            MAP[i][j] = symbol;
        }
    }
}

void CMap::SetNPC(char s, int x, int y) {
    MAP[y][x] = s;
}

void CMap::removePosition(int y, int x) {
    MAP[y][x] = '\0';
}

void CMap::RenderMap() {
    int width = 2 * MAP_SIZE_X + 2;
    CUI::GetInstance().Clear();

    for (int j = 0; j < width; j++) {
        cout << "~";
    }
    cout << endl;

    for (int i = 0; i < MAP_SIZE_Y; i++) {
        cout << "|";
        for (int j = 0; j < MAP_SIZE_X; j++) {
            string temp = " ";
            if (MAP[i][j] == '=') {
                temp = "=";
                temp = temp + MAP[i][j];
                cout << temp;
            }
            else if (MAP[i][j] == '\0') {
                cout << "  ";
            }
            else {
                temp = temp + MAP[i][j];
                cout << temp;
            }
        }
        cout << "|" << endl;
    }

    for (int j = 0; j < width; j++) {
        cout << "~";
    }
    cout << endl;
}
void CMap::Movement(char input) {
    MAP[player->GetPosY()][player->GetPosX()] = '\0';
    player->SetlastInput(input);
    player->Move(MAP, MAP_SIZE_X, MAP_SIZE_Y);
    SetPosition();
    RenderMap();
}

void CMap::SetRoom(int map_size_x, int map_size_y, int playerSpawnX, int playerSpawnY) {
	SetMAP_SIZE(map_size_x, map_size_y);
	SetMap();
    SetPlayerPOS(playerSpawnX, playerSpawnY);
	SetPosition();
}

void CMap::DeleteRoom() {
    for (int i = 0; i < MAP_SIZE_X; i++) {
        for (int j = 0; j < MAP_SIZE_Y; j++) {
            MAP[i][j] = '\0';
        }
    }
    MAP_SIZE_X = 0;
    MAP_SIZE_Y = 0;
    name.clear();

    if (player != nullptr) {
        player->SetPosX(0);
        player->SetPosY(0);
    }
}

void CMap::SetName(const std::string& n)
{
    name = n;
}

std::string CMap::GetName() const
{
    return name;
}

CMap::CMap() {
    player = new CPlayer();
	SetMap();
	MAP_SIZE_X = 0;
	MAP_SIZE_Y = 0;

}

CMap::~CMap() {
    delete player;
}
