#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<semaphore.h>
int c=0;
sem_t lock_var;
struct sharedTable
{
	int pen;
	int paper;
	int question_paper;
};
void *student1(void *arg)
{

}
void *student2(void *arg)
{

}
void *student3(void *arg)
{
	
}
int main()
{
	sem_init(&lock_var,0,1);
	pthread_t student1 , student2 , student3;
	struct sharedTable s;

	pthread_create(&student1,NULL,S1,&s);
	pthread_create(&student2,NULL,S2,&s);
	pthread_create(&student3,NULL,S3,&s);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	
	return 0;
}