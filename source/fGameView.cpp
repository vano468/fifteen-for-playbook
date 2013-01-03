#include "fGameView.h"
#include <stdio.h>

fGameView::fGameView() {

}

fGameView::~fGameView() {

}

void fGameView::drawBoard() {
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

void fGameView::drawNumbers(fGameModel *game) {
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
			char txt[2];
			sprintf(txt, "%d", num);
			if (num) 
				IwGxPrintString(x, y, txt);
		}
}

void fGameView::draw( fGameModel *game )
{
	drawBoard();
	drawNumbers(game);
}



