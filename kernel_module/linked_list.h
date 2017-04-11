#include "keyvalue.h"
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/poll.h>

struct node
{
	struct keyvalue_set keyval;
	struct node *next;
};


int add_node(struct node **head, struct keyvalue_set *keyval)
{
	struct node *new_node = kmalloc(sizeof(struct keyvalue_set), GFP_KERNEL);
	if (!new_node)
		return -1;
	if (access_ok( struct keyvalue_set, keyval, sizeof(struct keyvalue_set) )) {
		printk(KERN_ALERT "access ok in add_node");
		copy_from_user( &(new_node->keyval), keyval, sizeof(struct keyvalue_set) );
		
		//char *d = (new_node->keyval).data;
		//int s = (new_node->keyval).size;
		//int i;
		//for (i=1;i<=s;i++)
		//	printk(KERN_ALERT "Data = %c", d[i-1]);
		//printk(KERN_ALERT "Data = %s", d);
		
		new_node->next = *head;
	
		*head = new_node;
		return 1;
	}
	else {
		printk(KERN_ALERT "access NOT ok");
		return -1;
	}
}

int find_node(struct node *head, struct keyvalue_get **keyval)
{
	struct keyvalue_get new_keyval;
	
	if (access_ok( struct keyvalue_get, *keyval, sizeof(struct keyvalue_get) )) {
		printk(KERN_ALERT "access ok");
		copy_from_user( &new_keyval, *keyval, sizeof(struct keyvalue_get) );
		
		printk(KERN_ALERT "Key to be searched = %d", (new_keyval).key);
		
		struct node *temp = head;
		int flag = -1;
		 
		while (temp!=NULL)
		{
			printk(KERN_ALERT "Temp key = %d", (temp->keyval).key);
		
			if ((temp->keyval).key == (new_keyval).key)
			{
				flag = (temp->keyval).key;
				//copy_to_user( *keyval, &temp, sizeof(struct keyvalue_set) );
				//copy_from_user( &(new_node->keyval), *keyval, sizeof(struct keyvalue_set) );
				//printk(KERN_ALERT "Value found = %d", (temp->keyval).data);
				new_keyval.size = &((temp->keyval).size);
				new_keyval.data = ((temp->keyval).data);
				copy_to_user( *keyval, &new_keyval, sizeof(struct keyvalue_get) );
				
				break;
			}
			temp = temp->next;
		}
		return flag;
	}
	else
	{
		return -1;
	}
	
}
int delete_node(struct node *head, struct keyvalue_get **keyval)
{
	struct keyvalue_get new_keyval;
	
	if (access_ok( struct keyvalue_get, *keyval, sizeof(struct keyvalue_get) )) {
		printk(KERN_ALERT "access ok");
		copy_from_user( &new_keyval, *keyval, sizeof(struct keyvalue_get) );
		
		printk(KERN_ALERT "Key to be searched = %d", (new_keyval).key);
		
		struct node *current = head;
		struct node *previous = NULL;		
		int flag = -1;
		 
		while (current!=NULL)
		{
			printk(KERN_ALERT "Current key = %d", (current->keyval).key);
		
			if ((current->keyval).key == (new_keyval).key)
			{
				if(previous == NULL){
					current = current->next;
					free(head);
					head = current -> next;					
				}
				else{
					previous->next = current ->next;
					free(current);
					current = previous ->next;
				
				}		
			}
			else{
				previous = current ;
				current = current ->next;
			}
					flag = (current->keyval).key;
					//copy_to_user( *keyval, &temp, sizeof(struct keyvalue_set) );
					//copy_from_user( &(new_node->keyval), *keyval, sizeof(struct keyvalue_set) );
					//printk(KERN_ALERT "Value found = %d", (temp->keyval).data);
				
				//new_keyval.size = &((current->keyval).size);
				//new_keyval.data = ((current->keyval).data);
				//copy_to_user( *keyval, &new_keyval, sizeof(struct keyvalue_get) );
				
	 }
		return flag;
	}
	else
	{
		return -1;
	}	
}
