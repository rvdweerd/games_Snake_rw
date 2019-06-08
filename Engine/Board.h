#pragma once
#include "Colors.h"
//#include "Game.h"
#include "Graphics.h"

class Board
{
public:
	Board(int headerpos, int headerdir);
	void DrawBoard(Graphics &gfx);
	void BoardUpdateReduceTail();
	void BoardUpdateAdvanceHead();
	void BoardGrow();
	bool OutOfBounds(); 
	void TestForBorderJump();
	bool IsGameOver();
	bool IsInitialized();
	int  GetSnakeDirection();
	void SetSnakeDirection(int dir);
	void SetTileColor(Color c);

private:
	int snakeHead;
	int snakeDirection;
	int snakeLength = 2;
	Color tile_color = Colors::White;
	
	static constexpr int board_x0 = 5;
	static constexpr int board_y0 = 5;
	static constexpr int growth = 100;
	static constexpr int tile_size = 7;
	static constexpr int boardSizeX = 1340/7;
	static constexpr int boardSizeY = 690/7;
	
	int board_array[boardSizeX * boardSizeY];
	bool initialized = false;
	bool gameOver = false;
};