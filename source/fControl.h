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
	CViewPtr viewOver;

	CButtonPtr buttonStart;
	CButtonPtr gameButtons[BOARD_SIZE][BOARD_SIZE];

	void InitNUI();
	void InitMenu();
	void InitGame();
	void InitOver();

	void makeMove(int, int);
	void renameButtons();

public:
	fControl();
	~fControl();

	void InitApp();

	bool onButtonStartClick();
	bool onButtonGameClick(CButton*);
};


