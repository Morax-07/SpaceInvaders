//LIBRERIE
#include "raylib.h"
#include <iostream>

//CLASSI
#include "Tentacolo.h"

using namespace std;




//METODI CLASSE TENTACOLO
//costruttore
Tentacolo::Tentacolo()
{
	texture_tentacolo = LoadTexture("data/sprite/tentacolo.png");
}

//distruttore
Tentacolo::~Tentacolo()
{
	UnloadTexture(texture_tentacolo);
}

//stampa il tentacolo
void Tentacolo::stampaTentacolo()
{
	DrawTextureV(texture_tentacolo, posizione_tentacolo, WHITE);
}

//aggiorna la posizione del tentacolo
void Tentacolo::aggiornaTentacolo(int direzione)
{
	posizione_tentacolo.x += direzione;
}

//ritorna la hitbox del tentacolo
Rectangle Tentacolo::hitbox()
{
	return { posizione_tentacolo.x, posizione_tentacolo.y, (float)texture_tentacolo.width, (float)texture_tentacolo.height };
}