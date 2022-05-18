/*=============================================================================  
|   Source code:  CardDeck.c
|        Author:  Julian Pineiro
|=============================================================================*/

#include "StudPokerHeader.h"

/* *Definitions of Suits and Ranks */
char *ranks[RANKS] = { "A", "2", "3", "4", "5", "6", "7",
"8", "9", "10", "J", "Q", "K" };
char *suits[SUITS] = { "S","H","D","C" };


/*----------------------------Initilize Deck -----------------------
 *|  Function cardDeck()
 *|
 *|  Purpose:  Fill an array of cards with values and properties.
 *|
 *|  @param  deck - An empty array of cards.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void cardDeck(Card deck[])
{

	CardRank rank = Ace;
	CardSuit suit = Spades;
	int value = 0;
	int count = 0;

	for (rank = Ace ; rank <= King; rank++)
	{
		
		for(suit = Spades; suit <= Clubs;suit++)
		{
			
			value = (rank * SUITS) + suit;
			deck[count].rank = ranks[rank];
			deck[count].suit = suits[suit];
			deck[count].rankValue = rank;
			deck[count].suitValue = suit;
			deck[count].cardValue = value;
			count++;
		}

	}

}

/*----------------------------Display Deck -------------------------------
 *|  Function cardDeck()
 *|
 *|  Purpose:  Displays cards that are in the deck calling the decodeCard()
 *|		function to make sense of the integers.
 *|
 *|  @param  deck - An array of cards.
 *|  @param  size - the size of the array of integers.
 *|  @param  format - The number of card elements placed on every line.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void displayDeck(Card deck[],int size, int format)
{
	
	int count = 0;
	
	for (count = 0; count < size;count++)
	{
		
		char *current_rank = deck[count].rank;
		char *current_suit = deck[count].suit;
		
		if (size == HAND_SIZE)
		{
			printf("\t[%s-%s]",current_rank,current_suit);
		}
		else
		{
			printf("[%s-%s]\t",current_rank,current_suit);

		}

		if (((count + 1) % format) == 0 && format != HAND_SIZE)
		{
			printf("\n"); // new line
		}

	}
	if (size != HAND_SIZE)
	{
		printf("\n"); // new line

	}

} // end function


/*----------------------------Order Cards -------------------------------
 *|  Function orderCards()
 *|
 *|  Purpose:  Orders the players cards to make them easier to evaluate.
 *|   		The function orders through the use of bubble sort.
 *|  Source: https://www.geeksforgeeks.org/bubble-sort/
 *|
 *|  @param  hand - An array filled with integers.
 *|  @param  size - the size of the array of cards.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void orderCards(Card hand[], int size)
{
	int count = 0;
	int count2 = 0;
	Card testVal = {0};

	for (count = 0;count < (size - 1); count++)
	{

		for (count2 = 0; count2 < size - count - 1; count2++)
		{

			if (hand[count2].cardValue > hand[count2 + 1].cardValue)
			{
				testVal = hand[count2];
				hand[count2] = hand[count2 + 1];
				hand[count2 + 1] = testVal;
			}

		}

	}


} // end function




/*----------------------------Shuffle Deck -------------------------------
 *|  Function shuffle()
 *|
 *|  Purpose:  Takes an array of integers and swaps with a ranodom value
 *| 		started from the back of the deck.
 *|  Source:  https://en.wikipedia.org/wiki/Fisher-Yates_shuffle
 *|
 *|  @param  deck - An array filled with integers.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void shuffle(Card deck[])
{
	int count = 0;
	int random = 0;
	for (count = (DECK_SIZE - 1) ; count > -1 ;count--)
	{
		random = (rand()) % DECK_SIZE;
		Card initialValue = deck[count];
		deck[count] = deck[random]; //import random library
		deck[random] = initialValue;

	}			


} // end function

