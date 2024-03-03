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

struct list_head* find_mid_node(struct list_head *head){
    struct list_head *hare=head->next->next;
    struct list_head *tortoise=head->next;
    while(hare!=head||hare!=head->prev){
        hare=hare->next->next;
        tortoise=tortoise->next;
    }
    return tortoise;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if(!head||list_empty(head))
        return false;
    struct list_head *tortoise=find_mid_node(head);
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
    struct list_head *merge_h = NULL, **indirect = &m_head, **iter = NULL;
    for (; left && right; *iter = (*iter)->next) {
        iter = strcmp(list_entry(left, element_t, list)->value,list_entry(right, element_t, list)->value) >= 0? &right: &left;
        *indirect = *iter;
        indirect = &(*indirect)->next;
    }
    *indirect = (struct list_head *) ((u_int64_t) left | (u_int64_t) right);
    return m_head;
}

struct list_head* merge_sort(struct list_head *head){
if (!head || !head->next)
        return head;
    struct list_head *fast = head, *slow = head, *mid;

    for (; fast && fast->next; fast = fast->next->next)
        slow = slow->next;
    mid = slow;
    mid->prev->next = NULL;
    struct list_head *left = merge_divide(head);
    struct list_head *right = merge_divide(mid);
    return merge_two_nodes(left, right);
}


/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {
    if (!head || list_empty(head) || list_is_singular(head))
        return;
    head->prev->next = NULL;
    head->next = merge_divide(head->next);
    struct list_head *fir = head, *sec = head->next;
    for (; sec != NULL; sec = sec->next) {
        sec->prev = fir;
        fir = sec;
    }
    fir->next = head;
    head->prev = fir;
    if (descend)
        q_reverse(head);

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
