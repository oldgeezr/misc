#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
	list_t list;
	list = (list_t)malloc(sizeof(list));
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	
	return list;
}

void list_delete(list_t list)
{
	struct node* conductor;
	conductor = list->tail;

	if (conductor != NULL) {

		while (conductor->next != NULL) {
			conductor = conductor->next;
			free(conductor->prev);
		}
		free(list);
	}
}

// Checked
void list_insert(list_t list, int index, int data)
{
	struct node* conductor;
	conductor = list->tail;

	if (conductor != NULL && index <= list->length-1 && index >= 0) {

		struct node* new_node;
		new_node = (struct node*)malloc(sizeof(new_node));
		new_node->data = data;

		int i = 0;
		while (i != index) {
			conductor = conductor->next;
			i++;
		}

		if (conductor->prev == NULL) {
			new_node->prev = NULL;
		} else {
			conductor->prev->next = new_node;
			new_node->prev = conductor->prev;
		}

		conductor->prev = new_node;
		new_node->next = conductor;
		
		list->length++;
		}
	}

// Checked
void list_append(list_t list, int data)
{
	struct node* new_node;
	new_node = (struct node*)malloc(sizeof(new_node));
	new_node->next=NULL;
	new_node->data=data;

	if (list->length==0) {
		new_node->prev=NULL;
		list->head=new_node;
		list->tail=new_node;
	} else {
		new_node->prev = list->head;;
		list->head->next = new_node;
		list->head = new_node;
	}

	list->length++;
}

void list_print(list_t list)
{
	struct node* conductor;
	conductor = list->tail;

	while (conductor->next != NULL) {
		printf("%d ", conductor->data);
		conductor = conductor->next;
	}

	printf("%d ", conductor->data);
	printf("\n");
}

long list_sum(list_t list)
{
	struct node* conductor;
	conductor = list->tail;
	long sum = 0;

	while (conductor->next != NULL) {
		conductor = conductor->next;
		sum += conductor->data;
	}

	sum += conductor->data;
	return sum;
}

int list_get(list_t list, int index)
{
	struct node* conductor;
	conductor = list->tail;

	if (conductor != NULL && index <= list->length-1 && index >= 0) {

		int i = 0;
		while (i != index) {
			conductor = conductor->next;
			i++;
		}

		return conductor->data;
	}
	return 0;
}

int list_extract(list_t list, int index)
{
	struct node* conductor;
	conductor = list->tail;
	index++;

	if (conductor != NULL && index <= list->length-1 && index >= 0) {

		int data;
		int i = 0;
		while (i != index) {
			conductor = conductor->next;
			i++;
		}

		data = conductor->data;

		if (conductor->prev == NULL) {
			conductor->next->prev = NULL;
			list->tail = conductor->next;
		} else if (conductor->next == NULL) {
			conductor->prev->next = NULL;
			list->head = conductor->prev;
		} else {
			conductor->prev->next = conductor->next;
			conductor->next->prev = conductor->prev;
		}

		free(conductor);
		list->length--;

		return data;
	}
	return 0;
}
