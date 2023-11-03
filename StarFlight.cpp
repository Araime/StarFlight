#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

void CreateMap(string(*map)[30], int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					map[i][j] = char(201);
				}
				else if (j < width - 1)
				{
					map[i][j] = char(205);
				}
				else if (j < width)
				{
					map[i][j] = char(187);
				}
			}
			else if (i < height - 1)
			{
				if (j == 0)
				{
					map[i][j] = char(186);
				}
				else if (j < width - 1)
				{
					map[i][j] = " ";
				}
				else if (j < width)
				{
					map[i][j] = char(186);
				}
			}
			else if (i < height)
			{
				if (j == 0)
				{
					map[i][j] = char(200);
				}
				else if (j < width - 1)
				{
					map[i][j] = char(205);
				}
				else if (j < width)
				{
					map[i][j] = char(188);
				}
			}
		}
	}
}

void PrintMapBorders(string(*map)[30], int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

void CreateStarsArr(int(*stars)[2], int stars_qty, int width)
{
	int height = -2;
	for (size_t i = 0; i < stars_qty; i++)
	{
		stars[i][0] = height;
		stars[i][1] = 1 + rand() % (width - 2);
		height -= 5;
	}
}

void CreateShipArr(int(*ship)[2], int width, int height)
{
	ship[0][0] = height - 3;
	ship[0][1] = width / 2;
	ship[1][0] = height - 2;
	ship[1][1] = width / 2;
	ship[2][0] = height - 2;
	ship[2][1] = width / 2 - 1;
	ship[3][0] = height - 2;
	ship[3][1] = width / 2 + 1;
}

// for move console cursore
void GoToXY(short x, short y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void PrintScores(int scores)
{
	cout << "Scores: " << scores << endl;
}

void PrintLives(int lives)
{
	cout << "Lives: ";
	char heart = 003;
	char dash = 249;

	switch (lives)
	{
		case 3: cout << heart << heart << heart; break;
		case 2: cout << heart << heart << dash; break;
		case 1: cout << heart << dash << dash; break;
		default: cout << dash << dash << dash; break;
	}
	cout << endl;
}

void ChangeGameSpeed(int scores, double* speed)
{
	switch (scores)
	{
		case 25: *speed = 0.1; break;
		case 50: *speed = 0.08; break;
		case 75: *speed = 0.06; break;
		case 100: *speed = 0.04; break;
	}
}

void UpdateStarsCoord(int(*stars)[2], int stars_qty)
{
	for (int i = 0; i < stars_qty; i++)
	{
		stars[i][0]++;
	}
}

void UpdateScores(int(*stars)[2], int stars_qty, int* scores, int height)
{
	for (int i = 0; i < stars_qty; i++)
	{
		if (stars[i][0] > height - 2)
		{
			*scores += 1;
		}
	}
}

void RespawnStar(int(*stars)[2], int stars_qty, int height, int width)
{
	for (int i = 0; i < stars_qty; i++)
	{
		if (stars[i][0] > height - 2)
		{
			stars[i][0] = 1;
			stars[i][1] = 1 + rand() % (width - 2);
		}
	}
}

void UpdateShipCoord(int(*ship)[2], int ship_parts, string(*map)[30], char ship_sym)
{
	for (int i = 0; i < ship_parts; ++i)
	{
		int ship_y = ship[i][0];
		int ship_x = ship[i][1];
		map[ship_y][ship_x] = ship_sym;
	}
}

void ClearOldShipCoord(int(*ship)[2], int ship_parts, string(*map)[30])
{
	for (int i = 0; i < ship_parts; ++i)
	{
		int ship_y = ship[i][0];
		int ship_x = ship[i][1];
		map[ship_y][ship_x] = ' ';
	}
}

void ClearOldStarCoord(int(*stars)[2], int stars_qty, string(*map)[30])
{
	for (int i = 0; i < stars_qty; i++)
	{
		// ignore if star over the game field
		if (stars[i][0] < 1)
		{
			continue;
		}
		else
		{
			int star_y = stars[i][0];
			int star_x = stars[i][1];
			map[star_y][star_x] = ' ';
		}
	}
}

void DrawStarsOnMap(int(*stars)[2], int stars_qty, string(*map)[30], char star_sym)
{
	for (int i = 0; i < stars_qty; i++)
	{
		// ignore if star over the game field
		if (stars[i][0] < 1)
		{
			continue;
		}
		else
		{
			int star_y = stars[i][0];
			int star_x = stars[i][1];
			map[star_y][star_x] = star_sym;
		}
	}
}

void CheckCollision(int(*stars)[2], int stars_qty, int(*ship)[2], int ship_parts, int* lives)
{
	for (int i = 0; i < stars_qty; i++)
	{
		// ignore if star over the game field
		if (stars[i][0] < 1)
		{
			continue;
		}
		else
		{
			for (int j = 0; j < ship_parts; j++)
			{
				if (stars[i][0] == ship[j][0] && stars[i][1] == ship[j][1])
				{
					*lives -= 1;
				}
			}
		}
	}
}

void CheckLives(int lives, bool* isRunning)
{
	if (lives == 0) *isRunning = false;
}

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
