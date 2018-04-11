#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<semaphore.h>

int track_var = 0; // To keep the track of all the completed process

int s1=0,s2=0,s3=0; //variables to know which processes have been completed

sem_t lock_var; //Semaphore variable for locking

int order[4]={}; // To note the order of completion of the tasks
int o=0;

struct sharedTable
{
	int pen;
	int paper;
	int question_paper;
};


// Student Process 1 having Pen needs Question Paper and Paper to complete the assignment
void *student1(void *arg)
{
	
	sem_wait(&lock_var);

	struct sharedTable *s = (struct sharedTable*)arg;

	s->pen+=1; // Student 1 has got pen from Starting

	
	if(s->pen==0 || s->paper==0 || s->question_paper==0)
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
		s->paper=0;
		s->question_paper=0;
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

	s->paper+=1; //Student 2 has got Paper from Starting

	
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
			s->pen=0;
			s->paper=0;
			s->question_paper=0;
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

// / Student Process 3 having Question Paper needs Pen and Paper to complete the assignment
void *student3(void *arg)
{
	sem_wait(&lock_var);

	struct sharedTable *s = (struct sharedTable*)arg;
	s->question_paper+=1;
	
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
		s->pen=0;
		s->paper=0;
		s->question_paper=0;
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
	sem_init(&lock_var,0,1);

	pthread_t t1 , t2 , t3;

	struct sharedTable s;

	int choice;
	printf("\n\t Initially The Students have\n");
	printf("\t Student 1 has      Pen       needs Paper and Question paper\n");
	printf("\t Student 2 has     Paper      needs Pen and Question paper\n");
	printf("\t Student 3 has Question_paper needs Pen and Paper\n");

	while(track_var!=3)

	{
		
		printf("\n\t Enter the things you want to place on the Shared Table\n");
		printf("\t Enter 1 for Paper and Question paper\n");
		printf("\t Enter 2 for Pen and Question paper\n");
		printf("\t Enter 3 for Pen and Paper\n");
		scanf("%d",&choice);
		s.pen=0;
		s.paper=0;
		s.question_paper=0;

		switch(choice)
		{
			case 1:
				{
					s.pen=0;
					s.paper=1;
					s.question_paper=1;
					break;
				}
			case 2:
				{
					s.pen=1;
					s.paper=0;
					s.question_paper=1;
					break;
				}
			case 3:
				{
					s.pen=1;
					s.paper=1;
					s.question_paper=0;
					break;
				}
			default:
				{
				printf("\t You chose wrong option try again\n");
				}
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