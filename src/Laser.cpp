//LIBRERIE
#include <iostream>
#include "raylib.h"


//CLASSI
#include "Laser.h"

using namespace std;





//METODI CLASSE LASER
//costruttore
Laser::Laser(Vector2 posizione, Color colore_laser, float velocita)
{
	this->posizione = posizione;
	this->colore_laser = colore_laser;
	this->velocita = velocita;

	laser_attivo = true;
}

//stampa il laser
void Laser::stampaLaser()
{
	if(laser_attivo)
	{
		DrawRectangle(posizione.x, posizione.y, 2, 10, colore_laser);
	}
}

//aggiorna la posizione del laser e il suo stato
void Laser::aggiornaLaser()
{
	posizione.y += velocita;

	if((posizione.y < 65 || posizione.y > GetScreenHeight() - 80) && laser_attivo)
	{
		laser_attivo = false;
	}
}

//genera hitbox laser
Rectangle Laser::hitbox()
{
	if (laser_attivo)
	{
		Rectangle rect = { posizione.x, posizione.y, 4, 10 };
		return rect;
	}
	else
	{
		Rectangle rect = { posizione.x, posizione.y, 0, 0 };
		return rect;
	}
}