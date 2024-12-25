#pragma once

//CLASSI
#include "Laser.h"





//CLASSE PLAYER
class Player
{
	//elementi privati
	private:
		Vector2 posizione_player = {(float)((GetScreenWidth() / 2) - 15), (float)(GetScreenHeight() - 105)};
		

	//elementi pubblici
	public:
		Texture2D player[6] = {};

		std::vector<Laser> lasers;

		Player();
		~Player();
		void stampaPlayer(int tex);
		void aggiornaPosizione(float direzione);
		void collisioneBordi();
		void sparaLaser();
		Rectangle hitbox();
		void reset();
};