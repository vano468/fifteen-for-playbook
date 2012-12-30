#include "s3e.h"
#include "IwGx.h"

#include "definitions.h"

struct boardCell {
	int x;
	int y;
};

void drawBoard();
boardCell getBoardCellByCoord(int32, int32);