#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new_ls= (struct list_head *)malloc(sizeof(struct list_head));
    if(new_ls){
    INIT_LIST_HEAD(new_ls);
    return new_ls;
    }
    return NULL;
}

/* Free all storage used by queue */
void q_free(struct list_head *head) {
    if(!head){
        return;
    }
    element_t *entry, *safe;
    list_for_each_entry_safe (entry,safe,head, list);
    q_release_element(entry);
    free(head);

}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    element_t *new_e=(element_t*) malloc(sizeof(element_t));
    if (!new_e){
    free(new_e);
        return false;
    }
    else{
        size_t len_e=strlen(s)+1;
        new_e->value=(char *)malloc(len_e);
        if (!new_e->value){
            free(new_e);
            return false;
        }
        else{
        memcpy(new_e->value,s,len_e);
        list_add(&(new_e->list),head);
        return true;
        }
        }
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    element_t *new_e=(element_t*) malloc(sizeof(element_t));
    if (!new_e){
        free(new_e);
        return false;
    }
    else{
    size_t len_e=strlen(s)+1;
    new_e->value=(char *)malloc(len_e);
    if (!new_e->value){
        free(new_e);
        return false;
    }
    else{
    memcpy(new_e->value,s,len_e);
    list_add_tail(&(new_e->list),head);
    return true;
    }
    }

}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    return -1;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
