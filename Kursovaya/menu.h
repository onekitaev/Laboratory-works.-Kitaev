#include "struct.h"
#include "output.h"
#include "list_func.h"
#include "file_func.h"

void menu(int flag);
void menu_delete_element(Head* head, int flag);
void menu_output_list(Head* head, int flag);
void menu_add_element(Head* head, int flag);
void menu_sort_element(Head* head, int flag);
void menu_change_element(Head* head, int flag);
Head* (*find[7])(Head *head);
void menu_find_element(Head* head, int flag);

