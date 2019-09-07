#pragma once
class Figure
{
	int shape, speed, angle, x, y;

public:
	Figure();
	~Figure();
	Figure(int shape, int angle, int x, int y);
	void Move(int dx, int dy);
	void Rotate();
	int GetSpeed();
	void SetSpeed(int nSpeed);
	bool GetVal(int x, int y);
	int GetX();
	int GetY();
};