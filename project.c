#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<semaphore.h>

struct sharedTable
{
	int pen;
	int paper;
	int question_paper;
};


// Student Process 1 having pen needs Question Paper and Paper to complete the assignment
void *student1(void *arg)
{
	
	sem_wait(&lock_var);

	struct sharedTable *s = (struct sharedTable*)arg;
	s->pen+=1;
	printf("\n\n\n\nStudent1\n");
	printf("Pen - %d Paper - %d QP - %d\n\n\n\n" ,s->pen,s->paper,s->question_paper);
	if(s->pen==0||s->paper==0||s->question_paper==0)
	{
		s->pen-=1;
		sem_post(&lock_var);

		wait();
	}
	else
	{
		if(s1==0)
		{
		printf("\n\t Student Process 1 completed his task\n");
		track_var++;
		s->pen=0;
		s->question_paper=0;
		s->paper=0;
		order[o]=1;
		o++;
		s1=1;
		}
		else
		{
			printf("\n\t Try Choosing Another option :- 1\n");
		}
	}
	sem_post(&lock_var);	
}

// Student Process 2 having Paper needs Pen and Question Paper to complete the assignment
void *student2(void *arg)
{
	
	sem_wait(&lock_var);

	struct sharedTable *s = (struct sharedTable*)arg;
	s->paper+=1;
	printf("\n\n\n\nStudent2\n");
	printf("Pen - %d Paper - %d QP - %d\n\n\n\n" ,s->pen,s->paper,s->question_paper);
	if(s->pen==0||s->paper==0||s->question_paper==0) 
	{	
		s->paper-=1;
		sem_post(&lock_var);
		
		wait();
	}
	else
	{
		if(s2==0)
		{
			printf("\n\t Student Process 2 completed his task\n");

			track_var++;
			s->question_paper=0;
			s->paper=0;
			s->pen=0;
			order[o]=2;
			o++;
			s2=1;
		}
		else
		{
			printf("\n\t Try Choosing Another option :-2\n");
		}
	}

	sem_post(&lock_var);
}

// / Student Process 1 having Question Paper needs Pen and Paper to complete the assignment
void *student3(void *arg)
{
	sem_wait(&lock_var);

	struct sharedTable *s = (struct sharedTable*)arg;
	s->question_paper+=1;
	printf("\n\n\n\nStudent3\n");
	printf("Pen - %d Paper - %d QP - %d\n\n\n\n" ,s->pen,s->paper,s->question_paper);
	if(s->pen==0||s->paper==0||s->question_paper==0)
	{	s->question_paper-=1;
		sem_post(&lock_var);
		wait();
	}
	else
	{
		if(s3==0)
		{
		printf("\n\t Student Process 3 completed his task\n");
		track_var++;
		s->question_paper=0;
		s->pen=0;
		s->paper=0;
		order[o]=3;
		o++;
		s3=1;
		}
		else
		{
		printf("\n\t Try Choosing Another option :-3\n");
		}
	}

	sem_post(&lock_var);
}
int main()
{
	sem_init(&lock_var,0,2);

	pthread_t t1 , t2 , t3;

	struct sharedTable s;
	s.pen=0;

	s.paper=0;

	s.question_paper=0;

	int choice;
	printf("\t Initially The Students have\n");
	printf("\t Student 1 has Pen \n");
	printf("\t Student 2 has Paper \n");
	printf("\t Student 3 has Question_paper\n");

	while(track_var!=3)

	{

		printf("\t Enter the things you want to place on the Shared Table\n");
		printf("\t Enter 1 for Pen and paper\n");
		printf("\t Enter 2 for pen and qustion paper\n");
		printf("\t Enter 3 for paper and question paper\n");
		scanf("%d",&choice);

		switch(choice)
		{
			
		}

		//Student Process 1 Thread
		pthread_create(&t1,NULL,student1,&s);

		//Student Process 2 Thread
		pthread_create(&t2,NULL,student2,&s);

		//Student Process 3 Thread
		pthread_create(&t3,NULL,student3,&s);

		//Thread joining all
		pthread_join(t1,NULL);

		pthread_join(t2,NULL);

		pthread_join(t3,NULL);
	}

	printf("\t All students completed the task!!!\n");
	printf("\t In the Order\n");
	printf("\t Student %d -->> Student %d -->> Student %d \n",order[0],order[1],order[2]);
	return 0;
}