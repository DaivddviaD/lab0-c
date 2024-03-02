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
    if (!head){
        return;
    }
    element_t *entry, *safe;
    list_for_each_entry_safe(entry,safe,head,list)
    q_release_element(entry);
    free(head);
}


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
    if(!head||list_empty(head))
        return NULL;
    element_t *rem_h=(element_t*)malloc(sizeof(element_t));
    if (!rem_h){
        free(rem_h);
        return NULL;
    }
    rem_h=list_entry(head->next, element_t,list);
    list_del(&rem_h->list);
    if (sp && bufsize){
        strncpy(sp,rem_h->value,bufsize-1);
        sp[bufsize-1]='\0';
    }
    return rem_h;


}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if(!head||list_empty(head))
        return NULL;
    element_t *rem_l=(element_t*)malloc(sizeof(element_t));
    if (!rem_l){
        free(rem_l);
        return NULL;
    }
    rem_l=list_entry(head->next, element_t,list);
    list_del(&rem_l->list);
    if (sp && bufsize){
        strncpy(sp,rem_l->value,bufsize-1);
        sp[bufsize-1]='\0';
    }
    return rem_l;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    int size=0;
    if (head||!list_empty(head)){
        struct list_head *node;
        list_for_each(node, head){
        size++;
    }
    }
    return size;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if(!head||list_empty(head))
        return false;
    struct list_head *hare=head->next->next;
    struct list_head *tortoise=head->next;
    while(hare!=head||hare!=head->prev){
        hare=hare->next->next;
        tortoise=tortoise->next;
    }
    element_t *Tor=list_entry(tortoise,element_t,list);
    list_del(tortoise);
    q_release_element(Tor);
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head)
        return false;
    element_t *entry=(element_t*)malloc(sizeof(element_t));
    element_t *entry_prev=(element_t*)malloc(sizeof(element_t);
    if(entry||entry_prev){
        free(entry);
        free(entry_prev);
        return false;
    }
    list_for_each_entry(entry,head,list){
        entry_prev=list_entry(entry->list.prev, element_t, list);
        if (entry_prev->value==entry->value){
            list_del(&entry_prev->list);
            q_release_element(entry_prev);
        }
    }
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{   q_reversek(head,2);
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {
    if (head||!list_empty(head)||q_size(head)){
        struct list_head *temp_node=head->next;
        while(temp_node!=head){
            temp_node=temp_node->next;
            list_move(temp_node->prev,head);
        }
    }
    return;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    int count=0;
    struct list_head *node,*cut;
    struct list_head *last=head->prev;
    list_for_each(node,head){
        count++;
        if (count==k){
            count=0;
            cut=node->next;
            head->prev=node;
            node->next=head;
            q_reverse(head);
            head->prev=last;
            node->next=cut;
        }
    }
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
