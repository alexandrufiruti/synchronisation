#include "node.h"
#include <stdlib.h>
#include <stdio.h>

void print_node(struct Node* s)
{
	printf("%d ", s->data);
}

void add_node(struct Node** head, int data)
{
	struct Node* new_node;
	new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->data = data;
	new_node->next = NULL;
	new_node->callback = &print_node;
	if (*head == NULL)
		*head = new_node;
	else
	{
		struct Node* current_node;
		current_node = *head;
		while(current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}

void delete_node(struct Node** head, int data)
{
	if (*head == NULL)
			printf("List is empty!\n");
	else
	{
		struct Node* current_node;
		current_node = *head;
		if(current_node->data == data)
		{
			//delete head
			struct Node* next_node = current_node->next;
			free((void *)*head);
			*head = next_node;
			return;
		}
		while(current_node->next->data != data)
		{
			current_node = current_node->next;
			if(current_node->next == NULL)
				return;
		}
		struct Node* next_node = current_node->next->next;
		free((void *)current_node->next);
		current_node->next = next_node;
		}
}

void print_list(struct Node** head)
{
	if (*head == NULL)
		printf("List is empty!\n");
	else
	{
		struct Node* current_node;
		current_node = *head;
		while(current_node != NULL)
		{
			(*current_node->callback)(current_node);
			current_node = current_node->next;
		}
		printf("\n");
	}
}

void sort_list(struct Node** head)
{
	//Bubble Sort implementation

    int swapped, i;
    struct Node *ptr1;
    struct Node *end = NULL;

    if (*head == NULL)
        printf("List is empty!\n");
    else
    {
		do
		{
			swapped = 0;
			ptr1 = *head;

			while (ptr1->next != end)
			{
				if (ptr1->data > ptr1->next->data)
				{
					swap(ptr1, ptr1->next);
					swapped = 1;
				}
				ptr1 = ptr1->next;
			}
			end = ptr1;
		}
		while (swapped);
    }
}

void flush_list(struct Node** head)
{
	if (*head == NULL)
		printf("List is empty!\n");
	else
	{
		struct Node* current_node;
		current_node = *head;
		struct Node* next_node;
		while(current_node != NULL)
		{
			next_node = current_node->next;
			free((void *)current_node);
			current_node = next_node;
		}
		*head = NULL;
	}
}

void swap(struct Node *a, struct Node *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
