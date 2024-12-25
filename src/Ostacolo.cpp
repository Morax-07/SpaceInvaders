//LIBRERIE
#include <vector>
#include <iostream>
#include "raylib.h"


//CLASSI
#include "Ostacolo.h"

using namespace std;





//METODI CLASSE OSTACOLO
Ostacolo::Ostacolo(Vector2 posizione_ostacolo)
{
	this->posizione_ostacolo = posizione_ostacolo;

	griglia_ostacolo = {
		{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
	};

	for(int riga = 0; riga < griglia_ostacolo.size(); riga++)
	{
		for (int colonna = 0; colonna < griglia_ostacolo[0].size(); colonna++)
		{
			if(griglia_ostacolo[riga][colonna] == 1)
			{
				float pos_x = posizione_ostacolo.x + colonna * 2;
				float pos_y = posizione_ostacolo.y + riga * 2;

				Blocco blocco = Blocco({ pos_x, pos_y });
				blocchi.push_back(blocco);
			}
		}
	}
}

//disegna ostacolo
void Ostacolo::stampaOstacolo()
{
	for(auto& blocco : blocchi)
	{
		blocco.stampaBlocco();
	}
}