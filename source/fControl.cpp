#include "fControl.h"
#include "IwGx.h"

fControl::fControl() {

}

fControl::~fControl() {

}

void fControl::InitNUI() {
	app = CreateApp();
	window = CreateWindow();
	app->AddWindow(window);
}

void fControl::InitMenu() {
	viewMenu = CreateView("canvas");
	buttonStart = CreateButton(CAttributes()
		.Set("name", "button1")
		.Set("caption", "start")
		.Set("x1", "50%")
		.Set("y1", "50%")
		.Set("width", "20%")
		.Set("height", "10%")
		.Set("alignW", "centre")
		.Set("alignH", "centre"));
	buttonStart->SetEventHandler("click", this, &fControl::onButtonStartClick);

	viewMenu->AddChild(buttonStart);
	window->SetChild(viewMenu);
	app->ShowWindow(window);
}

bool fControl::onButtonStartClick() {
	window->SetChild(viewGame);
	game.randomizeGameBoard();
	renameButtons();
	return true;
}

void fControl::InitGame() {
	viewGame = CreateView("canvas");

	for (int i = viewGame->GetNumChildren() - 1; i >= 0; ++i)
		viewGame->RemoveChild(viewGame->GetChild(i));
	
	s3eSurfaceSetInt(S3E_SURFACE_DEVICE_ORIENTATION_LOCK, S3E_SURFACE_LANDSCAPE_FIXED);

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

			CButtonPtr button = CreateButton(CAttributes()
				.Set("x1", x)
				.Set("y1", y)
				.Set("width",  cellSize)
				.Set("height", cellSize)
				.Set("caption", (CString)numChar));
			gameButtons[i][j] = button;
			button->SetEventHandler("click", this, &fControl::onButtonGameClick);
			viewGame->AddChild(button);
		}
	gameButtons[game.getEmptyY()][game.getEmptyX()]->SetAttribute("visible", false);
}

void fControl::InitApp() {
	InitNUI();
	InitMenu();
	InitGame();
	InitOver();
	app->Run();
}

bool fControl::onButtonGameClick(CButton* _button) {
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (game.getGameBoardNum(i, j)) {
				CString attr1;
				CString attr2;
				_button->GetAttribute("caption", attr1);
				gameButtons[i][j]->GetAttribute("caption", attr2);
				if (attr1 == attr2) {
					makeMove(i, j);
					if (game.isOver())
						window->SetChild(viewOver);
					return true;
				}
			}
		}
	return true;
}

void fControl::makeMove(int x, int y) {
	if (game.setMove(x, y))
		renameButtons();
}

void fControl::renameButtons() {
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j) {
			gameButtons[i][j]->SetAttribute("caption", game.getGameBoardNum(i, j));
			gameButtons[i][j]->SetAttribute("visible", true);
		}
	gameButtons[game.getEmptyY()][game.getEmptyX()]->SetAttribute("visible", false);
}

void fControl::InitOver() {
	viewOver = CreateView();
	CLabelPtr label = CreateLabel(CAttributes()
								  .Set("caption", "Congratulations!")
								  .Set("x1", "50%")
								  .Set("y1", "25%")
								  .Set("width", "25%")
								  .Set("height", "10%")
								  .Set("alignW", "centre")
								  .Set("alignH", "centre"));
	CButtonPtr button = CreateButton(CAttributes()
									.Set("name", "button1")
									.Set("caption", "start")
									.Set("x1", "50%")
									.Set("y1", "50%")
									.Set("width", "20%")
									.Set("height", "10%")
									.Set("alignW", "centre")
									.Set("alignH", "centre"));
	button->SetEventHandler("click", this, &fControl::onButtonStartClick);
	viewOver->AddChild(button);
	viewOver->AddChild(label);
}
