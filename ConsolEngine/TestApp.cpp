// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include <stdlib.h>
#include <time.h>

TestApp::TestApp() : Parent(25, 25)
{
	srand(time(NULL));
	fig_current = Figure(rand() % 5, 0, 8, 1);
	fig_next = Figure(rand() % 5, 0, 8, 1);
	FillA = FillArea();

	int counter = 1000;
}

void TestApp::KeyPressed(int btnCode)
{
	Figure curr = fig_current;
	if (btnCode == 75) { //left
		curr.Move(-1, 0);
	} else if (btnCode == 77) { //right
		curr.Move(1, 0);
	} else if (btnCode == 80) { //down
		curr.SetSpeed(DELAY);
	} else if (btnCode == 32) { //space
		curr.Rotate();
	} else if (btnCode == 27) { //ESCAPE
		Parent::exit();
	}
	if (FillA.IsCollision(curr) == false) {
		fig_current = curr;
		DrawFillArea();
		DrawFig();
	}
}

void TestApp::DrawFillArea()
{
	//границы заполненной области погоризонтали
	for (int j = 0; j < FillArea::WIDTH + 10; j++) {
		SetChar(j, 0, U'Ø');
		SetChar(j, (FillArea::HEIGHT + 1), U'Ø');
	}
	//границы заполненной области по вертикали
	for (int i = 0; i < FillArea::HEIGHT + 1 + ScoreSpace; i++) {
		SetChar(0, i, U'Ø');
		SetChar((FillArea::WIDTH + 1), i, U'Ø');
	}
	//отрисовка заполненной области
	for (int i = 1; i <= FillArea::HEIGHT; i++) {
		for (int j = 1; j <= FillArea::WIDTH; j++) {
			if (FillA.GetVal(j - 1, i - 1) == true) {
				SetChar(j, i, '*');
			} else {
				SetChar(j, i, '.');
			}
		}
	}
}

void TestApp::DrawFig()
{
	int x = fig_current.GetX();
	int y = fig_current.GetY();

	//отрисовка фигуры
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fig_current.GetVal(j, i) == true) {
				SetChar(x + j, y + i, '*');
			}
		}
	}
}
void TestApp::DrawNextFig()
{
	/*//границы области подсказки следующей фигуры по горизонтали
	for (int j = FillArea::WIDTH + 2; j < FillArea::WIDTH + 10; j++) {
		SetChar(j, 0, U'Ø');
		SetChar(j, 5, U'Ø');
	}*/
	//границы области подсказки следующей фигуры по вертикали
	for (int i = 0; i < FillArea::HEIGHT + 1; i++) {
		SetChar(FillArea::WIDTH + 9, i, U'Ø');
	}
	//пустые поля области подсказки следующей фигуры
	for (int i = 1; i < FillArea::HEIGHT + 1; i++) {
		for (int j = FillArea::WIDTH + 2; j < FillArea::WIDTH + 9; j++) {
			SetChar(j, i, ' ');
		}
	}
	//отрисовка следующей фигуры
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fig_next.GetVal(j, i) == true) {
				SetChar(j + FillArea::WIDTH + 4, i + 2, '*');
			}
		}
	}

}

void TestApp::Draw()
{
	//отрисовка заполненной области
	DrawFillArea();
	//отрисовка текущей фигуры
	DrawFig();
	//отрисовка следующей фигуры
	DrawNextFig();
	//отрисовка score table
	DrawScore();
}

void TestApp::Turn()
{
	//текущую фигуру вниз
	Figure curr = fig_current;
	curr.Move(0, 1);
	//фигура столкнулась с заполненной областью
	if (FillA.IsCollision(curr) == false) {
		fig_current = curr;
	} else {
		//добавить фигуру к заполненной области
		FillA.Merge(fig_current);
		//удалить сплошные линии
		FillA.RemoveSolidLines();
		//новая фигура
		fig_current = fig_next;
		fig_next = Figure(rand() % 5, 0, 8, 1);
		//если новая фигура касается заполненной области - обновить игру
		if (FillA.IsCollision(fig_current)) {
			FillA.Repeat();
		}
	}
}

void TestApp::RepeatF(float deltaTime)
{
	//отрисовка экрана
	Draw();
	//задержка хода
	if (counter > DELAY / fig_current.GetSpeed()) {
		counter = 0;
		//ход
		Turn();
	}
	counter++;
}

void TestApp::DrawScore()
{
	std::stack<char> ScoreCh;
	int tmp = FillA.GetScore(), itr = 9;

	if (tmp){
		while (tmp > 0) {
			ScoreCh.push(tmp % 10 + '0');
			tmp /= 10;
		}
	} else {
		ScoreCh.push('0');
	}
	for (int i = 1; i < FillArea::WIDTH + 1; i++) {
		SetChar(i, FillArea::HEIGHT + ScoreSpace, U'Ø');
	}
	for (int i = 1; i < FillArea::WIDTH + 1; i++)
		SetChar(i, FillArea::HEIGHT + 3, ' ');
	SetChar(2, FillArea::HEIGHT + 3, U'˃');
	SetChar(3, FillArea::HEIGHT + 3, 'S');
	SetChar(4, FillArea::HEIGHT + 3, 'c');
	SetChar(5, FillArea::HEIGHT + 3, 'o');
	SetChar(6, FillArea::HEIGHT + 3, 'r');
	SetChar(7, FillArea::HEIGHT + 3, 'e');
	SetChar(8, FillArea::HEIGHT + 3, ':');

	while (!ScoreCh.empty()) {
		SetChar(itr++, FillArea::HEIGHT + 3, ScoreCh.top());
		ScoreCh.pop();
	}


}
