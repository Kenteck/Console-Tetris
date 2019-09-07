#include "FillArea.h"

FillArea::FillArea()
{
	Repeat();
}

FillArea::~FillArea(void)
{
}

void FillArea::Repeat()
{
	for (int i = 0; i < FillArea::HEIGHT; i++) {
		for (int j = 0; j < FillArea::WIDTH; j++) {
			map[i][j] = false;
		}
	}
	
	for (int i = 0; i < FillArea::WIDTH; i++) {
		map[FillArea::HEIGHT][i] = true;
	}
	score = 0;
}

bool FillArea::GetVal(int x, int y)
{
	return map[y][x];
}

bool FillArea::IsCollision(Figure& curr)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (curr.GetVal(j, i) == true) {
				int x = curr.GetX() + j - 1;
				int y = curr.GetY() + i;
				if (x < 0 || x >= FillArea::WIDTH || y < 0 || y >= FillArea::HEIGHT)
					return true;
				if (curr.GetVal(j, i) == map[y][x])
					return true;
			}
		}
	}
	return false;
}

void FillArea::Merge(Figure& curr)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (curr.GetVal(j, i) == true) {
				int x = curr.GetX() + j - 1;
				int y = curr.GetY() + i;
				if (x >= 0 || x < FillArea::WIDTH || y >= 0 || y < FillArea::HEIGHT)
					map[y][x] = map[y][x] | curr.GetVal(j, i);
			}
		}
	}
}

void FillArea::RemoveSolidLines()
{
	for (int i = 0; i < FillArea::HEIGHT; i++) {
		bool solid = true;
		for (int j = 0; j < FillArea::WIDTH; j++) {
			solid &= map[i][j];
		}
		if (solid == true) {
			RemoveSolidLine(i);
		}
	}
}

void FillArea::RemoveSolidLine(int k)
{
	//опускаем строки заполненной области
	for (int i = k - 1; i >= 0; i--) {
		for (int j = 0; j < FillArea::WIDTH; j++) {
			map[i + 1][j] = map[i][j];
		}
	}
	//очищаем первую строку заполненной области
	for (int j = 0; j < FillArea::WIDTH; j++) {
		map[0][j] = false;
	}
	
	ScoreInc();
}


void FillArea::ScoreInc()
{
	score += 100;
}

int FillArea::GetScore() 
{
	return score;
}