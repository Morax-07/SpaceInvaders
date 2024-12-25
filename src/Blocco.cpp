//LIBRERIE
#include <vector>
#include <iostream>
#include "raylib.h"


//CLASSI
#include "Blocco.h"

using namespace std;





//METODI CLASSE BLOCCO
//costruttore
Blocco::Blocco(Vector2 posizione_blocco)
{
	this -> posizione_blocco = posizione_blocco;
}

//stampa blocco
void Blocco::stampaBlocco()
{
	DrawRectangle(posizione_blocco.x, posizione_blocco.y, 2, 2, {171, 171, 171, 255});
}

//genera hitbox blocco
Rectangle Blocco::hitbox()
{
	Rectangle rect = {posizione_blocco.x, posizione_blocco.y, 2, 2};

	return rect;
}