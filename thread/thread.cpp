#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <iostream>

#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

#include "thread.h"

Thread::Thread() : tid(0), tgid(0), thread_id(0), thread_name(NULL)
{
}

Thread::~Thread()
{
}

const pid_t& Thread::get_tid() const {return tid;}
const pid_t& Thread::get_tgid() const {return tgid;}
const pthread_t& Thread::get_thread_id() const {return thread_id;}
const char* Thread::get_thread_name() const {return thread_name;}

bool Thread::is_started() const {return thread_id != 0;}
bool Thread::am_self() const {return pthread_self() == thread_id;}

void Thread::create(const char *name, size_t stacksize)
{
  assert(strlen(name) < 16);
  thread_name = name;

  int ret = try_create(stacksize);
  if(ret != 0)
  {
    std::cerr << "Thread::create(): pthread_create failed with error " << ret << std::endl;
    assert(false);
  }
}

int Thread::try_create(size_t stacksize)
{
  pthread_attr_t* thread_attr = NULL;
  pthread_attr_t thread_attr_loc;

  unsigned page_size = sysconf(_SC_PAGESIZE);
  unsigned long page_mask = ~(unsigned long)(page_size-1);

  stacksize &= page_mask;
  if(stacksize)
  {
    thread_attr = &thread_attr_loc;
    pthread_attr_init(thread_attr);
    pthread_attr_setstacksize(thread_attr, stacksize);
  }

  //the child thread will inherit my thread mask, thus, to set the child's thread mask,
  //I set the mine, and after the child thread is created, I restore my thread mask;
  sigset_t sigset, old_sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGPIPE);

  int ret, r;
  r = pthread_sigmask(SIG_BLOCK, &sigset, &old_sigset);
  assert(r == 0);

  ret = pthread_create(&thread_id, thread_attr, entry_func, (void*)this);

  r = pthread_sigmask(SIG_SETMASK, &old_sigset, NULL);
  assert(r == 0);

  if(thread_attr)
  {
    pthread_attr_destroy(thread_attr);	
  }

  return ret;
}

//static
void* Thread::entry_func(void* arg)
{
  void* ret = ((Thread*)arg)->body_wrapper();
  return ret;
}

void* Thread::body_wrapper()
{
  tid = syscall(SYS_gettid);
  tgid = getpid();
  assert(thread_id == pthread_self());
  pthread_setname_np(thread_id, thread_name);

  
  std::cout << "start thread: " << thread_name << "[" << thread_id << "\t" << tid << "\t" << tgid << "]" << std::endl;

  return body();
}

bool Thread::kill(int signal)
{
  if (thread_id)
    return pthread_kill(thread_id, signal);
  return -EINVAL;
}

void Thread::join(void** prval)
{
  if(thread_id==0)
    assert(false);

  int ret = pthread_join(thread_id, prval);
  if(ret != 0)
  {
    std::cerr << "Thread::join(): pthread_join failed with error " << ret << std::endl;
    assert(false);
  }

  thread_id = 0;
}

int Thread::detach()
{
  return pthread_detach(thread_id);
}
