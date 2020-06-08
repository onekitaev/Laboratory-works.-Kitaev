#include "menu.h"

void menu(int flag)
{
    int opt;
    Head *ph;
    ph = create_head();
    fill_list(ph, flag);
    do{
        output_menu();
        scanf("%d",&opt);
        fflush(stdin);
        if(opt == 7){
            free_list(ph);
            return;
        }
        if (opt > 7 || opt < 0){
            puts("Wrong entry");
        }
    }while(opt > 7 || opt < 0);
    if(opt == 0) information(ph);
    if(opt == 1) menu_add_element(ph, flag);
    if(opt == 2) menu_change_element(ph, flag);
    if(opt == 3) menu_delete_element(ph, flag);
    if(opt == 4) menu_find_element(ph, flag);
    if(opt == 5) menu_sort_element(ph, flag);
    if(opt == 6) menu_output_list(ph, flag);
}

void menu_delete_element(Head* head, int flag){
    int idd;
    Node *tmp;
    if(!head->count){
		puts("No elements in list!");
		if (flag == 0) menu(0);
		else menu(1);
	}
    else {
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
		Writing_list_to_new_doc(head);
    	menu(1);
	}
	return;
}

void menu_output_list(Head* head, int flag){
	if(!head->count){
		puts("No elements in list!");
        if (flag == 0) menu(0);
		else menu(1);
	}
    else output_list(head);
    Writing_list_to_new_doc(head);
    menu(1);
}

void menu_add_element(Head* head, int flag){
	int uid;
    Node *node , *tmp;
    if(head){
        if(head->count != 0){
            puts("\nFill new struct\n");
            node = get_node();
            puts("\nEnter element`s id");
            scanf("%d" , &uid);
            if((uid > 0) && (uid <= head->count)){
                tmp = head->first;
                if(tmp->id == uid){
                    head->first->prev = node;
                    node->next = head->first;
                    head->first = node;
                    node->id = 1;
                } else {
                    while(tmp != NULL){
                        if(tmp->id == uid){
                            node->next = tmp;
                            node->id = tmp->id;
                            node->prev = tmp->prev;
                            tmp->prev->next = node;
                            tmp->prev = node;
                            tmp = NULL;
                        } else tmp = tmp->next;
                    }
                }
                increase_id(head,node->next);
                head->count++;
            }
            else if((uid > 0) && (uid == head->count+1)) {

                tmp = head->first;

                while(tmp->id != uid-1){
                    tmp = tmp->next;
                }
                if(tmp->next == NULL){
                    tmp->next = node;
                    head->last = node;
                    node->prev = tmp;
                    node->id = head->count+1;
                }
            }
            else puts("There is no this id in the list! Or trying to add before the first element!");
        } else puts("Fill the list first!");
    }
    output_list(head);
	if(head){
		puts("Structure successfully added!");
		Writing_list_to_new_doc(head);
		menu(1);
	}
}

void menu_sort_element(Head* head, int flag){
    int c;
	if(!head->count){
		puts("No elements in list!");
		menu(flag);
	}
    else{
        do{
            parameters();
            scanf("%d",&c);
            fflush(stdin);
            if (c > 9 || c < 1) puts("Error entry. Try again.");
        }while(c > 9 || c < 1);
		sort[1] = sort_by_name;
		sort[2] = sort_by_inter_org;
		sort[3] = sort_by_territory;
        sort[4] = sort_by_population;
        sort[5] = sort_by_cap_popul;
        sort[6] = sort_by_year;
        sort[7] = sort_by_GDP;
		sort_cards(head, c);
		Writing_list_to_new_doc(head);
    	menu(1);
	}
	return;
}

void menu_change_element(Head* head, int flag){
    int c, i;
    if(!head->count){
		puts("No elements in list!");
		menu(flag);
	}
    else {
		Node *node = head->first;
        states *st = malloc(sizeof(states));
        do{
            output_list(head);
            puts("Please enter number of the structure what do you want to change:");
            scanf("%d",&c);
            fflush(stdin);
            if (c <= 0) puts("Error entry. Try again.");
        }while(c <= 0);
        if(c > head->count) puts("Not enough elements in list to change!");
        else{
            i = 1;
            while(i != c){
                node = node -> next;
                i++;
            }
            st = structure_filling();
            node->data = st;
        }
		Writing_list_to_new_doc(head);
    	menu(1);
	}
	return;
}



void menu_find_element(Head* head, int flag){
    int c;
	if(!head->count){
		puts("No elements in list!");
		menu(flag);
	}
    else{
		Head *head0 = head;
		int end, save, cnt, c;
        find[1] = find_by_name;
        find[2] = find_by_inter_org;
        find[3] = find_by_terr;
        find[4] = find_by_popul;
        find[5] = find_by_cap_popul;
        find[6] = find_by_year;
        find[7] = find_by_GDP;
		do{
            do{
                parameters();
                scanf("%d",&c);
                fflush(stdin);

                if (c > 8 || c < 1){
                    puts("Invalid input. Try again.");
                }
            }while(c > 8 || c < 1);
			head0 = find[c](head0);
			Node *node = head0->first;
			cnt = 0;
			while(node){
				cnt++;
				node = node->next;
			}
			if(cnt){
				output_list(head0);
				puts("Do you want to add another condition to search?");
				puts("||   1 - YES   ||");
				puts("||   0 - NO    ||");
				scanf("%d", &end);
                if (end == 0) {
                    puts("Do you want to save result?");
                    puts("||   1 - YES   ||");
				    puts("||   0 - NO    ||");
                    scanf("%d", &save);
                    if(save == 1) Writing_list_to_new_doc(head);
                }
			}
			else{
				puts("No elements in list!");
				end = 0;
			}
		}while(end);
    	menu(1);
	}
	return;
}
