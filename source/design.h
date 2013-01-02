#ifndef DESIGN_H
#define DESIGN_H

#include "definitions.h"
#include "game.h"
#include "s3e.h"
#include "IwGx.h"

struct boardCell {
	int x;
	int y;
};

static Fifteen *game;

void gameInit();
void gameKill();
void drawBoard();
void drawNumbers();
boardCell getBoardCellByCoord(int32, int32);

#endif //DESIGN_H