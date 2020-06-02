#pragma once

#include "struct.h"
#include "func.h"
void command_selecting(Head *q);
Node *get_node();
Node *add_last(Head *q);
Node *add_first1(Head *q);
int charToInt(char numeric);
int str_len(char *s);
void scan();
void delete_elem(Head *head);
void decrease_id(Head *head , Node *node);
void increase_id(Head *head , Node *node);
void insert_before_last(Head *head);
void free_del(Node *tmp);


