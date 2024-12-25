//LIBRERIE
#include "raylib.h"
#include <iostream>

//CLASSI
#include "Boss.h"

using namespace std;



//METODI CLASSE BOSS
//costruttore
Boss::Boss()
{
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
			case 0:
				texture_boss[i] = LoadTexture("data/sprite/boss_stato1.png");
				break;
			case 1:
				texture_boss[i] = LoadTexture("data/sprite/boss_stato2.png");
				break;
			case 2:
				texture_boss[i] = LoadTexture("data/sprite/boss_stato1_fase2.png");
				break;
			case 3:
				texture_boss[i] = LoadTexture("data/sprite/boss_stato2_fase2.png");
				break;
			case 4:
				texture_boss[i] = LoadTexture("data/sprite/boss_sconfitto1.png");
				break;
			case 5:
				texture_boss[i] = LoadTexture("data/sprite/boss_sconfitto2.png");
				break;
			default:
				break;
		}
	}

	posizione_boss = { (((float)GetScreenWidth() / 2) - ((float)texture_boss[0].width / 2)), 60};
}

//distruttore
Boss::~Boss()
{
	for (int i = 0; i < 6; i++)
	{
		UnloadTexture(texture_boss[i]);
	}
}

//stampa il boss
void Boss::stampaBoss(Texture2D texture)
{
	DrawTextureV(texture, posizione_boss, WHITE);

	DrawRectangleLines(GetScreenWidth() - 32, 200, 24, 204, WHITE);
	DrawRectangle(GetScreenWidth() - 30, 202 + ((100 - vita_boss) * 2), 20, vita_boss * 2, { 255, 0, 0, 150 });
}

//genera hitbox boss
Rectangle Boss::hitbox()
{
	if (boss_vivo)
	{
		Rectangle rect = { posizione_boss.x - 5, posizione_boss.y, texture_boss[0].width + 5, texture_boss[0].height - 20 };
		return rect;
	}
	else
	{
		Rectangle rect = { posizione_boss.x - 5, posizione_boss.y, 0, 0};
		return rect;
	}
}