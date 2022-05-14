#include "game_header.h"
/** \file list.c
 * Plik Ÿród³owy list.
 * Zawiera definicje funkcji obs³ugujacych listê.
 */

 /**
*Funkcja dodaje element do listy.
*
*Jeœli lista jest pusta, tworzy j¹ i dodaje pierwszy element. W przypadku, gdy ju¿ znajduj¹ siê na niej elementy,
* nowy element jest dodawany na nastêpn¹ pozycjê.
*@param node podwójny wskaŸnik na liste
*@param Damage obra¿enia przedmiotu
*@param X wspó³rzêdna x przedmiotu
*@param Y wspó³rzêdna y przedmiotu
*@param Speed szybkoœæ przedmiotu
*/
void append(struct dll_node** node, int Damage, int X, int Y, int Speed)
{
    struct dll_node* tmp;
    if (*node)
    {
        if ((*node)->next)
        {
            append(&(*node)->next, Damage, X, Y, Speed);

        }
        else
        {
            (*node)->next = (struct dll_node*)malloc(sizeof(struct dll_node));
            (*node)->next->item.exclusive_info = Damage;
            (*node)->next->item.x = X;
            (*node)->next->item.y = Y;
            (*node)->next->item.speed = Speed;
            (*node)->next->next = NULL;
            (*node)->next->prev = *node;

        }
    }
    else
    {
        (*node) = (struct dll_node*)malloc(sizeof(struct dll_node));
        (*node)->item.exclusive_info = Damage;
        (*node)->item.x = X;
        (*node)->item.y = Y;
        (*node)->item.speed = Speed;
        (*node)->next = NULL;
        (*node)->prev = NULL;

    }
}

/**
*Funkcja usuwa element z pocz¹tku listy.
*
*Funkcja sprawdza najpierw czy istnieje kolejny element listy. Jeœli nie, to usuwany element jest
* ostatnim elementem listy.  W innym przypadku, w polu prev kolejnego elementu
* zapisywana jest wartosc NULL. Stanie siê on wtedy pierwszym elementem listy. Nastêpnie zwalniany
* jest dotychczasowy pocz¹tkowy element.
*@param front wskaŸnik na pocz¹tkowy element listy
*@return next - wskaŸnik na nowy pocz¹tkowy element listy
*/
struct dll_node* delete_front(struct dll_node* front)
{
    struct dll_node* next = front->next;
    if (NULL != next)
        next->prev = NULL;
    free(front);
    front = NULL;
    return next;
}

/**
*Funkcja usuwa element z wnêtrza listy.
*
*Funkcja zmienia adresy przypisane do pola next elementu poprzedz¹jacego usuwany oraz pola prev elementu
* nastêpnego w taki sposób, ¿e element usuwany zostaje wy³¹czony z listy. Nastêpnie nastêpuje zwolnienie pamiêci.
*@param node wskaŸnik na element listy do usuniêcia
*/
void delete_within(struct dll_node* node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    free(node);
    node = NULL;
}

/**
*Funkcja usuwa ostatni element na liœcie.
*
*Funkcja siêga do elementu przedostatniego i w jego polu next zapisuje
*wartoœæ NULL. W ten sposób element stanie siê ostatnim na liœcie. Nastêpnie funkcja zwalnia pamiêæ.
*@param back wskaŸnik na ostatni element listy
*/
void delete_back(struct dll_node* back)
{
    back->prev->next = NULL;
    free(back);
    back = NULL;

}

/**
*Funkcja g³ówna usuwaj¹ca element listy.
*
*Funkcja sprawdza najpierw czy lista jest pusta. Nastêpnie sprawdzane jest po³o¿enie elementu do usuniêcia i w zale¿noœci od tego
*wywo³ywana jest jedna z trzech funkcji pomocniczych (delete_front, delete_within, delete_back).
*@param front podwójny wskaŸnik na pierwszy element listy
*@param toDelete wskaŸnik na element do usuniêcia
*@return 1 - jeœli element zosta³ usuniêty
*@return 0 - jeœli lista jest pusta
*@see delete_front() delete_within() delete_back()
*/
int delete_node(struct dll_node** front, struct dll_node* toDelete)
{
    if (NULL == *front || toDelete == NULL) {
        return 0;
    }
    if ((*front) == toDelete)
    {
        (*front) = delete_front((*front));

        return 1;
    }
    struct dll_node* node = toDelete;
    if (NULL != node)
    {
        if (NULL != node->next)
            delete_within(node);
        else
            delete_back(node);
    }
    return 1;
}


/**
*Funkcja usuwa liste.
*
*Funkcja usuwa elementy listy, dopóki wskaŸnik front jest ró¿ny od NULL.
*@param front podwójny wskaŸnik na pocz¹tkowy element listy
*/
void remove_list(struct dll_node** front)
{
    struct dll_node* next;
    while (*front)
    {
        next = (*front)->next;
        free(*front);
        *front = next;
    }
    *front = NULL;
}
