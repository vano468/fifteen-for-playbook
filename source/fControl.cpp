#include "fControl.h"

fControl::fControl() {

}

fControl::~fControl() {

}

void fControl::viewInit() {
	IwGxInit();
    IwGxSetColClear(0, 0, 0xff, 0xff);
}

void fControl::viewClear() {
	IwGxClear();
}

void fControl::viewFlush() {
	IwGxFlush();
	IwGxSwapBuffers();
	s3eDeviceYield(0);	
}

void fControl::viewKill() {
	IwGxTerminate();
}

boardCell fControl::getBoardCellByCoord(int32 x, int32 y) {
	int16 sFaceWidth  = (int16)s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int16 sFaceHeight = (int16)s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	int boardCellCount = BOARD_SIZE;

	int16 boardSize = sFaceHeight > sFaceWidth ? sFaceWidth : sFaceHeight;
	while (boardSize % 8) --boardSize; // stupid

	int16 emptySpaceHeight = (sFaceHeight - boardSize) / 2;
	int16 emptySpaceWidth  = (sFaceWidth  - boardSize) / 2;

	int16 tempCellHeight = y - emptySpaceHeight;
	int16 tempCellWidth  = x - emptySpaceWidth;
	int16 cellSize = boardSize / boardCellCount;

	boardCell curCell;
	curCell.x = -1; 
	curCell.y = -1;

	if (tempCellHeight < 0 || tempCellWidth <0) return curCell;

	// stupid
	for (int i = 0; i < BOARD_SIZE; ++i) {
		tempCellHeight -= cellSize;
		tempCellWidth  -= cellSize;
		if (tempCellHeight < 0 && curCell.y < 0) curCell.y = i;
		if (tempCellWidth  < 0 && curCell.x < 0) curCell.x = i;
	}

	if (curCell.x < 0 || curCell.y < 0) 
		curCell.x = curCell.y = -1;

	return curCell;
}

void fControl::drawView()
{
	if (game.getState() == STATE_MENU)
		menuView.draw();
	if (game.getState() == STATE_GAME)
		gameView.draw(&game);
}
