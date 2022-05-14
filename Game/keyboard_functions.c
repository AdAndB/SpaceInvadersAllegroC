#include "game_header.h"
/** \file keyboard_functions.c
 * Plik Ÿród³owy keyboard_functions.
 * Zawiera funkcje odpowiedzialne za obs³ugê klawiatury.
 */

 /**
 *Funkcja inicjalizuj¹ca klawiaturê.
 * 
 *@see keyboard_update()
 */
void keyboard_init()
{
    init_check(al_install_keyboard(), "keyboard");
    memset(key, 0, sizeof(key));
}

/**
 *Funkcja odpowiedzialna za p³ynne sterowanie.
 *
 *@param event zdarzenie 
 */
void keyboard_update(ALLEGRO_EVENT* event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;
    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= KEY_RELEASED;
        break;
    }
}