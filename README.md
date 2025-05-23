1) Function "item_data" returns address of local variable "char buf[]". 
The lifetime of local variable is determined by the execution time of the function in which it is defined.
static char buf[];

2) In 64-bit systems: int can have the size of 4 bytes or 8 bytes depending on 
the particular architecture and compiler, -  as a result need to deсlare a buffer length 21
and to use snprintf() to safe buffer from overflow.

char *item_data(const list_t *list)
{
    static char buf[21];
    snprintf(buf, sizeof(buf), "%d", list->data);
    return buf;
}

3) The new list item field "*next" must has NULL initialisation. 
( item->next = malloc(sizeof(list_t)) )->next = NULL;

4) Operation on 'item->next' may be undefined
malloc can return NULL if memory allocation failed. Need to return result of malloc.

// Inserts a new list item after the one specified as the argument.
void* insert_next_to_list(list_t *item, int data) {
    list_t* result = (list_t*)malloc(sizeof(list_t));
    if(result) {
        (item->next = result)->next = NULL;
        item->next->data = data;
    }
    return (void*) result;
}

5) Inside "remove_next_from_list" need to use a pointer to a local variable with type list_t to temporarily 
store the next node memory address after the deleted node in order to rebuild the linked list chain.

6) Function "remove_next_from_list" should return a value error(warning) (-1) that only the root  
is left and there is nothing else to delete. 

// Removes an item following the one specified as the argument.
int remove_next_from_list(list_t *item) {
    if (!(item->next)) return -1;

    list_t temp_list_pnt;
    list_t *temp = &temp_list_pnt;

    temp->next = item->next->next;
    free(item->next);
    item->next = temp->next;

    return 0;
}
	
7) Typographical error in comment: specificed -> specified

