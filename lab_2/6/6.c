#include "stdio.h"
#include "stdlib.h"

typedef struct node {
    int data;
    struct node *next;
} node_t;

void print_list(node_t *);
void free_nodes(node_t*);

node_t *prepare_list();
node_t *create_node(int);
node_t *delete_from_specified_range(node_t*, int, int);

int main(void) {
    int a = 0;
    int b = 0;

    node_t *head = prepare_list();

    printf("Utworzona lista jednokierunkowa: ");
    print_list(head);

    printf("\nPodaj pozycje, od ktorej chcesz usunac dane: ");
    scanf("%d", &a);

    printf("\nPodaj pozycje, od ktorej chcesz usunac dane: ");
    scanf("%d", &b);

    head = delete_from_specified_range(head, a, b);

    printf("Lista jednokierunkowa po usuwaniu danych z zakresu [%d, %d]: ", a, b);
    print_list(head);

    free_nodes(head);
    return EXIT_SUCCESS;
}

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d ", current -> data);
        current = current -> next;
    }
}

void free_nodes(node_t *head) {
    node_t *tmp = NULL;

    while (head != NULL) {
        tmp = head;
        head = head -> next;
        free(tmp);
    }
}

node_t *create_node(const int data) {
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node -> data = data;
    node -> next = NULL;

    return node;
}

node_t *prepare_list() {
    node_t *head = create_node(2);
    head -> next = create_node(4);
    head -> next -> next = create_node(1);
    head -> next -> next -> next = create_node(3);
    head -> next -> next -> next -> next = create_node(5);

    return head;
}

node_t *delete_from_specified_range(node_t *head, const int a, const int b) {
    if (head == NULL || a > b || a < 0)
        return head;

    node_t *current = head;
    node_t *previous = NULL;
    node_t *temp = NULL;

    int position = 0;

    while (current != NULL && position < a) {
        previous = current;
        current = current -> next;
        position++;
    }

    while (current != NULL && position <= b) {
        temp = current;
        current = current -> next;
        free(temp);
        position++;
    }

    if (previous != NULL)
        previous -> next = current;
    else
        head = current;

    return head;
}


