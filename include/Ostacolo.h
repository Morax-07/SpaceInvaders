#pragma once

//CLASSI
#include "Blocco.h"





//CLASSE BLOCCO
class Ostacolo
{
	//elementi privati
	private:
		std::vector<std::vector<int>> griglia_ostacolo;


	//elementi pubblici
	public:
		Vector2 posizione_ostacolo;

		std::vector<Blocco> blocchi;

		Ostacolo(Vector2 posizione_ostacolo);
		void stampaOstacolo();
};