#pragma once

#include "fGameView.h"
#include "fGameModel.h"
#include "fMenuView.h"
#include "s3e.h"
#include "IwGx.h"
#include "IwNUI.h"

using namespace IwNUI;

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

	CAppPtr app;
	CWindowPtr window;
	CViewPtr view1;
	CViewPtr view2;

	int state;

	boardCell getBoardCellByCoord(int32, int32);

};


