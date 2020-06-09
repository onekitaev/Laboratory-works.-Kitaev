#include "user_menu.h"
//Выбор команды
void command_selecting(Head *q)
{
    char s[MAXLEN];
    int f;
    Node *temp;
    puts("\n1 - Add first\n2 - Add last\n3 - Delete element\n4 - Insert after\n5 - List output\n0 - Exit");
    fgets(s, 200, stdin);
    //перевод char в int. Благодаря этой функции мы можем вводить что угодно и программа не сломается
    f = charToInt(s[0]);
    if(str_len(s) == 1) {
        if (q -> count > 0) {
            if(f == 1) {
                //создание нового узла
                if((q -> count) == 0) temp = create_node(q);
                else {
                    //добавление в начало
                    temp = get_node();
                    add_first1(q, temp);
                }
            }
            if(f == 2) {
                if((q -> count) == 0) temp = create_node(q);
                else {
                    temp = get_node();
                    add_last(q, temp);
                }
            }
            else if(f == 3) delete_elem(q);
            else if(f == 4) {
                temp = get_node();
                insert_after(q, temp);
            }
            else if(f == 5) output_list(q);
        }
        else puts("Fill the list first!");
    }
    while(f != 0) {
        if(str_len(s) == 0) {
            if (q -> count > 0) {
                if(f == 1) {
                    if((q -> count) == 0) temp = create_node(q);
                    else {
                        temp = get_node();
                        add_first1(q, temp);
                    }
                }
                if(f == 2) {
                    if((q -> count) == 0) temp = create_node(q);
                    else {
                        temp = get_node();
                        add_last(q, temp);
                    }
                }
                else if(f == 3) delete_elem(q);
                else if(f == 4) {
                    temp = get_node();
                    insert_after(q, temp);
                }
                else if(f == 5) output_list(q);
            }
            else puts("Fill the list first!");
        }
        puts("\n1 - Add first\n2 - Add last\n3 - Delete element\n4 - Insert after\n5 - List output\n0 - Exit");
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
void add_last(Head *q, Node *temp)
{
    temp -> id = q -> count + 1;
    temp -> next = q -> first;
    temp -> prev = q -> last;
    q -> last -> next = temp;
    q -> first -> prev = temp;
    q -> last = temp;
    q -> count++;
    return temp;
}
//Добавление узла в начало списка
void add_first1(Head *head, Node *temp)
{
    temp -> id = 1;
    temp -> next = head -> first;
    temp -> prev = head -> last;
    head -> last -> next = temp;
    head -> first -> prev = temp;
    head -> first = temp;
    increase_id(head , head -> first -> next);
    head -> count++;
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
    int id;
    Node *tmp;
    tmp = head -> first;
    puts("\nEnter the element`s id:");
    scanf("%d" , &id);
    if((id <= head -> count - 1) && (id > 0)){
        while(tmp != NULL){
            if(tmp -> id == id){
                if(tmp -> next == tmp){ // Если происходит удаление единственного элемента в кольце
                    free_del(tmp);
                    head -> first = NULL;
                    head -> last = NULL;
                } else{
                    if(head -> first == tmp){ // Если удаляется первый элемент в кольце
                        head -> last -> next = tmp -> next;
                        tmp -> next -> prev = head -> last;
                        decrease_id(head, head -> first);
                        head -> first = tmp -> next;
                        free_del(tmp);
                    } else if (head -> last == tmp){ // Если удаляется последний элемент в кольце
                        head -> first -> prev = head -> last -> prev;
                        head -> last -> prev -> next = head -> last -> next;
                        head -> last = head -> last -> prev;
                        free_del(tmp);
                    } else { // Если удаляется не последний и не первый элемент
                        tmp -> next -> prev = tmp -> prev;
                        tmp -> prev -> next = tmp -> next;
                        decrease_id(head, tmp -> next);
                        free_del(tmp);
                    }
                }
                tmp = NULL;
            } else tmp = tmp -> next;
        }
    }
    else puts("There is no element with this id!");
    head -> count--;
    output_list(head);
}
//Добавление элемента списка после элемента, чей номер был введен
void insert_after(Head *head, Node *node)
{
    int id;
    Node *tmp;
    tmp = head -> first;
    puts("\nEnter the element`s id:");
    scanf("%d", &id);
    if(id > head -> count) { // Если такого элемента в кольце нет,то добавляем узел в конец
        node -> next = head -> first;
        node -> id = head -> count + 1;
        node -> prev = head -> last;
        head -> last -> next = node;
        head -> last = node;
        head -> first -> prev = node;
    } else {
        while(tmp != NULL){
            if(tmp -> id == id){
                if(tmp -> next == tmp){ // Если в кольце один узел
                    node -> next = tmp;
                    node -> prev = tmp;
                    tmp -> prev = node;
                    head -> last = node;
                    node -> id = head -> count + 1;
                    tmp -> next = node;
                } else { // Если несколько узлов в кольце
                    if(tmp -> next == head -> first){ // Если элемент является последним
                        node -> id = head -> count + 1;
                        node -> next = head -> first;
                        head -> first -> prev = node;
                        tmp -> next = node;
                        node -> prev = tmp;
                        head -> last = node;
                    } else { // Если элемент не последний
                        node -> next = tmp -> next;
                        tmp -> next -> prev = node;
                        node -> prev = tmp;
                        node -> id = tmp -> next -> id;
                        tmp -> next = node;
                        increase_id(head, node -> next);
                    }
                }
                tmp = NULL;
            } else tmp = tmp -> next;
        }
    }
    head -> count++;
    output_list(head);
}
//Уменьшение id
void decrease_id(Head *head, Node *node)
{
    int i;
    for(i = node -> id; i <= head -> count; i++){
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
//Увеличение id
void increase_id(Head *head, Node *node)
{
    int i;
    for(i = node -> id; i <= head -> count; i++){
        node -> id++;
        node = node -> next;
    }
}
