#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

void print_node(struct Node*);

void add_node(struct Node**, int);
void delete_node(struct Node**, int);
void print_list(struct Node**);
void sort_list(struct Node**);
void flush_list(struct Node**);

#endif
