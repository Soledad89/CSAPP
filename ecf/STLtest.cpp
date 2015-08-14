//#include <pthread.h>
//#include <stdio.h>
//#include <unistd.h>
//
//pthread_mutex_t mutex ;
//void *print_msg(void *arg){
//    int i=0;
//    pthread_mutex_lock(&mutex);
//    for(i=0;i<15;i++){
//        printf("output : %d\n",i);
//        usleep(100);
//    }
//    pthread_mutex_unlock(&mutex);
//    return NULL;
//}
//
//int main(int argc,char** argv){
//    pthread_t id1;
//    pthread_t id2;
//    pthread_mutex_init(&mutex,NULL);
//    pthread_create(&id1,NULL,print_msg,NULL);
//    pthread_create(&id2,NULL,print_msg,NULL);
//    pthread_join(id1,NULL);
//    pthread_join(id2,NULL);
//    pthread_mutex_destroy(&mutex);
//    return 1;
//}
//
//#include<stdlib.h>
//#include<stdio.h>
//#include<unistd.h>
//#include<pthread.h>
//
//typedef struct ct_sum
//{
//    int sum;
//    pthread_mutex_t lock;
//}ct_sum;
//
//void * add1(void * cnt)
//{
//    
//    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
//    int i;
//    for( i=0;i<50;i++)
//    {
//        (*(ct_sum*)cnt).sum+=i;
//        
//    }
//    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
//    pthread_exit(NULL);
//    return 0;
//}
//void * add2(void *cnt)
//{
//    int i;
//    cnt= (ct_sum*)cnt;
//    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
//    for( i=50;i<101;i++)
//    {    (*(ct_sum*)cnt).sum+=i;
//        
//    }
//    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
//    pthread_exit(NULL);
//    return 0;
//}
//
//
//int main(void)
//{
//    int i;
//    pthread_t ptid1,ptid2;
//    int sum=0;
//    ct_sum cnt;
//    pthread_mutex_init(&(cnt.lock),NULL);
//    cnt.sum=0;
//    
//    pthread_create(&ptid1,NULL,add1,&cnt);
//    pthread_create(&ptid2,NULL,add2,&cnt);
//
//    pthread_join(ptid1,NULL);
//    pthread_join(ptid2,NULL);
//    
//    printf("sum %d\n",cnt.sum);
//    
//    pthread_mutex_destroy(&(cnt.lock));
//    return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#define DEBUG 1

int num = 0;
pthread_mutex_t mylock;
pthread_cond_t qready=PTHREAD_COND_INITIALIZER;

void* thread_func(void *arg)
{
    int param = * ((int *) arg);
    int i;
    
    for(i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mylock);
        
        while(param != num)
            pthread_cond_wait(&qready, &mylock);
        
        printf("%c", param + 'A');
        num = (num + 1) % 3;
        
        pthread_mutex_unlock(&mylock);
        pthread_cond_broadcast(&qready);
    }
    
    return NULL;
}

int main()
{
    int i;
    pthread_t tid[3];
    void *tret = NULL;
    for(i = 0; i < 3; i++)
        pthread_create(&tid[i], NULL, thread_func, (void *) &i);
    for(i = 0; i < 3; i++)
        pthread_join(tid[i], &tret);

    return 0;
}


