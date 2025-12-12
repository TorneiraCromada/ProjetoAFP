#include <stdbool.h>
#include <stdio.h>
#include "movies.h"
#include <string.h>

const char genArr[18][20] = {"Ação","Aventura","Animação","Biografia","Comédia","Crime","Drama","Familia","Fantasia","História","Terror","Musica","Musical","Mistério","Romance","Scifi","Desporto","Thriller","Guerra"};

void listallmovies(movies *array, int op){
    int i;
    printf("Código | Título | Género | Diretor | Atores | Ano | Duração | Nota | Favoritos | Receita");
    switch (op)
    {
    case 1:
        for (i = 0; i < sizeof(array); i++)
        {
            /*Falta só pensar como os atores vão funcionar para listar todos*/
            printf("%d | %s | %s | %s | %s | %d | %d minutos | %d estrelas | %d favoritos | %f milhões de euros", array[i].code, array[i].title, genArr[array[i].genres], array[i].director, array[i].atores, array[i].year, array[i].duration, array[i].rating, array[i].favorite, array[i].revenue);
        }
        break;
    case 2:
        /*Ordenação por Rating*/
        break;
    case 3:
        /*Ordem alfabética do Título*/
        break;
    
    default:
        break;
    }
}

/*COMPLETO. Depois verifica se quiseres mas acho que não tem problemas*/
void searchmovie(movies *array, int op){
    char details[50];
    int i, j;
    char* p;
    switch (op)
    {
    case 1:
        printf("Insira um título para pesquisar: ");
        fgets(details, sizeof(details), stdin);
        printf("Código | Título | Género | Diretor | Atores | Ano | Duração | Nota | Favoritos | Receita");
        for (i = 0; i < sizeof(array); i++)
        {
            p = strstr(array[i].title, details);
            if (p)
            {
                /*Falta só pensar como os atores vão funcionar para listar todos*/
                printf("%d | %s | %s | %s | %s | %d | %d minutos | %d estrelas | %d favoritos | %f milhões de euros", array[i].code, array[i].title, genArr[array[i].genres], array[i].director, array[i].atores, array[i].year, array[i].duration, array[i].rating, array[i].favorite, array[i].revenue);
            }
            
        }
        
        break;
    case 2:
        printf("Insira um género para pesquisar: ");
        fgets(details, sizeof(details), stdin);
        for (j = 0; j < sizeof(genArr); j++)
            {
                p = strstr(genArr[j], details);
                if (p)
                {
                    break;
                }
            }
        if (p)
            {
                printf("Código | Título | Género | Diretor | Atores | Ano | Duração | Nota | Favoritos | Receita");
            } else {
                printf("ERRO: Género inválido");
                break;
            }
        for (i = 0; i < sizeof(array); i++)
        {
            if (array[i].genres == j)
            {
                /*Falta só pensar como os atores vão funcionar para listar todos*/
                printf("%d | %s | %s | %s | %s | %d | %d minutos | %d estrelas | %d favoritos | %f milhões de euros", array[i].code, array[i].title, genArr[array[i].genres], array[i].director, array[i].atores, array[i].year, array[i].duration, array[i].rating, array[i].favorite, array[i].revenue);
            }
            
        }
        break;
    case 3:
        printf("Insira um realizador para pesquisar: ");
        fgets(details, sizeof(details), stdin);
        printf("Código | Título | Género | Diretor | Atores | Ano | Duração | Nota | Favoritos | Receita");
        for (i = 0; i < sizeof(array); i++)
        {
            p = strstr(array[i].director, details);
            if (p)
            {
                /*Falta só pensar como os atores vão funcionar para listar todos*/
                printf("%d | %s | %s | %s | %s | %d | %d minutos | %d estrelas | %d favoritos | %f milhões de euros", array[i].code, array[i].title, genArr[array[i].genres], array[i].director, array[i].atores, array[i].year, array[i].duration, array[i].rating, array[i].favorite, array[i].revenue);
            }
        }
        break;
    case 4:
        printf("Insira um ator para pesquisar: ");
        fgets(details, sizeof(details), stdin);
        printf("Código | Título | Género | Diretor | Atores | Ano | Duração | Nota | Favoritos | Receita");
        for (i = 0; i < sizeof(array); i++)
        {
            for (j = 0; j < sizeof(array); j++)
            {
                p = strstr(array[i].atores[j], details);
                if (p){
                    break;
                }   
            }
            
            if (p)
            {
                //*Falta só pensar como os atores vão funcionar para listar todos*/
                printf("%d | %s | %s | %s | %s | %d | %d minutos | %d estrelas | %d favoritos | %f milhões de euros", array[i].code, array[i].title, genArr[array[i].genres], array[i].director, array[i].atores, array[i].year, array[i].duration, array[i].rating, array[i].favorite, array[i].revenue);
            }
        }
        break;
    default:
        printf("ERRO: Opção inválida");
        break;
    }
}


void showmovie(int code, movies *array){
   int index = binarySearch(code, array, sizeof(array));
   int i;
   if (index == -1)
   {
    printf("ERRO: Código inválido");
   } else {
    printf("-------------------------------------------------");
    printf("Código: %d\n", array[index].code);
    printf("Título: %s\n", array[index].title);
    printf("Género: %s\n", genArr[array[index].genres]);
    printf("Descrição: %s\n", array[index].description);
    printf("Realizador: %s\n", array[index].director);
    printf("Atores: ");
    for (i = 0; i < sizeof(array[index].atores); i++)
    {
        printf("%s\n    ", array[index].atores[i]);
    }
    printf("\nAno: %d\n", array[index].year);
    printf("Duração: %d minutos\n", array[index].duration);
    printf("Nota: %d estrelas\n", array[index].rating);
    printf("Favoritos: %d\n", array[index].favorite);
    printf("Receita: %f milhões de euros\n", array[index].revenue);
    printf("-------------------------------------------------");
   }
   
}


void addmovie(movies *array, movies input){
    int index = sizeof(array);
    int i, j;
    array[index].code = input.code;
    for (i = 0; i < sizeof(input.title); i++)
    {
        array[index].title[i] = input.title[i];
    }
    array[index].genres = input.genres;
    for (i = 0; i < sizeof(input.description); i++)
    {
        array[index].description[i] = input.description[i];
    }
    for (i = 0; i < sizeof(input.director); i++)
    {
        array[index].director[i] = input.director[i];
    }
    for (i = 0; i < sizeof(input.atores); i++)
    {
        for (j = 0; j < sizeof(input.atores[i]); j++)
        {
            array[index].atores[i][j] = input.atores[i][j];
        }
    }
    array[index].year = input.year;
    array[index].duration = input.duration;
    array[index].rating = input.rating;
    array[index].favorite = input.favorite;
    array[index].revenue = input.revenue;
}


int binarySearch(int val, movies *array, int arrayLength) {
    int start = 0;
    int end = arrayLength - 1;
    while (start <= end) {
    int middle = start + (end - start) / 2;

    if (array[middle].code == val) {
        return middle; 
    }

    else if (array[middle].code > val) {
        end = middle - 1;
    }

        else {
            start = middle + 1;
        }
    }

    return -1;
}
