//LIBRERIE
#include <iostream>
#include "raylib.h"
#include <vector>


//CLASSI
#include "Player.h"

using namespace std;





//METODI CLASSE PLAYER
//costruttore
Player::Player()
{
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
			case 0:
				player[i] = LoadTexture("data/sprite/player0.png");
				break;
			case 1:
				player[i] = LoadTexture("data/sprite/player1.png");
				break;
			case 2:
				player[i] = LoadTexture("data/sprite/player2.png");
				break;
			case 3:
				player[i] = LoadTexture("data/sprite/player3.png");
				break;
			case 4:
				player[i] = LoadTexture("data/sprite/player4.png");
				break;
			case 5:
				player[i] = LoadTexture("data/sprite/player5.png");
			default:
				break;
		}
	}
}

//distruttore
Player::~Player()
{
	for (int i = 0; i < 6; i++)
	{
		UnloadTexture(player[i]);
	}
}

//stampa il giocatore
void Player::stampaPlayer(int tex)
{
	DrawTexture(player[tex], posizione_player.x, posizione_player.y, WHITE);
}

//aggiornamento della posizione del giocatore
void Player::aggiornaPosizione(float direzione)
{
	posizione_player.x += direzione;
}

//controllo della collisione con i bordi del player 
void Player::collisioneBordi()
{
	if(posizione_player.x > GetScreenWidth() - 40)
	{
		posizione_player.x = GetScreenWidth() - 40;
	}

	if(posizione_player.x < 10)
	{
		posizione_player.x = 10;
	}
}

//spara laser
void Player::sparaLaser()
{
	lasers.push_back(Laser({posizione_player.x + 15, posizione_player.y - 15}, { 200, 255, 32, 255 }, -5));
}

//genera hitbox player
Rectangle Player::hitbox()
{
	Rectangle rect = { posizione_player.x, posizione_player.y, 30, 15 };

	return rect;
}

void Player::reset()
{
	posizione_player = { (float)((GetScreenWidth() / 2) - 15), (float)(GetScreenHeight() - 105) };
}