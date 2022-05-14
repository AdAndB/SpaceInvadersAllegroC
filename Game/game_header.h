
#ifndef GAME_HEADER_H_INCLUDED
#define GAME_HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

/** \file game_header.h
 * Plik nag³ówkowy game_header.
 * Zawiera definicje sta³ych, zmiennych globalnych oraz deklaracje funkcji wykorzystanych w programie.
 */

 /**
 *Struktura przechowuj¹ca parametry wzmocnieñ lub pocisków.
 *
 *Struktura zawiera cztery pola. Pierwsze i drugie s³u¿y do przechowywania wspó³rzêdnych przedmiotu.
 * Trzeci zawiera informacje o szybkoœci, a czwarty o jego typie. Jeœli jest to pocisk to exclusive_info oznacza 
 * iloœæ zadawanych obra¿eñ. W przypadku, gdy jest to wzmocnienie exclusive_info informuje o jego rodzaju.
 */
struct MOVING_PARTICLE
{
    int x; ///<wspó³rzêdna x przedmiotu  
    int y; ///<wspó³rzêdna y przedmiotu  
    int speed; ///<szybkoœæ przedmiotu 
    int exclusive_info; ///<szczegó³owe informacje o rodzaju przedmiotu
};

/**
*Typ bazowy dwukierunkowej listy.
*
*Struktura zawiera trzy pola. Pierwsze pole s³u¿y do przechowywania wzmocnieñ lub pocisków.
* Dwa kolejne s¹ polami wskaŸnikowymi na nastêpny i poprzedni element.
*/
struct dll_node {
    struct MOVING_PARTICLE item; ///<przechowywany na liœcie przedmiot
    struct dll_node* next; ///<wskaŸnik na nastêpny element
    struct dll_node* prev; ///<wskaŸnik na poprzedni element
};

void append(struct dll_node** node, int exclusive_info, int x, int y, int speed);
int delete_node(struct dll_node** node, struct dll_node* to_delete);
void remove_list(struct dll_node** front);

//~~~~~~~   DISPLAY ~~~~~~~~
#define DISPLAY_WIDTH 960 ///<definicja sta³ej szerokoœci okna
#define DISPLAY_HEIGHT 720 ///<definicja sta³ej wysokoœci okna

ALLEGRO_DISPLAY* display; ///<wskaŸnik na okno programu
ALLEGRO_BITMAP* background; ///<wskaŸnik na bitmapê bêd¹c¹ t³em podczas rozgrywki
void init_check(bool test, const char* description);
void display_init();
void display_deinit();

//~~~~~~ MENU & SOUNDS  ~~~~~~~~
#define USERNAME_WORD_SIZE 20 ///<definicja sta³ej dla rozmiaru nazwy gracza
int menu_choice; ///<zmienna globalna oznaczaj¹ca aktualny segment gry
int select; ///<zmienna globalna oznaczaj¹ca wybór w menu

ALLEGRO_SAMPLE* gun_sound; ///<wskaŸnik na dŸwiêk wystrza³u
ALLEGRO_SAMPLE* hit_sound; ///<wskaŸnik na dŸwiêk trafienia pociskiem
ALLEGRO_AUDIO_STREAM* ingame; ///<wskaŸnik na muzykê podczas rozgrywki
ALLEGRO_BITMAP* menu; ///<wskaŸnik na bitmapê bêd¹c¹ t³em w menu gry
ALLEGRO_BITMAP* controls; ///<wskaŸnik na bitmapê bêd¹c¹ t³em w zak³adce sterowanie
ALLEGRO_BITMAP* score; ///<wskaŸnik na bitmapê bêd¹c¹ t³em w zak³adce wyniki
ALLEGRO_AUDIO_STREAM* menu_soundtrack; ///<wskaŸnik na muzykê w menu gry
ALLEGRO_SAMPLE* menu_sound; ///<wskaŸnik na dŸwiêk wyboru w menu gry

void ingame_music_init();
void menu_init();
void draw_menu(ALLEGRO_FONT* fontm);
void menu_deinit();
void save_score(long int player_score, char username[USERNAME_WORD_SIZE]);

//~~~~~~   KEYBOARD  ~~~~~~~~
#define KEY_SEEN 1 ///<definicja sta³ej oznaczaj¹cej wciœniêcie klawisza
#define KEY_RELEASED 2 ///<definicja sta³ej oznaczaj¹cej zwolnienie klawisza
unsigned char key[ALLEGRO_KEY_MAX]; ///<deklaracja tablicy wszystkich klawiszy

void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);

//~~~~~~ OBJECTS ~~~~~~~~ 

/**
*Struktura obiektów wystêpuj¹cych podczas rozgrywki.
*
*Struktura zawiera wskaŸniki na bitmapy modeli postaci oraz innych przedmiotów wystêpuj¹cych w grze.
*/
struct OBJECTS
{
    ALLEGRO_BITMAP* buff[3]; ///<tablica wskaŸników na bitmapy wzmocnieñ
    ALLEGRO_BITMAP* hero_after_hit; ///<wskaŸnik na bitmapê bêd¹c¹ modelem bohatera po otrzymaniu obra¿eñ
    ALLEGRO_BITMAP* shielded_hero; ///<wskaŸnik na bitmapê bêd¹c¹ modelem bohatera w stanie nierwa¿liwoœci na atak
    ALLEGRO_BITMAP* hero; ///<wskaŸnik na bitmapê bêd¹c¹ modelem bohatera
    ALLEGRO_BITMAP* enemy1; ///<wskaŸnik na bitmapê bêd¹c¹ modelem wrogów
    ALLEGRO_BITMAP* item; ///<wskaŸnik na bitmapê bêd¹c¹ modelem pocisku wroga
    ALLEGRO_BITMAP* bullet; ///<wskaŸnik na bitmapê bêd¹c¹ modelem pocisku bohatera
}objects;

void objects_init();
void objects_deinit();

//~~~~~~ HERO ~~~~~~~~ 
#define HERO_WIDTH 108 ///<definicja sta³ej szerokoœci bohatera
#define HERO_HEIGHT 160 ///<definicja sta³ej wysokoœci bohatera

void hero_init(struct HERO* hero);
void hero_update(struct HERO* hero);
void hero_update(struct HERO* hero);

/**
*Struktura przechowuj¹ca parametry bohatera.
*
*Struktura zawiera pola z parametrami bohatera: po³o¿enia, szybkoœci, iloœci ¿yæ.
*/
struct HERO
{
    int x; ///<wspó³rzêdna x bohatera  
    int y; ///<wspó³rzêdna y bohatera 
    int speed; ///<szybkoœæ poruszania siê bohatera 
    int lives; ///<iloœæ ¿yæ bohatera 
};

//~~~~~~ ENEMIES ~~~~~~~~  

/**
*Struktura przechowuj¹ca parametry wrogów.
*
*Struktura zawiera pola z parametrami wrogów: po³o¿enia, szybkoœci, iloœci ¿yæ, szerokoœæ, wysokoœæ.
*/
struct ENEMIES
{
    float x; ///<wspó³rzêdna x wroga  
    float y; ///<wspó³rzêdna y wroga 
    float speed; ///<szybkoœæ wroga 
    int life; ///<iloœæ ¿yæ wroga 
    int width; ///<szerokoœæ wroga 
    int height; ///<wysokoœæ wroga 

};

//~~~~~~ SHOTS AND BUFFS ~~~~~~~~ 
#define SHOT_SPEED 5 ///<definicja sta³ej szybkoœci pocisków
#define FRAMES_BETWEEN_SHOTS 25  ///<definicja sta³ej iloœci klatek odstêpu pomiêdzy strza³ami bohatera
#define SHOT_LENGTH 24 ///<definicja sta³ej d³ugoœci pocisku bohatera
#define SHOT_WIDTH 12 ///<definicja sta³ej szerokoœci pocisku bohatera
#define CACTUS_SHOT_SIZE 24 ///<definicja sta³ej szerokoœci i d³ugoœci pocisku wroga
#define BUFF_HEIGHT 48 ///<definicja sta³ej wysokoœci przedmiotów wzmacniaj¹cych
#define BUFF_WIDTH 48 ///<definicja sta³ej szerokoœci przedmiotów wzmacniaj¹cych
#define BUFF_SPEED 1 ///<definicja sta³ej szybkoœci spadania przedmiotów wzmacniaj¹cych


int shot_init(struct dll_node** player_shots, int damage, struct HERO hero, int speed, int shoot_mode);
void shots_update(struct dll_node** shots, struct dll_node* node);
void shots_draw(struct dll_node** shots);
void enemy_shots_draw(struct dll_node** shots);

void buff_init(struct dll_node** buffs, struct ENEMIES enemy);
void buffs_update(struct dll_node** buffs, struct dll_node* node);
void buffs_draw(struct dll_node** buffs);

//~~~~~~~~ ENEMIES ~~~~~~~~
#define BORDER 20 ///<definicja sta³ej odleg³oœci od ramek okna ograniczaj¹cej ruch wrogów
#define JUMP 20 ///<definicja sta³ej odleg³oœci skoku wrogów do kolejnego rzêdu
#define ENEMY_HEIGHT 70 ///<definicja sta³ej wysokoœci wrogów
#define ENEMY_WIDTH 42 ///<definicja sta³ej szerokoœci wrogów
#define ENEMY_FIRE_RATE 60 ///<definicja sta³ej iloœci klatek odstêpu pomiêdzy strza³ami wrogów
#define SCORE_PER_ENEMY 200 ///<definicja sta³ej iloœci punktów otrzymywanych za eliminacjê wroga

void enemies_set(struct ENEMIES* enemies, int columns, int rows, int width, int height,int health);
void enemies_draw(struct ENEMIES* enemies, int enemies_number);
void enemies_update(struct ENEMIES* enemies, int enemies_number, int* alive,struct HERO *hero);
void enemy_shoot(struct ENEMIES* enemies, int enemies_number, int alive, struct dll_node** enemy_shots, int speed);

//~~~~~~~~ HITBOX CHECKERS ~~~~~~~~

int check_hero_hitbox(struct HERO* hero, struct dll_node** enemy_shots);
void check_hero_buff_pickup(struct HERO* hero, struct dll_node** buffs, int* shoot_mode, int* shield, int* damage);
void check_enemy_hitbox(struct ENEMIES* enemies, int enemies_number, struct dll_node** shots, struct dll_node** buffs, long int* score);

#endif
