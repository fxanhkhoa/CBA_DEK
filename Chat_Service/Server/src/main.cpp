#include <iostream>
#include "Server.h"
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

/* function prototype */
void *run_thread_ss(void *threadid);
void *run_thread_sc(void *threadid);

int main(int argc, char const *argv[])
{
  pthread_t threads;
  int rc;
  int i;

  rc = pthread_create(&threads, NULL, run_thread_sc, (void *)i);

  if (rc)
  {
    cout << "Error: Unable to create thread, "<< rc << endl;
    exit(-1);
  }
  pthread_exit(NULL);
  return 0;
}


void *run_thread_ss(void *threadid)
{

}

void *run_thread_sc(void *threadid)
{
  long tid;
  tid = (long)threadid;
  Server _Server;
  _Server.Create_Master_Socket();
  _Server.Set_Master_Socket_Multiple();
  _Server.Type_Socket();
  _Server.Bind_Socket();
  _Server.Specify_Pending();
  _Server.Accept_Incoming();
  _Server.Start_Run();
  pthread_exit(NULL);
}
