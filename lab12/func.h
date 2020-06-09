#pragma once

#include "struct.h"

Head *create_head();
Node *create_node(Head *q);
void malloc_node(Node *temp);
void fill_list(Head *q);
char **split(char **mes, char *string);
void clear_array(char **arr, int cnt);
Node *adding_to_node(char **arr, int id);
void add_first(Head *head, Node *node);
void filling(Head *head, Node *p1, Node *p);
void output_list(Head *q);
void print_header();
void *node_out(Node *temp);
void free_list(Head *head);



