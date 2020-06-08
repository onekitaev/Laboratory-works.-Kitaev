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
    char *name;        //�������� �����������
    char *inter_org;   //�������� ������������� �����������
    int terr;          //���������� ������
    float pop;         //��������� ������ � ���������
    float pop_cap;     // ��������� ������� � ���������
    int year_of_entry; //��� ���������� � �����������
    int GDP[1];        //��� ������
};
//��������� �������� ������
struct Node
{
    int id;       //Id ��������
    states *data; //������
    Node *next;   // ��������� �� ��������� ������� ������
    Node *prev;   // ��������� �� ���������� ������� ������
};
// ��������� ������ ������
struct Head
{
    int count;    // ���������� ��������� � ������
    Node *first;  // ��������� �� ������ ������� � ������
    Node *last;   // ��������� �� ��������� ������� ������
};
