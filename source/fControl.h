#pragma once

#include "fGameModel.h"
#include "IwNUI.h"
#include <vector>

using namespace IwNUI;

class fControl {
	fGameModel game;

	CAppPtr app;
	CWindowPtr window;
	CViewPtr viewMenu;
	CViewPtr viewGame;

	CButtonPtr buttonStart;

	void InitNUI();
	void InitMenu();
	void InitGame();

public:
	fControl();
	~fControl();

	void InitApp();

	bool onButtonStartClick();
};


