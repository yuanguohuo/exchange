#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <sys/types.h>   // where type pid_t is defined

class Thread
{
  private:
    pid_t           tid;          // thread id; unique within a system; Linux specific and therefore not portable
    pid_t           tgid;         // process id (also, the thread group id, the tid of the leader thread)
    pthread_t       thread_id;    // posix thread id, unique within a process, because it's the address of TLS (therad local storage)
    const char *    thread_name;

    static void* entry_func(void* arg);
    void* body_wrapper();

    int try_create(size_t stacksize);

  protected:
    virtual void* body() = 0;

  public:
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    Thread();
    virtual ~Thread();

    const pid_t& get_tid() const;
    const pid_t& get_tgid() const;
    const pthread_t& get_thread_id() const;
    const char* get_thread_name() const;

    bool is_started() const;
    bool am_self() const;

    void create(const char *name, size_t stacksize = 0);
    bool kill(int signal);
    void join(void** prval = 0);
    int detach();
};

#endif
