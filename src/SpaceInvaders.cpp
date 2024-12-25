//LIBRERIE
#include <iostream>
#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>


//CLASSI
#include "Game.h"


using namespace std;






//MAIN
int main()
{
    Color nero = { 0, 0, 0, 255 };
    Image logo = LoadImage("data/sprite/logo.png");

    //crea finestra
    InitWindow(700, 770, "Space Invaders");
    InitAudioDevice();

    SetWindowIcon(logo);
    UnloadImage(logo);

    HideCursor();

    SetTargetFPS(60);

    //oggetti
    Game game = Game();


    system("clear");

    //game loop
    while(!WindowShouldClose())
    {
        //metodi per il funzionamento del gioco
        game.controlloInput();
        game.aggiornaGioco();

        BeginDrawing();
        ClearBackground(nero);

        game.stampaGioco();
        

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();


    //chiusura finestra
    cout << "\033[31m" << "<---  ! WINDOW CLOSED !  --->\n\n";

    return 0;
}