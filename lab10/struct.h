#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAXLEN 256

typedef struct Head Head;
typedef struct Node Node;
typedef struct states states;
//��������� �� ������������ 9
struct states
{
    char *name; //�������� �����������
    char *inter_org; //�������� ������������� �����������
    int terr; //���������� ������
    float pop; //��������� ������ � ���������
    float pop_cap; // ��������� ������� � ���������
    int year_of_entry; //��� ���������� � �����������
    int data_of_app[3]; //���� ��������� �����������
};
//��������� �������� ������
struct Node
{
    int id; //Id ��������
    states *data; //������
    Node *next; // ��������� �� ��������� ������� ������
};
// ��������� ������ ������
struct Head
{
    int count; // ���������� ��������� � ������
    Node *first; // ��������� �� ������ ������� � ������
    Node *last; // ��������� �� ��������� ������� ������
};
