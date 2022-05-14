#include"game_header.h"
/** \file hero_functions.c
 * Plik Ÿród³owy hero_functions.
 * Zawiera funkcje steruj¹ce bohaterem.
 */

/**
*Funkcja ustawiaj¹ca parametry startowe bohatera.
*
*Funkcja ustawia po³o¿enie pocz¹tkowe bohatera, jego szybkoœæ i iloœæ ¿yæ.
*@param hero struktura przechowuj¹ca parametry bohatera
*@see hero_update()
*/
void hero_init(struct HERO* hero)
{
    hero->speed = 10;
    hero->x = (DISPLAY_WIDTH / 2) - (HERO_WIDTH / 2);
    hero->y = DISPLAY_HEIGHT - 85;
    hero->lives = 3;
}

/**
*Funkcja aktualizuj¹ca po³o¿enie bohatera.
*
*Funkcja aktualizuje po³o¿enie bohatera na podstawie wykrytych klawiszy steruj¹cych.
*@param hero struktura przechowuj¹ca parametry bohatera
*@see hero_init()
*/
void hero_update(struct HERO* hero)
{
    if (hero->lives > 0)
    {
        if (key[ALLEGRO_KEY_LEFT])
            hero->x -= hero->speed;
        if (key[ALLEGRO_KEY_RIGHT])
            hero->x += hero->speed;

        if (hero->x < 0)
            hero->x = 0;
        if (hero->x > DISPLAY_WIDTH - HERO_WIDTH)
            hero->x = DISPLAY_WIDTH - HERO_WIDTH;
    }
}

