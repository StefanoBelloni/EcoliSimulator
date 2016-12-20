#ifndef MY_MUTEX_H
#define MY_MUTEX_H

// fake class, not to use too many #ifdef NO_M_THREAD
#if NO_M_THREAD
struct MyMutex{
    void lock(){};
    void unlock(){};
};

#endif

#endif
