#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAXLEN 256
#define SIZE 256
#define WordLen 20

typedef struct Head Head;
typedef struct Node Node;
typedef struct states states;

struct states
{
    char *name;        //Название государства
    char *inter_org;   //Название международной организации
    int terr;          //Территория страны
    float pop;         //Население страны в миллионах
    float pop_cap;     // Население столицы в миллионах
    int year_of_entry; //Год вступления в организацию
    int GDP[1];        //ВВП страны
};
//Структура элемента списка
struct Node
{
    int id;       //Id элемента
    states *data; //данные
    Node *next;   // Указатель на следующий элемент списка
    Node *prev;   // Указатель на предыдущий элемент списка
};
// Структура головы списка
struct Head
{
    int count;    // Количество элементов в списке
    Node *first;  // Указатель на первый элемент в списке
    Node *last;   // Указатель на последний элемент списка
};
