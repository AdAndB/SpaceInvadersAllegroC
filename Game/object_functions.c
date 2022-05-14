#include "game_header.h"
/** \file object_functions.c
 * Plik Ÿród³owy object_functions.
 * Zawiera funkcje steruj¹ce bitmapami wykorzystywanymi podczas rozgrywki.
 */

 /**
 *Funkcja inicjalizuj¹ca bitmapy wymagane do rygrywki.
 *
 *Funkcja inicjalizuje bitmapy do gry i jednoczeœnie sprawdza poprawnoœæ wykonania tych instrukcji.
 *@see objects_deinit()
 */
void objects_init()
{
    objects.buff[0] = al_load_bitmap("data/images/shield_buff.png");
    init_check(objects.buff[0], "shield_buff");

    objects.buff[1] = al_load_bitmap("data/images/bullet_buff.png");
    init_check(objects.buff[1], "bullet_buff");

    objects.buff[2] = al_load_bitmap("data/images/hp_boost.png");
    init_check(objects.buff[2], "hp_boost");

    objects.hero_after_hit = al_load_bitmap("data/images/hero_after_hit.png");
    init_check(objects.hero_after_hit, "hero_after_hit");

    objects.shielded_hero = al_load_bitmap("data/images/shielded_hero.png");
    init_check(objects.shielded_hero, "shielded_hero");

    objects.hero = al_load_bitmap("data/images/hero.png");
    init_check(objects.hero, "hero");

    objects.enemy1 = al_load_bitmap("data/images/mr_cactus.png");
    init_check(objects.enemy1, "mr_cactus");

    objects.item = al_load_bitmap("data/images/c_shot.png");
    init_check(objects.item, "cactus_shot");

    objects.bullet = al_load_bitmap("data/images/bullet.png");
    init_check(objects.bullet, "bullet");
}

/**
 *Funkcja niszcz¹ca bitmapy wykorzystywane podczas rygrywki.
 *
 *Funkcja niszczy bitmapy, które nie s¹ ju¿ wymagane do dzia³ania programu.
 *@see objects_init()
 */
void objects_deinit()
{
    al_destroy_bitmap(objects.buff[0]);
    al_destroy_bitmap(objects.buff[1]);
    al_destroy_bitmap(objects.buff[2]);
    al_destroy_bitmap(objects.shielded_hero);
    al_destroy_bitmap(objects.hero_after_hit);
    al_destroy_bitmap(objects.hero);
    al_destroy_bitmap(objects.enemy1);
    al_destroy_bitmap(objects.item);
    al_destroy_bitmap(objects.bullet);
}