#include "game_header.h"
/** \file enemy_functions.c
 * Plik �r�d�owy enemy_functions.
 * Zawiera funkcje steruj�ce wrogimi jednostkami.
 */

 /**
*Funkcja ustawiaj�ca parametry startowe wrog�w.
*
*Funkcja ustawia po�o�enie wrog�w, szybko��, ilo�� �y�, szeroko�� i  wysoko��.
*@param enemies struktura przechowuj�ca parametry wrog�w
*@param columns ilo�� kolumn wrog�w
*@param rows ilo�� rz�d�w wrog�w
*@param width szeroko�� wrog�w
*@param height wysoko�� wrog�w
*@param health ilo�� �y� wrog�w
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
*Funkcja rysuj�ca wrog�w.
*
*Funkcja rysuje wrog�w na odpowiednich wsp�rz�dnych.
*@param enemies struktura przechowuj�ca parametry wrog�w
*@param enemies_number ilo�� wrog�w na ekranie
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
*Funkcja aktualizuj�ca po�o�enie wrog�w.
*
*Funkcja aktualizuje po�o�enie wrog�w na bazie ich szybko�ci poruszania oraz rozmiaru okna gry
*(przy zbli�eniu do kraw�dzi nast�puje przeskok do kolejnego rz�du).
*@param enemies struktura przechowuj�ca parametry wrog�w
*@param enemies_number ilo�� wrog�w na ekranie
*@param alive ilo�� �ywych wrog�w
*@param hero struktura przechowuj�ca parametry bohatera
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
*Funkcja odpowiadaj�ca za wystrzeliwanie pocisk�w przez wrog�w.
*
*Funkcja losuje jednego z wrog�w pozosta�ych na ekranie, kt�ry odda strza�.
*@param enemies struktura przechowuj�ca parametry wrog�w
*@param enemies_number ilo�� wrog�w na ekranie
*@param alive ilo�� �ywych wrog�w
*@param enemy_shots podw�jny wska�nik na list� przechowuj�c� pociski wrog�w
*@param speed szybko�� pocisku
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