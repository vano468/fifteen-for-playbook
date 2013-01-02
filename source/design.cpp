#include "design.h"
#include <stdio.h>

void drawBoard() {
	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
    CIwMaterial* pMat = IW_GX_ALLOC_MATERIAL();
    IwGxSetMaterial(pMat);

	int16 sFaceWidth  = (int16)s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int16 sFaceHeight = (int16)s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	int boardCellCount = BOARD_SIZE;
	static CIwSVec2 points[BOARD_POINTS];

	int16 boardSize = sFaceHeight > sFaceWidth ? sFaceWidth : sFaceHeight;
	while (boardSize % BOARD_SIZE) --boardSize; // stupid
	int16 emptySpaceHeight = (sFaceHeight - boardSize) / 2;
	int16 emptySpaceWidth  = (sFaceWidth  - boardSize) / 2;
	int16 cellSize = boardSize / boardCellCount;

	int j = 0;
	for (int i = 0; i < boardCellCount + 1; ++i) {
		points[j].x = emptySpaceWidth;
		points[j].y = i * cellSize + emptySpaceHeight;
		points[j+1].x = emptySpaceWidth + cellSize * boardCellCount;
		points[j+1].y = points[j].y;
		j += 2;
	}
	for (int i = 0; i < boardCellCount + 1; ++i) {
		points[j].x = i * cellSize + emptySpaceWidth;
		points[j].y = emptySpaceHeight;
		points[j+1].x = points[j].x;
		points[j+1].y = emptySpaceHeight + cellSize * boardCellCount;
		j += 2;
	}

	IwGxSetVertStreamScreenSpace(points, BOARD_POINTS);
    IwGxDrawPrims(IW_GX_LINE_LIST, NULL, BOARD_POINTS);
}

void drawNumbers() {
	int16 sFaceWidth  = (int16)s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int16 sFaceHeight = (int16)s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	int boardCellCount = BOARD_SIZE;

	int16 boardSize = sFaceHeight > sFaceWidth ? sFaceWidth : sFaceHeight;
	while (boardSize % 8) --boardSize; // stupid

	int16 emptySpaceHeight = (sFaceHeight - boardSize) / 2;
	int16 emptySpaceWidth  = (sFaceWidth  - boardSize) / 2;

	int16 cellSize = boardSize / boardCellCount;
	for (int j = 0, y = emptySpaceHeight; j < BOARD_SIZE; ++j, y += cellSize)
		for (int i = 0, x = emptySpaceWidth; i < BOARD_SIZE; ++i, x += cellSize) {
			IwGxPrintSetScale(8); 
			int num = game->getGameBoardNum(i, j);
			char txt[33];
			sprintf(txt, "%d", num);
			if (num) 
				IwGxPrintString(x, y, txt);
		}
}

boardCell getBoardCellByCoord(int32 x, int32 y) {
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

void gameInit() {
	game = new Fifteen();
}

void gameKill() {
	delete game;
}