#include "output.h"

//Вывод списка
void output_list(Head *q)
{
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
    printf("|%2s|%10s |%9s |%10s |%9s |%7s |%5s |%11s|\n","id","State name","Inter org","State terr","State pop","Cap pop","Year","GDP   ");
    printf("+--+-----------+----------+-----------+----------+--------+------+-----------+\n");
}

void node_out(Node *temp)
{
    printf("|%2d|%10s |%9s |%10d |%9.3f |%7.3f |%5d |%11d|\n",
        temp->id,temp->data->name,temp->data->inter_org,temp->data->terr,temp->data->pop,temp->data->pop_cap,temp->data->year_of_entry,temp->data->GDP[0]);
}
void output_menu()
{
    puts("");
    puts("/////        Program menu:        /////");
    puts("||||| 0 - information             |||||");
    puts("||||| 1 - add card                |||||");
    puts("||||| 2 - change card             |||||");
    puts("||||| 3 - delete card             |||||");
    puts("||||| 4 - find card by parameter  |||||");
    puts("||||| 5 - sort cards by parameter |||||");
    puts("||||| 6 - show all cards          |||||");
    puts("||||| 7 - exit                    |||||");
    puts("///////////////////////////////////////");
    puts("Your choose: ");
}

void information(Head *head)
{
    printf("In the main menu you can choose: \n");
    printf("\n The program allows you to work with a list of data\n using the following steps:\n"
           "Add a new card , you will be prompted to enter the data of this card\n"
           "Edit the card fields you want\n"
           "Remove an unnecessary card from the list\n"
           "Sort list by selected attribute\n"
           "Find the cards you need using the search by fields. At the end, \n"
           "you will be asked to save the resulting list to a new file. If you agree,\n"
           "you can do with it all the same actions as with the original list.\n"
           "All other changes with the list are automatically saved in a new file\n");
    Writing_list_to_new_doc(head);
    menu(1);
}
void parameters()
{
    puts("Please choose parameter:");
    puts("1 - Country name(char)");
    puts("2 - International organization(char)");
    puts("3 - Territory(int)");
    puts("4 - Country population(float)");
    puts("5 - Capital population(float)");
    puts("6 - Year of entry(int)");
    puts("7 - GDP of country(int)");
    puts("Your choose:");
}
