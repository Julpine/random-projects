/*=============================================================================  
|   Source code:  MainCardHandler.c
|        Author:  Julian Pineiro
|  
|        Language:  C 
|     Compile/Run:  gcc MainCardHandler.c CardDeck.c TestCase.c GameLogic.c
|			./a.out (cards) (players)
|		    make
|			./output (cards) (players)
|					
| +----------------------------------------------------------------------------  
|  
|  Description: This program simulates Stud Poker. With a deck of
|               52 cards players are handed out 5 cards each from a shuffled deck. 
|		The program then orders and ranks each player's hand based on its 
|		value. After that a winner is decided from the set of players.
|		This then gets printed out and displayed as output. 
|                               							 
|                  
|        
|        Input: This program takes in two commandline inputs. First input
|		is a number that represents the number of cards in the game.
|		Second input is a number that represents the number of people
|		in the game.
|          
|				  
|	 Output: Program displays the original deck, a shuffled deck, and
|	         the cards that each player has. The cards will be printed
|	 	multiple times to display Sorted hands, Hand Types, and
|		Winners. Along with that a test case will be run on seperate
|		hands.
|				
|
|      Process:  
|				1. Create an array of Cards (deck).
|				2. Print the deck. Then shuffle.
|				3. Print out the shuffled deck.
|				4. Deal cards out to players
|				5. Calculate the winners and hands
|				6. Display each hand based on Style type
|				7. Run Test Case
|  
|   Required Features Not Included:  Shuffle is not dynamic and doesn't validate 
|                		     if the inputs are integers.
|  
|   Known Bugs: Ace does not work on high card Straights.						
| *==========================================================================*/


#include "StudPokerHeader.h"


int main(int argc,char *argv[])
{
		
	if(verify(argc, argv))
	{
		int cards =  atoi(argv[CARD_INPUT]);
		int players =  atoi(argv[PLAYER_INPUT]);		
		Card deck[DECK_SIZE] = {0};
		Player playerList[MAX_PLAYERS] = {0};
		
		printf("Number of cards: %d\nNumber of Players: %d\n\n",cards ,players );
		
		cardDeck(deck);
		printf("Initial Deck\n");
		displayDeck(deck,DECK_SIZE,DECK_FORMAT);
		
		shuffle(deck);
		printf("Shuffled Deck\n");
		displayDeck(deck,DECK_SIZE,DECK_FORMAT);

		dealCards(deck,cards,players,playerList);
		playGame(cards,players,playerList);
		
		
	}
	else
	{
		printf("Error! Values do not fit within the specified range\n");
		printf("Number of Cards per player must be 5\n");
		printf("Number of Players per game must be within 1-10\n");

	}
	
	return NO_ERROR;

} // end main



/*---------------------------- Verification -----------------------------------
 *|  Function verify()
 *|
 *|  Purpose:  To verify if the given commandline inputs are valid.
 *|
 *|  @param  argc - Amount of items from the commandline input
 *|  @param  argv - Pointer to an array of strings in the commandline input
 *|
 *|  @return  TRUE/FALSE - value (1) / value (0)
 *------------------------------------------------------------------------*/
int verify(int argc, const char *argv[])
{
	int elements = argc - 1; // Always has a starting of 1 element

	if(elements != REQUIRED_ELEMENTS)
	{
		
		return FALSE;

	}
	
	const char *Cards = argv[CARD_INPUT];
	const char *Players = argv[PLAYER_INPUT];
	int cardAmount = atoi(Cards);
	int playerAmount = atoi(Players);

	if(!checkConstraints(cardAmount, playerAmount))
	{

		return FALSE;

	}

	return TRUE;
		
}	// end function



/*---------------------------- Constraints -----------------------------------
 *|  Function checkConstraints()
 *|
 *|  Purpose:  Checks to see if the numbers given fall within the constraints
 *|	       Deck = 52 cards / Max value of items = 13/ Min value of items = 1
 *|
 *|  @param  cards - The number of cards that will be used.
 *|  @param  players - The number of players that will be used.
 *|
 *|  @return  TRUE/FALSE - value (1) / value (0)
 *------------------------------------------------------------------------*/
int checkConstraints(int cards, int players)
{
	/* Checking if value goes over the maximum */
	if ( cards != HAND_SIZE || players > MAX_PLAYERS)
	{
		return FALSE;

	}

	/* Checking if value goes under the minimum */
	if ( cards != HAND_SIZE || players > MAX_PLAYERS)
	{
		return FALSE;

	}
	
	/* Checking if the product is greater than the deck */
	if( (cards * players) > DECK_SIZE )
	{
		return FALSE;
	}

	return TRUE;

} //end function



/*---------------------------- Play Game ---------------------------------
 *|  Function playGame()
 *|
 *|  Purpose:  To play the game and display all of the different types of
 *|		displays using the Style enum.
 *|
 *|  @param  cards - The number of cards per player.
 *|  @param  players - The number of people there are.
 *|  @param  playerList - Array of players
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void playGame(int cards, int players, Player playerList[])
{
	Style displayCount = 0;
	for (displayCount = 0; displayCount <= Test;displayCount++)
	{
		if (displayCount != Test)
		{
			displayHands(cards,players,playerList,displayCount);

		}
		else
		{
			testerCase();
		}
	}

} //end function



/*----------------------------Display Player Hands -----------------------
 *|  Function displayPlayerHands()
 *|
 *|  Purpose:  To display the list of cards for each player. The display
 *|		changes when explicitly told to change
 *|
 *|  @param  cards - The number of cards per player.
 *|  @param  players - The number of people there are.
 *|  @param  playerList - An array of players.
 *|  @param  display - The type of display that will be used based on Style
 *|			enum.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void displayHands(int cards, int players, Player playerList[], Style display)
{

	int playerCount = 0;
	int cardCount = 0;
	
	displayStyleTitle(display);

	if (display > Sorted)
	{

		calcPlayerHands(playerList, players);
		calcWinner(playerList, players);
	}

	for (playerCount = 0;playerCount < players;playerCount++)
	{
		/* Sorts cards if they are not being displayed Normal */
		if (display != Normal)
		{
			orderCards(playerList[playerCount].playHand, cards);
		}

		/* Calls on the display function in CardDeck.c */
		printf("\nPlayer: %d] - ", (playerList[playerCount].playerID + 1));
		displayDeck(playerList[playerCount].playHand,cards,cards);
		displayHandLogic(playerList[playerCount],display);
	}

	printf("\n\n"); // print 2 new lines

} // end function



/*----------------------------Display Style Title -----------------------
 *|  Function displayStyleTitle()
 *|
 *|  Purpose:  Prints out a title based on which style is being used.
 *|		
 *|
 *|  @param  display - The type of display that will be used based on Style
 *|			enum.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void displayStyleTitle(Style display)
{

	if (display == Normal)
	{
		printf("Player Hands: (dealt from top/front of deck)");
	}
	else if (display == Sorted)
	{
		printf("Player Hands: (Sorted)");
	}
	else if (display == Ranked)
	{
		printf("Player Hands: (Ranked)");
	}
	else if (display == Winner)
	{
		printf("Player Hands: (Winners)");
	}
	else
	{
		printf("Test Case");
	}

} // end function



/*----------------------------Display Hand Logic -----------------------
 *|  Function displayHandLogic()
 *|
 *|  Purpose:  Based on what display style used this function will append
 *|		either the hand value or the winner.
 *|
 *|  @param  currentPlayer - The number of cards per player.
 *|  @param  display - The type of display that will be used based on Style
 *|			enum.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void displayHandLogic(Player currentPlayer, Style display)
{
	if (display > Sorted)
	{
		displayHandValue(currentPlayer);
		if (display == Winner)
		{
			displayWinner(currentPlayer);
		}
	}

} // end function



/*---------------------------- Deal Cards -----------------------------------
 *|  Function dealCards()
 *|
 *|  Purpose:  Distributes cards from the top of the deck to each player.
 *|
 *|  @param  deck - The deck of cards in an array
 *|  @param  cards - The number of cards per player.
 *|  @param  players - The number of players.
 *|  @param  playerList - A list of the current players.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void dealCards(Card deck[],int cards,int players, Player playerList[])
{
	int count = 0;
	int product = cards * players;	// Total amount of cards used
	int deckEnd = 0;
	int playerCount = 0;
	int cardCount = 0;
		

	for(playerCount = 0;playerCount < players;playerCount++)
	{
		playerList[playerCount].playerID = playerCount;
		playerList[playerCount].status = Unknown;
	
		for (cardCount = 0;cardCount < cards;cardCount++)
		{
			
			playerList[playerCount].playHand[cardCount] = deck[deckEnd];
			deckEnd++;
		}
	}

} //end function
