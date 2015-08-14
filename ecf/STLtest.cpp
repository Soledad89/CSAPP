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
    int param = (int) arg;
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
        pthread_create(&tid[i], NULL, thread_func, (void *) i);
    for(i = 0; i < 3; i++)
        pthread_join(tid[i], &tret);

    return 0;
}


//
//void * thread_func(void *arg)
//{
//    int param = int(arg);
//    char c='A'+param;
//    int ret,i=0;
//    for (; i < 10; i++)
//    {
//        pthread_mutex_lock(&mylock);
//        while (param != n)  //刚运行时，n = 0， param = 0,条件不成立，所以直接打印A
//        {
//#ifdef DEBUG
//            printf("thread %d waiting\n", param);
//#endif
//            ret = pthread_cond_wait(&qready, &mylock);
//            if (ret == 0)
//            {
//#ifdef DEBUG
//                printf("thread %d wait success\n", param);
//#endif
//            } else
//            {
//#ifdef DEBUG
//                printf("thread %d wait failed:%s\n", param, strerror(ret));
//#endif
//            }
//        }
//        // printf("%d ",param+1);
//        printf("%c ",c);  //打印A后
//        n=(n+1)%NUM;      //n变成了1，对线程2会产出影响！！！！
//        pthread_mutex_unlock(&mylock);
//        //会唤醒所有的线程，因为当这个线程完后会等pthread_cond_wait()执行两次后才能退出while (param != n)
//        pthread_cond_broadcast(&qready);
//        
//    }
//    return (void *)0;
//}
//
//#if 0
////假设为线程2
//
//void * thread_func(void *arg)//传入值1
//{
//    int param=(int)arg;
//    char c='A'+param;
//    int ret,i=0;
//    for (; i < 10; i++)
//    {
//        pthread_mutex_lock(&mylock);
//        while (param != n)  //和线程1同时执行，所以刚开始时条件满足
//        {
//#ifdef DEBUG
//            printf("thread %d waiting\n", param);
//#endif
//            //执行到此时，等待线程1发送信号，当线程1的A打印完后，n的值也变成了1，条件就不成立了
//            ret = pthread_cond_wait(&qready, &mylock);
//            if (ret == 0)
//            {
//#ifdef DEBUG
//                printf("thread %d wait success\n", param);
//#endif
//            } else
//            {
//#ifdef DEBUG
//                printf("thread %d wait failed:%s\n", param, strerror(ret));
//#endif
//            }
//        }
//        // printf("%d ",param+1);
//        printf("%c ",c); //此时打印值B
//        n=(n+1)%NUM;    //对打印C的线程3产生影响！！！
//        pthread_mutex_unlock(&mylock);
//        pthread_cond_broadcast(&qready);
//    }
//    return (void *)0;
//}
//
//#endif
//
//int main(int argc, char** argv) {
//    
//    int i=0,err;
//    pthread_t tid[NUM];
//    void *tret;
//    for(;i<NUM;i++)
//    {
//        err=pthread_create(&tid[i],NULL,thread_func,(void *)i);
//        if(err!=0)
//        {
//            printf("thread_create error:%s\n",strerror(err));
//            exit(-1);
//        }
//    }
//    for (i = 0; i < NUM; i++)
//    {
//        err = pthread_join(tid[i], &tret);
//        if (err != 0)
//        {
//            printf("can not join with thread %d:%s\n", i,strerror(err));
//            exit(-1);
//        }
//    }
//    printf("\n");
//    return 0;
//}
