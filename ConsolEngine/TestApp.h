// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
#include "Figure.h"
#include "FillArea.h"
#include <stack>

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	Figure fig_current;
	Figure fig_next;
	FillArea FillA;
	int counter = 0;
	const int DELAY = 20;
	const int ScoreSpace = 5;
	
public:
	TestApp();
	virtual void KeyPressed(int btnCode);
	virtual void RepeatF(float deltaTime);
	void Turn();
	void Draw();
	void DrawFillArea();
	void DrawFig();
	void DrawNextFig();
	void DrawScore();
	
};
