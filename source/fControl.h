#pragma once

#include "fGameModel.h"
#include "IwNUI.h"

using namespace IwNUI;

class fControl {
	fGameModel game;

	CAppPtr app;
	CWindowPtr window;
	CViewPtr viewMenu;
	CViewPtr viewGame;

	CButtonPtr buttonStart;

	CButtonPtr gameButtons[BOARD_SIZE][BOARD_SIZE];

	int clickedX;
	int clickedY;

	void InitNUI();
	void InitMenu();
	void InitGame();

public:
	fControl();
	~fControl();

	void InitApp();

	bool onButtonStartClick();
	bool onButtonGameClick(CButton* _button);
};


