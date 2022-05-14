#include "game_header.h"
/** \file menu_and_display_functions.c
 * Plik Ÿród³owy menu_and_display_functions.
 * Zawiera funkcje odpowiedzialne za obs³ugê menu, okna i dŸwiêków.
 */

menu_choice = 0;
select = 1;

/**
*Funka sprawdzaj¹ca pomyœlnoœæ wykonanej inizjalizacji.
*
* Funkcja wyœwietla komunikat jeœli nast¹pi³ problem przy inicjalizacji.
*/
void init_check(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

/**
 *Funkcja tworz¹ca okno i bitmapê t³a.
 *
 *Funkcja tworzy okno i bitmapê t³a i jednoczeœnie sprawdza poprawnoœæ wykonania tych instrukcji..
 */
void display_init()
{
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    init_check(display, "display");
    init_check(al_init_image_addon(), "image addon");
    background = al_load_bitmap("data/images/background.png");
    init_check(background, "background");
}
/**
 *Funkcja niszcz¹ca okno i bitmapê t³a.
 *
 *Funkcja niszczy okno i bitmapê t³a przed zakoñczeniem programu.
 */
void display_deinit()
{
    al_destroy_bitmap(background);
    al_destroy_display(display);
}

/**
 *Funkcja inicjalizuj¹ca dŸwiêki gry.
 *
 *Funkcja inicjalizuje wszystkie dŸwiêki u¿ywane w trakcie rozgrywki i jednoczeœnie sprawdza poprawnoœæ
 * wykonania tych instrukcji.
 */
void ingame_music_init()
{
    ingame = al_load_audio_stream("data/sounds/ingame.ogg", 2, 2048);
    init_check(ingame, "ingame soundtrack");
    al_set_audio_stream_playmode(ingame, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(ingame, al_get_default_mixer());

    gun_sound = al_load_sample("data/sounds/shoot.wav");
    init_check(gun_sound, "gun sound");

    hit_sound = al_load_sample("data/sounds/hit.wav");
    init_check(hit_sound, "hit sound");
}



/**
 *Funkcja inicjalizuj¹ca bitmapy i dŸwiêki do menu gry.
 *
 *Funkcja inicjalizuje wszystkie bitmapy i dŸwiêki u¿ywane w menu gry i jednoczeœnie sprawdza poprawnoœæ
 * wykonania tych instrukcji.
 */
void menu_init()
{
    menu = al_load_bitmap("data/images/menu.png");
    init_check(menu, "menu");

    controls = al_load_bitmap("data/images/controls.png");
    init_check(controls, "controls");

    score = al_load_bitmap("data/images/score.png");
    init_check(score, "score");

    
    menu_soundtrack = al_load_audio_stream("data/sounds/menu_soundtrack.ogg", 2, 2048);
    init_check(menu_soundtrack, "menu soundtrack");
    al_set_audio_stream_playmode(menu_soundtrack, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(menu_soundtrack, al_get_default_mixer());
    
    menu_sound = al_load_sample("data/sounds/menu_sound.wav");
    init_check(menu_sound, "menu sound");
}

/**
 *Funkcja rysuj¹ca menu gry.
 *
 *Funkcja rysuje wszystkie elementy menu gry. Do odczytywania tablicy wyników korzysta z obs³ugi pliku txt.
 * @param fontm czcionka wykorzystywana w grze
 */
void draw_menu(ALLEGRO_FONT* fontm)
{
    if (menu_choice == 0)
    {

        al_draw_bitmap(menu, 0, 0, 0);
        if (select == 1) al_draw_text(fontm, al_map_rgb(227, 66, 71),
            DISPLAY_WIDTH / 2 - al_get_text_width(fontm, "GRAJ") / 2, 268, 0, "GRAJ");
        else al_draw_text(fontm, al_map_rgb(255, 255, 255),
            DISPLAY_WIDTH / 2 - al_get_text_width(fontm, "GRAJ") / 2, 269, 0, "GRAJ");
        if (select == 2) al_draw_text(fontm, al_map_rgb(227, 66, 71),
            DISPLAY_WIDTH / 2 - al_get_text_width(fontm, "STEROWANIE") / 2, 326, 0, "STEROWANIE");
        else al_draw_text(fontm, al_map_rgb(255, 255, 255),
            DISPLAY_WIDTH / 2 - al_get_text_width(fontm, "STEROWANIE") / 2, 327, 0, "STEROWANIE");
        if (select == 3) al_draw_text(fontm, al_map_rgb(227, 66, 71),
            DISPLAY_WIDTH / 2 - al_get_text_width(fontm, "WYNIKI") / 2, 386, 0, "WYNIKI");
        else al_draw_text(fontm, al_map_rgb(255, 255, 255),
            DISPLAY_WIDTH / 2 - al_get_text_width(fontm, "WYNIKI") / 2, 387, 0, "WYNIKI");
    }
    if (menu_choice == 2)
    {
        al_draw_bitmap(controls, 0, 0, 0);
    }
    if (menu_choice == 3)
    {
#pragma warning(suppress : 4996)
        FILE* file = fopen("LeaderBoard.txt", "r");
        char letter;
        char scores[4][USERNAME_WORD_SIZE + 50];
        int j = 0;
        int i = 0;
        if (file) {
            while (!feof(file))
            {
#pragma warning(suppress : 4996)
                fscanf(file, "%c", &letter);
                if (letter == '\n') {

                    
                    i++;
                    j = 0;
                }
                else if (letter != '\0')
                {
                    scores[i][j] = letter;
                    j += 1;
                }

            }
            
        }

        al_draw_bitmap(score, 0, 0, 0);
        al_draw_text(fontm, al_map_rgb(255, 255, 255), 410, 333, 0, scores[0]);
        al_draw_text(fontm, al_map_rgb(255, 255, 255), 410, 367,0, scores[1]);
        al_draw_text(fontm, al_map_rgb(255, 255, 255), 410, 401, 0, scores[2]);
        fclose(file);
    }
    al_flip_display();
}

/**
 *Funkcja niszcz¹ca elementy menu gry.
 *
 *Funkcja niszczy bitmapy oraz dŸwiêki z menu gry.
 */
void menu_deinit()
{
    al_destroy_sample(menu_sound);
    al_destroy_bitmap(menu);
    al_destroy_bitmap(controls);
    al_destroy_bitmap(score);
    al_destroy_audio_stream(menu_soundtrack);
}

/**
 *Funkcja zapisuj¹ca wyniki gry.
 *
 *Funkcja zapisuje najlepsze wyniki do pliku tekstowego.
 * @param player_score liczba uzyskanych punktów w trakcie rozgrywki
 * @param username[] nazwa gracza
 */
void save_score(long int player_score, char username[USERNAME_WORD_SIZE]) {
    FILE* file = NULL;
    char scores[4][USERNAME_WORD_SIZE + 50];
    char letter;
    char tmp1[USERNAME_WORD_SIZE + 50];
    int i = 0;
    int j = 0;
    int g = 3;
    int counter = 0;
    int read_score[3];
    char player_score_char[USERNAME_WORD_SIZE + 50];
#pragma warning(suppress : 4996)
    sprintf(player_score_char, "%d ", player_score);
#pragma warning(suppress : 4996)
    strcpy(tmp1, player_score_char);
#pragma warning(suppress : 4996)
    strcat(tmp1, username);
#pragma warning(suppress : 4996)
    strcat(tmp1, "\n");
#pragma warning(suppress : 4996)
    file = fopen("LeaderBoard.txt", "r");
    if (file) {
        while (!feof(file))
        {
#pragma warning(suppress : 4996)
            fscanf(file, "%c", &letter);
            if (letter == '\n') {

                scores[i][j] = letter;
                i++;
                j = 0;
            }
            else if (letter != '\0')
            {
                scores[i][j] = letter;
                j += 1;
            }


        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                read_score[i] = atoi(scores[i]);
                printf("%c", scores[i][j]);
                if (scores[i][j] == '\n') {
                    break;
                }
            }

        }
        fclose(file);
#pragma warning(suppress : 4996)
        for (int i = 0; i < 3; i++)
        {

            printf("\nRead_score: %d      Player_score: %d", read_score[i], player_score);
            if (read_score[i] < player_score) {
                printf("\n%d", player_score);
                g = i;
                break;
            }
        }
        for (int i = 2; i >= g; i--) {
#pragma warning(suppress : 4996)
            strncpy(scores[i + 1], scores[i], USERNAME_WORD_SIZE + 50);
        }
#pragma warning(suppress : 4996)
        strcpy(scores[g], tmp1);
    }
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 50; j++)
        {

            printf("%c", scores[i][j]);
            if (scores[i][j] == '\n') {
                break;
            }
        }

    }
#pragma warning(suppress : 4996)
    file = fopen("LeaderBoard.txt", "w+");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 50; j++)
        {
#pragma warning(suppress : 4996)
            fprintf(file, "%c", scores[i][j]);
            if (scores[i][j] == '\n') {
                break;
            }
        }

    }
    fclose(file);

}

