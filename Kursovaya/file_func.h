#pragma once
#include "struct.h"
#include "list_func.h"
#include "output.h"

void fill_list(Head *q, int flag1);
char **split(char **mes, char *string);
Node *adding_to_node(char **arr, int id);
void clear_array(char **arr, int cnt);
void update_database(Head* list);
char *writing_struct_to_string(states* st);
states *structure_filling();
float reading_float();
int reading_int();
void Writing_list_to_new_doc(Head* head);
