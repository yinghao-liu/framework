# 008
exception in pthread_mutex_lock and pthread_cond_wait when thread been pthread_cancel  
environment: Ubuntu 18.04.1 && gcc 7.4.0

## Description
`./main` then type 'c', then 'p'  
two threads, block in pthread_wait, then cancel one of them, that cause the mutex.lock = 2,  
so all other threads will be blocked in pthread_lock.

## Notes


## reference
1. man pthread_cond_wait
