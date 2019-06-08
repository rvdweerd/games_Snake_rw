#include "Board.h"
#include "Colors.h"
//#include "Game.h"
#include "Graphics.h"

Board::Board(int headerpos, int headerdir)
{
	for (int i = 0; i < boardSizeX*boardSizeY; i++)
	{
		board_array[i] = 0;
	}
	snakeHead = headerpos;
	snakeDirection = headerdir;
	board_array[snakeHead] = snakeLength;
	board_array[boardSizeX*boardSizeY-1] = -1;
	initialized = true;
}

void Board::BoardUpdateReduceTail()
{
	for (int i = 0; i < boardSizeX*boardSizeY; i++)
	{
		if (board_array[i] > 0)
		{
			board_array[i]--;
		}
	}
}

void Board::BoardUpdateAdvanceHead()
{
		int next;
		if (snakeDirection == 0) { next = snakeHead + 1; }
		if (snakeDirection == 2) { next = snakeHead - 1; }
		if (snakeDirection == 1) { next = snakeHead + boardSizeX;}
		if (snakeDirection == 3) { next = snakeHead - boardSizeX; }

		if (board_array[next] > 0)
		{
			gameOver = true;
		}

		if (board_array[next] == -1)
		{
			board_array[next] = snakeLength;
			BoardGrow();
			snakeLength += growth;
			snakeHead = next;
		}
		else
		{
			board_array[next] = snakeLength;
			snakeHead = next;
		}
}

void Board::BoardGrow()
{
	for (int i = 0; i < boardSizeX*boardSizeY; i++)
	{
		if (board_array[i] > 0)
		{
			board_array[i] += growth;
		}
	}

	board_array[(boardSizeY*boardSizeY * snakeLength) % (boardSizeX*boardSizeY-snakeLength)] = -1;
}

bool Board::OutOfBounds()
{
	return
		((snakeHead + 1) %  boardSizeX == 0            && snakeDirection == 0) ||
		((snakeHead)     %  boardSizeX == 0            && snakeDirection == 2) ||
		((snakeHead)    >= (boardSizeY - 1)*boardSizeX && snakeDirection == 1) ||
		((snakeHead)     <  boardSizeX                 && snakeDirection == 3);
}

void Board::TestForBorderJump()
{
	if ((snakeHead + 1) % boardSizeX == 0 && snakeDirection == 0)
	{
		snakeHead -= boardSizeX;
	}

	if ((snakeHead) % boardSizeX == 0 && snakeDirection == 2)
	{
		snakeHead += boardSizeX;
	}

	if ((snakeHead) >= (boardSizeY - 1)*boardSizeX && snakeDirection == 1)
	{
		snakeHead -= (boardSizeY - 1)*boardSizeX;
	}

	if ((snakeHead) < boardSizeX                     && snakeDirection == 3)
	{
		snakeHead += (boardSizeY - 1)*boardSizeX;
	}
}

int Board::GetSnakeDirection()
{
	return snakeDirection;
}

void Board::SetSnakeDirection(int dir)
{
	snakeDirection = dir;
}

bool Board::IsGameOver()
{
	return gameOver;
}

bool Board::IsInitialized()
{
	return initialized;
}

void Board::SetTileColor(Color c)
{
	tile_color = c;
}

void Board::DrawBoard(Graphics& gfx)
{
	for (int i = 0; i < boardSizeY; i++)
	{
		for (int j = 0; j < boardSizeX; j++)
		{
			if (board_array[(boardSizeX )*i + j] > 0)
			{
				gfx.DrawRect(board_x0 + j * tile_size, board_y0 + i * tile_size, board_x0 + j * tile_size + tile_size, board_y0 + i * tile_size + tile_size, tile_color);
			}
			if (board_array[(boardSizeX)*i + j] == -1)
			{
				gfx.DrawRect(board_x0 + j * tile_size, board_y0 + i * tile_size, board_x0 + j * tile_size + tile_size, board_y0 + i * tile_size + tile_size, Colors::Red);
			}
			
		}
	}

	for (int i = board_x0 - 1; i < (board_x0 + boardSizeX*tile_size); i++)
	{
		gfx.PutPixel(i, board_y0 - 1                                   , Colors::Red);
		gfx.PutPixel(i, board_y0 + boardSizeY*tile_size- 1             , Colors::Red);
	}

	for (int j = board_y0 - 1; j < (board_y0 + boardSizeY * tile_size); j++)
	{
		gfx.PutPixel(board_x0-1, j, Colors::Red);
		gfx.PutPixel(board_x0-1+boardSizeX*tile_size, j, Colors::Red);	
	}
	
}
