/*=============================================================================  
|   Source code:  TestCase.c
|        Author:  Julian Pineiro
|=============================================================================*/


#include "StudPokerHeader.h"

void testerCase()
{

	Card testDeck[DECK_SIZE] = {0};
	cardDeck(testDeck);
	Player testList[HAND_TYPES] = {0};
	int count = 0;
	int adder = 0;
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = (7 * count);
		testList[0].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = 6 + count;
		if (count > 1)
		{
			adder = 30 + (5 * count);
		}
		testList[1].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = 10 + count;
		if (count > 3)
		{
			adder = 20 + (5 * count);
		}
		testList[2].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = 36 + count;
		if (count > 2)
		{
			adder = 3 + (5 * count);
		}
		testList[3].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = 12 + (4 * count);
		if (count > 2)
		{
			adder = 13 + (4 * count);
		}
		testList[4].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = 3 + (8 * count);
		testList[5].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = 30 + count;
		testList[6].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = 40 + count;
		testList[7].playHand[count]= testDeck[adder];
	}
	for(count = 0;count < HAND_SIZE;count++)
	{
		adder = (4 * count);
		testList[8].playHand[count]= testDeck[adder];
	}

	displayHands(HAND_SIZE,HAND_TYPES,testList,Test);
}