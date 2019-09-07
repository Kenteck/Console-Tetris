#pragma once
#include "Figure.h"

class FillArea
{
public:
	static const int HEIGHT = 20;
	static const int WIDTH = 15;

	FillArea();
	~FillArea();
	bool GetVal(int x, int y);
	bool IsCollision(Figure& curr);
	void Merge(Figure& t);
	void RemoveSolidLines();
	void RemoveSolidLine(int k);
	void Repeat();
	///////////////////////////////
	void ScoreInc();
	int GetScore();
private:
	bool map[HEIGHT + 2][WIDTH];
	int score = 0;
};