#include "s3e.h"
#include "IwGx.h"

#include "definitions.h"
#include "game.h"

struct boardCell {
	int x;
	int y;
};

static Fifteen *game;

void gameInit();
void drawBoard();
boardCell getBoardCellByCoord(int32, int32);