#ifndef MOVIES_H
#define MOVIES_H
#define MAX_MOVIES 1000

#include <stdbool.h>
typedef enum {
    Action,
    Adventure,
    Animation,
    Biography,
    Comedy,
    Crime,
    Drama,
    Family,
    Fantasy,
    History,
    Horror,
    Music,
    Musical,
    Mystery,
    Romance,
    Scifi,
    Sport,
    Thriller,
    War,
    GENRE_COUNT
} Genre;

typedef struct {
    int code;
    char title[100];
    Genre genre;
    char description[501];
    char director[100];
    char actors[10][100];
    int num_actors;
    int year;
    int duration;
    float rating;
    int favorite;
    float revenue;
} Movie;

// Declaração do array de nomes de gêneros
extern const char *genre_names[GENRE_COUNT];

// Funções utilitárias
void clear_screen();
void clear_input_buffer();
int get_valid_int(const char *prompt, int min, int max);
float get_valid_float(const char *prompt, float min, float max);
int find_available_code(Movie movies[], int total);

// Funções de ordenação
void bubble_sort_code(Movie movies[], int total);
void bubble_sort_rating(Movie movies[], int total);
void bubble_sort_title(Movie movies[], int total);

// Funções de listagem
void list_all_movies(Movie movies[], int total);

// Funções de pesquisa
void search_movie(Movie movies[], int total, int option);

// Funções de visualização
void show_movie_details(int code, Movie movies[], int total);
int binary_search(int code, Movie movies[], int total);

// Funções de adição
void add_movie(Movie movies[], int *total, Movie new_movie);
void add_movie_interactive(Movie movies[], int *total);

// Funções de arquivo
int load_movies_from_csv(const char *filename, Movie movies[], int max_movies);
int save_movies_to_csv(const char *filename, Movie movies[], int total);

// Funções auxiliares
Genre string_to_genre(const char *genre_str);
const char* genre_to_string(Genre genre);

// Função para remover duplicados
void remove_duplicate_movies(Movie movies[], int *total);

// Funções de alteração
void alter_movie(Movie movies[], int *total, Movie new_info);
void alter_movie_interactive(Movie movies[], int *total);

// Funções de menu
void search_movie_menu(Movie movies[], int total);
void show_movie_menu(Movie movies[], int total);
void import_movies_from_file(Movie movies[], int *total);
void export_movies_to_file(Movie movies[], int total);
#endif