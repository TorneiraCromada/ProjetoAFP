#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "movies.h"

const char *genre_names[GENRE_COUNT] = {
    "Action", "Adventure", "Animation", "Biography", "Comedy",
    "Crime", "Drama", "Family", "Fantasy", "History",
    "Horror", "Music", "Musical", "Mystery", "Romance",
    "Scifi", "Sport", "Thriller", "War"
};

// ==================== FUNÇÕES UTILITÁRIAS ====================

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int get_valid_int(const char *prompt, int min, int max) {
    int value;
    int valid = 0;
    
    while(!valid) {
        printf("%s", prompt);
        if(scanf("%d", &value) == 1) {
            if(value >= min && value <= max) {
                valid = 1;
            } else {
                printf("Valor deve estar entre %d e %d\n", min, max);
            }
        } else {
            printf("Entrada invalida! Digite um numero.\n");
            clear_input_buffer();
        }
    }
    
    clear_input_buffer();
    return value;
}

float get_valid_float(const char *prompt, float min, float max) {
    float value;
    int valid = 0;
    
    while(!valid) {
        printf("%s", prompt);
        if(scanf("%f", &value) == 1) {
            if(value >= min && value <= max) {
                valid = 1;
            } else {
                printf("Valor deve estar entre %.1f e %.1f\n", min, max);
            }
        } else {
            printf("Entrada invalida! Digite um numero.\n");
            clear_input_buffer();
        }
    }
    
    clear_input_buffer();
    return value;
}
    int find_available_code(Movie movies[], int total) {
        if(total == 0) {
            return 1;
        }
        bubble_sort_code(movies, total);
        for(int i = 0; i < total; i++) {
            if(movies[i].code != i + 1) {
                return i + 1; 
            }
        }
        return movies[total - 1].code + 1;
    }
// ==================== FUNÇÕES DE ORDENAÇÃO ====================

void bubble_sort_code(Movie movies[], int total) {
    int i, j;
    Movie temp;
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (movies[j].code > movies[j + 1].code) {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_rating(Movie movies[], int total) {
    int i, j;
    Movie temp;
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (movies[j].rating < movies[j + 1].rating) {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_title(Movie movies[], int total) {
    int i, j;
    Movie temp;
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (strcasecmp(movies[j].title, movies[j + 1].title) > 0) {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
}

// ==================== FUNÇÕES DE LISTAGEM ====================

void list_all_movies(Movie movies[], int total) {
    int option = 0;
    int i;
    
    do {
        printf("\n=== LISTAR FILMES ===\n");
        printf("1. Por codigo (crescente)\n");
        printf("2. Por nota (decrescente)\n");
        printf("3. Por titulo (alfabetico)\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &option);
        getchar();
        
        switch (option) {
            case 1:
                bubble_sort_code(movies, total);
                printf("\n");
                printf("+--------+----------------------------------------------------+-----------------+--------+\n");
                printf("| Codigo | Titulo                                            | Genero          | Nota   |\n");
                printf("+--------+----------------------------------------------------+-----------------+--------+\n");
                for(i = 0; i < total; i++) {
                    printf("| %-6d | %-50.50s | %-15.15s | %6.1f |\n", 
                           movies[i].code, movies[i].title, 
                           genre_to_string(movies[i].genre), movies[i].rating);
                }
                printf("+--------+----------------------------------------------------+-----------------+--------+\n");
                break;
                
            case 2:
                bubble_sort_rating(movies, total);
                printf("\n");
                printf("+----------------------------------------------------+-----------------+--------+--------+\n");
                printf("| Titulo                                            | Genero          | Nota   | Ano    |\n");
                printf("+----------------------------------------------------+-----------------+--------+--------+\n");
                for(i = 0; i < total; i++) {
                    printf("| %-50.50s | %-15.15s | %6.1f | %6d |\n", 
                           movies[i].title, genre_to_string(movies[i].genre),
                           movies[i].rating, movies[i].year);
                }
                printf("+----------------------------------------------------+-----------------+--------+--------+\n");
                break;
                
            case 3:
                bubble_sort_title(movies, total);
                printf("\n");
                printf("+----------------------------------------------------+--------+-----------------+\n");
                printf("| Titulo                                            | Codigo | Genero          |\n");
                printf("+----------------------------------------------------+--------+-----------------+\n");
                for(i = 0; i < total; i++) {
                    printf("| %-50.50s | %6d | %-15.15s |\n", 
                           movies[i].title, movies[i].code, 
                           genre_to_string(movies[i].genre));
                }
                printf("+----------------------------------------------------+--------+-----------------+\n");
                break;
                
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
                
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
        
        if (option != 0 && option >= 1 && option <= 3) {
            printf("\nTotal de filmes: %d\n", total);
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while (option != 0);
}

// ==================== FUNÇÕES DE PESQUISA ====================

void search_movie(Movie movies[], int total, int option) {
    char search_term[100];
    int i, j, found = 0;
    
    if (total == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }
    
    printf("\n=== PESQUISAR FILMES ===\n");
    printf("Termo de pesquisa: ");
    fgets(search_term, sizeof(search_term), stdin);
    search_term[strcspn(search_term, "\n")] = 0;
    
    // Converter para minúsculas para busca case-insensitive
    for(i = 0; search_term[i]; i++) {
        search_term[i] = tolower(search_term[i]);
    }
    
    printf("\n");
    printf("+--------+----------------------------------------------------+-----------------+--------+\n");
    printf("| Codigo | Titulo                                            | Genero          | Nota   |\n");
    printf("+--------+----------------------------------------------------+-----------------+--------+\n");
    
    switch(option) {
        case 1: // Por titulo
            for(i = 0; i < total; i++) {
                char title_lower[100];
                strcpy(title_lower, movies[i].title);
                for(j = 0; title_lower[j]; j++) {
                    title_lower[j] = tolower(title_lower[j]);
                }
                
                if(strstr(title_lower, search_term) != NULL) {
                    printf("| %-6d | %-50.50s | %-15.15s | %6.1f |\n", 
                           movies[i].code, movies[i].title, 
                           genre_to_string(movies[i].genre), movies[i].rating);
                    found++;
                }
            }
            break;
            
        case 2: // Por genero
            for(i = 0; i < total; i++) {
                const char *genre_str = genre_to_string(movies[i].genre);
                char genre_lower[20];
                strcpy(genre_lower, genre_str);
                for(j = 0; genre_lower[j]; j++) {
                    genre_lower[j] = tolower(genre_lower[j]);
                }
                
                if(strstr(genre_lower, search_term) != NULL) {
                    printf("| %-6d | %-50.50s | %-15.15s | %6.1f |\n", 
                           movies[i].code, movies[i].title, 
                           genre_to_string(movies[i].genre), movies[i].rating);
                    found++;
                }
            }
            break;
            
        case 3: // Por diretor
            for(i = 0; i < total; i++) {
                char director_lower[100];
                strcpy(director_lower, movies[i].director);
                for(j = 0; director_lower[j]; j++) {
                    director_lower[j] = tolower(director_lower[j]);
                }
                
                if(strstr(director_lower, search_term) != NULL) {
                    printf("| %-6d | %-50.50s | %-15.15s | %6.1f |\n", 
                           movies[i].code, movies[i].title, 
                           genre_to_string(movies[i].genre), movies[i].rating);
                    found++;
                }
            }
            break;
            
        case 4: // Por ator
            for(i = 0; i < total; i++) {
                for(j = 0; j < movies[i].num_actors; j++) {
                    char actor_lower[100];
                    strcpy(actor_lower, movies[i].actors[j]);
                    int k;
                    for(k = 0; actor_lower[k]; k++) {
                        actor_lower[k] = tolower(actor_lower[k]);
                    }
                    
                    if(strstr(actor_lower, search_term) != NULL) {
                        printf("| %-6d | %-50.50s | %-15.15s | %6.1f |\n", 
                               movies[i].code, movies[i].title, 
                               genre_to_string(movies[i].genre), movies[i].rating);
                        found++;
                        break; // Mostra o filme apenas uma vez
                    }
                }
            }
            break;
    }
    
    printf("+--------+----------------------------------------------------+-----------------+--------+\n");
    
    if(found == 0) {
        printf("Nenhum filme encontrado com o termo: %s\n", search_term);
    } else {
        printf("\nTotal encontrado: %d filme(s)\n", found);
    }
}

// ==================== FUNÇÕES DE VISUALIZAÇÃO ====================

void show_movie_details(int code, Movie movies[], int total) {
    int index = binary_search(code, movies, total);
    
    if(index == -1) {
        printf("ERRO: Filme com codigo %d nao encontrado!\n", code);
        return;
    }
    
    Movie *movie = &movies[index];
    
    printf("\n========================================================\n");
    printf("                DETALHES DO FILME\n");
    printf("========================================================\n");
    printf("Codigo:     %d\n", movie->code);
    printf("Titulo:     %s\n", movie->title);
    printf("Genero:     %s\n", genre_to_string(movie->genre));
    printf("Diretor:    %s\n", movie->director);
    printf("Ano:        %d\n", movie->year);
    printf("Duracao:    %d minutos\n", movie->duration);
    printf("Nota:       %.1f/5.0\n", movie->rating);
    printf("Favoritos:  %d votos\n", movie->favorite);
    printf("Receita:    $%.2f milhoes\n", movie->revenue);
    printf("\nDescricao:\n%s\n", movie->description);
    printf("\nAtores:\n");
    
    if(movie->num_actors > 0) {
        for(int i = 0; i < movie->num_actors; i++) {
            if(strlen(movie->actors[i]) > 0) {
                printf("  - %s\n", movie->actors[i]);
            }
        }
    } else {
        printf("  (Nenhum ator cadastrado)\n");
    }
    printf("========================================================\n");
}

int binary_search(int code, Movie movies[], int total) {
    // Busca linear simples - não modifica o array original
    for(int i = 0; i < total; i++) {
        if(movies[i].code == code) {
            return i;  // Retorna o índice onde o filme foi encontrado
        }
    }
    
    return -1;  // Filme não encontrado
}

// ==================== FUNÇÕES DE ADIÇÃO ====================

void add_movie(Movie movies[], int *total, Movie new_movie) {
    // Verificar se o codigo ja existe
    for(int i = 0; i < *total; i++) {
        if(movies[i].code == new_movie.code) {
            printf("ERRO: Codigo %d ja existe!\n", new_movie.code);
            return;
        }
    }
    
    // Adicionar o novo filme
    movies[*total] = new_movie;
    (*total)++;
    
    printf("Filme '%s' adicionado com sucesso! (Codigo: %d)\n", 
           new_movie.title, new_movie.code);
}

void add_movie_interactive(Movie movies[], int *total) {
    if(*total >= MAX_MOVIES) {
        printf("ERRO: Limite maximo de filmes atingido (%d)\n", MAX_MOVIES);
        return;
    }
    
    Movie new_movie;
    
    printf("=== ADICIONAR NOVO FILME ===\n\n");
    
    // Gerar código automaticamente (menor código disponível)
    new_movie.code = find_available_code(movies, *total);
    printf("Codigo automaticamente gerado: %d\n", new_movie.code);
    
    // Titulo
    printf("Titulo: ");
    fgets(new_movie.title, sizeof(new_movie.title), stdin);
    new_movie.title[strcspn(new_movie.title, "\n")] = 0;
    
    // Genero
    printf("\nGeneros disponiveis:\n");
    for(int i = 0; i < GENRE_COUNT; i++) {
        printf("%2d. %s\n", i, genre_names[i]);
    }
    int genre_choice = get_valid_int("Escolha o genero (numero): ", 0, GENRE_COUNT - 1);
    new_movie.genre = (Genre)genre_choice;
    
    // Descricao
    printf("Descricao: ");
    fgets(new_movie.description, sizeof(new_movie.description), stdin);
    new_movie.description[strcspn(new_movie.description, "\n")] = 0;
    
    // Diretor
    printf("Diretor: ");
    fgets(new_movie.director, sizeof(new_movie.director), stdin);
    new_movie.director[strcspn(new_movie.director, "\n")] = 0;
    
    // Atores
    printf("Quantos atores deseja adicionar? (1-10): ");
    int num_actors = get_valid_int("", 1, 10);
    new_movie.num_actors = 0;
    
    for(int i = 0; i < num_actors; i++) {
        printf("Ator %d: ", i + 1);
        fgets(new_movie.actors[i], sizeof(new_movie.actors[i]), stdin);
        new_movie.actors[i][strcspn(new_movie.actors[i], "\n")] = 0;
        new_movie.num_actors++;
    }
    
    // Ano
    new_movie.year = get_valid_int("Ano de lancamento: ", 1888, 2024);
    
    // Duracao
    new_movie.duration = get_valid_int("Duracao (minutos): ", 1, 500);
    
    // Nota
    new_movie.rating = get_valid_float("Nota (0.0-10.0): ", 0.0, 10.0);
    
    // Favorito
    new_movie.favorite = get_valid_int("Contagem de favoritos: ", 0, 10000);
    
    // Receita
    new_movie.revenue = get_valid_float("Receita (em milhoes): ", 0.0, 10000.0);
    
    // Adicionar ao array
    add_movie(movies, total, new_movie);
    
    printf("\nPressione Enter para continuar...");
    clear_input_buffer();
    getchar();
}

// ==================== FUNÇÕES DE ALTERAÇÃO ====================

void alter_movie(Movie movies[], int *total, Movie new_info){
    // Ir até ao filme
    for(int i = 0; i < *total; i++){
        if(movies[i].code == new_info.code){
            movies[i] = new_info;
            printf("Informações do filme '%s' alteradas com sucesso! (Codigo: %d)\n",
            new_info.title, new_info.code);
            return;
        }
    }

    //Caso o id não seja encontrado
    printf("ERRO: Codigo %d não encontrado", new_info.code);
}

void alter_movie_interactive(Movie movies[], int *total){
    Movie new_info;
    int check;

    printf("=== ALTERAR FILME ===\n\n");

    //Codigo para pesquisa
    new_info.code = get_valid_int("Codigo do filme: ", 1, 999999);

    //Verificar se o codigo existe
    check = binary_search(new_info.code, movies, *total);

    if (check == -1)
    {
        printf("ERRO: Código %d não existe!", new_info.code);
        printf("Pressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }

    // Titulo
    printf("Titulo: ");
    fgets(new_info.title, sizeof(new_info.title), stdin);
    new_info.title[strcspn(new_info.title, "\n")] = 0;
    
    // Genero
    printf("\nGeneros disponiveis:\n");
    for(int i = 0; i < GENRE_COUNT; i++) {
        printf("%2d. %s\n", i, genre_names[i]);
    }
    int genre_choice = get_valid_int("Escolha o genero (numero): ", 0, GENRE_COUNT - 1);
    new_info.genre = (Genre)genre_choice;
    
    // Descricao
    printf("Descricao: ");
    fgets(new_info.description, sizeof(new_info.description), stdin);
    new_info.description[strcspn(new_info.description, "\n")] = 0;
    
    // Diretor
    printf("Diretor: ");
    fgets(new_info.director, sizeof(new_info.director), stdin);
    new_info.director[strcspn(new_info.director, "\n")] = 0;
    
    // Atores
    printf("Quantos atores deseja adicionar? (1-10): ");
    int num_actors = get_valid_int("", 1, 10);
    new_info.num_actors = 0;
    
    for(int i = 0; i < num_actors; i++) {
        printf("Ator %d: ", i + 1);
        fgets(new_info.actors[i], sizeof(new_info.actors[i]), stdin);
        new_info.actors[i][strcspn(new_info.actors[i], "\n")] = 0;
        new_info.num_actors++;
    }
    
    // Ano
    new_info.year = get_valid_int("Ano de lancamento: ", 1888, 2024);
    
    // Duracao
    new_info.duration = get_valid_int("Duracao (minutos): ", 1, 500);
    
    // Nota
    new_info.rating = get_valid_float("Nota (0.0-10.0): ", 0.0, 10.0);
    
    // Favorito
    new_info.favorite = get_valid_int("Contagem de favoritos: ", 0, 10000);
    
    // Receita
    new_info.revenue = get_valid_float("Receita (em milhoes): ", 0.0, 10000.0);
    
    // Adicionar ao array
    alter_movie(movies, total, new_info);
    printf("\nPressione Enter para continuar...");
    clear_input_buffer();
    getchar();
    
}

// ==================== FUNÇÕES DE REMOÇÃO ====================

void remove_movie(Movie movies[], int *total){
    int remove_code, check;

    //Codigo para remover
    remove_code = get_valid_int("Codigo do filme: ", 1, 999999);

    check = binary_search(remove_code, movies, *total);

    if (check == -1)
    {
        printf("ERRO: Código %d não encontrado!", remove_code);
        return;
    }

    movies[check].code = movies[*total].code;
    bubble_sort_code(movies, *total);
    *total = *total -1;

    printf("Filme removido com sucesso!\n");
    printf("\nPressione Enter para continuar...");
    clear_input_buffer();
    getchar();
}


// ==================== FUNÇÕES DE ARQUIVO ====================

int load_movies_from_csv(const char *filename, Movie movies[], int max_movies) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo %s\n", filename);
        return 0;
    }
    
    char line[2048];
    int count = 0;
    
    // Pular cabecalho
    if(fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }
    
    while(fgets(line, sizeof(line), file) && count < max_movies) {
        // Remover newline
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0; // Remove carriage return para arquivos Windows
        
        // Verificar se a linha esta vazia
        if(strlen(line) == 0 || line[0] == '\0') {
            continue;
        }
        
        char *tokens[15];
        int token_count = 0;
        
        // Usar copia para tokenizacao
        char line_copy[2048];
        strcpy(line_copy, line);
        
        char *token = strtok(line_copy, ";");
        while(token != NULL && token_count < 15) {
            tokens[token_count] = token;
            token_count++;
            token = strtok(NULL, ";");
        }
        
        if(token_count >= 11) { // Certificar que temos todas as colunas
            // Codigo
            movies[count].code = atoi(tokens[0]);
            
            // Titulo
            strncpy(movies[count].title, tokens[1], sizeof(movies[count].title)-1);
            movies[count].title[sizeof(movies[count].title)-1] = '\0';
            
            // Genero - o CSV tem 'genres' no cabecalho
            movies[count].genre = string_to_genre(tokens[2]);
            
            // Descricao
            strncpy(movies[count].description, tokens[3], sizeof(movies[count].description)-1);
            movies[count].description[sizeof(movies[count].description)-1] = '\0';
            
            // Diretor
            strncpy(movies[count].director, tokens[4], sizeof(movies[count].director)-1);
            movies[count].director[sizeof(movies[count].director)-1] = '\0';
            
            // Atores
            char actors_str[1000];
            strncpy(actors_str, tokens[5], sizeof(actors_str)-1);
            actors_str[sizeof(actors_str)-1] = '\0';
            
            char *actor_token = strtok(actors_str, ",");
            int actor_idx = 0;
            movies[count].num_actors = 0;
            
            while(actor_token != NULL && actor_idx < 10) {
                // Remover espacos extras
                while(*actor_token == ' ') actor_token++;
                strncpy(movies[count].actors[actor_idx], actor_token, 99);
                movies[count].actors[actor_idx][99] = '\0';
                movies[count].num_actors++;
                actor_idx++;
                actor_token = strtok(NULL, ",");
            }
            
            // Ano
            movies[count].year = atoi(tokens[6]);
            
            // Duracao
            movies[count].duration = atoi(tokens[7]);
            
            // Nota - tratar separador decimal
            char rating_str[50];
            strncpy(rating_str, tokens[8], sizeof(rating_str)-1);
            rating_str[sizeof(rating_str)-1] = '\0';
            
            // Substituir virgula por ponto se necessario
            for(int i = 0; rating_str[i]; i++) {
                if(rating_str[i] == ',') rating_str[i] = '.';
            }
            movies[count].rating = atof(rating_str);
            
            // Favorito
            movies[count].favorite = atoi(tokens[9]);
            
            // Receita - tratar separador decimal
            char revenue_str[50];
            strncpy(revenue_str, tokens[10], sizeof(revenue_str)-1);
            revenue_str[sizeof(revenue_str)-1] = '\0';
            
            // Remover possiveis espacos extras no final
            char *end = revenue_str + strlen(revenue_str) - 1;
            while(end > revenue_str && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) {
                *end = '\0';
                end--;
            }
            
            // Substituir virgula por ponto se necessario
            for(int i = 0; revenue_str[i]; i++) {
                if(revenue_str[i] == ',') revenue_str[i] = '.';
            }
            movies[count].revenue = atof(revenue_str);
            
            count++;
        } else {
            printf("Aviso: Linha %d ignorada - formato incorreto\n", count+1);
        }
    }
    
    fclose(file);
    printf("Carregados %d filmes de %s\n", count, filename);
    return count;
}

int save_movies_to_csv(const char *filename, Movie movies[], int total) {
    FILE *file = fopen(filename, "w");
    if(file == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo %s\n", filename);
        return 0;
    }
    
    // Escrever cabecalho - com 'genres' para corresponder ao seu CSV
    fprintf(file, "code;title;genres;description;director;actors;year;duration;rating;favorite ;revenue\n");
    
    for(int i = 0; i < total; i++) {
        // Preparar string de atores
        char actors_str[1000] = "";
        for(int j = 0; j < movies[i].num_actors; j++) {
            if(j > 0) strcat(actors_str, ",");
            strcat(actors_str, movies[i].actors[j]);
        }
        
        // Nota: espaco em 'favorite ' para corresponder ao cabecalho original
        fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%d;%.1f;%d;%.2f\n",
                movies[i].code,
                movies[i].title,
                genre_to_string(movies[i].genre),
                movies[i].description,
                movies[i].director,
                actors_str,
                movies[i].year,
                movies[i].duration,
                movies[i].rating,
                movies[i].favorite,
                movies[i].revenue);
    }
    
    fclose(file);
    printf("Salvos %d filmes em %s\n", total, filename);
    return total;
}

// ==================== FUNÇÕES AUXILIARES ====================

Genre string_to_genre(const char *genre_str) {
    // Primeiro, remover espacos extras
    char clean_str[50];
    int j = 0;
    for(int i = 0; genre_str[i] && j < sizeof(clean_str)-1; i++) {
        if(genre_str[i] != ' ' || (j > 0 && clean_str[j-1] != ' ')) {
            clean_str[j++] = genre_str[i];
        }
    }
    clean_str[j] = '\0';
    
    // Remover espacos finais
    while(j > 0 && clean_str[j-1] == ' ') {
        clean_str[--j] = '\0';
    }
    
    // Procurar correspondencia exata
    for(int i = 0; i < GENRE_COUNT; i++) {
        if(strcasecmp(clean_str, genre_names[i]) == 0) {
            return (Genre)i;
        }
    }
    
    // Tentar mapear variacoes comuns
    if(strcasecmp(clean_str, "Sci-fi") == 0 || 
       strcasecmp(clean_str, "Science Fiction") == 0 ||
       strcasecmp(clean_str, "Science-Fiction") == 0 ||
       strcasecmp(clean_str, "SciFi") == 0 || 
       strcasecmp(clean_str, "SF") == 0) {
        return Scifi;
    }
    if(strcasecmp(clean_str, "Biographical") == 0) {
        return Biography;
    }
    if(strcasecmp(clean_str, "Animated") == 0) {
        return Animation;
    }
    if(strcasecmp(clean_str, "Thriller") == 0 ||
       strcasecmp(clean_str, "Suspense") == 0) {
        return Thriller;
    }
    
    // Se nao encontrar, retorna Action como default
    return Action;
}

const char* genre_to_string(Genre genre) {
    if(genre >= 0 && genre < GENRE_COUNT) {
        return genre_names[genre];
    }
    return "Unknown";
}

// ==================== FUNÇÃO PARA REMOVER DUPLICADOS ====================

void remove_duplicate_movies(Movie movies[], int *total) {
    if(*total <= 1) return;
    
    int new_total = 0;
    int found_duplicates = 0;
    
    for(int i = 0; i < *total; i++) {
        int is_duplicate = 0;
        
        // Verificar se este filme já existe nos filmes mantidos
        for(int j = 0; j < new_total; j++) {
            // Comparar por código (único) ou título + ano
            if(movies[i].code == movies[j].code) {
                is_duplicate = 1;
                found_duplicates++;
                printf("Duplicado removido: %s (Código: %d)\n", 
                       movies[i].title, movies[i].code);
                break;
            }
            // Opcional: também verificar por título e ano
            else if(strcasecmp(movies[i].title, movies[j].title) == 0 && 
                    movies[i].year == movies[j].year) {
                is_duplicate = 1;
                found_duplicates++;
                printf("Duplicado removido: %s (%d)\n", 
                       movies[i].title, movies[i].year);
                break;
            }
        }
        
        // Se não for duplicado, manter
        if(!is_duplicate) {
            movies[new_total] = movies[i];
            new_total++;
        }
    }
    
    *total = new_total;
    
    if(found_duplicates > 0) {
        printf("\nRemovidos %d filmes duplicados. Total agora: %d\n", 
               found_duplicates, *total);
    }
}

// ==================== FUNÇÕES DE MENU ====================

void search_movie_menu(Movie movies[], int total) {
    if(total == 0) {
        printf("Nenhum filme cadastrado.\n");
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }
    
    int option;
    
    printf("=== PESQUISAR FILMES ===\n");
    printf("1. Por titulo\n");
    printf("2. Por genero\n");
    printf("3. Por diretor\n");
    printf("4. Por ator\n");
    printf("0. Voltar\n");
    
    option = get_valid_int("Escolha uma opcao: ", 0, 4);
    
    if(option != 0) {
        search_movie(movies, total, option);
        
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
    }
}

void show_movie_menu(Movie movies[], int total) {
    if(total == 0) {
        printf("Nenhum filme cadastrado.\n");
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }
    
    printf("=== VER DETALHES DO FILME ===\n");
    int code = get_valid_int("Digite o codigo do filme: ", 1, 999999);
    
    show_movie_details(code, movies, total);
    
    printf("\nPressione Enter para continuar...");
    clear_input_buffer();
    getchar();
}

// ==================== NOVAS FUNÇÕES DE IMPORTAR/EXPORTAR ====================

void import_movies_from_file(Movie movies[], int *total) {
    char filename[50];
    char full_path[80];  
    
    printf("=== IMPORTAR FILMES DE ARQUIVO ===\n\n");
    printf("Nome do arquivo CSV (sem 'files/'): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    snprintf(full_path, sizeof(full_path), "files/%s", filename);
    
    // Verificar se o arquivo existe
    FILE *test = fopen(full_path, "r");
    if(test == NULL) {
        printf("ERRO: Arquivo '%s' nao encontrado na pasta 'files/'!\n", filename);
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }
    fclose(test);
    
    // Perguntar ao usuário se quer importar
    printf("\nDeseja importar filmes do arquivo 'files/%s'? (S/N): ", filename);
    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();
    
    if(toupper(confirm) != 'S') {
        printf("Importacao cancelada.\n");
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }
    
    // Verificar se há espaço suficiente
    int available_space = MAX_MOVIES - *total;
    if(available_space <= 0) {
        printf("ERRO: Nao ha espaço para importar mais filmes! Limite maximo: %d\n", MAX_MOVIES);
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }
    
    // Importar filmes usando a função existente
    int imported_count = load_movies_from_csv(full_path, &movies[*total], available_space);
    
    if(imported_count > 0) {
        *total += imported_count;
        
        // Remover duplicados após importação
        remove_duplicate_movies(movies, total);
        
        printf("\nSUCESSO: %d filme(s) importado(s) do arquivo '%s'!\n", imported_count, filename);
        printf("Total de filmes no sistema agora: %d\n", *total);
    } else {
        printf("Nenhum filme foi importado. O arquivo pode estar vazio ou com formato incorreto.\n");
    }
    
    printf("\nPressione Enter para continuar...");
    clear_input_buffer();
    getchar();
}

void export_movies_to_file(Movie movies[], int total) {
    char filename[50];
    char full_path[80];
    
    printf("=== EXPORTAR FILMES PARA ARQUIVO ===\n\n");
    
    if(total == 0) {
        printf("Nenhum filme para exportar.\n");
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }
    
    printf("Nome do arquivo CSV (ex: meus_filmes.csv): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    
    // Adicionar extensão .csv se não tiver
    if(strstr(filename, ".csv") == NULL && strstr(filename, ".CSV") == NULL) {
        // Verificar se cabe a extensão
        if(strlen(filename) + 4 < sizeof(filename)) {
            strcat(filename, ".csv");
        } else {
            printf("ERRO: Nome do arquivo muito longo!\n");
            printf("\nPressione Enter para continuar...");
            clear_input_buffer();
            getchar();
            return;
        }
    }
    
    // Adicionar "files/" automaticamente
    snprintf(full_path, sizeof(full_path), "files/%s", filename);
    
    // Perguntar ao usuário se quer exportar
    printf("\nDeseja exportar %d filme(s) para o arquivo 'files/%s'? (S/N): ", total, filename);
    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();
    
    if(toupper(confirm) != 'S') {
        printf("Exportacao cancelada.\n");
        printf("\nPressione Enter para continuar...");
        clear_input_buffer();
        getchar();
        return;
    }
    
    // Usar a função save_movies_to_csv existente
    int exported_count = save_movies_to_csv(full_path, movies, total);
    
    if(exported_count > 0) {
        printf("\nSUCESSO: %d filme(s) exportado(s) para o arquivo 'files/%s'!\n", exported_count, filename);
    } else {
        printf("ERRO: Nao foi possivel exportar os filmes.\n");
    }
    
    printf("\nPressione Enter para continuar...");
    clear_input_buffer();
    getchar();
}
