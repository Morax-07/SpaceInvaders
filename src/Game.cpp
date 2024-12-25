//LIBRERIE
#include <iostream>
#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>


//CLASSI
#include "Game.h"

using namespace std;





//METODI CLASSE GAME
//costruttore
Game::Game()
{
    ostacoli = creaOstacoli();

	sfondo = LoadTexture("data/sprite/sfondo.png");
    vite = LoadTexture("data/sprite/vite.png");
    game_over_1 = LoadTexture("data/sprite/game_over_1.png");
    game_over_2 = LoadTexture("data/sprite/game_over_2.png");
    intro_1 = LoadTexture("data/sprite/schermo_intro_1.png");
    intro_2 = LoadTexture("data/sprite/schermo_intro_2.png");
    livello_boss = LoadTexture("data/sprite/livello10.png");

    tema_menu = LoadMusicStream("data/suoni/tema_menu.mp3");
    tema_intro_vittoria = LoadMusicStream("data/suoni/intro-vittoria.mp3");
    livelli = LoadMusicStream("data/suoni/livelli.mp3");
    battaglia_boss = LoadMusicStream("data/suoni/boss.mp3");
    game_over = LoadMusicStream("data/suoni/game_over.mp3");
    movimento_mystery_ship = LoadSound("data/suoni/movimento_mystery_ship.wav");
    alieno_ms_pl_colpiti_tentacolo = LoadSound("data/suoni/alieno_ms_pl_colpiti_tentacolo.mp3");
    laser_giocatore = LoadSound("data/suoni/laser.mp3");
    esplosione_giocaotre_boss = LoadSound("data/suoni/esplosione_giocatore_boss.wav");
    movimento_alieno = LoadSound("data/suoni/movimento_alieni.mp3");


    stelle_menu = creaStelle();

    alieni = creaAlieni();

    spown_miystery_ship = GetRandomValue(35, 50);

    direzione_alieni = 10;

    record = caricamentoRecord();

    switch (livello)
    {
        case 1:
            velocita_alieni = 0.45;
            break;
        default:
            livello = 1;
            velocita_alieni = 0.45;
            break;
    }
}

//distruttore
Game::~Game()
{
    cout << "\033[33m" << "UNLOADING TEXTURES AND SOUNDS\n";
    cout << "\033[0m";
    UnloadTexture(sfondo);
    UnloadTexture(vite);
    UnloadTexture(game_over_1);
    UnloadTexture(game_over_2);
    UnloadTexture(intro_1);
    UnloadTexture(intro_2);
    UnloadTexture(livello_boss);

    UnloadMusicStream(tema_menu);
    UnloadMusicStream(tema_intro_vittoria);
    UnloadMusicStream(livelli);
    UnloadMusicStream(battaglia_boss);
    UnloadMusicStream(game_over);
    UnloadSound(movimento_mystery_ship);
    UnloadSound(alieno_ms_pl_colpiti_tentacolo);
    UnloadSound(laser_giocatore);
    UnloadSound(esplosione_giocaotre_boss);
    UnloadSound(movimento_alieno);

    salvataggioRecord();

    Alieno::unloadTextureAlieni();
}

//stampa tutti gli elementi e le grafiche
void Game::stampaGioco()
{

    //stampa menu
    if (menu)
    {
        if(!IsMusicStreamPlaying(tema_menu))
            PlayMusicStream(tema_menu);

        UpdateMusicStream(tema_menu);

        for (auto& stella : stelle_menu)
        {
            stampaStella(stella);
        }

        DrawRectangle(0, 60, GetScreenWidth(), GetScreenHeight() - 120, { 0, 0, 0, 180 });
        DrawRectangleLines(1, 59, GetScreenWidth() - 1, GetScreenHeight() - 120, bianco);
        DrawText("SPACE INVADERS", (GetScreenWidth() / 2) - (MeasureText("SPACE INVADERS", 60) / 2), 300, 60, bianco);
        DrawRectangleLines((GetScreenWidth() / 2) - (MeasureText("SPACE INVADERS", 60) / 2) - 10, 290, MeasureText("SPACE INVADERS", 60) + 20, 115, bianco);
        DrawText("PRESS ENTER", (GetScreenWidth() / 2) - (MeasureText("PRESS ENTER", 20) / 2), 375, 20, bianco);
    }

    //stampa l'intro
    if (intro_in_corso && !menu)
    {
        if(!IsMusicStreamPlaying(tema_intro_vittoria))
            PlayMusicStream(tema_intro_vittoria);

        UpdateMusicStream(tema_intro_vittoria);

        scambio_schermo_intro++;

        if (scambio_schermo_intro == 50)
        {
            stato_intro = !stato_intro;
            scambio_schermo_intro = 0;
        }

        DrawText("Space Invaders", 10, 10, 40, bianco);

        if (stato_intro)
        {
            DrawTexture(intro_1, 0, 60, WHITE);
        }
        else
        {
            DrawTexture(intro_2, 0, 60, WHITE);
        }

        DrawRectangleLines(1, 59, GetScreenWidth() - 1, GetScreenHeight() - 120, bianco);
        
        if (livello > 1)
        {
            DrawText("It's them again...", 50, 550, 20, bianco);
        }
        else
        {
            DrawText("It's them...", 50, 550, 20, bianco);
        }

        DrawText("They are coming, you must save the Earth!", 50, 580, 20, bianco);
        DrawText("Press Enter [enter] to start...", 10, GetScreenHeight() - 50, 15, bianco);
    }

    //stampa il gioco
    if (!stampa_game_over && !intro_in_corso && !vittoria && !menu)
    {
        //stampa lo sfondo
        DrawTexture(sfondo, 0, 60, WHITE);

        //stampa le vite
        stampaVite();
        
        if (livello < 10)
        {
            //stampa player
            if (running || (!running && frame_da_inizio_game_over < 120))
            {
                giocatore.stampaPlayer(PV);
            }
            else if (!running && frame_da_inizio_game_over >= 120 && frame_da_inizio_game_over < 150)
            {
                giocatore.stampaPlayer(4);
            }
            else if (!running && frame_da_inizio_game_over >= 150)
            {
                if (!IsSoundPlaying(esplosione_giocaotre_boss) && frame_da_inizio_game_over <= 160)
                {
                    PlaySound(esplosione_giocaotre_boss);
                }

                giocatore.stampaPlayer(5);
            }

            //stampa tutti gli ostacoli
            stampaOstacoli();

            //stampa tutti i laser del giocatore
            for (auto& laser : giocatore.lasers)
            {
                laser.stampaLaser();
            }

            //spara tutti gli alieni
            for (auto& alieno : alieni)
            {
                alieno.stampaAlieno();
            }

            //stampa tutti i laser sparati dagli alieni
            for (auto& laser : laser_alieni)
            {
                laser.stampaLaser();
            }

            //stampa la mystery ship
            mystery_ship.stampaMysteryShip();

            //stampa il livello
            stampaPunteggioLivello(2, livello, GetScreenWidth() - 35, 30, 20, 15);
        }

        //livello del boss
        else
        {
            //stampa livello 10
            DrawTexture(livello_boss, GetScreenWidth() - 30, 30, WHITE);

            //stampa player
            if (running || (!running && frame_da_inizio_game_over < 120))
            {
                giocatore.stampaPlayer(PV);
            }
            else if (!running && frame_da_inizio_game_over >= 120 && frame_da_inizio_game_over < 150)
            {
                giocatore.stampaPlayer(4);
            }
            else if (!running && frame_da_inizio_game_over >= 150)
            {
                if (!IsSoundPlaying(esplosione_giocaotre_boss) && frame_da_inizio_game_over <= 160)
                {
                    PlaySound(esplosione_giocaotre_boss);
                }

                giocatore.stampaPlayer(5);
            }

            if (boss.boss_vivo)
            {
                //stampa i laser del giocatore
                for (auto& laser : giocatore.lasers)
                {
                    laser.stampaLaser();
                }

                //stampa i laser del boss
                for (auto& laser : laser_boss)
                {
                    laser.stampaLaser();
                }

                //stampa gli alieni del boss
                if (alieni.size() != 0)
                {
                    for (auto& alieno : alieni)
                    {
                        alieno.stampaAlieno();
                    }
                }

                //stampa i laser degli alieni
                for (auto& laser : laser_alieni)
                {
                    laser.stampaLaser();
                }
            }

            //stampa il boss
            if (boss.boss_vivo)
            {
                tempo_cambio_texture_boss++;

                if (tempo_cambio_texture_boss / 60 == 1 && !cambio_texture_boss)
                {
                    tempo_cambio_texture_boss = 0;
                    cambio_texture_boss = true;
                }
                else if (tempo_cambio_texture_boss / 60 == 1 && cambio_texture_boss)
                {
                    tempo_cambio_texture_boss = 0;
                    cambio_texture_boss = false;
                }
                
                if (!seconda_fase_boss)
                {
                    if (pausa)
                    {
                        boss.stampaBoss(boss.texture_boss[0]);
                    }
                    else if (cambio_texture_boss)
                    {
                        boss.stampaBoss(boss.texture_boss[0]);
                    }
                    else if (!cambio_texture_boss)
                    {
                        boss.stampaBoss(boss.texture_boss[1]);
                    }
                }
                else
                {
                    if (pausa)
                    {
                        boss.stampaBoss(boss.texture_boss[2]);
                    }
                    else if (cambio_texture_boss)
                    {
                        boss.stampaBoss(boss.texture_boss[2]);
                    }
                    else if (!cambio_texture_boss)
                    {
                        boss.stampaBoss(boss.texture_boss[3]);
                    }
                }
            }
            else
            {
                tempo_cambio_texture_boss++;

                if (tempo_cambio_texture_boss <= 240)
                {
                    boss.stampaBoss(boss.texture_boss[3]);
                }
                else if (tempo_cambio_texture_boss > 240 && tempo_cambio_texture_boss <= 300)
                {
                    boss.stampaBoss(boss.texture_boss[4]);
                }
                else if (tempo_cambio_texture_boss > 300 && tempo_cambio_texture_boss <= 330)
                {
                    if (!IsSoundPlaying(esplosione_giocaotre_boss))
                    {
                        PlaySound(esplosione_giocaotre_boss);
                    }

                    boss.stampaBoss(boss.texture_boss[5]);
                    punteggio += 1500;
                }
                else if (tempo_cambio_texture_boss > 330 && tempo_cambio_texture_boss <= 400)
                {

                }
                else if (tempo_cambio_texture_boss > 400)
                {
                    fine_gioco = true;
                    vittoria = true;
                }
            }

            if (boss.boss_vivo)
            {
                //stampa gli ostacoli
                stampaOstacoli();

                //stampa il tentacolo
                if (tentacolo_attivo)
                {
                    tentacolo.stampaTentacolo();
                }
            }
        }

        //grafica
        DrawText("Space Invaders", 10, 10, 40, bianco);
        DrawText("Level: ", GetScreenWidth() - 100, 30, 20, bianco);
        DrawText("Record: ", GetScreenWidth() - 425, GetScreenHeight() - 50, 20, bianco);
        stampaPunteggioLivello(6, record, GetScreenWidth() - 345, GetScreenHeight() - 50, 20, 13);
        DrawText("Score: ", GetScreenWidth() - 200, GetScreenHeight() - 50, 20, bianco);
        stampaPunteggioLivello(6, punteggio, GetScreenWidth() - 120, GetScreenHeight() - 50, 20, 13);
        DrawRectangleRoundedLines(rect, 0.1, 10, bianco);
        DrawLine(1, 85, 0, GetScreenHeight() - 85, bianco);
        DrawLine(GetScreenWidth(), 85, GetScreenWidth(), GetScreenHeight() - 85, bianco);
    }

    //stampa il game over
    else if(stampa_game_over && !vittoria && !menu && !pausa)
    {
        if(!IsMusicStreamPlaying(game_over))
            PlayMusicStream(game_over);

        UpdateMusicStream(game_over);

        if (scambio_schermo_game_over == 45)
        {
            scambio_schermo_game_over = 0;
            stato_schermo_game_over = !stato_schermo_game_over;
        }

        //stampa lo sfondo del game over
        if (stato_schermo_game_over)
        {
            DrawTexture(game_over_1, 0, 60, WHITE);
        }
        else
        {
            DrawTexture(game_over_2, 0, 60, WHITE);
        }

        //grafica
        DrawText("GAME OVER", 10, 10, 40, bianco);
        DrawRectangleLines(1, 59, GetScreenWidth() - 1, GetScreenHeight() - 120, bianco);
        DrawText("Record: ", GetScreenWidth() - 200, GetScreenHeight() - 50, 20, bianco);
        stampaPunteggioLivello(6, punteggio, GetScreenWidth() - 120, GetScreenHeight() - 50, 20, 13);
        DrawText("You lost...", 50, 550, 20, bianco);
        DrawText("They will now rule the Earth...", 50, 580, 20, bianco);
        DrawText("Try again - [R]", 10, GetScreenHeight() - 50, 15, bianco);
        DrawText("Save and Exit - [esc]", 10, GetScreenHeight() - 25, 15, bianco);
    }

    //stampa la vittoria
    else if (vittoria && !menu && !pausa)
    {
        if(!IsMusicStreamPlaying(tema_intro_vittoria))
            PlayMusicStream(tema_intro_vittoria);

        UpdateMusicStream(tema_intro_vittoria);

        //grafica
        DrawText("YOU WON", 10, 10, 40, bianco);
        DrawTexture(sfondo, 0, 60, WHITE);
        DrawRectangle(0, GetScreenHeight() - 300, 400, 240, { 0, 0, 0, 255 });
        DrawRectangleLines(1, 59, GetScreenWidth() - 1, GetScreenHeight() - 120, bianco);

        if (!fine_gioco)
        {
            DrawText("They are gone...", 50, 550, 20, bianco);
            DrawText("But they might come back...", 50, 580, 20, bianco);
        }
        else
        {
            DrawText("They are gone...", 50, 550, 20, bianco);
            DrawText("You did it, you saved the Earth!", 50, 580, 20, bianco);
        }

        DrawText("Continue... - [enter]", 10, GetScreenHeight() - 50, 15, bianco);
        DrawText("Save and Exit - [esc]", 10, GetScreenHeight() - 25, 15, bianco);
    }

    //mette in pausa il gioco
    if (pausa)
    {
        DrawText("Pause ||", (GetScreenWidth() / 2) - 29, 70, 15, WHITE);
    }
}

//aggiorna il gioco
void Game::aggiornaGioco()
{
    //aggiorna le stelle del menu
    if (menu)
    {
        if (intervalloStelle(0.5))
        {
            for (auto& stella : stelle_menu)
            {
                aggiornaStella(&stella);
            }
        }
    }
    else
    {
        //attivazione della vittoria
        if (alieni.size() == 0 && livello < 10)
        {
            tempo_da_inizio_vittoria++;
            vittoria_in_corso = true;

            if (tempo_da_inizio_vittoria == 300)
            {
                vittoria = true;
            }
        }

        //intervallo tra stampa del gioco dopo intro e inizio del gioco
        if (!intro_in_corso && tempo_da_fine_intro < 120)
        {
            tempo_da_fine_intro++;
        }

        //aggiornamento del gioco
        if (!pausa && running && !intro_in_corso && tempo_da_fine_intro == 120 && !vittoria && !vittoria_in_corso)
        {
            if (livello < 10)
            {
                if(!IsMusicStreamPlaying(livelli))
                    PlayMusicStream(livelli);

                UpdateMusicStream(livelli);

                tempo_inizio_nuova_partita++;

                //spown della mystery ship
                if (spown_miystery_ship == (tempo_inizio_nuova_partita / 60) - ultimo_spown_mystery_ship)
                {
                    mystery_ship.spownaMysteryShip();
                    ultimo_spown_mystery_ship = tempo_inizio_nuova_partita;
                    spown_miystery_ship = GetRandomValue(35, 50);
                }

                if (mystery_ship.mystery_ship_attiva && !IsSoundPlaying(movimento_mystery_ship))
                {
                    SetSoundVolume(movimento_mystery_ship, 0.05);
                    PlaySound(movimento_mystery_ship);
                }
                else if (!mystery_ship.mystery_ship_attiva && IsSoundPlaying(movimento_mystery_ship))
                {
                    StopSound(movimento_mystery_ship);
                }

                //aggiorna la posizione dei laser del giocatore
                for (auto& laser : giocatore.lasers)
                {
                    laser.aggiornaLaser();
                }

                //fa sparare laser agli alieni
                alienoSparaLaser();

                //aggiorna la posizione dei laser degli alieni
                for (auto& laser : laser_alieni)
                {
                    laser.aggiornaLaser();
                }

                //aggiorna la posizione degli alieni e cancella quelli colpiti
                if (intervalloAlieni(velocita_alieni))
                {
                    muoviAlieni();
                    cancellaAlieno();

                    SetSoundVolume(movimento_alieno, 0.3);
                    PlaySound(movimento_alieno);
                }

                //aggiorna la posizione della mystery ship
                mystery_ship.aggiornaMysteryShip();
            }

            //livello del boss
            else
            {
                if(!IsMusicStreamPlaying(battaglia_boss))
                    PlayMusicStream(battaglia_boss);

                UpdateMusicStream(battaglia_boss);

                //controlla la vita del boss
                boss.boss_vivo = (boss.vita_boss <= 0) ? false : true;
                boss_sconfitto = (!boss.boss_vivo) ? true : false;

                if (boss.boss_vivo)
                {
                    //spowna gli alieni del boss
                    if (alieni.size() == 0 && intervalloSpownAlieni(GetRandomValue(25, 30)))
                    {
                        alieni = creaAlieniBoss();
                    }

                    //controllo della posizione degli alieni spownati dal boss (muovere dentro lo schermo o normalmente)
                    if (alieni.size() != 0)
                    {
                        if (alieni_boss_fuori)
                        {
                            //muove alieni verso dentro allo schermo
                            if (intervalloAlieni(velocita_alieni))
                            {
                                for (auto& alieno : alieni)
                                {
                                    alieno.aggiornaAlieno(10);
                                    cancellaAlieno();

                                    SetSoundVolume(movimento_alieno, 0.3);
                                    PlaySound(movimento_alieno);
                                }

                                posizione_alieni_boss_x += 10;
                            }

                            //fai sparare i laser agli alieni
                            alienoSparaLaser();
                        }
                        else
                        {
                            //muovi gli alieni normalmente
                            if (intervalloAlieni(velocita_alieni))
                            {
                                muoviAlieni();
                                cancellaAlieno();

                                SetSoundVolume(movimento_alieno, 0.3);
                                PlaySound(movimento_alieno);
                            }

                            //fai sparare i laser agli alieni
                            alienoSparaLaser();
                        }
                    }

                    //controlla se gli alieni sono entrati nello schermo
                    alieni_boss_fuori = (posizione_alieni_boss_x > 135) ? false : true;

                    //aggiorna la posizione dei laser del giocatore
                    for (auto& laser : giocatore.lasers)
                    {
                        laser.aggiornaLaser();
                    }

                    //aggiorna i laser degli alieni del boss
                    for (auto& laser : laser_alieni)
                    {
                        laser.aggiornaLaser();
                    }

                    //il boss spara laser
                    bossSparaLaser();

                    //aggiorna la posizione e lo stato dei laser del boss
                    for (auto& laser : laser_boss)
                    {
                        laser.aggiornaLaser();
                    }

                    //controllo della vita del boss per inizio seconda fase
                    if (boss.vita_boss < 25 && !seconda_fase_boss)
                    {
                        seconda_fase_boss = true;
                    }

                    //gestisce la seconda fase del boss e lo spown del tentacolo
                    if (seconda_fase_boss)
                    {
                        intervallo_per_recuper_vita_boss++;

                        if (!tentacolo_spownato)
                        {
                            tentacolo_attivo = true;
                        }

                        //fa recuperare la vita al boss nella seconda fase
                        if (intervallo_per_recuper_vita_boss / 60 == 2 && boss.boss_vivo)
                        {
                            boss.vita_boss++;
                            intervallo_per_recuper_vita_boss = 0;
                        }
                    }

                    //muove il tentacolo
                    if (tentacolo_attivo)
                    {
                        spownDespownTentacolo();
                    }
                }
                else
                {
                    StopMusicStream(battaglia_boss);
                }
            }

            //controlla tutte le collisioni
            controllaCollisioni();

            //disattiva i laser che hanno colpito qualcosa o che sono usciti dallo schermo
            disattivaLaserInattivi();

            //controlla il record e aggiorna il record stampato se il punteggio � maggiore del record
            controllaRecord();

            //game over in caso di vite finite
            if (PV == 0)
            {
                running = false;
            }
        }

        //aggiornamento del gioco durante il game over
        else if (!running)
        {
            if (!stampa_game_over)
            {
                frame_da_inizio_game_over++;
            }

            if (stampa_game_over)
            {
                scambio_schermo_game_over++;
            }

            if (frame_da_inizio_game_over >= 280)
            {
                stampa_game_over = true;
            }
        }
    }
}

//stampa il punteggio e il livello con degli 0 davanti
void Game::stampaPunteggioLivello(int lung_testo, int testo, int pos_x, int pos_y, int font_size, int distanza)
{
    string txt = to_string(testo);

    for (int i = 0; i < lung_testo - TextLength(txt.c_str()); i++)
    {
        DrawText("0", pos_x, pos_y, font_size, bianco);
        pos_x += distanza;
    }

    DrawText(txt.c_str(), pos_x, pos_y, font_size, bianco);
}

//intervallo laser
bool Game::intervalloLaser(double inter)
{
    double tempo_attuale = GetTime();

    if (tempo_attuale - tempo_laser >= inter)
    {
        tempo_laser = tempo_attuale;
        return true;
    }
    else
    {
        return false;
    }
}

//intervalo movimento alieno
bool Game::intervalloAlieni(double inter)
{
    double tempo_attuale = GetTime();

    if (tempo_attuale - tempo_alieni >= inter)
    {
        tempo_alieni = tempo_attuale;
        return true;
    }
    else
    {
        return false;
    }
}

//intervallo laser alieni
bool Game::intervalloLaserAlieni(double inter)
{
    double tempo_attuale = GetTime();

    if (tempo_attuale - tempo_laser_alieni >= inter)
    {
        tempo_laser_alieni = tempo_attuale;
        return true;
    }
    else
    {
        return false;
    }
}

//intervallo spown degli alieni
bool Game::intervalloSpownAlieni(double inter)
{
    double tempo_attuale = GetTime();

    if (tempo_attuale - tempo_spown_alieni >= inter)
    {
        tempo_spown_alieni = tempo_attuale;
        return true;
    }
    else
    {
        return false;
    }
}

//intervallo laser del boss
bool Game::intervalloLaserBoss(double inter)
{
    double tempo_attuale = GetTime();

    if (tempo_attuale - tempo_laser_boss >= inter)
    {
        tempo_laser_boss = tempo_attuale;
        return true;
    }
    else
    {
        return false;
    }
}

//intervallo movimento stelle menu
bool Game::intervalloStelle(double inter)
{
    double tempo_attuale = GetTime();

    if (tempo_attuale - tempo_stelle >= inter)
    {
        tempo_stelle = tempo_attuale;
        return true;
    }
    else
    {
        return false;
    }
}

//gestione degli input
void Game::controlloInput()
{
    if (IsKeyDown(KEY_RIGHT) && !pausa && running && tempo_da_fine_intro == 120 && tempo_da_inizio_vittoria == 0 && !boss_sconfitto && !menu)
    {
        giocatore.aggiornaPosizione(+4);
    }
    if (IsKeyDown(KEY_LEFT) && !pausa && running && tempo_da_fine_intro == 120 && tempo_da_inizio_vittoria == 0 && !boss_sconfitto && !menu)
    {
        giocatore.aggiornaPosizione(-4);
    }
    if (IsKeyDown(KEY_SPACE) && intervalloLaser(0.4) && !pausa && running && tempo_da_fine_intro == 120 && tempo_da_inizio_vittoria == 0 && !boss_sconfitto && !menu)
    {
        SetSoundVolume(laser_giocatore, 0.2);
        PlaySound(laser_giocatore);

        giocatore.sparaLaser();
    }
    if (IsKeyPressed(KEY_P) && running && !intro_in_corso && !vittoria && !boss_sconfitto && !menu)
    {
        if (livello < 10 && alieni.size() != 0)
        {
            pausa = !pausa;
        }

        if (livello == 10)
        {
            pausa = !pausa;
        }
    }
    if (IsKeyPressed(KEY_R) && !running)
    {
        reset();
        initPartita();
    }
    if (IsKeyPressed(KEY_ENTER) && (intro_in_corso || vittoria))
    {
        if (intro_in_corso && !menu)
        {
            intro_in_corso = false;
        }

        if (vittoria)
        {
            reset();
            initPartita();
        }

        if (menu)
        {
            menu = false;
        }
    }
}

//stampa le vite rimanenti
void Game::stampaVite()
{
    int pos_x_vite = 20;

    for (int i = 0; i < PV; i++)
    {
        DrawTexture(vite, pos_x_vite, GetScreenHeight() - 40, WHITE);
        pos_x_vite += 50;
    }
}

//cancella i laser inattivi
void Game::disattivaLaserInattivi()
{
    for (auto laser = giocatore.lasers.begin(); laser != giocatore.lasers.end();)
    {
        if (!laser->laser_attivo)
        {
            laser = giocatore.lasers.erase(laser);
        }
        else
        {
            laser++;
        }
    }

    for (auto laser = laser_alieni.begin(); laser != laser_alieni.end();)
    {
        if (!laser->laser_attivo)
        {
            laser = laser_alieni.erase(laser);
        }
        else
        {
            laser++;
        }
    }

    for (auto laser = laser_boss.begin(); laser != laser_boss.end();)
    {
        if (!laser->laser_attivo)
        {
            laser = laser_boss.erase(laser);
        }
        else
        {
            laser++;
        }
    }
}

//crea gli ostacoli
std::vector<Ostacolo> Game::creaOstacoli()
{
    std::vector<Ostacolo> ostacoli;

    for(int num_ostacoli = 0; num_ostacoli < 5; num_ostacoli++)
    {
        ostacoli.push_back(Ostacolo(Vector2 {pos_ost_x, 615}));
        pos_ost_x += 140;
    }

    return ostacoli;
}

//stampa gli ostacoli
void Game::stampaOstacoli()
{
    for(auto& ostacolo: ostacoli)
    {
        ostacolo.stampaOstacolo();
    }
}

//crea gli alieni
std::vector<Alieno> Game::creaAlieni()
{
    std::vector<Alieno> al;

    for (float riga = 0; riga < 5; riga++)
    {
        for (float colonna = 0; colonna < 11; colonna++)
        {
            int tipo_alieno;
            float x = 75 + colonna * 50;
            float y = 90 + riga * 50;

            if (riga == 0)
            {
                tipo_alieno = 1;
            }
            else if (riga == 1 || riga == 2)
            {
                tipo_alieno = 2;
            }
            else
            {
                tipo_alieno = 3;
            }

            al.push_back(Alieno(tipo_alieno, { x, y }));
        }
    }

    return al;
}

//controlla posizione alieni
void Game::controllaPosAlieni()
{
    if (alieni.size() != 0)
    {
        alieni_devono_scendere = false;

        for (auto& alieno : alieni)
        {
            if (alieno.posizione_alieno.x < 10 && !alieni_scesi)
            {
                direzione_alieni = 10;
                muoviGiuAlieni();
            }

            if (alieno.posizione_alieno.x + 60 > GetScreenWidth() && !alieni_scesi)
            {
                direzione_alieni = -10;
                muoviGiuAlieni();
            }
        }
    }
}

//aggiorna la posizione degli alieni
void Game::muoviAlieni()
{
    if (alieni.size() != 0)
    {
        controllaPosAlieni();

        if (!alieni_devono_scendere)
        {
            for (auto& alieno : alieni)
            {
                alieno.aggiornaAlieno(direzione_alieni);
            }

            alieni_scesi = false;
        }
    }
}

//aggiorna la posizione verticale degli alieni
void Game::muoviGiuAlieni()
{
    if (alieni.size() != 0)
    {
        for (auto& alieno : alieni)
        {
            alieni_devono_scendere = true;

            alieno.posizione_alieno.y += discesa_alieni;
            alieno.stato_alieno = !alieno.stato_alieno;

            alieni_scesi = true;
        }

        posizione_alieni_y += discesa_alieni;
    }
}

//alieni sparano laser
void Game::alienoSparaLaser()
{
    if (intervalloLaserAlieni(velocita_sopwn_laser_alieni) && alieni.size() != 0)
    {
        int alieno_casuale = GetRandomValue(0, alieni.size() - 1);
        Alieno alieno = alieni[alieno_casuale];

        laser_alieni.push_back(Laser({ alieno.posizione_alieno.x + 25, alieno.posizione_alieno.y + 50 }, { 255, 0, 15, 255 }, 6));
    }
}

//collisioni 
void Game::controllaCollisioni()
{
    //collisioni Player-Bordi
    giocatore.collisioneBordi();

    //collisioni LaserPlayer-AltreRobe
    for (auto& laser : giocatore.lasers)
    {
        if (alieni.size() != 0)
        {
            //collisione LaserPlayer-Alieno
            auto alieno = alieni.begin();

            while (alieno != alieni.end())
            {
                if (CheckCollisionRecs(alieno->hitbox(), laser.hitbox()))
                {
                    switch (alieno->tipoAlieno())
                    {
                    case 1:
                        punteggio += 300;
                        break;
                    case 2:
                        punteggio += 200;
                        break;
                    case 3:
                        punteggio += 100;
                        break;
                    case 4:
                        punteggio += 400;
                    default:
                        break;
                    }

                    PlaySound(alieno_ms_pl_colpiti_tentacolo);

                    alieno->alieno_vivo = false;

                    velocita_sopwn_laser_alieni += 0.005;

                    laser.laser_attivo = false;
                }
                else
                {
                    alieno++;
                }
            }
        }

        //collisione LaserPlayer-Blocchi
        for (auto& ostacolo : ostacoli)
        {
            auto blocco = ostacolo.blocchi.begin();

            while (blocco != ostacolo.blocchi.end())
            {
                if (CheckCollisionRecs(blocco->hitbox(), laser.hitbox()))
                {
                    blocco = ostacolo.blocchi.erase(blocco);
                    laser.laser_attivo = false;
                }
                else
                {
                    blocco++;
                }
            }
        }

        if (mystery_ship.mystery_ship_attiva)
        {
            //collisione LaserPlayer-MysteryShip
            if (CheckCollisionRecs(laser.hitbox(), mystery_ship.hitbox()))
            {
                PlaySound(alieno_ms_pl_colpiti_tentacolo);

                punteggio += 500;

                mystery_ship.mystery_ship_colpita = true;
                mystery_ship.mystery_ship_attiva = false;
                laser.laser_attivo = false;
            }
        }
    }


    //collisioni LaserAlieni-AltreRobe
    for (auto& laser : laser_alieni)
    {
        //collisioni LaserAlieni-Blocchi
        for (auto& ostacolo : ostacoli)
        {
            auto blocco = ostacolo.blocchi.begin();

            while (blocco != ostacolo.blocchi.end())
            {
                if (CheckCollisionRecs(blocco->hitbox(), laser.hitbox()))
                {
                    blocco = ostacolo.blocchi.erase(blocco);
                    laser.laser_attivo = false;
                }
                else
                {
                    blocco++;
                }
            }
        }

        //collisioni LaserAlieni-Player
        if (CheckCollisionRecs(laser.hitbox(), giocatore.hitbox()))
        {
            PlaySound(alieno_ms_pl_colpiti_tentacolo);

            laser.laser_attivo = false;
            PV--;
        }

        //collisioni LaserAlieni-Tentacolo
        if (livello == 10 && CheckCollisionRecs(laser.hitbox(), tentacolo.hitbox()))
        {
            laser.laser_attivo = false;
        }
    }

    //collisioni Alieni-AltreRobe
    if (posizione_alieni_y > 480 && alieni.size() != 0)
    {
        for (auto& alieno : alieni)
        {
            //collisioni Alieni-Blocchi
            for (auto& ostacolo : ostacoli)
            {
                auto blocco = ostacolo.blocchi.begin();

                while (blocco != ostacolo.blocchi.end())
                {
                    if (CheckCollisionRecs(blocco->hitbox(), alieno.hitbox()))
                    {
                        blocco = ostacolo.blocchi.erase(blocco);
                    }
                    else
                    {
                        blocco++;
                    }
                }
            }

            //collisioni Alieni-Player
            if (CheckCollisionRecs(alieno.hitbox(), giocatore.hitbox()))
            {
                PV = 0;
            }
        }
    }

    //collisioni durante battaglia boss
    if (livello == 10)
    {
        //collisioni LaserPlayer-AltreRobe
        for (auto& laser : giocatore.lasers)
        {
            //collisioni LaserPlayer-Boss
            if (CheckCollisionRecs(laser.hitbox(), boss.hitbox()))
            {
                PlaySound(alieno_ms_pl_colpiti_tentacolo);

                laser.laser_attivo = false;
                boss.vita_boss--;
                intervallo_spown_laser_boss -= 0.005;
            }

            //collisioni LaserPlayer-Tentacolo
            if (CheckCollisionRecs(laser.hitbox(), tentacolo.hitbox()))
            {
                PlaySound(alieno_ms_pl_colpiti_tentacolo);

                laser.laser_attivo = false;
            }
        }

        //collisioni LaserBoss-AltreRobe
        for (auto& laser : laser_boss)
        {
            //collisioni LaserBoss-Blocchi
            for (auto& ostacolo : ostacoli)
            {
                auto blocco = ostacolo.blocchi.begin();

                while (blocco != ostacolo.blocchi.end())
                {
                    if (CheckCollisionRecs(blocco->hitbox(), laser.hitbox()))
                    {
                        laser.laser_attivo = false;
                        blocco = ostacolo.blocchi.erase(blocco);
                    }
                    else
                    {
                        blocco++;
                    }
                }
            }

            //collisioni LaserBoss-Player
            if (CheckCollisionRecs(laser.hitbox(), giocatore.hitbox()))
            {
                PlaySound(alieno_ms_pl_colpiti_tentacolo);

                laser.laser_attivo = false;
                PV--;
            }

            //collisioni LaserBoss-Tentacolo
            if (CheckCollisionRecs(laser.hitbox(), tentacolo.hitbox()))
            {
                laser.laser_attivo = false;
            }
        }
    }
}

//cancella l'alieno se � stato colpito
void Game::cancellaAlieno()
{
    auto alieno = alieni.begin();

    while (alieno != alieni.end())
    {
        if (!alieno->alieno_vivo)
        {
            alieno = alieni.erase(alieno);
        }
        else
        {
            alieno++;
        }
    }
}

//inizializza nuova partita in caso di sconfitta
void Game::initPartita()
{
    ostacoli = creaOstacoli();

    switch (livello)
    {
    case 1:
        velocita_alieni = 0.45;
        break;
    case 2:
        velocita_alieni = 0.45;
        break;
    case 3:
        velocita_alieni = 0.4;
        break;
    case 4:
        velocita_alieni = 0.35;
        break;
    case 5:
        velocita_alieni = 0.35;
        break;
    case 6:
        velocita_alieni = 0.35;
        break;
    case 7:
        velocita_alieni = 0.3;
        break;
    case 8:
        velocita_alieni = 0.3;
        break;
    case 9:
        velocita_alieni = 0.25;
        break;
    case 10:
        velocita_alieni = 0.1;
        boss.boss_vivo = true;
        break;
    default:
        livello = 1;
        velocita_alieni = 0.45;
        break;
    }

    if (livello < 10)
    {
        alieni = creaAlieni();
        spown_miystery_ship = GetRandomValue(35, 50);
    }

    direzione_alieni = 10;
}

//resetta la partita prima di inizializzarla
void Game::reset()
{
    giocatore.reset();

    alieni.clear();
    laser_alieni.clear();
    ostacoli.clear();
    giocatore.lasers.clear();
    laser_boss.clear();

    pos_ost_x = 40;

    running = true;
    stampa_game_over = false;

    if (vittoria)
    {
        intro_in_corso = true;
        vittoria = false;
        livello++;
        discesa_alieni++;
        vittoria_in_corso = false;
    }
    else
    {
        vittoria = false;
        intro_in_corso = true;
        livello = 1;
        PV = 3;
        punteggio = 0;
        discesa_alieni = 7;
    }

    if (fine_gioco)
    {
        fine_gioco = false;
        boss_sconfitto = false;
        discesa_alieni = 7;
    }

    frame_da_inizio_game_over = 0;
    scambio_schermo_game_over = 0;
    tempo_da_fine_intro = 0;
    ultimo_spown_mystery_ship = 0;
    tempo_inizio_nuova_partita = 0;
    tempo_da_inizio_vittoria = 0;
    velocita_sopwn_laser_alieni = 0.2;
    tempo_cambio_texture_boss = 0;

    posizione_alieni_y = (livello < 10) ? 215 : 300;
    posizione_alieni_boss_x = -125;
    boss.vita_boss = 100;
    seconda_fase_boss = false;
    tentacolo_spownato = false;
    tentacolo_attivo = false;
    tentacolo_dentro_schermo = false;
    intervallo_spown_laser_boss = 0.7;

    mystery_ship.mystery_ship_attiva = false;
}

//aggiorna il record se il punteggio � pi� alto del record
void Game::controllaRecord()
{
    if (punteggio > record)
    {
        record = punteggio;
    }
}

//salva record
void Game::salvataggioRecord()
{
    ofstream file_record("data/file/record.txt");

    if (file_record.is_open())
    {
        file_record << record;
        file_record.close();
    }
    else
    {
        cerr << "Error: failed to save record to file\n";
    }
}

//carica record
int Game::caricamentoRecord()
{
    int record_caricato = 0;
    ifstream file_record("data/file/record.txt");

    if (file_record.is_open())
    {
        file_record >> record_caricato;
        file_record.close();
    }
    else
    {
        cerr << "Error: failed to load record from file\n";
    }

    return record_caricato;
}

//fa sparare i laser al boss
void Game::bossSparaLaser()
{
    if (intervalloLaserBoss(intervallo_spown_laser_boss))
    {
        float punto_x_di_spown = GetRandomValue(10, GetScreenWidth() - 10);
        laser_boss.push_back(Laser({ punto_x_di_spown, 61 }, { 120, 2, 13, 255 }, 6));
    }
}

//crea alieni durantre battaglia boss
std::vector<Alieno> Game::creaAlieniBoss()
{
    std::vector<Alieno> alieni;

    posizione_alieni_boss_x = -125;
    posizione_alieni_y = 275;

    float offset = 0;

    for (int i = 0; i < 5; i++)
    {
        alieni.push_back(Alieno(4, { -250 + offset, 275 }));
        offset += 50;
    }

    return alieni;
}

//muove il tentacolo dentro e fuori lo schermo
void Game::spownDespownTentacolo()
{
    if (tentacolo.posizione_tentacolo.x < 0 && !tentacolo_dentro_schermo)
    {
        tentacolo.aggiornaTentacolo(7);
    }

    if (tentacolo.posizione_tentacolo.x == 0 && !tentacolo_dentro_schermo)
    {
        PlaySound(alieno_ms_pl_colpiti_tentacolo);

        tentacolo_dentro_schermo = true;
        ostacoli.clear();
    }

    if (tentacolo_dentro_schermo)
    {
        tentacolo.aggiornaTentacolo(-7);
    }

    if (tentacolo.posizione_tentacolo.x < -GetScreenWidth() && tentacolo_dentro_schermo)
    {
        tentacolo_attivo = false;
        tentacolo_spownato = true;
    }
}

//popola il vettore delle stelle
std::vector<Cerchio> Game::creaStelle()
{
    std::vector<Cerchio> stelle;

    for (int i = 0; i < 60; i++)
    {
        stelle.push_back(Cerchio{ {(float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(70, GetScreenHeight() - 70)}, GetRandomValue(1, 6) });
    }

    return stelle;
}

//stampa una stella
void Game::stampaStella(Cerchio stella)
{
    DrawCircle(stella.centro.x, stella.centro.y, stella.raggio, bianco);
}

//aggiorna una stella
void Game::aggiornaStella(Cerchio* stella)
{
    if (stella->raggio > 3)
    {
        velocita = 6;
    }
    else
    {
        velocita = 2;
    }

    stella->centro.x -= velocita;

    if (stella->centro.x < 0 - stella->raggio)
    {
        stella->centro.x = GetScreenWidth() + stella->raggio;
    }
}