//LIBRERIE
#include "raylib.h"
#include <iostream>



//CLASSI
#include "MysteryShip.h"


using namespace std;



//METODI CLASSE MYSTERY SHIP
//costruttore
MysteryShip::MysteryShip()
{
	texture_mystery_ship[0] = LoadTexture("data/sprite/mystery_ship.png");
	texture_mystery_ship[1] = LoadTexture("data/sprite/mystery_ship_sconfitta.png");

	mystery_ship_attiva = false;
	posizione_mystery_ship = {};
	velocita = 0;
}

//distruttore
MysteryShip::~MysteryShip()
{
	UnloadTexture(texture_mystery_ship[0]);
	UnloadTexture(texture_mystery_ship[1]);
}

//spowna la mystery ship
void MysteryShip::spownaMysteryShip()
{
	posizione_mystery_ship.y = 90;

	int lato_di_spown = GetRandomValue(0, 1);

	if (lato_di_spown == 0)
	{
		posizione_mystery_ship.x = -84;
		velocita = 2;
	}
	if (lato_di_spown == 1)
	{
		posizione_mystery_ship.x = GetScreenWidth();
		velocita = -2;
	}

	mystery_ship_attiva = true;
}

//aggiorna la posizione della mystery ship
void MysteryShip::aggiornaMysteryShip()
{
	if (mystery_ship_attiva && !mystery_ship_colpita)
	{
		posizione_mystery_ship.x += velocita;

		if (posizione_mystery_ship.x > GetScreenWidth() || posizione_mystery_ship.x < -84)
		{
			mystery_ship_attiva = false;
		}
	}
	else if (mystery_ship_colpita && tempo_mystery_ship_colpita <= 20)
	{
		tempo_mystery_ship_colpita++;
	}

	if (tempo_mystery_ship_colpita == 20)
	{
		mystery_ship_colpita = false;
		tempo_mystery_ship_colpita = 0;
	}
}

//stampa la mystery ship
void MysteryShip::stampaMysteryShip()
{
	if (mystery_ship_attiva)
	{
		DrawTextureV(texture_mystery_ship[0], posizione_mystery_ship, WHITE);
	}
	else if (mystery_ship_colpita)
	{
		DrawTextureV(texture_mystery_ship[1], posizione_mystery_ship, WHITE);
	}
}

//genera hitbox mystrery ship
Rectangle MysteryShip::hitbox()
{
	if (mystery_ship_attiva && !mystery_ship_colpita)
	{
		Rectangle rect = { posizione_mystery_ship.x + 5, posizione_mystery_ship.y, 79, 35 };
		return rect;
	}
	else
	{
		Rectangle rect = { posizione_mystery_ship.x + 5, posizione_mystery_ship.y - 500, 0, 0 };
		return rect;
	}
}