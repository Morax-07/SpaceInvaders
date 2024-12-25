#pragma once





//CLASSE LASER
class Laser
{
	//elementi privati
	private:
		Vector2 posizione;
		Color colore_laser;
		int velocita;


	//elementi pubblici
	public:
		bool laser_attivo = true;

		Laser(Vector2 posizione, Color colore_laser, float velocita);
		void stampaLaser();
		void aggiornaLaser();
		Rectangle hitbox();
};