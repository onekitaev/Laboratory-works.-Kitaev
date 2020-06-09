#pragma once

#include "struct.h"
#include "func.h"
void command_selecting(Head *q);
Node *get_node();
void add_last(Head *q, Node *temp);
void add_first1(Head *head, Node *temp);
int charToInt(char numeric);
int str_len(char *s);
void scan();
void delete_elem(Head *head);
void decrease_id(Head *head , Node *node);
void increase_id(Head *head , Node *node);
void free_del(Node *tmp);
void insert_after(Head *head, Node *node);


