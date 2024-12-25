//LIBRERIE
#include <iostream>
#include "raylib.h"


//CLASSI
#include "Alieno.h"

using namespace std;


Texture2D Alieno::sprite_alieni[12] = {};

//METODI CLASSE ALIENO
//costruttore
Alieno::Alieno(int tipo_alieno, Vector2 posizione_alieno)
{
	this -> tipo_alieno = tipo_alieno;
	this -> posizione_alieno = posizione_alieno;

	if(sprite_alieni[tipo_alieno - 1].id == 0)
	{
		for (int i = 1; i < 13; i++)
		{
			switch (i)
			{
				case 1:
					sprite_alieni[0] = LoadTexture("data/sprite/alieno1_stato1.png");
					break;
				case 2:
					sprite_alieni[1] = LoadTexture("data/sprite/alieno2_stato1.png");
					break;
				case 3:
					sprite_alieni[2] = LoadTexture("data/sprite/alieno3_stato1.png");
					break;
				case 4:
					sprite_alieni[3] = LoadTexture("data/sprite/alieno4_stato1.png");
					break;
				case 5:
					sprite_alieni[4] = LoadTexture("data/sprite/alieno1_stato2.png");
					break;
				case 6:
					sprite_alieni[5] = LoadTexture("data/sprite/alieno2_stato2.png");
					break;
				case 7:
					sprite_alieni[6] = LoadTexture("data/sprite/alieno3_stato2.png");
					break;
				case 8:
					sprite_alieni[7] = LoadTexture("data/sprite/alieno4_stato2.png");
					break;
				case 9:
					sprite_alieni[8] = LoadTexture("data/sprite/alieno1_sconfitto.png");
					break;
				case 10:
					sprite_alieni[9] = LoadTexture("data/sprite/alieno2_sconfitto.png");
					break;
				case 11:
					sprite_alieni[10] = LoadTexture("data/sprite/alieno3_sconfitto.png");
					break;
				case 12:
					sprite_alieni[11] = LoadTexture("data/sprite/alieno4_sconfitto.png");
					break;
				default:
					break;
			}
		}
	}
}

//stampa un alieno
void Alieno::stampaAlieno()
{
	if (!stato_alieno && alieno_vivo)
	{
		DrawTextureV(sprite_alieni[tipo_alieno - 1], posizione_alieno, WHITE);
	}
	else if(stato_alieno && alieno_vivo)
	{
		DrawTextureV(sprite_alieni[tipo_alieno + 3], posizione_alieno, WHITE);
	}
	else if (!alieno_vivo)
	{
		DrawTextureV(sprite_alieni[tipo_alieno + 7], posizione_alieno, WHITE);
	}

}

//toglie le texture dalla gpu
void Alieno::unloadTextureAlieni()
{
	for (int i = 0; i < 12; i++)
	{
		UnloadTexture(sprite_alieni[i]);
	}
}

//aggiorna la posizione degli alieni
void Alieno::aggiornaAlieno(int direzione)
{
	posizione_alieno.x += direzione;
	stato_alieno = !stato_alieno;
}

//ritorna tipo alieno
int Alieno::tipoAlieno()
{
	return tipo_alieno;
}

//genera hitbox alieno
Rectangle Alieno::hitbox()
{
	if (alieno_vivo)
	{
		Rectangle rect = { posizione_alieno.x, posizione_alieno.y, 50, 50 };
		return rect;
	}
	else
	{
		Rectangle rect = { posizione_alieno.x, posizione_alieno.y, 0, 0 };
		return rect;
	}
}