#pragma once

#include "fGameView.h"
#include "fGameModel.h"
#include "s3e.h"
#include "IwGx.h"

struct boardCell {
	int x;
	int y;
};

class fControl {
	fGameModel game;
	fGameView view;

public:
	fControl();
	~fControl();
	
	void viewInit();
	void viewClear();
	void viewFlush();
	void viewKill();

	void drawBoard();
	void drawNumbers();

	boardCell getBoardCellByCoord(int32, int32);
};

