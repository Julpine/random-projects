#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <mpi.h>
#define MAX_WORDS 58110
#define MAX_LENGTH  20
#define ALPHABET_LENGTH 26

//function prototypes.
void initializeWordList();
void initializeLetterList();
int evaluateWord();
int evaluateWordList();
void insertionSort();
double calcTime();

//defines cpu and numcpus variables for mpi use
int cpu, numcpus;

//struct used to define frequency with which each letter repeats on the alphabet
typedef struct Letter
{
	char letter;
	int frequency;
}Letter;


/*------------------------------------Description-----------------------------------------
Function: mpiEvaluate

Description: evaluate method desinged for mpi use. it takes the list of words, the frequency
list and the total number of words to read and distributes the work in between cores. The
Master CPU (cpu = 0) sends the wordList  to the different cpus, does its own share of the
work with the it wordlist, then receives the number of misses from the other cpu's and
finally prints the result.

Returns: prints total number of misses to the screen gathered from all the cores running

Params:
- wordList = list of words passed by the the CPU 0
- letterList = frequency list passed by the CPU 0
- wordsToRead = total words. Its divided so that each cpu takes an 'even' share

----------------------------------------------------------------------------------------*/

void mpiEvaluate(char wordList[][MAX_LENGTH], Letter letterList[], int wordsToRead)
{
	int counter, slave, misses = 0, coresMisses = 0, tag1 = 1, tag2 = 2, tag3 = 3;
	MPI_Status status;

	//divide the work that need to be done between cpus
	int numeach = wordsToRead/numcpus;

	if (cpu == 0)
	{
		// sent  how many needs to be process (numeach) and the list of words (wordList) to
		//each slave cpu
		for(slave = 1; slave < numcpus; slave++)
		{
			MPI_Send(&numeach, 1, MPI_INT, slave, tag1, MPI_COMM_WORLD);
			MPI_Send(&wordList[numeach * slave][0], numeach * MAX_LENGTH, MPI_CHAR, slave, tag2, MPI_COMM_WORLD);
		}

		//process own share of wordList from 0 to numeach
		for(counter = 0; counter < numeach; counter++)
		{
			misses += evaluateWord(wordList[counter], letterList);
		}

		// receive number of misses from other cpus
		for(slave = 1; slave < numcpus; slave++)
		{
			MPI_Recv(&coresMisses, 1, MPI_INT, slave, tag3, MPI_COMM_WORLD, &status);
			misses += coresMisses;
		}

		printf("AMOUNT OF MISSES : %d FOR %d words\n", misses, wordsToRead);
	}

	else
	{
		// receive amount of work (numeach) and the words (wordList) from cpu 0.
		MPI_Recv(&numeach, 1 , MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
		char data[numeach][MAX_LENGTH];
		MPI_Recv(&data, numeach * MAX_LENGTH , MPI_CHAR, 0, tag2, MPI_COMM_WORLD, &status);

		for(counter = 0; counter < numeach; counter++)
		{
			misses += evaluateWord(data[counter], letterList);
		}
		//sent total misses calculated
		MPI_Send(&misses, 1, MPI_INT, 0, tag3, MPI_COMM_WORLD);
	}

}

int main(int argc, char** argv)
{
	//used for measuring the time it takes to compile
	struct timespec start, end;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &cpu);
	MPI_Comm_size(MPI_COMM_WORLD, &numcpus);

	int wordsToRead; //parameter to read x amount of words with user input.
	int misses;
	char wordList[MAX_WORDS][MAX_LENGTH]; //list of words.
	Letter letterList[ALPHABET_LENGTH]; //frequency list
	double time_working = 0.0;

	initializeLetterList(letterList);

	//run single core and see what the results are
	if (cpu == 0)
	{

		puts("Enter the amount of words to read from the file. Number of words should be less than 58,000.");
		puts("It will read up to EOF if you enter more words than there are available");
		scanf("%d", &wordsToRead);
		if (wordsToRead > 58110)
			wordsToRead = 58110;

		puts("==============SINGLE CORE================");

		initializeWordList(wordList, wordsToRead);

		clock_gettime(CLOCK_REALTIME, &start);

		int counter;
		for(counter = 0; counter < wordsToRead; counter++)
		{
			misses += evaluateWord(wordList[counter], letterList);
		}

		clock_gettime(CLOCK_REALTIME, &end);

		//time_working = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
		time_working = calcTime(start, end);

		printf("AMOUNT OF MISSES : %d FOR %d words\n", misses, wordsToRead);
		printf("Time elpased is %f seconds\n", time_working);

		puts("==============MULTI CORE================");
		initializeLetterList(letterList);
	}

	//multicore starts here
	clock_gettime(CLOCK_REALTIME, &start);
	mpiEvaluate(wordList, letterList, wordsToRead);
	clock_gettime(CLOCK_REALTIME, &end);

	time_working = calcTime(start, end);

	if (cpu == 0)
		printf("Time elpased is %f seconds\n", time_working);

	MPI_Finalize();

	return 0;
}

/*------------------------------------Description-----------------------------------------
Function: calcTime

Description: calculates time elapsed between its 2 accepted parametes

Returns: calculated time in secods (as a double).

Params:
- start = struct timespec defined in time.h. Holds the time the process started
- end = struct timespec defined in time.h. Holds the time the process ended
----------------------------------------------------------------------------------------*/

double calcTime(struct timespec start, struct timespec end)
{
	const double BILLION = 1000000000.0;
	return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
}


/*------------------------------------Description-----------------------------------------
Function: initializeLetterList

Description: Initializes the letter list with the optimized alphabet
based on the letter frequency of the Oxford dictionary.

Returns: array of struct type Letter, with frequency initialized to zero

Params:
- letterList
- usePreOptimization
- optimizedAlphabet
----------------------------------------------------------------------------------------*/

void initializeLetterList(Letter letterList[])
{
	int i;
	for(i = 0; i < ALPHABET_LENGTH; i ++)
	{
		letterList[i].letter = 97 + i;
		letterList[i].frequency = 0;
	}

}


/*------------------------------------Description-----------------------------------------
Function: initializeWordList

Description: Initializes the word list from an input file. Uses default name "words.dat"
for the file located in the directoryu where the source file is. It will continue grabbing
words from the input file as long as EOF hasn't been reached or up to the amount of words
to read.

Returns: array of strings read from the file

Params:
- wordList = two dimensional array with first dimension being the amount of words,
second dimension being the length of each word. string array.
- wordsToRead  = the amount of words to read from the file.
----------------------------------------------------------------------------------------*/

void initializeWordList(char wordList[][MAX_LENGTH], int wordsToRead)
{
	char * fileName = "50kwords.dat";
	FILE * filePtr = fopen(fileName, "r");

	if(filePtr == NULL)
	{
		printf("File %s not found", fileName);
		exit(1);
	}

	int wordCounter = 0;

	while(!feof(filePtr) && wordCounter < wordsToRead)
	{
		fscanf(filePtr, "%s", wordList[wordCounter]);
		wordCounter++;
	}

	fclose(filePtr);
}


/*------------------------------------Description-----------------------------------------
Function: evaluateWordList

Description: Evaluates a specific amount of words from the word list by checking each
letter in each position with the help of a frequency list. It calls the function
'evaluateWord' to get the toal number of misses

Returns: the total number of misses in the word

Params:
- wordList[][] = the list of words to be evaluated.
- letterList[] = the list of Letter structs that will be used to evaluate each word.
- amountToEvaluate = how many words it will evaluate from the list.

----------------------------------------------------------------------------------------*/

int evaluateWordList(char wordList[][MAX_LENGTH], Letter letterList[], int amountToEvaluate)
{
	int i;
	int missCounter = 0;


	for(i = 0; i < amountToEvaluate; i++)
	{
		missCounter = missCounter + evaluateWord(wordList[i], letterList);
	}

	return missCounter;
}

/*------------------------------------Description-----------------------------------------
Function: evaluateWord

Description: Evaluates a single word using the frequency list. It compares the entire word
to the current element on the list. It records a hit for the element if the letter of the
word matches the current element in the frequency array, and records a miss if loop reaches
the end of the word without a hit. It then sorst the frequency list as to have an updated
value of the most frequent letters used.

Returns: number of misses in that word array word[], or -1 if error.

Params:
- word = The string to be evaluated
- letterList = The frequency list.
----------------------------------------------------------------------------------------*/

int evaluateWord(char word[], Letter letterList[])
{
	size_t wordL = strlen(word);

	int counter, charCounter, missCounter = 0, hitCounter = 0, freqCount = 0;

	for(counter = 0; counter < ALPHABET_LENGTH; counter++, freqCount = 0)
	{
		for(charCounter = 0; charCounter < wordL; charCounter++)
		{
			if(letterList[counter].letter == word[charCounter])
			{
				freqCount++;
			}
			else if(charCounter == wordL - 1 && freqCount == 0)
			{
				missCounter++;
			}
		}

		hitCounter += freqCount;
		letterList[counter].frequency += freqCount;

		if(hitCounter == wordL)
		{
			insertionSort(letterList);
			return missCounter;
		}
	}

	return -1;
}


/*------------------------------------Description-----------------------------------------
Function: insertionSort

Description: Uses insertion sort to sort a letterList based on the frequency of each Letter
struct. Insertion sort is used given that is one of the best algorithms to sort almost
ordered arrays.

Returns: ordered letterList

Params:
- letterList = the array of Letters to be sorted based on parameter frequency
----------------------------------------------------------------------------------------*/

void insertionSort(Letter letterList[])
{
	int i;
	for(i = 1; i < ALPHABET_LENGTH; i++)
	{
		int j = i;
		Letter temp = letterList[i];
		for(; j > 0 && letterList[j - 1].frequency < temp.frequency; j--)
		{
			letterList[j] = letterList[j - 1];
		}

		letterList[j] = temp;
	}
}
