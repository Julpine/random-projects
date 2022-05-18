/*=============================================================================  
|   Header File:  StudPokerHeader.h
|        Author:  Julian Pineiro
=============================================================================*/

#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>		// Needed for Input and Output
#include <stdlib.h>		// required for rand()
#include <time.h>		// Required for rand()
#include <inttypes.h>		// Needed to check other types of ints
#define NO_ERROR 0		// No error in the program
#define FALSE 0			// The value is false
#define TRUE 1			// The Value is true
#define STRING_END '\0'		// Value of a string End char
#define CARD_INPUT 1		// Inupt value of card
#define PLAYER_INPUT 2		// Inupt value of player
#define REQUIRED_ELEMENTS 2	// Number of elements needed in input
#define DECK_SIZE 52		// Size of the deck
#define HAND_SIZE 5		// Size of a Hand
#define MAX_PLAYERS 10		// Max players allowed to play
#define MIN_PLAYERS 1		// Minimum players allowed to play
#define RANKS 13		// Number of Ranks
#define SUITS 4			// Number of suits
#define DECK_FORMAT 13		// Number of items per line
#define INITIAL_CARD 0		// Index value of the initial card
#define PAIR 2			// Number of cards in a pair of cards
#define NO_MATCH 1		// When the card has no matching
#define HAND_TYPES 9		// The amount of hand types that a player can have
#define GAME_OUTCOME 3		// The amount of different game Outcomes
#define ONE_PAIR 1		// When only 1 pair is present
#define THREE_OF_KIND 3		// Three cards of the same
#define FOUR_OF_KIND 4		// Four cards of the same


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



