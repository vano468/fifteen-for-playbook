#include "fMenuView.h"
#include "IwNUI.h"
#include "fControl.h"
using namespace IwNUI;

fMenuView::fMenuView()
{

}

fMenuView::~fMenuView()
{

}

void fMenuView::draw()
{
	CButtonPtr button1 = CreateButton(CAttributes()
	.Set("name", "button1")
	.Set("caption", "Start!")
	.Set("x1", "50")
	.Set("y1", "50"));
	button1->SetEventHandler("click", this, &fMenuView::onButton1Click);

	parent->view1->AddChild(button1);
	parent->window->SetChild(parent->view1);
	parent->app->ShowWindow(parent->window);

	parent->app->Run();
}

void fMenuView::setParent( fControl* _parent )
{
	parent = _parent;
}

bool fMenuView::onButton1Click( )
{
	parent->state = STATE_GAME;
	parent->window->SetChild(parent->view2);
	return true;
}

