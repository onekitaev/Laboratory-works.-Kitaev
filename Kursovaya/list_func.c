#include "list_func.h"

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
void add_first_node(Head *head , Node *node)
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

void free_del(Node *tmp)
{
    free(tmp -> data -> name);
    free(tmp -> data -> inter_org);
    free(tmp -> data);
    free(tmp);
}

void decrease_id(Head *head, Node *node)
{
    while(node != NULL){
        node -> id--;
        node = node -> next;
    }
}

//Увеличение id
void increase_id(Head *head, Node *node)
{
    while(node != NULL){
        node -> id++;
        node = node -> next;
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
    printf("Enter state establishment GDP: ");
    scanf("%d", &temp -> data -> GDP[0]);
}


int sort_by_name(Node *node){
    return (strcmp(node->data->name, node->next->data->name) > 0);
}

int sort_by_inter_org(Node *node){
    return (strcmp(node->data->inter_org, node->next->data->inter_org) > 0);
}

int sort_by_territory(Node *node){
	return (node->data->terr > node->next->data->terr);
}

int sort_by_population(Node *node){
	return (node->data->pop > node->next->data->pop);
}

int sort_by_cap_popul(Node *node){
	return (node->data->pop_cap > node->next->data->pop_cap);
}

int sort_by_year(Node *node){
	return (node->data->year_of_entry > node->next->data->year_of_entry);
}

int sort_by_GDP(Node *node){
	return (node->data->GDP[0] > node->next->data->GDP[0]);
}

void sort_cards(Head *head, int c){
    Node *node = head->first;
	states *tab;
	int check = 1;
    while (check) {
        check = 0;
		node = head->first;
        do{
            if (sort[c](node)) {
                check = 1;
                tab = node->data;
                node->data = node->next->data;
                node->next->data = tab;
            }
			node = node->next;
        }while(node != head->last);
    }
}


void delete_node(Head *head, Node *node){
	if(!head || !node) return;
    if(node == head->first) head->first = node->next;
    else node->prev->next = node->next;

    if(node == head->last) head->last = node->prev;
    else node->next->prev = node->prev;
    head->count--;
    free(node);
}

Head* find_by_terr(Head *head){
	Node* node = head->first;
	int value;
	puts("Enter parameter value:");
	scanf("%d", &value);
	node = head->first;
	while(node){
		if (!(value == node->data->terr)) delete_node(head, node);
		node = node->next;
	}
	return(head);
}

Head* find_by_popul(Head *head){
	Node* node = head->first;
	int value;
	puts("Enter parameter value:");
	scanf("%f", &value);
	node = head->first;
	while(node){
		if (!(value == node->data->pop)) delete_node(head, node);
		node = node->next;
	}
	return(head);
}

Head* find_by_cap_popul(Head *head){
	Node* node = head->first;
	int value;
	puts("Enter parameter value:");
	scanf("%f", &value);
	node = head->first;
	while(node){
		if (!(value == node->data->pop_cap)) delete_node(head, node);
		node = node->next;
	}
	return(head);
}

Head* find_by_year(Head *head){
	Node* node = head->first;
	int min, max, res;
	do{
        puts("Enter a MIN value:");
		res = scanf("%d", &min);
        fflush(stdin);
        if (!res || min < 0){
            puts("Invalid input. Try again.");
            system("pause");
        }
    }while(!res || min < 0);
	do{
        puts("Enter a MAX value:");
		if(scanf("%d", &max)) res++;
        fflush(stdin);
        if (res < 2 || max < 0){
            puts("Invalid input. Try again.");
            system("pause");
        }
    }while(res < 2 || max < 0);
	node = head->first;
	while(node){
			if(!(min <= node->data->year_of_entry && max >= node->data->year_of_entry)) delete_node(head, node);
			node = node->next;
	}
	return(head);
}


Head* find_by_GDP(Head *head){
	Node* node = head->first;
	int min, max, res;
	do{
        puts("Enter a MIN value:");
		res = scanf("%d", &min);
        fflush(stdin);
        if (!res || min < 0){
            puts("Invalid input. Try again.");
            system("pause");
        }
    }while(!res || min < 0);
	do{
        puts("Enter a MAX value:");
		if(scanf("%d", &max)) res++;
        fflush(stdin);
        if (res < 2 || max < 0){
            puts("Invalid input. Try again.");
            system("pause");
        }
    }while(res < 2 || max < 0);
	node = head->first;
	while(node){
			if(!(min <= node->data->GDP[0] && max >= node->data->GDP[0])) delete_node(head, node);
			node = node->next;
	}
	return(head);
}

Head* find_by_name(Head *head){
	Node* node = head->first;
	char *value;
	value = malloc(20 * sizeof(char));
	puts("Enter country name:");
	fflush(stdin);
	fgets(value, 20, stdin);
	node = head->first;
	while(node){
		if (!(strncmp(value, node->data->name, strlen(value) - 1) == 0)) delete_node(head, node);
		node = node->next;
	}
	return(head);
}
Head* find_by_inter_org(Head *head){
	Node* node = head->first;
	char *value;
	value = malloc(20 * sizeof(char));
	puts("Enter international organization name:");
	fflush(stdin);
	fgets(value, 20, stdin);
	node = head->first;
	while(node){
		if (!(strncmp(value, node->data->inter_org, strlen(value) - 1) == 0)) delete_node(head, node);
		node = node->next;
	}
	return(head);
}
