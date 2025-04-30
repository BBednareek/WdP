#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie {
    char* title;
    double score;
};

typedef struct item {
    struct movie movie;
    struct item *next;
} item_t;

void print_list(item_t *);
void free_nodes(item_t *);

item_t *prepare_list();
item_t *create_node(struct movie);
item_t *delete_duplicates(item_t *);

int main(void) {
    item_t *head = prepare_list();

    printf("Podstawowa lista jednokierunkowa: \n");
    print_list(head);

    delete_duplicates(head);

    printf("Lista jednokierunkowa po sprawdzeniu, czy zawieraja sie duplikaty: \n");
    print_list(head);

    free_nodes(head);
    return EXIT_SUCCESS;
}

void print_list(item_t * head) {
    item_t * current = head;

    while (current != NULL) {
        printf("Tytul: %s\n", current -> movie.title);
        printf("Ocena: %.2lf\n", current -> movie.score);
        printf("==================\n");
        current = current -> next;
    }
}

void free_nodes(item_t *head) {
    item_t *tmp = NULL;

    while (head != NULL) {
        tmp = head;
        head = head -> next;
        free(tmp);
    }
}

item_t *create_node(struct movie movie) {
    item_t *node = (item_t *)malloc(sizeof(item_t));

    node -> movie = movie;
    node -> next = NULL;

    return node;
}

item_t *prepare_list() {
    struct movie movie1 = {.title = "Star Wars", .score = 8.7};
    struct movie movie2 = {.title = "Harry Potter", .score = 9.3};
    struct movie movie3 = {.title = "Alice in Borderland", .score = 4.8};
    struct movie movie4 = {.title = "Star Wars", .score = 4.1};

    item_t *head = create_node(movie1);
    head -> next = create_node(movie2);
    head -> next -> next = create_node(movie3);
    head -> next -> next -> next = create_node(movie4);

    return head;
}

item_t *delete_duplicates(item_t *head) {
    if (head == NULL)
        return NULL;

    item_t *current = head;

    while (current != NULL) {
        double rating = current -> movie.score;
        int count = 1;

        item_t *runner = current;

        while (runner->next != NULL) {
            if (strcmp(current->movie.title, runner->next->movie.title) == 0) {
                rating += runner -> next -> movie.score;
                count++;

                item_t *duplicate = runner->next;
                runner->next = duplicate->next;
                free(duplicate);
            } else
                runner = runner->next;
        }

        current -> movie.score = rating / count;
        current = current->next;
    }

    return head;
}