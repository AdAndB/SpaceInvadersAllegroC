#include "game_header.h"
/** \file hitbox_functions.c
 * Plik �r�d�owy hitbox_functions.
 * Zawiera funkcje odpowiadaj�ce za wykrywanie zderze� obiekt�w.
 */

 /**
 *Funkcja wykrywaj�ca zderzenia bohatera z pociskami.
 *
 *Funkcja sprawdza czy dosz�o do zderzenia bohatera z pociskami. Je�li tak, nast�puje zmniejszenie ilo�ci �y�
 * bohatera oraz zwr�cenie przez funkcje ilo�ci klatek, w czasie kt�rych b�dzie on niewra�liwy na ataki. 
 *@param hero struktura przechowuj�ca parametry bohatera
 *@param enemy_shots podw�jny wska�nik na list� przechowuj�c� pociski wrog�w
 *@return 90 - ilo�� klatek nierwa�liwo�ci je�li bohater zosta� trafiony
 *@return 0 - ilo�� klatek nierwa�liwo�ci je�li bohater nie zosta� trafiony
 *@see check_hero_buff_pickup() , check_enemy_hitbox()
 */
int check_hero_hitbox(struct HERO* hero, struct dll_node** enemy_shots) {
    struct dll_node* tmp = *enemy_shots;
    while (tmp)
    {
        if (((tmp->item.y + CACTUS_SHOT_SIZE > hero->y) && (tmp->item.x >= hero->x && tmp->item.x <= hero->x + HERO_WIDTH))
            || ((tmp->item.y + CACTUS_SHOT_SIZE > hero->y) && (tmp->item.x + CACTUS_SHOT_SIZE >= hero->x && tmp->item.x <= hero->x + HERO_WIDTH)))
        {
            hero->lives -= tmp->item.exclusive_info;
            al_play_sample(hit_sound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            delete_node(enemy_shots, tmp);
            return 90;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    return 0;
}

/**
 *Funkcja sprawdzaj�ca zebranie wzmocnienia przez bohatera.
 *
 *Funkcja sprawdza czy dosz�o do zderzenia bohatera z wzmocnieniem. Je�li tak, nast�puje jego realizacja.
 * W zale�no�ci od typu wzmocnienia jest to tymczasowa niewra�liwo�� bohatera na otrzymywane ataki,
 * dodatkowe �ycie lub wzmocnienie zadawanych obra�e� / zwi�kszenie ilo�ci wystrzeliwanych pocisk�w.
 *@param hero struktura przechowuj�ca parametry bohatera
 *@param buffs podw�jny wska�nik na list� przechowuj�c� wzmocnienia
 *@param shoot_mode tryb strzelania
 *@param shield liczba klatek aktywno�ci tarczy
 *@param damage aktualna warto�� zadawanych obra�e�
 *@see check_hero_hitbox() , check_enemy_hitbox()
 */
void check_hero_buff_pickup(struct HERO* hero, struct dll_node** buffs, int* shoot_mode, int* shield, int* damage) {
    struct dll_node* tmp = *buffs;
    while (tmp)
    {
        if (((tmp->item.y + BUFF_HEIGHT > hero->y) && (tmp->item.x >= hero->x && tmp->item.x <= hero->x + HERO_WIDTH))
            || ((tmp->item.y + BUFF_HEIGHT > hero->y) && (tmp->item.x + BUFF_WIDTH >= hero->x && tmp->item.x <= hero->x + HERO_WIDTH)))
        {

            if (tmp->item.exclusive_info == 0) {
                *shield = 240;
            }
            else if (tmp->item.exclusive_info == 1) {
                if (*shoot_mode < 2)
                {
                    *shoot_mode += 1;
                }
                else
                {
                    *damage += 1;
                }
            }
            else if (tmp->item.exclusive_info == 2) {
                if (hero->lives<9)
                {
                    hero->lives += 1;
                }
            }
            delete_node(buffs, tmp);
            tmp = *buffs;
        }
        else
        {
            tmp = tmp->next;
        }
    }
}

/**
 *Funkcja wykrywaj�ca zderzenia wrog�w z pociskami.
 *
 *Funkcja sprawdza czy dosz�o do zderzenia wrog�w z pociskami. Je�li tak, nast�puje zmniejszenie ilo�ci �y�
 * danego wroga. Gdy ich ilo�� b�dzie r�wna lub mniejsza od 0, zostanie wylosowana liczba decyduj�ca o tym, czy nast�pi
 * upuszczenie wzmocnienia. Dodatkowo licznik score zlicza punkty po zabiciu wroga.
 *@param enemies struktura przechowuj�ca parametry wrog�w
 *@param enemies_number ilo�� wrog�w na ekranie
 *@param shots podw�jny wska�nik na list� przechowuj�c� pociski
 *@param buffs podw�jny wska�nik na list� przechowuj�c� wzmocnienia
 *@param score ilo�� punkt�w gracza
 *@see check_hero_hitbox() , check_hero_buff_pickup()
 */
void check_enemy_hitbox(struct ENEMIES* enemies, int enemies_number, struct dll_node** shots, struct dll_node** buffs, long int*score) {
    struct dll_node* tmp;
    int random;
    for (int i = 0; i < enemies_number; i++)
    {
        tmp = *shots;
        if (enemies[i].life > 0)
        {
            while (tmp)
            {
                if ((tmp->item.y >= enemies[i].y && (tmp)->item.y <= enemies[i].y + enemies[i].height) && ((tmp)->item.x >= enemies[i].x && (tmp)->item.x <= enemies[i].x + enemies[i].width)
                    || (tmp->item.y >= enemies[i].y && (tmp)->item.y <= enemies[i].y + enemies[i].height) && ((tmp)->item.x + SHOT_WIDTH >= enemies[i].x && (tmp)->item.x + SHOT_WIDTH <= enemies[i].x + enemies[i].width))
                {

                    enemies[i].life -= tmp->item.exclusive_info;
                    al_play_sample(hit_sound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    delete_node(shots, tmp);
                    if(enemies[i].life<=0){
                        *score += SCORE_PER_ENEMY;
                        random = rand() % 1600;
                        if (random % 20 == 0) {
                            buff_init(buffs, enemies[i]);
                        }
                    }
                    tmp = *shots;
                }
                else
                {
                    tmp = tmp->next;
                }

            }
        }

    }

}


