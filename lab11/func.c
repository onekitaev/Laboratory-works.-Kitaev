#include "func.h"

Head *create_head()
{
    Head *p = NULL;
    p = malloc(sizeof(Head));
    if(p) {
        p -> count = 0;
        p -> first = NULL;
        p -> last = NULL;
    }
    return p;
}
//Создание узла *
Node *create_node(Head *q)
{
    Node *temp;
    temp = malloc(sizeof(Node));
    malloc_node(temp);
    temp -> prev = NULL;
    temp -> next = NULL;
    temp -> id = q -> count + 1;
    q -> count += 1;
    q -> first = temp;
    q -> last = temp;
    return temp;
}
//Выделение памяти под узел
void malloc_node(Node *temp)
{
    temp -> data = malloc(sizeof(states));
    temp -> data -> name = malloc(30 * sizeof(char));
    temp -> data -> inter_org = malloc(30 * sizeof(char));
}
//Заполнение списка
void fill_list(Head *q)
{
    char message[MAXLEN];
    char **mes = NULL;
    int flag = 1, id = 1;
    Node *p, *p1;
    FILE *fp;
    fp = fopen("text.csv", "r");
    if (fp == NULL) puts("There was an error while opening file!");
    else if (q) {
        //Построчно считываем данные из файла
        while(((fgets(message, MAXLEN, fp)) != NULL) && (flag)) {
            //Запись строки в массив строк
            if((mes = split(mes, message)) != NULL){
                //добавление данных в узел
                if((p = adding_to_node(mes, id)) != NULL){
                    if(q -> count == 0) {
                        add_first(q, p);
                    }
                    else {
                        filling(q, p1, p);
                    }
                    p1 = p;
                    id++;
                }else flag = 0;
                clear_array(mes, 9);
            }
            else{
                flag = 0;
                puts("There was an error while reading data from file!");
            }
        }
    }
    fclose(fp);
    output_list(q);
}
//Разбиение строки на подстроки по разделителю
char **split(char **mes, char *string)
{
    int cnt = 0, i, cnt_clear = 0, flag = 1;
    char *sep = ";";
    char *str;
    for(i = 0; i < strlen(string); i++){
        if(string[i] == (*sep)) {
            cnt++;
        }
    }
    if((mes = malloc((cnt + 1)*sizeof(char*))) != NULL) {
        //функция strtok возвращает указатель на первый символ разделенной части строки
        str = strtok(string, sep);
        i = 0;
        if ((mes[i] = malloc((strlen(str) + 1)*sizeof(char))) != NULL) {
            strcpy(mes[i], str);
            cnt_clear++;
            i++;
            //Выделение очередной части строки
            while(((str = strtok(NULL, sep)) != NULL) && (flag != 0)){
                if((mes[i] = malloc((strlen(str) + 1)*sizeof(char))) != NULL){
                    strcpy(mes[i], str);
                    cnt_clear++;
                    i++;
                }
                else {
                    flag = 0;
                    clear_array(mes, cnt_clear);
                    mes = NULL;
                }
            }
        }
        else {
            clear_array(mes, cnt_clear);
            mes = NULL;
        }
    }
    return mes;
}
//Очистка двумерного массива
void clear_array(char **arr, int cnt)
{
    int i;
    for(i = 0; i < cnt; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}
//Функция, добавляющая строку, записанную в двумерном массиве, в узел *
Node *adding_to_node(char **arr, int id)
{
    Node *p;
    if((p = malloc(sizeof(Node))) != NULL){
        if((p -> data = malloc(sizeof(states))) != NULL){
            p -> data -> name = malloc((strlen(arr[0]) + 1)*sizeof(char));
            p -> data -> inter_org = malloc((strlen(arr[1]) + 1)*sizeof(char));
            if(p -> data -> name && p -> data -> inter_org){
                strcpy(p -> data -> name, arr[0]);
                strcpy(p -> data -> inter_org, arr[1]);
                p -> data -> terr = atoi(arr[2]);
                p -> data -> pop = atof(arr[3]);
                p -> data -> pop_cap = atof(arr[4]);
                p -> data -> year_of_entry = atoi(arr[5]);
                p -> data -> data_of_app[0] = atoi(arr[6]);
                p -> data -> data_of_app[1] = atoi(arr[7]);
                p -> data -> data_of_app[2] = atoi(arr[8]);
                p -> id = id;
                p -> next = NULL;
                p -> prev = NULL;
            } else {
                free(p -> data);
                free(p);
                p = NULL;
            }
        } else {
            free(p);
            p = NULL;
        }
    }
    return p;
}
//Добавление первого узла
void add_first(Head *head , Node *node)
{
    if(head && node){
        head -> count++;
        head -> first = node;
        head -> last = node;
    }
}
//Добавление узлов в список *
void filling(Head *head, Node *p1, Node *p)
{
    if(head && p1 && p){
        p1 -> next = p;
        p -> prev = p1;
        head -> last = p;
        head -> count++;
    }
}
//Вывод списка
void output_list(Head *q){
    if((q -> count) > 0) {
        Node *temp = NULL;
        temp = q -> first;
        print_header();
        while((temp -> next) != NULL) {
            node_out(temp);
            temp = temp -> next;
        }
        node_out(temp);
    }
    else printf("\n The list is empty!\n");
}

void print_header()
{
    printf(" ____________________________________________________________________________ \n");
    printf("|%2s|%10s |%9s |%10s |%9s |%7s |%5s |%11s|\n","id","State name","Inter org","State terr","State pop","Cap pop","Year","State app");
    printf("+--+-----------+----------+-----------+----------+--------+------+-----------+\n");
}

void node_out(Node *temp)
{
    printf("|%2d|%10s |%9s |%10d |%9.3f |%7.3f |%5d |%5d %2d %2d|\n",
        temp->id,temp->data->name,temp->data->inter_org,temp->data->terr,temp->data->pop,temp->data->pop_cap,temp->data->year_of_entry,temp->data->data_of_app[0],temp->data->data_of_app[1],temp->data->data_of_app[2]);
}

void free_list(Head *head)
{
    Node *tmp , *p;
    if(head){
        p = head -> first;
        while(p != NULL){
            tmp = p -> next;
            free(p -> data -> name);
            free(p -> data -> inter_org);
            free(p -> data);
            free(p);
            p = tmp;
        }
        free(head);
        head = NULL;
    }
}

