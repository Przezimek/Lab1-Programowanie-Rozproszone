#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/********************************************************************
*Struktora do przechowywania węzła listy: 			*
* -wskaźnik na kolejny węzeł 					*
* -wskaźnik na poprzedni węzeł 					*
* -długość napisu w środku, inicjalnie 0, po tym iterujemy	*
* -ilość miejsca na napis, inicjalnie 32 			*
* -wskaźnik na napis wewnątrz 					*
*********************************************************************/
typedef struct node // WĘZEŁ LISTY
{
struct node *next; // ->
struct node *prev;  // <-
int length; // 0
int size;   // 0/32 -> 32/64
char* str;  //   char[  ] -> realloc pod to samo miejsce, size x2
} node;

typedef struct OrganizacjaListy
{
struct node *first;
struct node *last;
struct node *actual;
int counter;
int max_size;
} OrgList;
/********************************************************************
*Funkcja dodająca znak do węzła (adres węzła, znak do dodania) *
* poczatkowo sprawdzenie czy napis się zmieści, *
* jeśli się nie zmieści to alokujemy 2 razy tyle pamięci co było *
* *
* wpisanie znaku pod i=rozmiar napisu + 1 *
* *
*********************************************************************/
void append(node *node, char c) // add, DODAJ WĘZEŁ
{
if (node->length == node->size) // wstępny warunek na to czy dodatkowy char sie zmiesci w napisie
{
node->size *= 2; // powiekszanie pamieci ze wspolczynnikiem x 2
node->str = realloc(node->str, node->size);
}
node->str[node->length++] = c; // dopisujemy znak do str[aktualna dlugosc napisu++]
}
/********************************************************************
*Funkcja wyświetlacjąca napis ze środka węzła(adres węzła) *
* wyczyszczenie linii po poprzenim napisie *
* wypisanie napisu z danego węzła listy *
* *
* *
* *
*********************************************************************/
void display(node *node)
{
printf("\r                                                                               \r"); // powrót do początku linii wypisanie 79 spacji i powrót do początku linii (CR) - szerokosc konsoli
for (int i = 0; i < node->length; i++)
printf("%c", node->str[i]); // wypisanie calej tablicy znakow spod str[] w petli
}

int main()
{
int c;

node* head = (node *)malloc(sizeof(node)); // inicjalizacja pierwszego węzła listy(głowa), alokacja pamieci pod strukture
head->length = 0; // inicjalnie długość napisu w środku: 0
head->prev = NULL; // inicjalnie nie ma el. poprzedniego, wskaźnik wskazuje na nulla
head->next = NULL; // inicjalnie nie ma el. następnego, wskaźnik wskazuje na nulla
head->size = 32; // inicjalnie ilość miejsca na napis w środku : 32
head->str = (char*)malloc(head->size); // alokacja pamięci pod napis wewnątrz struktury

OrgList* organizer = (OrgList *)malloc(sizeof(OrgList));
organizer->first = head->prev;
organizer->last = head->next;
organizer->actual = head;
organizer->counter = 0 ;
organizer->max_size = 10;

do // główna pętla programu
{
c = getch(); //pobiera każdy znak z klawiatury
if (c == ',') //sterowanie na przyciskach < > ,przesuwa w lewo
{
if (head->prev) // sprawdzenie czy w ogóle jest węzeł wcześniej
{
head = head->prev; // przesuniecie glowy w <-
display(head);
}
}
else if (c == '.') //sterowanie na przyciskach < > .przesuwa w prawo
{
if (head->next) // sprawdzenie czy w ogóle jest węzeł później
{
head = head->next; // przesuniecie glowy w ->
display(head);
}
}
else if (c == '\r') // enter wprowadza kolejny el. do pamięci -> nowy węzeł listy
{
if (organizer->counter > 10)
{
//tu kod na zwolnienie najstarszego wezla i przebudowanie listy
}
printf("\r                                        \r"); // ewentualnie możemy po każdym wpisie dać nową linię
node *oldHead = head; // przepisanie głowy listy do oldHead
while (head->next != NULL) // dopóki są kolejne elementy listy
head = head->next; // przepisujemy kolejny element do wcześniejszego
head->length = oldHead->length;
head->size = oldHead->size;
head->str = realloc(head->str, head->size);
memcpy(head->str, oldHead->str, head->length);
head->next = (node*)malloc(sizeof(node));
head->next->prev = head;
head = head->next;
head->length = 0;
head->next = NULL;
head->size = 32;
head->str = (char*)malloc(head->size);
}
else
{
printf("%c", c);
append(head, c);
}
} while (1);
}
