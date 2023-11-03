#pragma once

using namespace std;

void CreateMap(string(*map)[30], int height, int width);

void PrintMapBorders(string(*map)[30], int height, int width);

void CreateStarsArr(int(*stars)[2], int stars_qty, int width);

void CreateShipArr(int(*ship)[2], int width, int height);

void GoToXY(short x, short y);

void PrintScores(int scores);

void PrintLives(int lives);

void ChangeGameSpeed(int scores, double* speed);

void UpdateStarsCoord(int(*stars)[2], int stars_qty);

void UpdateScores(int(*stars)[2], int stars_qty, int* scores, int height);

void RespawnStar(int(*stars)[2], int stars_qty, int height, int width);

void UpdateShipCoord(int(*ship)[2], int ship_parts, string(*map)[30], char ship_sym);

void ClearOldShipCoord(int(*ship)[2], int ship_parts, string(*map)[30]);

void ClearOldStarCoord(int(*stars)[2], int stars_qty, string(*map)[30]);

void DrawStarsOnMap(int(*stars)[2], int stars_qty, string(*map)[30], char star_sym);

void CheckCollision(int(*stars)[2], int stars_qty, int(*ship)[2], int ship_parts, int* lives);

void CheckLives(int lives, bool* isRunning);
