#pragma once





//CLASSE TENTACOLO
class Tentacolo
{
	//elementi privati
	private:	
		Texture2D texture_tentacolo;


	//elementi pubblici
	public:
		Vector2 posizione_tentacolo = { (float)-GetScreenWidth(), 605 };

		Tentacolo();
		~Tentacolo();
		void stampaTentacolo();
		void aggiornaTentacolo(int direzione);
		Rectangle hitbox();
};