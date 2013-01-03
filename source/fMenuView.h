#pragma once

#include "s3e.h"
#include "IwGx.h"
#include "IwNUI.h"

using namespace IwNUI;

class fControl;

class fMenuView {
	fControl* parent;
public:
	fMenuView();
	~fMenuView();
	void draw();
	void setParent(fControl* _parent);

	bool onButton1Click();
};

#include "fControl.h"