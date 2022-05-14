#include "game_header.h"
/** \file enemy_functions.c
 * Plik Ÿród³owy enemy_functions.
 * Zawiera funkcje steruj¹ce wrogimi jednostkami.
 */

 /**
*Funkcja ustawiaj¹ca parametry startowe wrogów.
*
*Funkcja ustawia po³o¿enie wrogów, szybkoœæ, iloœæ ¿yæ, szerokoœæ i  wysokoœæ.
*@param enemies struktura przechowuj¹ca parametry wrogów
*@param columns iloœæ kolumn wrogów
*@param rows iloœæ rzêdów wrogów
*@param width szerokoœæ wrogów
*@param height wysokoœæ wrogów
*@param health iloœæ ¿yæ wrogów
*@see enemies_draw() , enemies_update() , enemy_shoot()
*/
void enemies_set(struct ENEMIES* enemies, int columns, int rows, int width, int height,int health)
{

    int tempx = 60, tempy = 10;
    int counter = 0;;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            enemies[counter].x = tempx;
            enemies[counter].y = tempy;
            enemies[counter].speed = -0.5;
            enemies[counter].life = health;
            enemies[counter].width = width;
            enemies[counter].height = height;
            tempx += 70;
            counter++;
        }
        tempx = 60;
        tempy += 90;
    }
}

/**
*Funkcja rysuj¹ca wrogów.
*
*Funkcja rysuje wrogów na odpowiednich wspó³rzêdnych.
*@param enemies struktura przechowuj¹ca parametry wrogów
*@param enemies_number iloœæ wrogów na ekranie
*@see enemies_set() , enemies_update() , enemy_shoot()
*/
void enemies_draw(struct ENEMIES* enemies, int enemies_number)
{
    for (int i = 0; i < enemies_number; i++)
    {
        if (enemies[i].life > 0)
        {

            al_draw_bitmap(objects.enemy1, enemies[i].x, enemies[i].y, 0);
        }
    }
}

/**
*Funkcja aktualizuj¹ca po³o¿enie wrogów.
*
*Funkcja aktualizuje po³o¿enie wrogów na bazie ich szybkoœci poruszania oraz rozmiaru okna gry
*(przy zbli¿eniu do krawêdzi nastêpuje przeskok do kolejnego rzêdu).
*@param enemies struktura przechowuj¹ca parametry wrogów
*@param enemies_number iloœæ wrogów na ekranie
*@param alive iloœæ ¿ywych wrogów
*@param hero struktura przechowuj¹ca parametry bohatera
*@see enemies_draw() , enemies_set() , enemy_shoot()
*/
void enemies_update(struct ENEMIES* enemies, int enemies_number, int* alive, struct HERO *hero)
{
    *alive = 0;
    bool help = false;
    for (int i = 0; i < enemies_number; i++)
    {
        if (enemies[i].life > 0)
        {
            *alive += 1;
        }

        if (enemies[i].y + ENEMY_HEIGHT >= DISPLAY_HEIGHT - 40) {
            hero->lives = 0;
        }

        if ((enemies[i].x + enemies[i].speed < BORDER) && (help == false) && enemies[i].life > 0)
        {
            help = true;
            for (int j = 0; j < enemies_number; j++)
            {

                enemies[j].x += 1;
                enemies[j].speed *= -1;
                enemies[j].y += JUMP;


            }
        }

        if (enemies[i].x + enemies[i].speed > (DISPLAY_WIDTH - enemies[i].width - BORDER) && (help == false) && enemies[i].life > 0)
        {
            help = true;
            for (int j = 0; j < enemies_number; j++)
            {
                enemies[j].x -= 1;
                enemies[j].speed *= -1;
                enemies[j].y += JUMP;
            }
        }
        enemies[i].x += enemies[i].speed;
        help = false;
    }
}

/**
*Funkcja odpowiadaj¹ca za wystrzeliwanie pocisków przez wrogów.
*
*Funkcja losuje jednego z wrogów pozosta³ych na ekranie, który odda strza³.
*@param enemies struktura przechowuj¹ca parametry wrogów
*@param enemies_number iloœæ wrogów na ekranie
*@param alive iloœæ ¿ywych wrogów
*@param enemy_shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski wrogów
*@param speed szybkoœæ pocisku
*@see enemies_draw() , enemies_update() , enemies_set()
*/
void enemy_shoot(struct ENEMIES* enemies, int enemies_number, int alive, struct dll_node** enemy_shots, int speed) {
    if (alive > 0)
    {


        int who_shoots = 1 + rand() % alive;
        int counter = 0;
        for (int i = 0; i < enemies_number; i++)
        {
            if (enemies[i].life > 0)
            {
                counter += 1;
            }
            if (counter == who_shoots)
            {
                append(enemy_shots, 1, enemies[i].x + enemies[i].width / 2, enemies[i].y + enemies[i].height, speed);
                break;

            }
        }
    }
}