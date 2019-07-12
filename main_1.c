#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include "linked_list.h"
#include "node.h"

#define NUM_THREADS 3

struct Node* head;

pthread_barrier_t barrier;
pthread_mutex_t lock;

void *thread_routine(void *arg)
{
	int threadId = ((intptr_t) arg)+1;
	int rc;
	printf("Thread %d ready.\n", threadId);

	rc = pthread_barrier_wait(&barrier);
	if (rc == PTHREAD_BARRIER_SERIAL_THREAD){
		printf("Threads starting!\n-----------------\n");
	}

	switch(threadId)
	{
	case 1:
		// Thread 1
		pthread_mutex_lock(&lock);
		add_node(&head, 2);
		printf("add(2) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		add_node(&head, 4);
		printf("add(4) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		add_node(&head, 10);
		printf("add(10) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		delete_node(&head, 2);
		printf("delete(2) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		sort_list(&head);
		printf("sort_list() by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		delete_node(&head, 10);
		printf("delete(10) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		delete_node(&head, 5);
		printf("delete(5) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		break;
	case 2:
		// Thread 2
		pthread_mutex_lock(&lock);
		add_node(&head, 11);
		printf("add(11) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		add_node(&head, 1);
		printf("add(1) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		delete_node(&head, 11);
		printf("delete(11) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		add_node(&head, 8);
		printf("add(8) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		print_list(&head);
		printf("print_list() by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		break;
	case 3:
		// Thread 3
		pthread_mutex_lock(&lock);
		add_node(&head, 30);
		printf("add(30) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		add_node(&head, 25);
		printf("add(25) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		add_node(&head, 100);
		printf("add(100) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		sort_list(&head);
		printf("sort_list() by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		print_list(&head);
		printf("print_list() by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		delete_node(&head, 100);
		printf("delete(100) by thread %d\n", threadId);
		pthread_mutex_unlock(&lock);

		break;
	}

	return NULL;
}

int main()
{
	printf("Current file is %s\n", __FILE__);

	head = (struct Node*) malloc(sizeof(struct Node));
	head = NULL;

	int i;
	pthread_t tids[NUM_THREADS];
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n mutex init has failed\n");
		return -1;
	}

	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	for(i=0; i<NUM_THREADS; i++)
		pthread_create(&tids[i], NULL, thread_routine, (void *) (intptr_t) i);
	for(i=0; i<NUM_THREADS; i++)
			pthread_join(tids[i], NULL);


	pthread_barrier_destroy(&barrier);

	printf("***** List before flushing *****\n");
	print_list(&head);
	flush_list(&head);
	free(head);
	pthread_mutex_destroy(&lock);

	return 0;
}
