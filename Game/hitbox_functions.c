#include "game_header.h"
/** \file hitbox_functions.c
 * Plik Ÿród³owy hitbox_functions.
 * Zawiera funkcje odpowiadaj¹ce za wykrywanie zderzeñ obiektów.
 */

 /**
 *Funkcja wykrywaj¹ca zderzenia bohatera z pociskami.
 *
 *Funkcja sprawdza czy dosz³o do zderzenia bohatera z pociskami. Jeœli tak, nastêpuje zmniejszenie iloœci ¿yæ
 * bohatera oraz zwrócenie przez funkcje iloœci klatek, w czasie których bêdzie on niewra¿liwy na ataki. 
 *@param hero struktura przechowuj¹ca parametry bohatera
 *@param enemy_shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski wrogów
 *@return 90 - iloœæ klatek nierwa¿liwoœci jeœli bohater zosta³ trafiony
 *@return 0 - iloœæ klatek nierwa¿liwoœci jeœli bohater nie zosta³ trafiony
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
 *Funkcja sprawdzaj¹ca zebranie wzmocnienia przez bohatera.
 *
 *Funkcja sprawdza czy dosz³o do zderzenia bohatera z wzmocnieniem. Jeœli tak, nastêpuje jego realizacja.
 * W zale¿noœci od typu wzmocnienia jest to tymczasowa niewra¿liwoœæ bohatera na otrzymywane ataki,
 * dodatkowe ¿ycie lub wzmocnienie zadawanych obra¿eñ / zwiêkszenie iloœci wystrzeliwanych pocisków.
 *@param hero struktura przechowuj¹ca parametry bohatera
 *@param buffs podwójny wskaŸnik na listê przechowuj¹c¹ wzmocnienia
 *@param shoot_mode tryb strzelania
 *@param shield liczba klatek aktywnoœci tarczy
 *@param damage aktualna wartoœæ zadawanych obra¿eñ
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
 *Funkcja wykrywaj¹ca zderzenia wrogów z pociskami.
 *
 *Funkcja sprawdza czy dosz³o do zderzenia wrogów z pociskami. Jeœli tak, nastêpuje zmniejszenie iloœci ¿yæ
 * danego wroga. Gdy ich iloœæ bêdzie równa lub mniejsza od 0, zostanie wylosowana liczba decyduj¹ca o tym, czy nast¹pi
 * upuszczenie wzmocnienia. Dodatkowo licznik score zlicza punkty po zabiciu wroga.
 *@param enemies struktura przechowuj¹ca parametry wrogów
 *@param enemies_number iloœæ wrogów na ekranie
 *@param shots podwójny wskaŸnik na listê przechowuj¹c¹ pociski
 *@param buffs podwójny wskaŸnik na listê przechowuj¹c¹ wzmocnienia
 *@param score iloœæ punktów gracza
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


