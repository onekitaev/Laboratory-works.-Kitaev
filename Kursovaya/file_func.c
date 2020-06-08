#include "file_func.h"

void fill_list(Head *q, int flag1)
{
    char message[MAXLEN];
    char **mes = NULL;
    int flag = 1, id = 1;
    Node *p, *p1;
    FILE *fp;
    if (flag1 == 0) fp = fopen("text.csv", "r");
    else if (flag1 == 1) fp = fopen("text1.csv", "r");
    if (fp == NULL) puts("There was an error while opening file!");
    else if (q) {
        //Построчно считываем данные из файла
        while(((fgets(message, MAXLEN, fp)) != NULL) && (flag)) {
            //Запись строки в массив строк
            if((mes = split(mes, message)) != NULL){
                //добавление данных в узел
                if((p = adding_to_node(mes, id)) != NULL){
                    if(q -> count == 0) {
                        add_first_node(q, p);
                    }
                    else {
                        filling(q, p1, p);
                    }
                    p1 = p;
                    id++;
                }else flag = 0;
                clear_array(mes, 7);
            }
            else{
                flag = 0;
                puts("There was an error while reading data from file!");
            }
        }
    }
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
                p -> data -> GDP[0] = atoi(arr[6]);
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

void Writing_list_to_new_doc(Head* head){
    FILE *df;
    df = fopen("text1.csv", "w");
    if (df == NULL){
    	puts("Unable to open file!");
    	return;
	}
    Node* node = head->first;
    char* str;
    for(node = head->first; node != NULL; node = node->next) {
        str = writing_struct_to_string(node->data);
        fwrite(str, sizeof(char), strlen(str), df);
        fflush(df);
    }
    fclose(df);
}

char *writing_struct_to_string(states* st){
    char sep[2] = ";";
    char *str = malloc(MAXLEN * sizeof(char));
    if (!str) return NULL;
    //Запись структуры в строку
    strncpy(str, st->name,strlen(st->name)+1);
    sprintf(str, "%s" "%s", str, sep);
    sprintf(str, "%s" "%s" "%s", str, st->inter_org, sep);
    sprintf(str, "%s" "%d" "%s", str, st->terr, sep);
    sprintf(str, "%s" "%.1f" "%s", str, st->pop, sep);
    sprintf(str, "%s" "%.1f" "%s", str, st->pop_cap, sep);
    sprintf(str, "%s" "%d" "%s", str, st->year_of_entry, sep);
    sprintf(str, "%s" "%d" "%s\n", str, st->GDP[0], sep);
    str = realloc(str, (strlen(str)+1) * sizeof(char));
    str[strlen(str)] = '\0';
    return str;
}

states *structure_filling() {
    states *st;
    st = malloc(sizeof(states));

    if (!st) return NULL;
    st->name = malloc((sizeof(char) * 20) + 1);
    if (!st->name) return NULL;
	printf("Enter name: ");
    fgets(st->name, 20, stdin);
	int slen = strlen(st->name);
    st->name[slen-1] = '\0';
    st->inter_org = malloc((sizeof(char) * 20) + 1);
    if (!st->inter_org) return NULL;
    printf("Enter international organization: ");
    fgets(st->inter_org, 20, stdin);
	slen = strlen(st->inter_org);
    st->inter_org[slen-1] = '\0';
    printf("Enter territory: ");
    st->terr = reading_int();
    printf("Enter population of country: ");
    st->pop = reading_float();
    printf("Enter capital population: ");
    st->pop_cap = reading_float();
    printf("Enter year: ");
    st->year_of_entry = reading_int();
    printf("Enter GDP of country: ");
    st->GDP[0] = reading_int();
    system("cls");

    return (st);
}

float reading_float(){
    float read;
    int res;
	do{
    	res = scanf("%f", &read);
    	fflush(stdin);
        if (!res || read < 0) puts("Incorrect value. Try again");
	}while(!res);
    return read;
}

int reading_int(){
    int read, res;
	do{
    	res = scanf("%d", &read);
    	fflush(stdin);
        if (!res || read < 0) puts("Incorrect value. Try again");
	}while(!res || read < 0);
    return read;
}
