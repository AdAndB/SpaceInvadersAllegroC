#include "game_header.h"
/** \file shots_and_buffs_functions.c
 * Plik �r�d�owy shots_and_buffs_functions.
 * Zawiera funkcje obs�uguj�ce pociski i wzmocnienia.
 */


 /**
 *Funkcja dodaj�ca pociski bohatera na list�.
 *
 *Funkcja dodaje pociski bohatera na list� uwzgl�dniaj�c tryb strzelania.
 *@param player_shots podw�jny wska�nik na list� przechowuj�c� pociski bohatera
 *@param damage warto�� zadawanych obra�e�
 *@param hero struktura przechowuj�ca parametry bohatera
 *@param speed szybko�� pocisku
 *@param shoot_mode tryb strzelania
 *@return 1 - je�li pociski zosta�y dodane
 *@return 0 - je�li pociski nie zosta�y dodane
 */
int shot_init(struct dll_node** player_shots, int damage, struct HERO hero, int speed, int shoot_mode) {
    if (key[ALLEGRO_KEY_SPACE])
    {
        if (shoot_mode == 0)
        {
            append(player_shots, damage, hero.x + HERO_WIDTH / 2 - SHOT_WIDTH, hero.y, speed);
        }
        else if (shoot_mode == 1) {
            append(player_shots, damage, hero.x + HERO_WIDTH / 3 - SHOT_WIDTH, hero.y, speed);
            append(player_shots, damage, hero.x + 2 * HERO_WIDTH / 3 - SHOT_WIDTH, hero.y, speed);
        }
        else
        {
            append(player_shots, damage, hero.x + HERO_WIDTH / 4 - SHOT_WIDTH, hero.y, speed);
            append(player_shots, damage, hero.x + HERO_WIDTH / 2 - SHOT_WIDTH, hero.y, speed);
            append(player_shots, damage, hero.x + 3 * HERO_WIDTH / 4 - SHOT_WIDTH, hero.y, speed);
        }
        al_play_sample(gun_sound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        return 1;
    }
    return 0;
}

/**
*Funkcja aktualizuj�ca po�o�enie pocisk�w.
*
*Funkcja aktualizuje po�o�enie pocisk�w na bazie ich szybko�ci poruszania oraz rozmiaru okna gry.
*@param shots podw�jny wska�nik na list� przechowuj�c� pociski
*@param node wska�nik na list�
*/
void shots_update(struct dll_node** shots, struct dll_node* node) {
    int counter = 0;
    if (node) {
        if (node->item.y < -30 || node->item.y > DISPLAY_HEIGHT + 20) {
            delete_node(shots, node);

        }
        else
        {
            node->item.y -= node->item.speed;
            shots_update(shots, node->next);
        }
    }
}

/**
*Funkcja rysuj�ca pociski bohatera.
*
*Funkcja rysuje pociski bohatera na odpowiednich wsp�rz�dnych.
*@param shots podw�jny wska�nik na list� przechowuj�c� pociski
*/
void shots_draw(struct dll_node** shots) {
    struct dll_node* tmp = *shots;
    while (tmp)
    {
        al_draw_bitmap(objects.bullet, tmp->item.x, tmp->item.y, 0);

        tmp = tmp->next;
    }

}

/**
*Funkcja rysuj�ca pociski wrog�w.
*
*Funkcja rysuje pociski wrog�w na odpowiednich wsp�rz�dnych.
*@param shots podw�jny wska�nik na list� przechowuj�c� pociski
*/
void enemy_shots_draw(struct dll_node** shots) {
    struct dll_node* tmp = *shots;
    while (tmp)
    {
        al_draw_bitmap(objects.item, tmp->item.x, tmp->item.y, 0);

        tmp = tmp->next;
    }

}

/**
*Funkcja losuj�ca wzmocnienie.
*
*Funkcja losuje jedno z trzech wzmocnie� i dodaje je do listy.
*@param buffs podw�jny wska�nik na list� przechowuj�c� wzmocnienia
*@param enemy struktura przechowuj�ca parametry wroga
*/
void buff_init(struct dll_node** buffs, struct ENEMIES enemy) {
    int buff_type = rand() % 3;
    if (key[ALLEGRO_KEY_SPACE])
    {
        append(buffs, buff_type, enemy.x + enemy.width / 2 - BUFF_WIDTH, enemy.y, BUFF_SPEED);
    }

}

/**
*Funkcja aktualizuj�ca po�o�enie wzmocnie�.
*
*Funkcja aktualizuje po�o�enie wzmocnie� na bazie ich szybko�ci poruszania oraz rozmiaru okna gry.
*@param shots podw�jny wska�nik na list� przechowuj�c� pociski
*@param node wska�nik na list�
*/
void buffs_update(struct dll_node** buffs, struct dll_node* node) {
    int counter = 0;
    if (node) {
        if (node->item.y < -30 || node->item.y > DISPLAY_HEIGHT + 20) {
            delete_node(buffs, node);

        }
        else
        {
            node->item.y += node->item.speed;
            buffs_update(buffs, node->next);
        }
    }
}

/**
*Funkcja rysuj�ca wzmocnienia.
*
*Funkcja rysuje wzmocnienia na odpowiednich wsp�rz�dnych.
*@param buffs podw�jny wska�nik na list� przechowuj�c� wzmocnienia
*/
void buffs_draw(struct dll_node** buffs) {
    struct dll_node* tmp = *buffs;
    while (tmp)
    {
        al_draw_bitmap(objects.buff[tmp->item.exclusive_info], tmp->item.x, tmp->item.y, 0);

        tmp = tmp->next;
    }

}