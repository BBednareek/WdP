#include "stdio.h"
#include "stdlib.h"

typedef struct node {
    int data;
    struct node *next;
} node_t;

void print_list(node_t *);
void free_nodes(node_t *head);

node_t *create_node(int);
node_t *prepare_list();
node_t *insert_node(node_t*, int, int);

int main(void) {
    int position = 0;
    int data = 0;

    node_t * head = prepare_list();

    printf("Utworzona lista jednokierunkowa: ");
    print_list(head);

    printf("\nPodaj pozycje, na ktora chcesz dodac dane: ");
    scanf("%d", &position);

    printf("\nPodaj dane, ktore chcesz wprowadzic na %d pozycje: ", position);
    scanf("%d", &data);

    head = insert_node(head, data, position);

    printf("\nLista jednokierunkowa po aktualizacji: ");
    print_list(head);

    free_nodes(head);
    free(head);

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

    if (head == NULL) {
        perror("Blad alokacji pamieci dla listy jednokierunkowej");
        return NULL;
    }

    head -> next = create_node(4);
    head -> next -> next = create_node(1);
    head -> next -> next -> next = create_node(3);
    head -> next -> next -> next -> next = create_node(5);

    return head;
}

node_t *insert_node(node_t *head, const int data, const int position) {
    if (position < 0)
        return head;

    if (position == 0) {
        node_t *new_node = create_node(data);
        new_node -> next = head;
        return new_node;
    }

    node_t *current = head;

    size_t i = 0;

    for (; i < position - 1 && current != NULL; i++)
        current = current -> next;

    if (current == NULL)
        return head;

    node_t *new_node = create_node(data);

    new_node -> next = current -> next;
    current -> next = new_node;

    return head;
}