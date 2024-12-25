#pragma once

//CLASSI
#include "Player.h"
#include "Ostacolo.h"
#include "Alieno.h"
#include "MysteryShip.h"
#include "Boss.h"
#include "Tentacolo.h"





//struttura cerchio per le stelle del menu
struct Cerchio
{
	Vector2 centro;
	int raggio;
};







//CLASSE GAME
class Game
{
	//elementi privati
	private:
		//attributi
		Player giocatore = Player();
		MysteryShip mystery_ship = MysteryShip();
		Boss boss = Boss();
		Tentacolo tentacolo = Tentacolo();

		Music tema_menu;
		Music tema_intro_vittoria;
		Music livelli;
		Music battaglia_boss;
		Music game_over;

		Sound alieno_ms_pl_colpiti_tentacolo;
		Sound movimento_mystery_ship;
		Sound movimento_alieno;
		Sound laser_giocatore;
		Sound esplosione_giocaotre_boss;

		std::vector<Cerchio> stelle_menu;

		std::vector<Ostacolo> ostacoli;
		float pos_ost_x = 40;

		Texture2D sfondo;
		Texture2D vite;
		Texture2D game_over_1;
		Texture2D game_over_2;
		Texture2D intro_1;
		Texture2D intro_2;
		Texture2D livello_boss;

		double tempo_laser = 0;
		double tempo_alieni = 0;
		double tempo_laser_alieni = 0;
		double tempo_spown_alieni = 0;
		double tempo_laser_boss = 0;
		double tempo_stelle = 0;

		std::vector<Alieno> alieni;

		int direzione_alieni;
		bool alieni_devono_scendere = false;
		bool alieni_scesi = false;
		int posizione_alieni_y = 215;
		int posizione_alieni_boss_x = -125;
		float velocita_sopwn_laser_alieni = 0.2;
		int discesa_alieni = 7;

		int spown_miystery_ship = 0;
		int ultimo_spown_mystery_ship = 0;
		int tempo_da_inizio_vittoria = 0;
		long int tempo_inizio_nuova_partita = 0;
		int tempo_da_fine_intro = 0;

		std::vector<Laser> laser_alieni;
		std::vector<Laser> laser_boss;

		int PV = 3;

		bool intro_in_corso = true;
		bool stato_intro = true;
		int scambio_schermo_intro = 0;

		bool pausa = false;
		bool running = true;
		bool gioco_iniziato = false;
		int frame_da_inizio_game_over = 0;
		int scambio_schermo_game_over = 0;
		bool stampa_game_over;
		bool stato_schermo_game_over = true;
		bool vittoria = false;
		bool vittoria_in_corso = false;

		int livello = 1;
		unsigned long int punteggio = 0;
		int record;

		float velocita_alieni;

		float intervallo_spown_laser_boss = 0.7;
		bool alieni_boss_fuori = true;
		int tempo_cambio_texture_boss = 0;
		bool cambio_texture_boss = false;
		bool seconda_fase_boss = false;
		int intervallo_per_recuper_vita_boss = 0;

		bool tentacolo_attivo = false;
		bool tentacolo_spownato = false;
		bool tentacolo_dentro_schermo = false;
		bool boss_sconfitto = false;

		bool fine_gioco = false;

		bool menu = true;
		float velocita = 0;


		Color bianco = { 255, 255, 255, 255 };
		Rectangle rect = { 1, 60, (float)GetScreenWidth() - 2, (float)GetScreenHeight() - 120 };

		//metodi
		//intervalli
		bool intervalloLaser(double inter);
		bool intervalloAlieni(double inter);
		bool intervalloLaserAlieni(double inter);
		bool intervalloSpownAlieni(double inter);
		bool intervalloLaserBoss(double inter);
		bool intervalloStelle(double inter);

		//despown laser
		void disattivaLaserInattivi();

		//ostacoli
		std::vector<Ostacolo> creaOstacoli();
		void stampaOstacoli();

		//alieni
		std::vector<Alieno> creaAlieni();
		void muoviAlieni();
		void muoviGiuAlieni();
		void controllaPosAlieni();
		void alienoSparaLaser();
		void cancellaAlieno();

		//boss
		void bossSparaLaser();
		std::vector<Alieno> creaAlieniBoss();

		//tentacolo boss
		void spownDespownTentacolo();

		//tutte le collisioni
		void controllaCollisioni();

		//stampa alcuni elementi
		void stampaVite();
		void stampaPunteggioLivello(int lung_testo, int testo, int pos_x, int pos_y, int font_size, int distanza);

		//reset per nuovo livello o game over
		void reset();
		void initPartita();

		//record
		void controllaRecord();
		void salvataggioRecord();
		int caricamentoRecord();

		//stelle menu
		std::vector<Cerchio> creaStelle();
		void stampaStella(Cerchio stella);
		void aggiornaStella(Cerchio* stella);
		


	//elementi pubblici
	public:
		Game();
		~Game();

		//elementi fondamentali per il gioco
		void stampaGioco();
		void aggiornaGioco();
		void controlloInput();
};