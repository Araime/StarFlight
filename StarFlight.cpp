#include <iostream>
#include <time.h>
#include <Windows.h>
#include "game_functions.h"

using namespace std;

int main()
{
	srand(time(NULL));
	// create map
	const int WIDTH = 30;
	const int HEIGHT = 20;
	string map[HEIGHT][WIDTH];
	CreateMap(map, HEIGHT, WIDTH);

	// add arrow to variable as enum
	enum Direction { LEFT, RIGHT, STOP };
	Direction dir = STOP;

	// create stars
	char star_sym = '*';
	const int STARS_QTY = 5;
	const int STARS_COORD = 2;
	int stars[STARS_QTY][STARS_COORD];
	CreateStarsArr(stars, STARS_QTY, WIDTH);

	// creat ship
	char ship_sym = 'O';
	int lives = 3;
	const int SHIP_PARTS = 4;
	const int SHIP_PART_COORD = 2;
	int ship[SHIP_PARTS][SHIP_PART_COORD];
	CreateShipArr(ship, WIDTH, HEIGHT);

	// detect the current time
	double time = clock();
	double speed = 0.2;

	// game variables
	bool isRunning = true;
	int scores = 0;

	// game cycle
	while (isRunning)
	{
		// checking the left key
		if (GetKeyState('A') & 0x8000)
		{
			// checking that the ship does not rest on the left edge
			if (ship[2][1] > 1)
			{
				dir = LEFT;
			}
		}
		// checking the right key
		if (GetKeyState('D') & 0x8000)
		{
			// checking that the ship does not rest on the right edge
			if (ship[3][1] < WIDTH - 2)
			{
				dir = RIGHT;
			}
		}
		// quit game
		if (GetKeyState('Q') & 0x8000)
		{
			isRunning = false;
		}

		// checking the elapsed time and executing
		if ((clock() - time) / CLOCKS_PER_SEC >= speed)
		{
			time = clock();

			// make an offset to the left
			if (dir == LEFT)
			{
				for (int i = 0; i < SHIP_PARTS; i++)
				{
					--ship[i][1];
				}
				dir = STOP;
			}
			// make an offset to the right
			if (dir == RIGHT)
			{
				for (int i = 0; i < SHIP_PARTS; i++)
				{
					++ship[i][1];
				}
				dir = STOP;
			}
			// update star coord
			UpdateStarsCoord(stars, STARS_QTY);

			// update scores
			UpdateScores(stars, STARS_QTY, &scores, HEIGHT);

			// respawn star
			RespawnStar(stars, STARS_QTY, HEIGHT, WIDTH);

			// update ship coord
			UpdateShipCoord(ship, SHIP_PARTS, map, ship_sym);

			//draw stars
			DrawStarsOnMap(stars, STARS_QTY, map, star_sym);

			// check collision
			CheckCollision(stars, STARS_QTY, ship, SHIP_PARTS, &lives);

			// print game from left corner
			GoToXY(0, 0);

			// draw scores and lives
			PrintScores(scores);
			PrintLives(lives);

			// draw all map with ship, star, etc...
			PrintMapBorders(map, HEIGHT, WIDTH);

			// clearing old star coordinates
			ClearOldStarCoord(stars, STARS_QTY, map);

			// clearing old ship coordinates
			ClearOldShipCoord(ship, SHIP_PARTS, map);

			// change game speed
			ChangeGameSpeed(scores, &speed);
		}

		// check game over
		CheckLives(lives, &isRunning);
	}

	// end game
	GoToXY(1, HEIGHT / 2);
	cout << "\tGAME OVER" << endl;
	GoToXY(WIDTH, HEIGHT);

	return 0;
}
