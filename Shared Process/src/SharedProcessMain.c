/*=============================================================================
|   Source code:  SharedProcessMain.c
|        Author:  Julian Pineiro
|
|    					Language:  C
|						Full Program:
|     Compile/Run:
|
|	makefile Compile: make build
|			     Run: ./SharedProcess 1 2 3 4 5 6 7
|		Dependencies: "SharedProcessHeader.h" must be in the same directory
|					  "makefile" must be in the same directory
|			          Amount of aruguments must be between 1-7 (not including
|					  the process argument) and must be unique integers between
|					  the values 0-9.
|
|	  Normal Compile: gcc SharedProcessMain.c -o SharedProcess
|				 Run: ./SharedProcess 1 2 3 4 5 6 7
|	    Dependencies: "SharedProcessHeader.h" must be in the same directory
|					  Amount of aruguments must be between 1-7 (not including
|					  the process argument) and must be unique integers between
|					  the values 0-9.
|				      
|
|
|
| +----------------------------------------------------------------------------
|
|  Description: This program takes a set of integers from command line input 
|				attaches shared memory based on its size. This shared memory
|				is filled with the arguments and the parent forks a number of 
|				children depending on the number of command line arguments given
|				by the user. Children processes will interact with shared memory
|				via their unique ID or index and multiply the value stored by 
|				Its ID. The parent waits for all the children to finish and then
|				returns.
|
|
|
|        Input: The input is taken through command line input where the amount
|				of arguments must be between 1-7 (not including the process)
|				and must be unique integers between the values 0-9.
|
|
|	    Output: This program will output a set of trace statements from both the
|				parent and children. The output is unbuffered after the fork takes
|				place to provide an accurate trace.
|
|
|      Process:
|				1. Verifys command line input
|				2. Request and attach shared memory
|				3. Fill shared memory with command line arguments
|				4. Display shared memory
|				5. Fork n children (n is the number of arguments)
|					-----------------------------------------------
|				6. (Parent Process) Concurrent
|				7. Wait for all children
|				8. Display shared memory and child exit codes
|				9. Detach shared memory
|				10. Remove shared memory
|				11. Return/End
|					-----------------------------------------------
|				6. (Child Process) Concurrent
|				7. Display and update shared memory
|				8. Return/End
|
|	Warning messages: Comparison between pointer and an integer when attaching
|					  shared memory. This is instructor approved because this
|					  comparison must be made.
|
|   Required Features Not Included:  None
|
|   Known Bugs: None
| *==========================================================================*/

#include "SharedProcessHeader.h"

int main(int argc,char *argv[])
{
	int uniqueID = 0;
	int status = 0;
	int const arguments = argc - INITIAL_ARG;
	int shmID = 0;
	int *shmPtr = NULL;
	pid_t ppid = getpid(); // parent process id
	
	printf("Parent: starts\n");
	if (verifyData(arguments, argv))
	{
		printf("Parent: validate command line\n\n");
		shmID = requestSharedMemory(arguments);
		shmPtr = attachSharedMemory(shmID);
		fillSharedMemory(shmPtr, arguments, argv);
		if (shmPtr == NULL)
		{
			return ERROR;
		}
		displaySharedMemory(shmPtr, arguments, uniqueID, ppid);
		
		printf("\nParent: forks (each) child\n");
		uniqueID = forkChildren(arguments);
		
		/** Parent Process */
		if (getpid() == ppid)
		{
			parentProcess(shmPtr, shmID, arguments, status);
			return NO_ERROR;
		}
		/** Child Process */
		else
		{
			childProcess(shmPtr, arguments, uniqueID, ppid);
		}	
	}
	return NO_ERROR;
	
} // end main



/*---------------------------- Verify Data -------------------------------
*|  Function verifyData()
*|
*|  Purpose:  To verify that user input fits within the specified bounds
*|			  of the program. User input must be between 1-7 arguments, and
*|			  each input must be a unique integer between 0-9.
*|
*|
*|  @param arguments - Amount of arguments in the command line
*|  @param argv - Array of strings input by the user
*|
*|  @return  True/False - True means a validated input
*------------------------------------------------------------------------*/
Boolean verifyData(int const arguments, char * argv[])
{

	int count = 0;
	int input = 0;
	int * inputList = NULL;
	
	Boolean isUnique = False;

	if (arguments < MIN_ARGS || arguments > MAX_ARGS)
	{
		fprintf(stderr, "Invalid number of arguments\n");
		return False;
	}

	inputList = convertInput(arguments, argv);
	if (inputList == NULL)
	{
		fprintf(stderr, "Specified argument out of bounds or invalid\n");
		return False;
	}

	isUnique = compareData(arguments, inputList);
	free((int*)inputList); // Free Malloc pointer inputList

	return isUnique;

} // end function



/*---------------------------- Compare Data -------------------------------
*|  Function compareData()
*|
*|  Purpose:  To compare the values of all the integer arguments. If any
*|		      elements are the same then return False.
*|
*|
*|  @param arguments - Amount of arguments in the command line
*|  @param inputList - Array of integers converted from the command line
*|
*|  @return  True/False - True if all integers are unique
*------------------------------------------------------------------------*/
Boolean compareData(int arguments, int * inputList)
{

	int count = 0;
	int count2 = 0;
	if (inputList == NULL)
	{
		return False;
	}

	for (count = 0; count < arguments; count++)
	{
		
		for (count2 = count + INITIAL_ARG; count2 < arguments; count2++)
		{

			if (inputList[count] == inputList[count2])
			{
				printf("%d-%d\n", inputList[count], inputList[count2]);
				fprintf(stderr,"Repeating arguments found\n");
				return False;
			}
			
		}
	}
	
	return True;
	
} // end function



/*---------------------------- Convert Input -----------------------------
*|  Function convertInput()
*|
*|  Purpose:  To turn string inputs from the command line into a variable
*|			  sized array of integers to make evaluating integers easier.
*|
*|
*|  @param arguments - Amount of user-input values
*|  @param argv - Array of strings input by the user
*|
*|  @return  inputList - A pointer to a variable sized array of ints
*|	
*| 	Warning: When calling this function the pointer must be set free since
*|			 this function calls Malloc
*|  
*------------------------------------------------------------------------*/
int * convertInput(int const arguments, char * argv[])
{
	int input = 0;
	int count = 0;
	int * inputList = malloc(arguments * sizeof(int));
	if (inputList == NULL) {
		fprintf(stderr, "malloc failed\n");
		return NULL;
	}
	
	for (count = 0; count < arguments; count++)
	{

		int validInteger = sscanf(argv[count + INITIAL_ARG], "%d", &input);
		if (validInteger == VALID_INT && validInputRange(input))
		{
			inputList[count] = input;
		}
		else
		{
			printf("Failure\n");
			return NULL;
		}

	}
	
	return inputList;

} // end function



/*---------------------------- Valid Range -------------------------------
*|  Function validInputRange()
*|
*|  Purpose:  Checks to see if an integer is between the valid range between
*|			  MIN_INPUT and MAX_INPUT
*|
*|
*|  @param input - An integer that will get evaluated
*|
*|  @return  True/False - True if integer fits within the valid range
*------------------------------------------------------------------------*/
Boolean validInputRange(int input)
{
	if (input < MIN_INPUT || input > MAX_INPUT)
	{
		return False;
	}
	else
	{
		return True;
	}
	
} // end function



/*---------------------------- Fork Children -------------------------------
*|  Function forkChildren()
*|
*|  Purpose:  Recursive function to spawn a select number of child processes
*|
*|
*|  @param children - Number of children to be forked
*|
*|  @return  process - the current process number running
*------------------------------------------------------------------------*/
int forkChildren(int children)
{
	char buf[BUF_LENGTH] = { 0 };
    pid_t pid = 0;
	int process = children;

    if (process <= LAST_FORK)
	{
		return LAST_FORK;
	}	

    if (process > LAST_FORK)
    {
		
		sprintf(buf,"Parent: forks child %d \n", process);
		write(STD_OUT, buf, strlen(buf));
		
        if ((pid = fork()) < CHILD_PROCESS)
        {
            fprintf(stderr,"fork failed\n");
        }
		/** Child Process */
        else if (pid == CHILD_PROCESS)
        {
            sprintf(buf,"\tChild ID: %d starts [%d] \n", process, getpid());
			write(STD_OUT, buf, strlen(buf));
			return process;
        }
		/** Parent Process */
		else if(pid > CHILD_PROCESS)
        {
			process = process--;
            forkChildren(process); // Recursive Call
        }
	
    }
	
} // end function



/*------------------------- Display Shared Memory ------------------------
*|  Function displaySharedMemory()
*|
*|  Purpose:  To display the contents of the shared memory section
*|
*|
*|  @param shmPtr - Pointer to shared memory
*|  @param size - Size of the shared memory segment
*|  @param uniqueID - Unique Id of the current child process
*|  @param ppid - Parent process id
*|
*|  @return  void
*------------------------------------------------------------------------*/
void displaySharedMemory(int *shmPtr, int const size, int uniqueID, pid_t ppid)
{
	char buf[BUF_LENGTH] = { 0 };
	int count = 0;

	if (getpid() == ppid)
	{
		sprintf(buf, "Parent: (shared memory)");
	}
	else
	{
		sprintf(buf, "\tChild ID: %d (shared memory)", uniqueID);
	}
	
	for (count = 0; count < size; count++)
	{
		sprintf(buf + strlen(buf), " %d", shmPtr[count]);
		
	}
	sprintf(buf + strlen(buf), "\n");
	write(STD_OUT, buf, strlen(buf));
}



/*------------------------ Update Shared Memory --------------------------
*|  Function updateSharedMemory()
*|
*|  Purpose:  To update the shared memory through index uniqueID. This update
*|			  involves taking the current integer at that index and multiplying
*|			  it by the unique Id then storing in the same location.
*|
*|
*|  @param uniqueID - Unique Id of the child
*|  @param arguments - Number of command line arguments
*|	@param shmPtr - Pointer to shared memory
*|
*|  @return  void
*------------------------------------------------------------------------*/
void updateSharedMemory(int uniqueID, int const arguments, int *shmPtr)
{
	
	int dataValue = shmPtr[uniqueID - INITIAL_ARG];
	dataValue = dataValue * uniqueID;
	shmPtr[uniqueID - INITIAL_ARG] = dataValue;
	
} // end function



/*---------------------------- Child Process -----------------------------
*|  Function childProcess()
*|
*|  Purpose:  To display and update shared memory through the use of a
*|			  unique Id for each child.
*|
*|
*|  @param shmPtr - Pointer to shared memory
*|  @param arguments - Amount of arguments int he command line input
*|  @param uniqueID - Unique Id of the current child process
*|  @param ppid - Parent process id
*|
*|  @return  void
*------------------------------------------------------------------------*/
void childProcess(int * shmPtr, int const arguments, int uniqueID, pid_t ppid)
{
	char buf[BUF_LENGTH] = { 0 };

	displaySharedMemory(shmPtr, arguments, uniqueID, ppid);
	
	sprintf(buf, "\tChild ID: %d unique ID = %d\n", uniqueID, uniqueID);
	write(STD_OUT, buf, strlen(buf));

	sprintf(buf,"\tChild ID: %d updates shared memory\n", uniqueID);
	write(STD_OUT, buf, strlen(buf));
	updateSharedMemory(uniqueID, arguments, shmPtr);

	displaySharedMemory(shmPtr, arguments, uniqueID, ppid);
	
	sprintf(buf, "\tChild ID: %d exits with code %d\n", uniqueID, NO_ERROR);
	write(STD_OUT, buf, strlen(buf));

} // end function



/*------------------------- Parent Process ------------------------
*|  Function parentProcess()
*|
*|  Purpose:  To run through all the parent steps after the fork takes
*|			  place in the main. Waits for all children to complete.
*|
*|
*|  @param shmPtr - Pointer to shared memory
*|  @param shmID - Shared memory ID
*|  @param arguments - Amount of arguments int he command line input
*|  @param status - Status of all the processes
*|
*|  @return  void
*------------------------------------------------------------------------*/
void parentProcess(int * shmPtr, int shmID, int const arguments, int status)
{
	
	char buf[BUF_LENGTH] = { 0 };
	int uniqueID = 0;
	ChildExit exitStorage[MAX_ARGS] = { 0 };
	int count = 0;
	
	printf("Parent: waits for (each) child\n");
	pid_t pid = wait(&status);
	int exitS = WEXITSTATUS(status);
	
	sprintf(buf, "Parent: detects child completion\n");
	write(STD_OUT, buf, strlen(buf));
	while (pid > MIN_VAL_PID && count < arguments)
	{
		exitStorage[count].pid = pid;
		exitStorage[count].exitCode = exitS;
		pid = wait(&status);
		count++;
	}
	
	for (count = 0; count < arguments; count++)
	{
		pid = exitStorage[count].pid;
		exitS = exitStorage[count].exitCode;
		sprintf(buf, "Parent: child PID %d & exit code %d\n", pid, exitS); 
		write(STD_OUT, buf, strlen(buf));
	}
	
	displaySharedMemory(shmPtr, arguments, uniqueID, getpid());
	shmdt(shmPtr);
	printf("Parent: detatches shared memory\n");
	shmctl(shmID, IPC_RMID, NULL);
	printf("Parent: removes shared memory\n");
	printf("Parent: finished\n");
			
} // end fuction



/*------------------------- Request Shared Memory ------------------------
*|  Function requestSharedMemory()
*|
*|  Purpose:  To request a segment of variable sized memory from the
*|			  operating system.
*|
*|
*|  @param arguments - Amount of arguments int he command line input
*|
*|  @return  shmID - Shared Memory ID of the requested memory
*------------------------------------------------------------------------*/
int requestSharedMemory(int const arguments)
{
	int shmID = 0;
	printf("Parent: requests shared memory\n");
	shmID = shmget(IPC_PRIVATE, arguments * sizeof(int), IPC_CREAT | MEM_REQ);
	if (shmID < MIN_VAL_SHM)
	{
		fprintf(stderr, "shmget error\n");
		return ERROR;
	}
	printf("Parent: receieves shared memory\n");
	return shmID;
	
} // end function



/*------------------------- Attach Shared Memory --------------------------
*|  Function attachSharedMemory()
*|
*|  Purpose:  To attach a segment of Shared Memory to the process for 
*|			  accessability to all children
*|
*|  @param shmID - Shared Memory ID of requested memory
*|
*|  @return  shmPtr - returns the pointer to shared memory,
*------------------------------------------------------------------------*/
int * attachSharedMemory(int shmID)
{
	int *shmPtr = NULL;
	if (shmID == ERROR)
	{
		return NULL;
	}
	else
	{
		shmPtr = (int *)shmat(shmID, NULL, FLAG_CONDITION);
		if ((int*)shmPtr == ERROR) 
		{
			printf("*** shmat error (server) ***\n");
			return NULL;
		}

		printf("Parent: attaches shared memory\n");
		return shmPtr;
	}
} // end function



/*------------------------- Fill Shared Memory -----------------------------
*|  Function fillSharedMemory()
*|
*|  Purpose:  To fill a segment of shared memory with the values given in
*|			  the command line input.
*|
*|  @param shmPtr - Pointer to shared memory
*|  @param arguments - Amount of arguments in the command line input
*|  @param argv - Array of strings from command line input
*|
*|  @return void
*------------------------------------------------------------------------*/
void fillSharedMemory(int *shmPtr, int const arguments, char *argv[])
{
	printf("Parent: fills shared memory\n");
	int *convert = convertInput(arguments, argv);
	int count = 0;

	for (count = 0; count < arguments; count++)
	{
		shmPtr[count] = convert[count];
		
	}

	free((int*)convert); // Free pointer from Malloc
	
} // end function

