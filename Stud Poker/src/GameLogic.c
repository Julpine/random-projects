/*=============================================================================  
|   Source code:  GameLogic.c
|        Author:  Julian Pineiro
|=============================================================================*/

#include "StudPokerHeader.h"

/* *Definitions of Hands and Outcomes */
char *gameOutcome[GAME_OUTCOME] = { "Unknown", "Lost", "Won"};

char *handTypes[HAND_TYPES] = { "High Card","One Pair","Two Pairs",
"Three of a Kind","Straight","Flush","Full House", "Four of a Kind",
"Straight Flush"};



/*----------------------------Display Hand Value -----------------------
 *|  Function displayHandValue()
 *|
 *|  Purpose:  Display the hand type that the player has.
 *|
 *|  @param  currentPlayer - The player that is currently being evaluated.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void displayHandValue(Player currentPlayer)
{

	HandType currentHand = currentPlayer.handValue;
	printf("\t%s",handTypes[currentHand]);

} // end function



/*----------------------------Display Winner ---------------------------
 *|  Function displayWinner()
 *|
 *|  Purpose:  Display "Won" if the player has won the game.
 *|
 *|  @param  currentPlayer - The player that is currently being evaluated.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void displayWinner(Player currentPlayer)
{
	GameStatus outcome = currentPlayer.status;
	if (outcome == Won)
	{
		printf("\t%s",gameOutcome[outcome]);
	}
} // end function



/*----------------------------Calculate Winner -----------------------
 *|  Function calcWinner()
 *|
 *|  Purpose:  Compare the hand types of each player and figure out who has
 *| 		won the game.
 *|
 *|  @param  playerList - An array of players.
 *|  @param  players - The amount of players.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void calcWinner(Player playerList[], int players)
{
	int count = 0;
	int count2 = 0;
	for (count = 0; count < players; count++)
	{
		
		HandType currentHand = playerList[count].handValue;
		playerList[count].status = Won;
		
		
		
		for (count2 = 0; count2 < players; count2++)
		{
			
			HandType testHand = playerList[count2].handValue;
			if (currentHand < testHand)
			{
				playerList[count].status = Lost;
			}
		}
		

	}
}


/*----------------------------Calculate Hands -----------------------
 *|  Function calcPlayerHands()
 *|
 *|  Purpose:  Calculates the hand that each player currently holds.
 *|
 *|  @param  playerList - An array of players.
 *|  @param  players - The amount of players.
 *|
 *|  @return  void
 *------------------------------------------------------------------------*/
void calcPlayerHands(Player playerList[], int players)
{
	int count = 0;
	//Card *hand;
	int highestMatch = 0;
	for (count = 0; count < players; count++)
	{
		//hand = playerList[count].playHand;
		highestMatch = findHighestMatch(playerList[count].playHand);
		//highestMatch = findPairs(playerList[count].playHand);

		if (highestMatch > NO_MATCH)
		{
			if(highestMatch == PAIR)
			{
				playerList[count].handValue = Pair;

				if(findPairs(playerList[count].playHand) == PAIR)
				{
					playerList[count].handValue = Two_Pairs;
				}

			}

			if(highestMatch == THREE_OF_KIND)
			{
				playerList[count].handValue = Three_of_a_Kind;

				if(findPairs(playerList[count].playHand) == ONE_PAIR)
				{
					playerList[count].handValue = Full_House;
				}
			}

			if(highestMatch == FOUR_OF_KIND)
			{
				playerList[count].handValue = Four_of_a_Kind;
			}
		}

		else if (isStraight(playerList[count].playHand))
		{
			
			playerList[count].handValue = Straight;

			if (isFlush(playerList[count].playHand))
			{
				playerList[count].handValue = Straight_Flush;
			}
		}
		else if (isFlush(playerList[count].playHand))
		{
			playerList[count].handValue = Flush;

		}
		else
		{
			playerList[count].handValue = High_Card;
		}

	}

} // end function




/*----------------------------Find Pairs -----------------------
 *|  Function findPairs()
 *|
 *|  Purpose: To find how many pairs are in the set of cards
 *|
 *|  @param  hand - An array of cards limited to a length of 5 for the hand.
 *|
 *|  @return  pairs - Number of unique pairs found in the hand
 *------------------------------------------------------------------------*/
int findPairs(Card hand[])
{
	int count = 0;
	int matchCount = 1;
	int pairs = 0;
	for (count = 1;count < HAND_SIZE;count++)
	{	
		CardRank currentCardRank = hand[count].rankValue;
		CardRank previousCardRank = hand[count - 1].rankValue;
		if (currentCardRank == previousCardRank)
		{
			matchCount++;
			if (matchCount == PAIR)
			{
				pairs++;
			}
			if (matchCount == (PAIR + 1))
			{
				pairs--;
			}
		}
		else
		{
			matchCount = 1;
		}

	}
	return pairs;

}



/*----------------------------Find Highest Match -----------------------
 *|  Function findHighestMatch()
 *|
 *|  Purpose:  To find the how many card ranks are in the hand
 *|
 *|  @param  hand- An array of cards held by the player.
 *|
 *|  @return  highestMatch - Highest number of the same card in hand
 *------------------------------------------------------------------------*/
int findHighestMatch(Card hand[])
{
	int count = 0;
	int matchCount = 1;
	int highestMatch = 1;

	/* Starting at the 2nd Card and comparing with 1st */
	for (count = 1;count < HAND_SIZE;count++)
	{	
		CardRank currentCardRank = hand[count].rankValue;
		CardRank previousCardRank = hand[count - 1].rankValue;
		if (currentCardRank == previousCardRank)
		{
			matchCount++;
			if (highestMatch < matchCount)
			{
				highestMatch = matchCount;
			}
		}

		else 
		{
			matchCount = 1; // reset match streak to 1
		}

	}
	return highestMatch;
}



/*----------------------------Flush-----------------------
 *|  Function isFlush()
 *|
 *|  Purpose:  Check to see if the current hand is a Flush.
 *| 		
 *|
 *|  @param  hand - An array of cards from a player.
 *|
 *|  @return  TRUE or FALSE
 *------------------------------------------------------------------------*/
int isFlush(Card hand[])
{
	int count = 0;

	/* Starting at the 2nd Card and comparing with 1st */
	for (count = 1;count < HAND_SIZE;count++)
	{
		CardSuit currentCardSuit = hand[count].suitValue;
		CardSuit previousCardSuit = hand[count - 1].suitValue;
		
		if (currentCardSuit != previousCardSuit)
		{
			return FALSE;
		}
	}
	return TRUE;

}	// end function



/*----------------------------Straight -----------------------
 *|  Function isStraight()
 *|
 *|  Purpose:  Check to see if the current hand is a straight.
 *| 		
 *|
 *|  @param  hand - An array of cards from a player.
 *|
 *|  @return  TRUE or FALSE
 *------------------------------------------------------------------------*/
int isStraight(Card hand[])
{
	int count = 0;

	/* Starting at the 2nd Card and comparing with 1st */
	for (count = 1;count < HAND_SIZE;count++)
	{
		CardRank currentCardRank = hand[count].rankValue;
		CardRank previousCardRank = hand[count - 1].rankValue;
		CardRank initialCardRank = hand[INITIAL_CARD].rankValue;

		if (currentCardRank != Ace)
		{
			if ((currentCardRank - 1) != previousCardRank)
			{
				return FALSE;
			}
		}
		if (currentCardRank == Ace && previousCardRank != King)
		{
			return FALSE;
		}
		
		
	}
	return TRUE;
} // end function

