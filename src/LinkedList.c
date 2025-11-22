
#include "tetris.h"

LinkedList_Parent *create_linked_list(int dimension[3][3], char *direction, Color color)
{
    LinkedList_Parent *parent = malloc(sizeof(*parent));

    if (parent != NULL)
    {

        Linked_Node *first = malloc(sizeof(*first));

        if (first != NULL)
        {
            first->color = color;
            memcpy(first->dimension, dimension, sizeof(first->dimension));
            first->next = NULL;
            first->prev = NULL;
            parent->head = first;
        }
        else
        {
            free(parent);
            parent = NULL;
        }
    }

    return parent;
}

Linked_Node *add_node(LinkedList_Parent *parent, int dimension[3][3], char *direction, Color color)
{
    if (parent == NULL)
    {
        return NULL;
    }

    Linked_Node *new_node = malloc(sizeof(*new_node));

    if (new_node != NULL)
    {
        memcpy(new_node->dimension, dimension, sizeof(new_node->dimension));
        new_node->color = color;
        new_node->next = NULL;

        Linked_Node *current = parent->head;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_node;
        new_node->prev = current;
    }

    return new_node;
}

Linked_Node *get_last_node(LinkedList_Parent *parent)
{
    if (parent == NULL)
    {
        return NULL;
    }

    Linked_Node *current = parent->head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    return current;
}

Linked_Node *get_first_node(LinkedList_Parent *parent)
{
    if (parent == NULL)
    {
        return NULL;
    }

    return parent->head;
}

void free_linked_list(LinkedList_Parent *parent)
{
    if (parent == NULL)
    {
        return;
    }

    Linked_Node *current = parent->head;
    Linked_Node *next_node;

    while (current != NULL)
    {
        next_node = current->next;
        free(current->dimension);
        free(current);
        current = next_node;
    }

    free(parent);
}

ScoreList *create_score_list()
{
    ScoreList *list = malloc(sizeof(ScoreList));
    list->size = 1;
    list->capacity = 10;
    list->entries = NULL;

    list->size = 0;
    list->capacity = 0;
    return list;
}

void free_score_list(ScoreList *list)
{
    if (list != NULL)
    {
        free(list->entries);
        list->entries = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}