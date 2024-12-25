#pragma once





//CLASSE BLOCCO
class Blocco
{
	//elementi privati
	private:
		Vector2 posizione_blocco;

	//elementi pubblici
	public:
		Blocco(Vector2 posizione_blocco);
		void stampaBlocco();
		Rectangle hitbox();
};