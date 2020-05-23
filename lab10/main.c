#include "struct.h"
#include "func.h"
#include "user_menu.h"

int main()
{
    Head *ph;

    ph = create_head();
    fill_list(ph);
    command_selecting(ph);
    free_list(ph);

    return 0;
}

























