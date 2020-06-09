#include <stdio.h>
#include <stdlib.h>
/*
Структура содержит 4 битовых поля типа unsigned char по 1 байту каждое.
Значения полей структуры задаются шестнадцатеричными кодами.
Разработать алгоритм и реализовать функцию побитового умножения каждого поля на заданную маску
(маска задается шестнадцатеричным кодом). Вывести результаты в виде шестнадцатеричных значений полей структуры.
*/

int main()
{
	struct {
	unsigned char a1 : 8;
	unsigned char a2 : 8;
	unsigned char a3 : 8;
	unsigned char a4 : 8;
	} IP;

    unsigned a1, a2, a3, a4, mask;
    printf("Please enter an IP-address\n");
    scanf("%x.%x.%x.%x", &a1, &a2, &a3, &a4);
    printf("Enter mask\n");
    scanf("%x", &mask);
    IP.a1 = a1 & mask;
    IP.a2 = a2 & mask;
    IP.a3 = a3 & mask;
    IP.a4 = a4 & mask;
    printf("Received IP\n");
    printf("%x.%x.%x.%x", IP.a1, IP.a2, IP.a3, IP.a4);

	return 0;
}
/*Пример: 2f.7b.11.ed
Маска: 2c
Ответ: 2c.28.0.2c
*/
