//
//  cthread.c
//  cthread
//
//  Created by Henrique Valcanaia on 15/09/16.
//  Copyright © 2016 Henrique Valcanaia. All rights reserved.
//

#include "cthread.h"

#define CCREATE_ERROR -1

int ccreate (void *(*start)(void *), void *arg) {
    pthread_t thread;
    pthread_attr_t attr_t;
    
    pthread_create(&thread, &attr_t, start, arg);
    
    TCB_t tcb;
    tcb.state = CREATION;
#ifdef __APPLE__
    pthread_threadid_np(thread, &tcb.tid);
#else
#ifdef unix
    
#endif
#endif
    tcb.ticket = generateTicket();
    if (getcontext(&tcb.context) == 0) {
        if (addThreadToReadyQueue(&tcb) == 0) {
            return tcb.tid;
        } else {
            return CCREATE_ERROR;
        }
    } else {
        return CCREATE_ERROR;
    }
}

int cyield() {
    return CYIELD_SUCCESS;
}

int cjoin(int tid) {
    return -1;
}

int csem_init (csem_t *sem, int count) {
    return -1;
}

int cwait (csem_t *sem) {
    return -1;
}

int csignal (csem_t *sem) {
    return -1;
}

int cidentify (char *name, int size) {
    const char* strNames = "Henrique Valcanaia - 240501\nPietro Degrazia - 243666\0";
    if (size >= strlen(strNames)) {
        strcpy(name, strNames);
        return 0;
    } else {
        return -1;
    }
}
