#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/* We create MAX_NUMTHREADS at most */
/* Problem size */
#define MAX_NUMTHREADS 20
#define VSIZE 2000000

int num_threads, subvector_dim;
int v[VSIZE];
int vmax[MAX_NUMTHREADS];
int index_v[MAX_NUMTHREADS];


void *f_max(void *arg)
{
    int i, begin_v, end_v, nthread, max_for_thread;
    nthread = *(int *)arg;
    begin_v = nthread * subvector_dim;
    if ( nthread == (num_threads-1) )
        end_v = VSIZE - 1;
    else
        end_v = begin_v + subvector_dim -1;
    max_for_thread=0;
    for (i=begin_v; i<=end_v; i++)
        if (v[i]>max_for_thread) max_for_thread=v[i];
    printf("Maximum computed by thread %02d (%u): %07d\n", nthread, pthread_self(), max_for_thread);
    vmax[nthread] = max_for_thread;
    pthread_exit(0);
}

int main(int argc, char * argv[])
{
    int i, max;
    time_t t;
    pthread_t thread[MAX_NUMTHREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr); /* They are to be joinable */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    srandom(time(&t));

    if (argc==1)
    {
        printf("Error: The number of threads is required as an argument\n");
        exit(-1);
    }
    num_threads=atoi(argv[1]);

    for (i=0; i<VSIZE; i++) /* We create the vector */
        v[i] = random() % VSIZE;
    puts("Data vector created");

    subvector_dim = VSIZE / num_threads;
    for (i = 0; i < num_threads; i++) /* We create threads, it can fail */
    {
        index_v[i]=i;
        if (pthread_create(&thread[i], &attr, f_max, (void *)&index_v[i]))
        {
            printf("On iteration %d: ", i);
            perror("error creating thread.");
            exit(-1);
        }
    }
    printf("%d Threads successfully created.\n\n", i);
    for (i = 0; i < num_threads; i++) /* We wait for their completion */
        if ( pthread_join(thread[i],NULL ) )
        {
            printf("On iteration %d: ", i); /* It can fail */
            perror("error joining thread.");
            exit(-1);
        }
    printf("\n%d Threads successfully joined.\n\n", i);

    max=0;

    for (i = 0; i < num_threads; i++)
        /* We get the maximum element returned by threads */
        if ( vmax[i] > max )
            max = vmax[i];
    printf("Final maximum: %d\n", max);
    pthread_attr_destroy(&attr);
    exit(0);
}
