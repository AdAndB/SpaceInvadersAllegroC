
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
 * Plik nag��wkowy game_header.
 * Zawiera definicje sta�ych, zmiennych globalnych oraz deklaracje funkcji wykorzystanych w programie.
 */

 /**
 *Struktura przechowuj�ca parametry wzmocnie� lub pocisk�w.
 *
 *Struktura zawiera cztery pola. Pierwsze i drugie s�u�y do przechowywania wsp�rz�dnych przedmiotu.
 * Trzeci zawiera informacje o szybko�ci, a czwarty o jego typie. Je�li jest to pocisk to exclusive_info oznacza 
 * ilo�� zadawanych obra�e�. W przypadku, gdy jest to wzmocnienie exclusive_info informuje o jego rodzaju.
 */
struct MOVING_PARTICLE
{
    int x; ///<wsp�rz�dna x przedmiotu  
    int y; ///<wsp�rz�dna y przedmiotu  
    int speed; ///<szybko�� przedmiotu 
    int exclusive_info; ///<szczeg�owe informacje o rodzaju przedmiotu
};

/**
*Typ bazowy dwukierunkowej listy.
*
*Struktura zawiera trzy pola. Pierwsze pole s�u�y do przechowywania wzmocnie� lub pocisk�w.
* Dwa kolejne s� polami wska�nikowymi na nast�pny i poprzedni element.
*/
struct dll_node {
    struct MOVING_PARTICLE item; ///<przechowywany na li�cie przedmiot
    struct dll_node* next; ///<wska�nik na nast�pny element
    struct dll_node* prev; ///<wska�nik na poprzedni element
};

void append(struct dll_node** node, int exclusive_info, int x, int y, int speed);
int delete_node(struct dll_node** node, struct dll_node* to_delete);
void remove_list(struct dll_node** front);

//~~~~~~~   DISPLAY ~~~~~~~~
#define DISPLAY_WIDTH 960 ///<definicja sta�ej szeroko�ci okna
#define DISPLAY_HEIGHT 720 ///<definicja sta�ej wysoko�ci okna

ALLEGRO_DISPLAY* display; ///<wska�nik na okno programu
ALLEGRO_BITMAP* background; ///<wska�nik na bitmap� b�d�c� t�em podczas rozgrywki
void init_check(bool test, const char* description);
void display_init();
void display_deinit();

//~~~~~~ MENU & SOUNDS  ~~~~~~~~
#define USERNAME_WORD_SIZE 20 ///<definicja sta�ej dla rozmiaru nazwy gracza
int menu_choice; ///<zmienna globalna oznaczaj�ca aktualny segment gry
int select; ///<zmienna globalna oznaczaj�ca wyb�r w menu

ALLEGRO_SAMPLE* gun_sound; ///<wska�nik na d�wi�k wystrza�u
ALLEGRO_SAMPLE* hit_sound; ///<wska�nik na d�wi�k trafienia pociskiem
ALLEGRO_AUDIO_STREAM* ingame; ///<wska�nik na muzyk� podczas rozgrywki
ALLEGRO_BITMAP* menu; ///<wska�nik na bitmap� b�d�c� t�em w menu gry
ALLEGRO_BITMAP* controls; ///<wska�nik na bitmap� b�d�c� t�em w zak�adce sterowanie
ALLEGRO_BITMAP* score; ///<wska�nik na bitmap� b�d�c� t�em w zak�adce wyniki
ALLEGRO_AUDIO_STREAM* menu_soundtrack; ///<wska�nik na muzyk� w menu gry
ALLEGRO_SAMPLE* menu_sound; ///<wska�nik na d�wi�k wyboru w menu gry

void ingame_music_init();
void menu_init();
void draw_menu(ALLEGRO_FONT* fontm);
void menu_deinit();
void save_score(long int player_score, char username[USERNAME_WORD_SIZE]);

//~~~~~~   KEYBOARD  ~~~~~~~~
#define KEY_SEEN 1 ///<definicja sta�ej oznaczaj�cej wci�ni�cie klawisza
#define KEY_RELEASED 2 ///<definicja sta�ej oznaczaj�cej zwolnienie klawisza
unsigned char key[ALLEGRO_KEY_MAX]; ///<deklaracja tablicy wszystkich klawiszy

void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);

//~~~~~~ OBJECTS ~~~~~~~~ 

/**
*Struktura obiekt�w wyst�puj�cych podczas rozgrywki.
*
*Struktura zawiera wska�niki na bitmapy modeli postaci oraz innych przedmiot�w wyst�puj�cych w grze.
*/
struct OBJECTS
{
    ALLEGRO_BITMAP* buff[3]; ///<tablica wska�nik�w na bitmapy wzmocnie�
    ALLEGRO_BITMAP* hero_after_hit; ///<wska�nik na bitmap� b�d�c� modelem bohatera po otrzymaniu obra�e�
    ALLEGRO_BITMAP* shielded_hero; ///<wska�nik na bitmap� b�d�c� modelem bohatera w stanie nierwa�liwo�ci na atak
    ALLEGRO_BITMAP* hero; ///<wska�nik na bitmap� b�d�c� modelem bohatera
    ALLEGRO_BITMAP* enemy1; ///<wska�nik na bitmap� b�d�c� modelem wrog�w
    ALLEGRO_BITMAP* item; ///<wska�nik na bitmap� b�d�c� modelem pocisku wroga
    ALLEGRO_BITMAP* bullet; ///<wska�nik na bitmap� b�d�c� modelem pocisku bohatera
}objects;

void objects_init();
void objects_deinit();

//~~~~~~ HERO ~~~~~~~~ 
#define HERO_WIDTH 108 ///<definicja sta�ej szeroko�ci bohatera
#define HERO_HEIGHT 160 ///<definicja sta�ej wysoko�ci bohatera

void hero_init(struct HERO* hero);
void hero_update(struct HERO* hero);
void hero_update(struct HERO* hero);

/**
*Struktura przechowuj�ca parametry bohatera.
*
*Struktura zawiera pola z parametrami bohatera: po�o�enia, szybko�ci, ilo�ci �y�.
*/
struct HERO
{
    int x; ///<wsp�rz�dna x bohatera  
    int y; ///<wsp�rz�dna y bohatera 
    int speed; ///<szybko�� poruszania si� bohatera 
    int lives; ///<ilo�� �y� bohatera 
};

//~~~~~~ ENEMIES ~~~~~~~~  

/**
*Struktura przechowuj�ca parametry wrog�w.
*
*Struktura zawiera pola z parametrami wrog�w: po�o�enia, szybko�ci, ilo�ci �y�, szeroko��, wysoko��.
*/
struct ENEMIES
{
    float x; ///<wsp�rz�dna x wroga  
    float y; ///<wsp�rz�dna y wroga 
    float speed; ///<szybko�� wroga 
    int life; ///<ilo�� �y� wroga 
    int width; ///<szeroko�� wroga 
    int height; ///<wysoko�� wroga 

};

//~~~~~~ SHOTS AND BUFFS ~~~~~~~~ 
#define SHOT_SPEED 5 ///<definicja sta�ej szybko�ci pocisk�w
#define FRAMES_BETWEEN_SHOTS 25  ///<definicja sta�ej ilo�ci klatek odst�pu pomi�dzy strza�ami bohatera
#define SHOT_LENGTH 24 ///<definicja sta�ej d�ugo�ci pocisku bohatera
#define SHOT_WIDTH 12 ///<definicja sta�ej szeroko�ci pocisku bohatera
#define CACTUS_SHOT_SIZE 24 ///<definicja sta�ej szeroko�ci i d�ugo�ci pocisku wroga
#define BUFF_HEIGHT 48 ///<definicja sta�ej wysoko�ci przedmiot�w wzmacniaj�cych
#define BUFF_WIDTH 48 ///<definicja sta�ej szeroko�ci przedmiot�w wzmacniaj�cych
#define BUFF_SPEED 1 ///<definicja sta�ej szybko�ci spadania przedmiot�w wzmacniaj�cych


int shot_init(struct dll_node** player_shots, int damage, struct HERO hero, int speed, int shoot_mode);
void shots_update(struct dll_node** shots, struct dll_node* node);
void shots_draw(struct dll_node** shots);
void enemy_shots_draw(struct dll_node** shots);

void buff_init(struct dll_node** buffs, struct ENEMIES enemy);
void buffs_update(struct dll_node** buffs, struct dll_node* node);
void buffs_draw(struct dll_node** buffs);

//~~~~~~~~ ENEMIES ~~~~~~~~
#define BORDER 20 ///<definicja sta�ej odleg�o�ci od ramek okna ograniczaj�cej ruch wrog�w
#define JUMP 20 ///<definicja sta�ej odleg�o�ci skoku wrog�w do kolejnego rz�du
#define ENEMY_HEIGHT 70 ///<definicja sta�ej wysoko�ci wrog�w
#define ENEMY_WIDTH 42 ///<definicja sta�ej szeroko�ci wrog�w
#define ENEMY_FIRE_RATE 60 ///<definicja sta�ej ilo�ci klatek odst�pu pomi�dzy strza�ami wrog�w
#define SCORE_PER_ENEMY 200 ///<definicja sta�ej ilo�ci punkt�w otrzymywanych za eliminacj� wroga

void enemies_set(struct ENEMIES* enemies, int columns, int rows, int width, int height,int health);
void enemies_draw(struct ENEMIES* enemies, int enemies_number);
void enemies_update(struct ENEMIES* enemies, int enemies_number, int* alive,struct HERO *hero);
void enemy_shoot(struct ENEMIES* enemies, int enemies_number, int alive, struct dll_node** enemy_shots, int speed);

//~~~~~~~~ HITBOX CHECKERS ~~~~~~~~

int check_hero_hitbox(struct HERO* hero, struct dll_node** enemy_shots);
void check_hero_buff_pickup(struct HERO* hero, struct dll_node** buffs, int* shoot_mode, int* shield, int* damage);
void check_enemy_hitbox(struct ENEMIES* enemies, int enemies_number, struct dll_node** shots, struct dll_node** buffs, long int* score);

#endif
