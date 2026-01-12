#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "movies.h"

void display_menu();

int main() {
    setlocale(LC_ALL, "pt_br.UTF-8");
    Movie movies[MAX_MOVIES];
    int total_movies = 0;
    int option;
    
    clear_screen();
    printf("===========================================\n");
    printf("     SISTEMA DE GESTÃO DE FILMES\n");
    printf("===========================================\n\n");
    
    do {
        display_menu();
        option = get_valid_int("Escolha uma opção (0-9): ", 0, 9);
        
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
                break;

            case 6:
                break;

                       case 7:
                clear_screen();
                if(total_movies > 0) {
                    printf("=== LIMPAR TODOS OS FILMES ===\n\n");
                    printf("Tem certeza que deseja limpar TODOS os %d filmes da memória?\n", total_movies);
                    printf("Esta ação não pode ser desfeita! (S/N): ");
                    
                    char confirm;
                    scanf(" %c", &confirm);
                    clear_input_buffer();
                    
                    if(toupper(confirm) == 'S') {
                        memset(movies, 0, sizeof(Movie) * total_movies);
                        total_movies = 0;
                        
                        printf("\nTodos os filmes foram REMOVIDOS da memória!\n");
                        printf("Memória totalmente zerada. Total de filmes: 0\n");
                    } else {
                        printf("\nOperação cancelada.\n");
                    }
                } else {
                    printf("Nenhum filme na memória para limpar.\n");
                }
                
                printf("\nPressione Enter para continuar...");
                clear_input_buffer();
                getchar();
                break;
                
            case 8:  
                clear_screen();
                import_movies_from_file(movies, &total_movies);
                break;
                
            case 9:
                clear_screen();
                export_movies_to_file(movies, total_movies);
                break;
                
            case 0:
                printf("\nTem certeza que deseja sair? (S/N): ");
                char confirm;
                scanf(" %c", &confirm);
                clear_input_buffer();
                
                if(toupper(confirm) != 'S') {
                    option = -1; 
                    break;
                }
                break;
                
            default:
                printf("Opção inválida!\n");
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
    printf("5. Alterar informações de um filme\n");
    printf("6. Eliminar filme\n");
    printf("7. Limpar todos os filmes em memória\n");
    printf("8. Importar filmes de arquivo\n");
    printf("9. Exportar filmes para arquivo\n");
    printf("0. Sair do programa\n");
    printf("===========================================\n");
}
