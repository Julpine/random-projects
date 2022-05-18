/*==========================================================================
|	Program Author: Julian Pineiro
|   Header File: SharedProcessHeader.h
|	
|	Header File for necessary libraries, definitions, and function prototypes
*==========================================================================*/


#include <string.h>		// Used for strlen()
#include <stdio.h> 		// Standard IO
#include <stdlib.h> 	// exit function and exit codes
#include <unistd.h> 	// Used for fork()
#include <sys/wait.h> 	// Used for wait() function
#include <sys/shm.h>	// Shared Memory Library
#include <sys/types.h>	// for pid type

#define MAX_ARGS 7		// Maximum arguments in the command line
#define MIN_ARGS 1		// Minimum arguments in the command line
#define MAX_INPUT 9		// Maximum integer input per argument
#define MIN_INPUT 0		// Minimum integer input per argument
#define NO_ERROR 0		// No Error is present
#define ERROR -1		// Error is present
#define BUF_LENGTH 80	// Buffer Length
#define INITIAL_ARG 1	// Initial argument in the command line
#define NEXT_VAL 1		// Next value in the array
#define STD_OUT 1		// Standard output code for write() function
#define VALID_INT 1		// Number of valid integers for sscanf
#define MEM_REQ 0666	// Memory request call number
#define CHILD_PROCESS 0	// Child return from fork function
#define LAST_FORK 0		// Last value in the fork function
#define MIN_VAL_PID 0	// Lowest valid child exit from the wait function
#define MIN_VAL_SHM 0	// Minumum value for a Shared Memory ID
#define FLAG_CONDITION 0// Flag needed for attaching shared memory


enum Boolean { False, True };
typedef enum Boolean Boolean;

struct ChildExit
{
	pid_t pid;
	int exitCode;
};
typedef struct ChildExit ChildExit;

/** Function Prototypes */
Boolean verifyData();
Boolean compareData();
Boolean validInputRange();
int * convertInput();
int requestSharedMemory();
int * attachSharedMemory();
void updateSharedMemory();
void displaySharedMemory();
void childProcess();
void parentProcess();
void fillSharedMemory();


