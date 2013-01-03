#pragma once

#include "definitions.h"
#include "fGameModel.h"
#include "s3e.h"
#include "IwGx.h"

class fGameView {
	
public:
	fGameView();
	~fGameView();

	void drawBoard();
	void drawNumbers(fGameModel *game);
};