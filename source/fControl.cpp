#include "fControl.h"

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
	table = CreateTable(CAttributes()
						.Set("name", "table")
						.Set("x1", "25%")
						.Set("width", "50%")
						.Set("x2", "25%")
						.Set("height", "100%"));
	for (int i = 0; i < BOARD_SIZE; ++i) {
		CTableItemPtr ti = CreateTableItem(CAttributes()
							 .Set("width", "100%")
							 .Set("height", "25%"));
		for (int j = 0; j < BOARD_SIZE; ++j) {
			char num[0xff];
			sprintf(num, "%d", game.getGameBoardNum(i, j));
			char x1[0xff];
			sprintf(x1, "%d%%", j*25);
			CLabelPtr label = CreateLabel(CAttributes()
								.Set("caption", num)
								.Set("width", "25%")
								.Set("x1", x1));
			ti->AddChild(label);
		}
		table->AddChild(ti);
		m_tableRows.push_back(ti);
	}
	viewGame->AddChild(table);
}

void fControl::InitApp()
{
	InitNUI();
	InitMenu();
	InitGame();
	app->Run();
}
