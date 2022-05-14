#include "game_header.h"
/** \file shots_and_buffs_functions.c
 * Plik Ÿród³owy shots_and_buffs_functions.
 * Zawiera funkcje obs³uguj¹ce pociski i wzmocnienia.
 */


 /**
 *Funkcja dodaj¹ca pociski bohatera na listê.
 *
 *Funkcja dodaje pociski bohatera na listê uwzglêdniaj¹c tryb strzelania.
 *@param player_shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski bohatera
 *@param damage wartoœæ zadawanych obra¿eñ
 *@param hero struktura przechowuj¹ca parametry bohatera
 *@param speed szybkoœæ pocisku
 *@param shoot_mode tryb strzelania
 *@return 1 - jeœli pociski zosta³y dodane
 *@return 0 - jeœli pociski nie zosta³y dodane
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
*Funkcja aktualizuj¹ca po³o¿enie pocisków.
*
*Funkcja aktualizuje po³o¿enie pocisków na bazie ich szybkoœci poruszania oraz rozmiaru okna gry.
*@param shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski
*@param node wskaŸnik na listê
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
*Funkcja rysuj¹ca pociski bohatera.
*
*Funkcja rysuje pociski bohatera na odpowiednich wspó³rzêdnych.
*@param shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski
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
*Funkcja rysuj¹ca pociski wrogów.
*
*Funkcja rysuje pociski wrogów na odpowiednich wspó³rzêdnych.
*@param shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski
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
*Funkcja losuj¹ca wzmocnienie.
*
*Funkcja losuje jedno z trzech wzmocnieñ i dodaje je do listy.
*@param buffs podwójny wskaŸnik na listê przechowuj¹c¹ wzmocnienia
*@param enemy struktura przechowuj¹ca parametry wroga
*/
void buff_init(struct dll_node** buffs, struct ENEMIES enemy) {
    int buff_type = rand() % 3;
    if (key[ALLEGRO_KEY_SPACE])
    {
        append(buffs, buff_type, enemy.x + enemy.width / 2 - BUFF_WIDTH, enemy.y, BUFF_SPEED);
    }

}

/**
*Funkcja aktualizuj¹ca po³o¿enie wzmocnieñ.
*
*Funkcja aktualizuje po³o¿enie wzmocnieñ na bazie ich szybkoœci poruszania oraz rozmiaru okna gry.
*@param shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski
*@param node wskaŸnik na listê
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
*Funkcja rysuj¹ca wzmocnienia.
*
*Funkcja rysuje wzmocnienia na odpowiednich wspó³rzêdnych.
*@param buffs podwójny wskaŸnik na listê przechowuj¹c¹ wzmocnienia
*/
void buffs_draw(struct dll_node** buffs) {
    struct dll_node* tmp = *buffs;
    while (tmp)
    {
        al_draw_bitmap(objects.buff[tmp->item.exclusive_info], tmp->item.x, tmp->item.y, 0);

        tmp = tmp->next;
    }

}