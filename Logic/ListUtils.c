
#include <stdio.h>
#include <stdlib.h>
#include "ListUtils.h"

typedef struct List /*The list struct*/
{
	void* data;
	struct List *next;
} List;
 

/**
 * Allocate a new list with the given data pointer at the head.
 * The list does not support NULL data - in this case if the data is NULL then an empty list will be created.
 *
 * May return NULL if malloc fails.
 */
ListRef newList(void* headData) 
{
	ListRef nList = (ListRef)malloc(sizeof(List)); /*Allocating memory for the List so its data won't be lost because it is local*/
	
	if(nList == NULL) 		/*In case the malloc failed we want to return NULL*/
	{
		return NULL;
	}
	
	nList->data = headData;          		   /*Inserting the headData to the head data*/       
	nList->next = NULL;
	return nList;
}

/**
 * We are given a reference to a list.
 * Return the data pointer held by the head of the list or NULL if the list is empty.
 */
void* headData(ListRef list)
{
	return list->data; /*If the list is defined empty (when the head is empty) it will return NULL as well*/
}

/**
 * We are given a reference to a list.
 * Return the tail of the given list or NULL if the list has less than 2 elements.
 */
ListRef tail(ListRef list) 
{
	return list->next; //If the list has last than 2 elements list->next will return NULL because there is nothing there
}

/**
 *We are given a reference to a list and data to append to the list.
 * Append the given data to the end of the list and return a pointer to the sub-list containing only this data.
 * If the given data is NULL no change will be made to the list and NULL will be returned.
 */
ListRef append(ListRef list, void* data)
{
	if(data == NULL)  /*If the given data is NULL then nothing is done and we return NULL*/
	{
		return NULL;
	}
	
	if(list->data == NULL)	/*If the list is NULL then we want the new node to be the list itself*/
	{
		list->data = data;
		return list;
	}
	else					/*Otherwise if the data isn't NULL and so is the list we want to truly add it to the list*/
	{
		ListRef new = (ListRef)malloc(sizeof(List));  /*We are allocating memory so the new node won't be discarded after the function is done*/
		new->data = data;						  /*We set the data to what we got*/
		new->next = NULL;						  /*and we don't have a next item*/
		
		ListRef temp = list;	
		while(temp->next != NULL)				  /*We want to get to the end of the list and insert the new node there*/
		{
			temp = temp->next;					  /*We look at the next node in the list until we see that the next item in it is NULL*/
												  /*which is where we want to insert the new node*/
			
		}
		temp->next = new;						  /*we add the new node to the end of the given list*/
		return new;								  /*and return the sub-list which is defined by the new node*/
	}
}

/**
*The function will free all the data in the list
*We are given a reference to a list and a function to free it
*/
void destroyList(ListRef list, FreeFunc freeData)
{
    if(list->next != NULL) 
    {
		destroyList(list->next, freeData);  /*If we still have some elements left in the list aside from the head we want to destroy them too*/
    }
	freeData(list->data);	/*finally we destroy the head of the list*/
    freeData(list);			/*and the list itself*/
}

/**
*We get a reference to a list and give 0 if it is not empty and any non-zero integer otherwise
*/
int isEmpty(ListRef list)
{
	if(list == NULL||list->data == NULL) /*If we get NULL reference or the List is defined as empty we return 1*/
	{
		return 1;
	}
	else									/*Otherwise the list is not empty so we return 0*/
	{
		return 0;
	}
}
