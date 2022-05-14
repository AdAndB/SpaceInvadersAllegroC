#include <stdio.h>
#include <stdlib.h>
#include "game_header.h"
/** \file main.c
 * Plik Ÿród³owy main.
 * Jest to g³ówny plik programu.
 */

 /**
*G³ówna funkcja main programu.
*
* Na pocz¹tku w funkcji main inicjalizowane s¹ wszystkie niezbêdne elementy. Nastêpnie rozpoczyna siê g³ówna
* pêtla gry, w której wywo³ywane s¹ funkcje zawarte w innych plikach Ÿród³owych.
*/
int main()
{
    srand(time(0));
    init_check(al_init(), "allegro library");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    init_check(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    init_check(queue, "queue");

    init_check(al_init_ttf_addon(), "ttf addon");
    ALLEGRO_FONT* font = al_load_ttf_font("data/fonts/Pixeboy.ttf", 30, 0);
    init_check(font, "font");

    init_check(al_install_audio(), "audio");
    init_check(al_init_acodec_addon(), "acodec addon");
    init_check(al_reserve_samples(10), "reserve samples");

    bool game_start = false;
    bool score_input_screen = false;
    char healthDisplay[255];
    char healthWord[] = "HP: ";
    char hpNumberDisplay[3];


    char scoreDisplay[255];
    char scoreWord[] = "Score: ";
    char scoreNumberDisplay[50];

    char username[USERNAME_WORD_SIZE];
    char playerStarterName[] = "nazwa";
#pragma warning(suppress : 4996)
    strcpy(username, playerStarterName);

    char letter[10];
    int spot = 10;

    int invincibilityFrames = 0;
    int damage = 1;
    int shield = 0;
    int shoot_mode = 0;
    struct HERO hero;
    long int player_score = 0;
    hero_init(&hero);
    struct dll_node* player_shots = NULL;
    struct dll_node* enemy_shots = NULL;
    struct dll_node* buffs = NULL;
    int columns = 12;
    int rows = 1;
    int enemy_health = 2;
    struct ENEMIES* enemies;
    enemies = (struct ENEMIES*)malloc(sizeof(struct ENEMIES) * columns * rows);


    display_init();
    keyboard_init();
    objects_init();
    menu_init();
    al_set_window_title(display, "Saloon Shooter");
    al_set_display_icon(display, objects.enemy1);

    int alive = columns * rows;
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;


    int shotLimiter = 0;
    int enemiesShotTimer = 0;

    int n = 0;

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);


        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (game_start) {
            }
            if (game_start)
            {
                if (hero.lives <= 0)
                {
                    rows = 0;
                    damage = 1;
                    shoot_mode = 0;
                    shield = 0;
                    enemy_health = 2;

                    score_input_screen = true;
                    remove_list(&player_shots);
                    remove_list(&enemy_shots);
                    remove_list(&buffs);
                    game_start = false;
                    al_destroy_audio_stream(ingame);
                    menu_init();
                    break;
                }
                if (alive <= 0) {
                    free(enemies);
                    if (rows < 3) {

                        rows += 1;
                    }
                    else
                    {
                        enemy_health += 1;
                    }
                    enemies = (struct ENEMIES*)malloc(sizeof(struct ENEMIES) * columns * rows);
                    remove_list(&player_shots);
                    remove_list(&enemy_shots);
                    enemies_set(enemies, columns, rows, ENEMY_WIDTH, ENEMY_HEIGHT, enemy_health);
                }
                if (shield <= 0 && invincibilityFrames <= 0) {
                    invincibilityFrames = check_hero_hitbox(&hero, &enemy_shots);
                }
                check_hero_buff_pickup(&hero, &buffs, &shoot_mode, &shield, &damage);
                check_enemy_hitbox(enemies, columns * rows, &player_shots, &buffs, &player_score);
                hero_update(&hero);
                enemies_update(enemies, columns * rows, &alive, &hero);
                if (shotLimiter == 0)
                {

                    shotLimiter = shot_init(&player_shots, damage, hero, SHOT_SPEED, shoot_mode);

                }
                else if (shotLimiter >= FRAMES_BETWEEN_SHOTS)
                {
                    shotLimiter = 0;
                }
                else if (shotLimiter > 0)

                {

                    shotLimiter += 1;
                }
                if (enemiesShotTimer >= ENEMY_FIRE_RATE)
                {
                    enemy_shoot(enemies, columns * rows, alive, &enemy_shots, -SHOT_SPEED);
                    enemiesShotTimer = 0;
                }
                else
                {
                    enemiesShotTimer += 1;
                }

                shots_update(&player_shots, player_shots);
                shots_update(&enemy_shots, enemy_shots);
                buffs_update(&buffs, buffs);

                if (key[ALLEGRO_KEY_ESCAPE]) {
                    hero.lives = 0;
                }
            }


            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (game_start)
            {
                break;
            }
            else if (score_input_screen)
            {

                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    if (spot < USERNAME_WORD_SIZE - 1)
                    {
                        username[spot] = 32;
                        spot += 1;
                    }

                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                    if (spot > 0) {
                        spot -= 1;
                        username[spot] = '\0';
                    }
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    save_score(player_score, username);
                    player_score = 0;
                    score_input_screen = false;
                }
                else
                {
                    if (spot < USERNAME_WORD_SIZE - 1) {
#pragma warning(suppress : 4996)
                        sprintf(letter, "%c", event.keyboard.keycode + 64);
#pragma warning(suppress : 4996)
                        strcat(username, letter);
                        spot += 1;
                    }
                }
                break;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                if (select == 1)
                {
                    game_start = true;
                    menu_deinit();
                    hero_init(&hero);
                    enemies_set(enemies, columns, rows, ENEMY_WIDTH, ENEMY_HEIGHT, enemy_health);
                    ingame_music_init();

                }
                else if (select == 2)
                {
                    menu_choice = 2;
                }
                else if (select == 3)
                {
                    menu_choice = 3;
                }
            }
            if (menu_choice == 0)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                    al_play_sample(menu_sound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if (select > 1) select -= 1;
                    else select = 3;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    al_play_sample(menu_sound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if (select < 3) select += 1;
                    else select = 1;
                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                if (menu_choice == 2 || menu_choice == 3)
                {
                    menu_choice = 0;
                }
                else
                {
                    done = true;
                }
            }

            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        keyboard_update(&event);

        if (redraw && al_is_event_queue_empty(queue))
        {
            if (score_input_screen)
            {

                al_draw_bitmap(background, 0, 0, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2 - al_get_text_width(font, "Zdobyte punkty:") / 2, 10, 0, "Zdobyte punkty:");
                al_draw_text(font, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2 - al_get_text_width(font, scoreNumberDisplay) / 2, 40, 0, scoreNumberDisplay);
                al_draw_text(font, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2 - al_get_text_width(font, username) / 2, DISPLAY_HEIGHT / 2 - 10, 0, username);
                al_flip_display();
            }
            else if (!game_start)
            {
                draw_menu(font);
            }
            else if (game_start)
            {
#pragma warning(suppress : 4996)
                sprintf(scoreNumberDisplay, "%ld", player_score);
#pragma warning(suppress : 4996)
                strcpy(scoreDisplay, scoreWord);
#pragma warning(suppress : 4996)
                strcat(scoreDisplay, scoreNumberDisplay);


#pragma warning(suppress : 4996)
                sprintf(hpNumberDisplay, "%d", hero.lives);
#pragma warning(suppress : 4996)   
                strcpy(healthDisplay, healthWord);
#pragma warning(suppress : 4996)
                strcat(healthDisplay, hpNumberDisplay);
                al_draw_bitmap(background, 0, 0, 0);
                if (hero.lives > 0)
                {
                    if (shield > 0) {
                        al_draw_bitmap(objects.shielded_hero, hero.x, hero.y, 0);
                        shield -= 1;
                    }
                    else
                    {
                        if (invincibilityFrames > 0)
                        {
                            if (invincibilityFrames % 10 <= 4) {
                                al_draw_bitmap(objects.hero_after_hit, hero.x, hero.y, 0);
                            }
                            invincibilityFrames -= 1;
                        }
                        else
                        {
                            al_draw_bitmap(objects.hero, hero.x, hero.y, 0);
                        }
                    }

                }
                shots_draw(&player_shots);
                enemy_shots_draw(&enemy_shots);
                enemies_draw(enemies, columns * rows);
                buffs_draw(&buffs);
                al_draw_text(font, al_map_rgb(0, 0, 0), 5, 5, 0, scoreDisplay);
                al_draw_text(font, al_map_rgb(116, 180, 61), 4, 4, 0, scoreDisplay);
                al_draw_text(font, al_map_rgb(0, 0, 0), DISPLAY_WIDTH - al_get_text_width(font, healthDisplay) - 4, DISPLAY_HEIGHT - 21, 0, healthDisplay);
                al_draw_text(font, al_map_rgb(209, 85, 70), DISPLAY_WIDTH - al_get_text_width(font, healthDisplay) - 5, DISPLAY_HEIGHT - 22, 0, healthDisplay);
                al_flip_display();
            }

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    display_deinit();
    remove_list(&player_shots);
    remove_list(&enemy_shots);
    remove_list(&buffs);
    free(enemies);
    return 0;
}