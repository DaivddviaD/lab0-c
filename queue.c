#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>

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


//this input is without head
struct list_head* find_mid_nodes(sturct list_head *first){
    struct list_head *hare=first,*tortoise=first;
    while(hare && hare->next){
        tortoise=tortoise->next;
        hare=hare->next->next;
    }
    return tortoise;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if(!head||list_empty(head))
        return false;
    head->prev->next=NULL;
    struct list_head *tortoise=find_mid_nodes(head->next);
    element_t *Tor=list_entry(tortoise,element_t,list);
    list_del(tortoise);
    q_release_element(Tor);
    head->prev->next=head;
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
{   
    q_reversek(head,2);
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
//used to divide list to sort

struct list_head *mergeTwoList(struct list_head *left,struct list_head *right,bool descend)
{
    struct list_head *merge_h = NULL, **merge_ad = &merge_h;

    for (struct list_head ** ptr=NULL; left && right; *ptr = (*ptr)->next) {
        ptr = (strcmp(list_entry(left, element_t, list)->value,
                       list_entry(right, element_t, list)->value) >= 0)!= descend ? &right: &left;
        *merge_ad= *ptr;
        merge_ad = &(*merge_ad)->next;
    }
    *merge_ad = (struct list_head *) ((u_int64_t) left | (u_int64_t) right);
    return merge_h;
}


struct list_head* Divide(struct list_head *first,bool descend){
if (!first || !first->next)
        return first;
    struct list_head *mid=find_mid_nodes(first)
    
    mid->prev->next = NULL;

    return mergeTwoList(Divide(first,descend), Divide(mid,descend),descend);
}



/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {
    if (!head || list_empty(head) || list_is_singular(head))
        return;
    head->prev->next = NULL;
    head->next = Divide(head->next,descend);
    head->prev->next=head;
}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
     if (!head||list_empty(head)){
        return 0;
    }
    struct list_head *cur=head->next->next,*del_node;
    while(cur!=head){
        if (cur->prev==head||strcmp(list_entry(cur->prev,element_t,list)->value,list_entry(cur,element_t,list)->value)<0){
            cur=cur->next;
        }else{
            del_node=cur->prev;
            list_del(del_node);
            q_release_element(list_entry(del_node,element_t,list));
        }
    }

    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return q_size(head);
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{   
    if (!head||list_empty(head)){
        return 0;
    }
    struct list_head *cur=head->next->next,*del_node;
    while(cur!=head){
        if (cur->prev==head||strcmp(list_entry(cur->prev,element_t,list)->value,list_entry(cur,element_t,list)->value)>0){
            cur=cur->next;
        }else{
            del_node=cur->prev;
            list_del(del_node);
            q_release_element(list_entry(del_node,element_t,list));
        }
    }
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return q_size(head);
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    if (!head||list_empty(head))
        return 0;
    
    int final_size;

    struct list_head *first_chain, *be_merged;
    first_chain=list_entry(head->next,queue_contex_t,chain)->q;
    first_chain->prev->next=NULL;
    final_size=q_size(first_chain);
    be_merge=head->next->next;

    while(be_merge!=head){
        struct list_head *be_merged_q=list_entry(be_merge,queue_contex_t,chain)->q;
        final_size+=q_size(be_merged_q);

        be_merged_q->prev->next=NULL;
        first_chain->next=mergeTwoList(first_chain->next,be_merge_q->next,descend);
        element_t *entry, *safe;
        list_for_each_entry_safe(entry,safe,be_merged_q,list)
        q_release_element(entry);
        INIT_LIST_HEAD(be_merged_q);
        be_merge=be_merge->next;
    }

    first_chain->prev->next=first_chain;


    // https://leetcode.com/problems/merge-k-sorted-lists/
    return final_size;
}
