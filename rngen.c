
#include <stdio.h> 
#include <stdlib.h> 

int GetRand(int min, int max);

int main(void)
{
	/* The 6 process states */
	char* states[6] = {"Current", "Ready", "Waiting", "Receiving", "Sleeping", "Suspended"};

	/* Current 6 Priority Numbers*/
	int* priNums[6] = { 1,2,3,4,5,6 };

	/* i = how many values needed, r = the random value used*/
	int i, r;

	/* Determine 2 values (1 for priority and 1 for process state)*/
	for (i = 0; i < 2; i++)
	{
		/* At the moment, 6 possible variations*/
		r = GetRand(0, 5);
		if (i == 0)
		{
			/* Determine Priority based on random value*/
			switch (r)
			{
			case 0:
				printf("Priority = %d\n",priNums[r]);
				break;
			case 1:
				printf("Priority = %d\n", priNums[r]);
				break;
			case 2:
				printf("Priority = %d\n", priNums[r]);
				break;
			case 3:
				printf("Priority = %d\n", priNums[r]);
				break;
			case 4:
				printf("Priority = %d\n", priNums[r]);
				break;
			case 5:
				printf("Priority = %d\n", priNums[r]);
				break;
			}
		}

		/* Determine process state based on random value*/
		if (i == 1)
		{
			switch (r)
			{
			case 0:
				printf("State = %s\n",states[r]);
				break;
			case 1:
				printf("State = %s\n", states[r]);
				break;
			case 2:
				printf("State = %s\n", states[r]);
				break;
			case 3:
				printf("State = %s\n", states[r]);
				break;
			case 4:
				printf("State = %s\n", states[r]);
				break;
			case 5:
				printf("State = %s\n", states[r]);
				break;
			}
		}
	}

	return(0);
}

/* Function to obtain random value, min = lowest, max = highest*/
int GetRand(int min, int max)
{
	static int Init = 0;
	int rc;

	/* Makes sure everytime this is run, provides different values*/
	if (Init == 0)
	{
		srand(time(NULL));
		Init = 1;
	}

	/* Gives a random value between the min and max values*/
	rc = (rand() % (max - min + 1) + min);

	return (rc);
}
