#pragma once




//CLASSE MYSTERY SHIP
class MysteryShip
{
	//elementi privati
	private:
		Texture2D texture_mystery_ship[2];
		Vector2 posizione_mystery_ship;
		int velocita;
		int tempo_mystery_ship_colpita = 0;


	//elementi pubblici
	public:
		bool mystery_ship_attiva;
		bool mystery_ship_colpita = false;

		MysteryShip();
		~MysteryShip();
		void stampaMysteryShip();
		void aggiornaMysteryShip();
		void spownaMysteryShip();
		Rectangle hitbox();
};