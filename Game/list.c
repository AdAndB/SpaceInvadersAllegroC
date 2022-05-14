#include "game_header.h"
/** \file list.c
 * Plik �r�d�owy list.
 * Zawiera definicje funkcji obs�ugujacych list�.
 */

 /**
*Funkcja dodaje element do listy.
*
*Je�li lista jest pusta, tworzy j� i dodaje pierwszy element. W przypadku, gdy ju� znajduj� si� na niej elementy,
* nowy element jest dodawany na nast�pn� pozycj�.
*@param node podw�jny wska�nik na liste
*@param Damage obra�enia przedmiotu
*@param X wsp�rz�dna x przedmiotu
*@param Y wsp�rz�dna y przedmiotu
*@param Speed szybko�� przedmiotu
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
*Funkcja usuwa element z pocz�tku listy.
*
*Funkcja sprawdza najpierw czy istnieje kolejny element listy. Je�li nie, to usuwany element jest
* ostatnim elementem listy.  W innym przypadku, w polu prev kolejnego elementu
* zapisywana jest wartosc NULL. Stanie si� on wtedy pierwszym elementem listy. Nast�pnie zwalniany
* jest dotychczasowy pocz�tkowy element.
*@param front wska�nik na pocz�tkowy element listy
*@return next - wska�nik na nowy pocz�tkowy element listy
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
*Funkcja usuwa element z wn�trza listy.
*
*Funkcja zmienia adresy przypisane do pola next elementu poprzedz�jacego usuwany oraz pola prev elementu
* nast�pnego w taki spos�b, �e element usuwany zostaje wy��czony z listy. Nast�pnie nast�puje zwolnienie pami�ci.
*@param node wska�nik na element listy do usuni�cia
*/
void delete_within(struct dll_node* node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    free(node);
    node = NULL;
}

/**
*Funkcja usuwa ostatni element na li�cie.
*
*Funkcja si�ga do elementu przedostatniego i w jego polu next zapisuje
*warto�� NULL. W ten spos�b element stanie si� ostatnim na li�cie. Nast�pnie funkcja zwalnia pami��.
*@param back wska�nik na ostatni element listy
*/
void delete_back(struct dll_node* back)
{
    back->prev->next = NULL;
    free(back);
    back = NULL;

}

/**
*Funkcja g��wna usuwaj�ca element listy.
*
*Funkcja sprawdza najpierw czy lista jest pusta. Nast�pnie sprawdzane jest po�o�enie elementu do usuni�cia i w zale�no�ci od tego
*wywo�ywana jest jedna z trzech funkcji pomocniczych (delete_front, delete_within, delete_back).
*@param front podw�jny wska�nik na pierwszy element listy
*@param toDelete wska�nik na element do usuni�cia
*@return 1 - je�li element zosta� usuni�ty
*@return 0 - je�li lista jest pusta
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
*Funkcja usuwa elementy listy, dop�ki wska�nik front jest r�ny od NULL.
*@param front podw�jny wska�nik na pocz�tkowy element listy
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
