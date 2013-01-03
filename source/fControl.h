#pragma once

#include "fGameView.h"
#include "fGameModel.h"
#include "fMenuView.h"
#include "s3e.h"
#include "IwGx.h"

struct boardCell {
	int x;
	int y;
};

class fControl {
	fGameModel game;
	fGameView gameView;
	fMenuView menuView;
public:
	fControl();
	~fControl();
	
	void viewInit();
	void viewClear();
	void viewFlush();
	void viewKill();

	void drawView();

	boardCell getBoardCellByCoord(int32, int32);
};

