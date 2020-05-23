#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
typedef struct state {
    char *name; //Название государства
    char *inter_org; //Название международной организации
    int terr; //Территория страны
    float pop; //Население страны в миллионах
    float pop_cap; // Население столицы в миллионах
    int year_of_entry; //Год вступления в организацию
    int data_of_app[3]; //Дата основания государства
}states;

int OutputKind(int n, states **str0, int (*funcName)(states**, int), char *str1, int len);
void print_header();
char **simple_split(char *str, int length, char sep);
void ClearStringArray(char **str, int n);
states *struct_fill(char **str);
void struct_out(states *str0);
void ClearStructure(states **str0, int n);
char state_name(states **str0, int i0);
char international_organizations(states **str0, int i0);
void new_gets(char *s, int lim);
void sort_course(int n, states **str0);
states *add_records();
int main()
{
    setlocale(LC_ALL, "RUS");
    enum {maxlen = 128};
    states **states0 = NULL;
    char (**kind)(states**, int) = NULL;
    char **s2 = NULL;
    char s1[maxlen];
    char sep = ';';
    char *Nam;
    int n, i, slen, option, printed, inp, add, m, add1;
    FILE *df;
    n = 0;
    add = 0;
    m = 2;
    fflush(stdin);
    if((df = fopen("text.csv","r")) != NULL){
        //Нахождение количества строк в файле
        while((fgets(s1, maxlen, df)) != NULL) n++;
        rewind(df);
        printf("Hello! You have a structure. Do you want to add something?\n");
        do
        {
            printf("1 - Yes\n");
            printf("2 - No\n");
            scanf("%d", &inp);
            fflush(stdin);
        } while((inp < 1) || (inp > 2));
        if (inp == 1) {
            printf("How many states do you want to add: ");
            scanf("%d", &add1);
            fflush(stdin);
            add = add1;
        }
        n = n + add;
        //Выделение памяти под структуру
        if((states0 = (states**)malloc(n*sizeof(states*))) != NULL) {
            //Заполнение структуры
            for (i = 0; i < n - add; i++) {
                fgets(s1, maxlen, df);
                s1[strlen(s1)] = '\0';
                s2 = simple_split(s1, strlen(s1), sep);
                if (s2 != NULL) {
                    states0[i] = struct_fill(s2);
                    if (states0[i] == NULL) puts("Structure not allocated!");
                }
                else puts("Error at data reading!");
            }
            //Дополнение элементов массива при вводе с клавиатуры
            if (inp == 1) {
                for (i = n - add; i < n; i++){
                    states0[i] = add_records();
                }
            }
        }
        else puts("No memory allocation!");
        fclose(df);
        kind = malloc(m *sizeof(int(*)(states**, int)));
        //Выбор сортировки, либо вывод структуры
        if((states0 != NULL) && (kind != NULL)){
            kind[0] = state_name;
            kind[1] = international_organizations;

            do
            {
                printf("Kinds of sort:\n");
                printf("1 - state name\n");
                printf("2 - international organizations\n");
                printf("3 - show full table\n");
                printf("Enter your choice: ");
                scanf("%d", &option);
                system("cls");
                if (option == 3) {
                    print_header();
                    for(i = 0; i < n; i++){
                        struct_out(states0[i]);
                    }
                }
            } while((option < 1) || (option > 2));
            //Сортировка структуры по введенной строки
            printf("Enter name: ");
            Nam = (char*)malloc(maxlen*sizeof(char));
            fflush(stdin);
            new_gets(Nam, maxlen);
            slen = strlen(Nam);
            sort_course(n, states0);
            printed = OutputKind(n, states0, kind[option - 1], Nam, slen);
            if(printed == 0) printf("\nThere's no such name\n");
            ClearStructure(states0, n);
        }
        else puts("Unable to make functions!");
        if(states0 != NULL){
            free(states0);
            states0 = NULL;
        }
        if(kind != NULL){
            free(kind);
            kind = NULL;
        }
    }
    else puts("File not found!");
    return 0;
}
//Вывод заголовка таблицы
void print_header()
{
    printf(" _________________________________________________________________________ \n");
    printf("|%10s |%9s |%10s |%9s |%7s |%5s |%11s|\n","State name","Inter org","State terr","State pop","Cap pop","Year","State app");
    printf("+-----------+----------+-----------+----------+--------+------+-----------+\n");
}

char **simple_split(char *str, int length, char sep)
{
    char **str_array = NULL;
    int i, j, k, m, key, count;
    //Подсчет слов в строке
    for(j = 0, m = 0; j < length; j++){
        if(str[j] == sep) m++;
    }
    key = 0;
    //Выделение памяти под массив строк
    str_array = (char**)malloc((m + 1)*sizeof(char*));
    if(str_array != NULL) {
        for(i = 0, count = 0; i <= m; i++, count++) {
            //Выделение памяти под каждую отдельную строку
            str_array[i] = (char*)malloc(length*sizeof(char));
            if(str_array[i] != NULL) key = 1;
            else {
                key = 0;
                i = m;
            }
        }
        if(key) {
            k = 0;
            m = 0;
            for(j = 0; j < length; j++) {
                if(str[j] != sep) str_array[m][j - k] = str[j];
                else {
                    str_array[m][j - k] = '\0';
                    k = j + 1;
                    m++;
                }
            }
        }
        else {
            puts("ERROR at string allocation!\n");
            ClearStringArray(str_array, count);
        }
     }
     return str_array;
}
//Функция очистки памяти, выделенной под двумерный массив
void ClearStringArray(char **str, int n)
{
    int i;
    for(i = 0; i < n; i++) {
        free(str[i]);
        str[i] = NULL;
    }
    free(str);
    str = NULL;

}

states *struct_fill(char **str)
{
    states *str0 = NULL;
    str0 = (states*)malloc(sizeof(states));
    if(str0 != NULL) {
        str0 -> name = str[0];
        str0 -> inter_org = str[1];
        str0 -> terr = atoi(str[2]);
        str0 -> pop = atof(str[3]);
        str0 -> pop_cap = atof(str[4]);
        str0 -> year_of_entry = atoi(str[5]);
        str0 -> data_of_app[0] = atoi(str[6]);
        str0 -> data_of_app[1] = atoi(str[7]);
        str0 -> data_of_app[2] = atoi(str[8]);
    }
    return str0;
}
void ClearStructure(states **str0, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        free(str0[i] -> name);
        str0[i] -> name = NULL;
        free(str0[i] -> inter_org);
        str0[i] -> inter_org = NULL;
    }
    free(str0);
}
void struct_out(states *str0)
{
    printf("|%10s |%9s |%10d |%9.3f |%7.3f |%5d |%5d %2d %2d|\n",
        str0->name,str0->inter_org,str0->terr,str0->pop,str0->pop_cap,str0->year_of_entry,str0->data_of_app[0],str0->data_of_app[1],str0->data_of_app[2]);
}

char state_name(states **str0, int i0)
{
    return str0[i0] -> name;
}
//Функция, при помощи которой добавляются структуры путем ввода их с клавиатуры
states *add_records()
{
    states *tab;
    int i, c;
    c = ' ';
    i = 0;
    if ((tab = malloc(sizeof(states))) != NULL) {
        tab -> name = malloc(sizeof(char) * 20);
        printf("Enter name: ");


        while (c != '\n') {
            c = getchar();
            tab -> name[i] = c;
            i++;
        }
        tab -> name[i - 1] = '\0';
        fflush(stdin);
        c = ' ';
        i = 0;
        tab -> inter_org = malloc(sizeof(char) * 20);
        printf("Enter name of international organization: ");
        while (c != '\n'){
            c = getchar();
            tab -> inter_org[i] = c;
            i++;
        }
        tab -> inter_org[i - 1] = '\0';
        fflush(stdin);
        printf("Enter territory of coutry: ");
        scanf("%d", &tab -> terr);
        fflush(stdin);
        printf("Enter population: ");
        scanf("%f", &tab -> pop);
        fflush(stdin);
        printf("Enter population of capital: ");
        scanf("%f", &tab -> pop_cap);
        fflush(stdin);
        printf("Enter year of entry into organization: ");
        scanf("%d", &tab -> year_of_entry);
        fflush(stdin);
        printf("Enter data of appearance (XXXX XX XX): ");
        scanf("%d %d %d", &tab -> data_of_app[0], &tab -> data_of_app[1], &tab -> data_of_app[2]);
        fflush(stdin);
        puts("Press any key...");
        getchar();
        system("cls");
    }
    return (tab);
}

char international_organizations(states **str0, int i0)
{
    return str0[i0] -> inter_org;
}
void new_gets(char *s, int lim)
{
    char c;
    int i;
    i = 0;
    while(((c = getchar()) != '\n') && (i < lim - 1))
    {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
}
//Сортировка структуры по убыванию значений последнего числового поля
void sort_course(int n, states **str0)
{
    states *tmp_struct;
    int i, j;
    for(i = 0; i < n; i = i + 1) {
        for(j = 0; j < n - i - 1; j = j + 1) {
            if(str0[j] -> year_of_entry > str0[j + 1] -> year_of_entry) {
                tmp_struct = str0[j];
                str0[j] = str0[j + 1];
                str0[j + 1] = tmp_struct;
            }
        }
     }
}
//Вывод отсортированной структуры в зависимости от выбора пользователя
int OutputKind(int n, states **str0, int (*funcName)(states**, int), char *str1, int len)
{
    int i, count, k, flag;
    char *string = NULL;
    count = 0;
    flag = 0;
    print_header();
    for(i = 0; i < n; i++) {
        string = funcName(str0, i);
        for (k = 0; k < strlen(string); k++) {
            if (string[k] == str1[k]) flag++;
        }
        if (flag == strlen(string)) {
            struct_out(str0[i]);
            count++;
        }
        flag = 0;
        free(string);
        string = NULL;
    }
    return count;
}
