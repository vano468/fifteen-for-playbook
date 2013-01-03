#pragma once

#include "definitions.h"
#include "fGameModel.h"
#include "s3e.h"
#include "IwGx.h"

class fGameView {
	void drawBoard();
	void drawNumbers(fGameModel *game);
public:
	fGameView();
	~fGameView();

	void draw(fGameModel *game);
};