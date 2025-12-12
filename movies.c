#include <stdbool.h>
#include <stdio.h>
#include "movies.h"
#include <string.h>
#include <strings.h>


void bubble_sort_code(movies filmes[], int total){
    int i=0, j=0;
    movies temp;
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (filmes[j].code > filmes[j + 1].code) {
                temp = filmes[j];
                filmes[j] = filmes[j + 1];
                filmes[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_rating(movies filmes[], int total){
    int i=0, j=0;
    movies temp;
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (filmes[j].rating < filmes[j + 1].rating) {
                temp = filmes[j];
                filmes[j] = filmes[j + 1];
                filmes[j + 1] = temp;
            }
        }
    }
}
void bubble_sort_title(movies filmes[], int total){
    int i, j;
    movies temp;
    
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (strcasecmp(filmes[j].title, filmes[j + 1].title) > 0) {
                temp = filmes[j];
                filmes[j] = filmes[j + 1];
                filmes[j + 1] = temp;
            }
        }
    }
}

void listallmovies(movies filmes[], int total){
    int s = 0, i;
    
    do {
        printf("\nLista por:\n\t1 - Codigo Crescente\n\t2 - Nota Decrescente\n\t3 - Titulo\n\t0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &s);
        getchar();
        switch (s) {
            case 1:
                bubble_sort_code(filmes, total);
                printf("\nCodigo | Título\n"); 
                printf("%6s-|-%-30s\n", "------", "------------------------------");
                for(i = 0; i < total; i++)
                    printf("%6d | %s\n", filmes[i].code, filmes[i].title);
                break;
                
            case 2:
                bubble_sort_rating(filmes, total);
                printf("\nTítulo | Nota\n");  
                printf("%-30s-|-%5s\n", "------------------------------", "-----");
                for(i = 0; i < total; i++)
                    printf("%-30s | %4.1f\n", filmes[i].title, filmes[i].rating); 
                break;
                
            case 3:
                bubble_sort_title(filmes, total);
                printf("\nTítulo\n------\n"); 
                for(i = 0; i < total; i++)
                    printf("%s\n", filmes[i].title);
                break;
                
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
                
            default:
                printf("\nOpção inválida! Escolha 1, 2, 3 ou 0.\n");
                break;
        }
        
        if (s != 0) {
            printf("\nPressione Enter para continuar...");
            getchar(); 
        }
        
    } while (s != 0);
}


movies searchmovie(){}


void showmovie(int code){}


void addmovie(char title[], genres genres[], char description[501], char director[25], char atores[30][30] ,int year, int duration, int rating, float revenue){}



