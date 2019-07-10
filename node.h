#ifndef NODE_H_
#define NODE_H_

struct Node
{
	int data;
	struct Node *next;
	void (*callback)(struct Node*);
};

#endif
