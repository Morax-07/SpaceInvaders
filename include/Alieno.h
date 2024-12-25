#pragma once




//CLASSE ALIENO
class Alieno
{
	//Elementi privati
	private:
		int tipo_alieno;


	//Elementi pubblici
	public:
		Vector2 posizione_alieno;
		static Texture2D sprite_alieni[12];
		bool alieno_vivo = true;

		bool stato_alieno = false;

		Alieno(int tipo_alieno, Vector2 posizione_alieno);
		void stampaAlieno();
		void aggiornaAlieno(int direzione);
		int tipoAlieno();
		static void unloadTextureAlieni();
		Rectangle hitbox();
};