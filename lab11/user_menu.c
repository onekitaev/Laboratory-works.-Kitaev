#include "user_menu.h"
//Выбор команды
void command_selecting(Head *q)
{
    char s[MAXLEN];
    int f;
    Node *temp;
    puts("\n1 - Add first\n2 - Add last\n3 - Delete element\n4 - Insert before the last\n5 - List output\n0 - Exit");
    fgets(s, 200, stdin);
    //перевод char в int. лагодаря этой функции мы можем вводить что угодно и программа не сломается
    f = charToInt(s[0]);
    if(str_len(s) == 1) {
        if(f == 1) {
            //создание нового узла
            if((q -> count) == 0) temp = create_node(q);
            else {
                //добавление в начало
                add_first1(q);
                temp = q -> first;
                scan(temp);
            }
        }
        if(f == 2) {
            if((q -> count) == 0) temp = create_node(q);
            else {
                add_last(q);
                temp = q -> last;
                scan(temp);
            }
        }
        else if(f == 3) delete_elem(q);
        else if(f == 4) insert_before_last(q);
        else if(f == 5) output_list(q);
    }
    while(f != 0) {
        if(str_len(s) == 0) {
            if(f == 1) {
                if((q -> count) == 0) temp = create_node(q);
                else {
                    add_first1(q);
                    temp = q -> first;
                    scan(temp);
                }
            }
            if(f == 2) {
                if((q -> count) == 0) temp = create_node(q);
                else {
                    add_last(q);
                    temp = q -> last;
                    scan(temp);
                }
            }
            else if(f == 3) delete_elem(q);
            else if(f == 4) insert_before_last(q);
            else if(f == 5) output_list(q);
        }
        puts("\n1 - Add first\n2 - Add last\n3 - Delete element\n4 - Insert before the last\n5 - List output\n0 - Exit");
        scanf("%s", &s);
        f = charToInt(s[0]);
        getchar();
    }
}
//Запись в узел с клавиатуры
Node *get_node()
{
    Node *new_node = NULL;
    if((new_node = (Node*)malloc(sizeof(Node))) != NULL){
        if((new_node -> data = (states*)malloc(sizeof(states))) != NULL){
            new_node -> data -> inter_org = (char*)malloc(MAXLEN*sizeof(char));
            new_node -> data -> name = (char*)malloc(MAXLEN*sizeof(char));
            if(new_node -> data -> inter_org && new_node -> data -> name){
                //getchar();
                scan(new_node);
                getchar();
            } else {
                new_node = NULL;
            }
        } else {
            new_node = NULL;
        }
        new_node -> next = NULL;
        new_node -> prev = NULL;
    }
    return new_node;
}
//Добавление узла в конец списка *
Node *add_last(Head *q)
{
    Node *temp;
    temp = malloc(sizeof(Node));
    malloc_node(temp);
    temp -> next = NULL;
    temp -> id = ((q -> count) + 1);
    temp -> prev = q -> last;
    q -> last -> next = temp;
    q -> last = temp;
    q -> count += 1;
    return temp;
}
//Добавление узла в начало списка
Node *add_first1(Head *q)
{
    Node *temp;
    temp = malloc(sizeof(Node));
    malloc_node(temp);
    temp -> prev = NULL;
    temp -> next = (q -> first);
    temp -> id = 1;
    q -> first -> prev = temp;
    q -> count += 1;
    q -> first = temp;
    increase_id(q, temp -> next);
    return temp;
}

int str_len(char *s)
{
    int r = 0;
    while(s[r] != '\0') r++;
    r--;
    return r;
}

int charToInt(char numeric)
{
    return numeric - 48;
}

void scan(Node *temp)
{
    puts("Enter the state name:");
    fgets(temp -> data -> name , MAXLEN , stdin);
    temp -> data -> name[strlen(temp -> data -> name) - 1] = '\0';
    puts("Enter the international organization:");
    fgets(temp -> data -> inter_org, MAXLEN, stdin);
    temp -> data -> inter_org[strlen(temp -> data -> inter_org) - 1] = '\0';
    puts("Enter the territory of the country:");
    scanf("%d", &temp -> data -> terr);
    puts("Enter the population of the country:");
    scanf("%f", &temp -> data -> pop);
    puts("Enter the population of the capital:");
    scanf("%f", &temp -> data -> pop_cap);
    puts("Enter the year this country joined the inter. org:");
    scanf("%d", &temp -> data -> year_of_entry);
    printf("Enter state establishment data (XXXX XX XX): ");
    scanf("%d %d %d", &temp -> data -> data_of_app[0], &temp -> data -> data_of_app[1], &temp -> data -> data_of_app[2]);
}
//Удаление узла из списка *
void delete_elem(Head *head)
{
    int idd;
    Node *tmp, *tmp1;
    if(head){
        if(head -> count != 0){
            puts("Enter the node id");
            scanf("%d" , &idd);
            if((idd > 0) && (idd <= head -> count)){
                tmp = head -> first;
                if(tmp -> id == idd){
                    if(tmp -> next != NULL){
                        head -> first -> id = 1;
                        decrease_id(head, head -> first -> next);
                    }
                    head -> first = tmp -> next;
                    free_del(tmp);
                } else {
                    while(tmp != NULL){
                        if(tmp -> id == idd){
                            if(head -> last == tmp){
                                head -> last = tmp -> prev;
                                head -> last -> next = NULL;
                                free_del(tmp);
                            } else {
                                tmp -> prev -> next = tmp -> next;
                                tmp -> next -> prev = tmp -> prev;
                                decrease_id(head, tmp);
                                free_del(tmp);
                            }
                            tmp = NULL;
                        } else tmp = tmp -> next;
                    }
                }
                head -> count--;
            } else puts("There is no this id in the list!");
        } else puts("The list is empty!");
    }
    output_list(head);
}
//Уменьшение id
void decrease_id(Head *head, Node *node)
{
    while(node != NULL){
        node -> id--;
        node = node -> next;
    }
}
void free_del(Node *tmp)
{
    free(tmp -> data -> name);
    free(tmp -> data -> inter_org);
    free(tmp -> data);
    free(tmp);
}
//Добавление узла перед последним *
void insert_before_last(Head *head)
{
    Node *node, *tmp;
    if(head){
        puts("\nFill new struct:\n");
        node = get_node();
        if(head -> count == 0){
            head -> first = node;
            head -> last = node;
            node -> id = 1;
        } else {
            tmp = head -> first;
            if(head -> count == 1){
                node -> next = tmp;
                node -> id = 1;
                head -> first = node;
                tmp -> prev = head -> first;
                head -> last = tmp;
                increase_id(head, node -> next);
            } else {
                node -> prev = head -> last -> prev;
                head -> last -> prev -> next = node;
                head -> last -> prev = node;
                node -> next = head -> last;
                node -> id = head -> count;
                increase_id(head, node -> next);
            }
        }
        head -> count++;
    }
    output_list(head);
}
//Увеличение id
void increase_id(Head *head, Node *node)
{
    while(node != NULL){
        node -> id++;
        node = node -> next;
    }
}
