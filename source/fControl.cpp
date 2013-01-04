#include "fControl.h"
#include "IwGx.h"

fControl::fControl() {

}

fControl::~fControl() {

}

void fControl::InitNUI()
{
	app = CreateApp();
	window = CreateWindow();
	app->AddWindow(window);
	viewMenu = CreateView("canvas");
	viewGame = CreateView("canvas");
}

void fControl::InitMenu()
{
	buttonStart = CreateButton(CAttributes()
		.Set("name", "button1")
		.Set("caption", "Start!")
		.Set("x1", "50")
		.Set("y1", "50"));
	buttonStart->SetEventHandler("click", this, &fControl::onButtonStartClick);

	viewMenu->AddChild(buttonStart);
	window->SetChild(viewMenu);
	app->ShowWindow(window);
}

bool fControl::onButtonStartClick( )
{
	window->SetChild(viewGame);
	return true;
}

void fControl::InitGame()
{
	for (int i = viewGame->GetNumChildren() - 1; i >= 0; ++i)
		viewGame->RemoveChild(viewGame->GetChild(i));
	
	int sFaceWidth  = (int)s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int sFaceHeight = (int)s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	int boardSize = sFaceHeight > sFaceWidth ? sFaceWidth : sFaceHeight;
	while (boardSize % 8) --boardSize; // stupid

	int emptySpaceHeight = (sFaceHeight - boardSize) / 2;
	int emptySpaceWidth  = (sFaceWidth  - boardSize) / 2;

	int cellSize = boardSize / BOARD_SIZE;

	for (int j = 0, y = emptySpaceHeight; j < BOARD_SIZE; ++j, y += cellSize)
		for (int i = 0, x = emptySpaceWidth; i < BOARD_SIZE; ++i, x += cellSize) {
			int  numInt = game.getGameBoardNum(i, j);
			char numChar[0xff];
			sprintf(numChar, "%d", numInt);
			if (numInt) {
				CButtonPtr button = CreateButton(CAttributes()
											 	 .Set("x1", x)
												 .Set("y1", y)
												 .Set("width",  cellSize)
												 .Set("height", cellSize)
												 .Set("caption", numChar));
				gameButtons[i][j] = button;
				button->SetEventHandler("click", this, &fControl::onButtonGameClick);
				viewGame->AddChild(button);
			} 
		}
}

void fControl::InitApp()
{
	InitNUI();
	InitMenu();
	InitGame();
	app->Run();
}

bool fControl::onButtonGameClick(CButton* _button)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (game.getGameBoardNum(i, j)) {
				CString attr1;
				CString attr2;
				_button->GetAttribute("caption", attr1);
				gameButtons[i][j]->GetAttribute("caption", attr2);
				if (attr1 == attr2) {
					clickedX = i;
					clickedY = j;
					return true;
				}
			}
		}
	return true;
}
