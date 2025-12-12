#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "movies.h"

#define CSV_FILE "files/movies_all.csv"

void display_menu();

int main() {
    setlocale(LC_ALL, "pt_PT.UTF-8");
    
    Movie movies[MAX_MOVIES];
    int total_movies = 0;
    int option;
    
    clear_screen();
    printf("===========================================\n");
    printf("     SISTEMA DE GESTAO DE FILMES\n");
    printf("===========================================\n\n");
    
    // Carregar filmes do CSV
    total_movies = load_movies_from_csv(CSV_FILE, movies, MAX_MOVIES);
    
    // Remover duplicados automaticamente
    if(total_movies > 0) {
        remove_duplicate_movies(movies, &total_movies);
    }
    
    if(total_movies == 0) {
        printf("AVISO: Nenhum filme carregado. O arquivo pode estar vazio ou nao existe.\n");
        printf("Voce pode adicionar filmes manualmente.\n");
    }
    
    do {
        display_menu();
        option = get_valid_int("Escolha uma opcao (0-6): ", 0, 6);
        
        switch(option) {
            case 1:
                clear_screen();
                list_all_movies(movies, total_movies);
                break;
                
            case 2:
                clear_screen();
                search_movie_menu(movies, total_movies);
                break;
                
            case 3:
                clear_screen();
                show_movie_menu(movies, total_movies);
                break;
                
            case 4:
                clear_screen();
                add_movie_interactive(movies, &total_movies);
                break;
                
            case 5:
                clear_screen();
                if(total_movies > 0) {
                    printf("=== FILMES FAVORITOS ===\n");
                    printf("%-8s | %-50s | %-15s | %-6s\n", 
                           "Codigo", "Titulo", "Genero", "Nota");
                    printf("---------|----------------------------------------------------|-----------------|--------\n");
                    
                    int favorite_count = 0;
                    for(int i = 0; i < total_movies; i++) {
                        if(movies[i].favorite) {
                            printf("%-8d | %-50.50s | %-15.15s | %-6.1f\n", 
                                   movies[i].code, movies[i].title, 
                                   genre_to_string(movies[i].genre), movies[i].rating);
                            favorite_count++;
                        }
                    }
                    
                    if(favorite_count == 0) {
                        printf("Nenhum filme marcado como favorito.\n");
                    } else {
                        printf("\nTotal de favoritos: %d\n", favorite_count);
                    }
                } else {
                    printf("Nenhum filme cadastrado.\n");
                }
                
                printf("\nPressione Enter para continuar...");
                clear_input_buffer();
                getchar();
                break;
                
            case 6:
                clear_screen();
                if(save_movies_to_csv(CSV_FILE, movies, total_movies)) {
                    printf("Filmes salvos com sucesso em %s\n", CSV_FILE);
                }
                printf("\nPressione Enter para continuar...");
                clear_input_buffer();
                getchar();
                break;
                
            case 0:
                printf("\nDeseja salvar as alteracoes antes de sair? (S/N): ");
                char save;
                scanf(" %c", &save);
                clear_input_buffer();
                
                if(toupper(save) == 'S') {
                    save_movies_to_csv(CSV_FILE, movies, total_movies);
                }
                
                printf("\nObrigado por usar o Sistema de Gestao de Filmes!\n");
                printf("Total de filmes no sistema: %d\n", total_movies);
                break;
                
            default:
                printf("Opcao invalida!\n");
                break;
        }
        
    } while(option != 0);
    
    return 0;
}

void display_menu() {
    clear_screen();
    printf("===========================================\n");
    printf("            MENU PRINCIPAL\n");
    printf("===========================================\n");
    printf("1. Listar todos os filmes\n");
    printf("2. Pesquisar filmes\n");
    printf("3. Ver detalhes de um filme\n");
    printf("4. Adicionar novo filme\n");
    printf("5. Listar filmes favoritos\n");
    printf("6. Salvar filmes no arquivo\n");
    printf("0. Sair do programa\n");
    printf("===========================================\n");
}