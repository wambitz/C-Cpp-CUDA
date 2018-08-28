// Example program
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define NUM_THREADS 5

struct thread_data
{
    int thread_id;
    char * message;
};

// void * PrintHello(void * threadid)
void * PrintHello(void * threadarg)
{
    struct thread_data * my_data = (struct thread_data *)threadarg;
    /*
    long tid;
    tid = (long)threadid;
    cout << "Hello World! Thread ID, " << tid << endl;
    */
    
    cout << "Thread ID: " << my_data->thread_id;
    cout << "Message: " << my_data->message << endl;
    
    pthread_exit(NULL);
}

void * wait(void * t)
{
    int i;
    long tid;
    
    tid = (intptr_t)t;
    
    sleep(1);
    
    cout << "Sleeping in thread " << endl;
    cout << "Thread with id: " << tid << "...exiting" << endl;
    
    pthread_exit(NULL);
}


int main()
{
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    
    void * status;
    // struct thread_data td[NUM_THREADS];
    
    int rc;
    int i;
    
    // Initialize and set thread joinable
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for (i = 0; i < NUM_THREADS; i++)
    {
        cout << "main() : creating thread, " << i << endl;
        
        // td[i].thread_id = i;
        // td[i].message = "This is a message"; 
        
        // rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
        // rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
        
        rc = pthread_create(&threads[i], &attr, wait, (void *)i);
        
        if (rc)
        {
            cout << "ERROR: Unable to create thread, " << rc << endl;
            exit(-1);
        }
    }
     
    // free attributes and wait for the other threads
    pthread_attr_destroy(&attr);
    
    for (i = 0; i < NUM_THREADS; i++)
    {
        cout << "main() : creating thread, " << i << endl;
        rc = pthread_join(threads[i], &status);
        
        if (rc)
        {
            cout << "ERROR: Unable to create join, " << rc << endl;
            exit(-1);
        }
        
        cout << "Main: completed thread id: " << i;
        cout << " exiting with status : " << status << endl;
    }
    
    cout << "Main: program exiting." << endl;
    pthread_exit(NULL);
    
    return 0;
}
