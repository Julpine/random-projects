/*=============================================================================  
|   Header File:  StudPokerHeader.h
|        Author:  Julian Pineiro  
=============================================================================*/

#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#define NO_ERROR 0
#define FALSE 0
#define TRUE 1
#define STRING_END '\0'
#define CARD_INPUT 1		// Inupt value of card
#define PLAYER_INPUT 2		// Inupt value of player
#define REQUIRED_ELEMENTS 2
#define DECK_SIZE 52		// Size of the deck
#define MAX_VAR 13			// Maximum players or cards
#define MIN_VAR 1			// Minimum players or cards
#define HAND_SIZE 5
#define MAX_PLAYERS 10
#define MIN_PLAYERS 1
#define RANKS 13			// Number of Ranks
#define SUITS 4				// Number of suits
#define DECK_FORMAT 13		// Number of items per line
#define INITIAL_CARD 0
#define PAIR 2
#define NO_MATCH 1
#define HAND_TYPES 9
#define GAME_OUTCOME 3


/* *Defining the card values */
enum CardRank{Ace,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King};
enum CardSuit{Spades,Hearts,Diamonds,Clubs};


/* *Defining Display, Outcomes, and Hand Types */
enum Style{Normal,Sorted,Ranked,Winner,Test};
enum GameStatus{Unknown,Lost,Won};
enum HandType{High_Card,Pair,Two_Pairs,Three_of_a_Kind,Straight,Flush,Full_House,
		Four_of_a_Kind,Straight_Flush};


/* *Type defining enums */
typedef enum GameStatus GameStatus;
typedef enum CardRank CardRank;
typedef enum CardSuit CardSuit;
typedef enum Style Style;
typedef enum HandType HandType;


/* *Card Structure */
struct Card {

	char *rank;
	char *suit;
	CardRank rankValue;
	CardSuit suitValue;
	int cardValue;

};
typedef struct Card Card;


/* *Player Structure */
struct Player {

	int playerID;
	Card playHand[HAND_SIZE]; 
	HandType handValue;
	GameStatus status;

};
typedef struct Player Player;


/* *Defining External Strings */
extern char *ranks[RANKS];
extern char *suits[SUITS];
extern char *gameOutcome[GAME_OUTCOME];
extern char *handTypes[HAND_TYPES];


/* Function prototypes MainCardHandler.c */
int isNumber();
int verify();
int checkConstrains();
void displayHands();
void displayHandLogic();
void dealCards();
void displayStyleTitle();
void playGame();


/* Function prototypes CardDeck.c */
void cardDeck();
void displayDeck();
void orderCards();
void shuffle();


/* *Function prototypes GameLogic.c */
void displayWinner();
void displayHandValue();
void calcWinner();
void calcPlayerHands();
int findHighestMatch();
int isFlush();
int isStraight();


/* *Function prototypes TestCase.c */
void testerCase();




#endif



