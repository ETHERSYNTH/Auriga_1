#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


typedef struct list_s
{
    struct list_s *next; // NULL for the last item in a list.
    int data;
}list_t;

char *item_data(const list_t *list);

// Counts the number of items in a list.
int count_list_items(const list_t *head) {
    if (head->next) {
        return count_list_items(head->next) + 1;
    } else {
        return 1;
    }
}

// Counts the number of items in a list.
int print_all_list_items(const list_t *head) {
    return count_list_items(head);
}

// Inserts a new list item after the one specified as the argument.
void* insert_next_to_list(list_t *item, int data) {
    list_t* result = (list_t*)malloc(sizeof(list_t));
    if(result) {
        (item->next = result)->next = NULL;
        item->next->data = data;
    }
    return (void*) result;
}

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

// Returns item data as text.
char *item_data(const list_t *list)
{
    static char buf[21];
    snprintf(buf, sizeof(buf), "%d", list->data);
    return buf;
}

static list_t root = {NULL, 1};

int main()
{
    list_t *last_added_node_address;
    list_t *before_last_added_node_address;


    print_all_list_items(&root);


    printf( "New node was created\n");
    last_added_node_address = insert_next_to_list(&root, 2);
    print_all_list_items(&root);

    printf( "New node was created\n");
    before_last_added_node_address = last_added_node_address = insert_next_to_list(last_added_node_address, 3);
    print_all_list_items(&root);

    printf( "New node was created\n");
    last_added_node_address = insert_next_to_list(last_added_node_address, 4);
    print_all_list_items(&root);

    remove_next_from_list(&root);
    print_all_list_items(&root);

    remove_next_from_list(before_last_added_node_address);
    print_all_list_items(&root);

    printf( "\nDelete function return %d\n\n", remove_next_from_list(&root) );
    print_all_list_items(&root);

    printf( "\nDelete function return %d\n\n", remove_next_from_list(&root) );
    print_all_list_items(&root);

    return 0;
}
