#pragma once




//CLASSE BOSS
class Boss
{
	//elementi privati
	private:
		Vector2 posizione_boss;


	//elementi pubblici
	public:
		Texture2D texture_boss[6] = {};

		bool boss_vivo = false;
		int vita_boss = 100;

		Boss();
		~Boss();
		void stampaBoss(Texture2D texture);
		Rectangle hitbox();
};