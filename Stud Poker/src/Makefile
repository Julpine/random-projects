output: MainCardHandler.o CardDeck.o GameLogic.o TestCase.o

	gcc MainCardHandler.o CardDeck.o GameLogic.o TestCase.o -o output



MainCardHandler.o: MainCardHandler.c StudPokerHeader.h

	gcc -c MainCardHandler.c



CardDeck.o: CardDeck.c StudPokerHeader.h

	gcc -c CardDeck.c



GameLogic.o: GameLogic.c StudPokerHeader.h

	gcc -c GameLogic.c



TestCase.o: TestCase.c StudPokerHeader.h

	gcc -c TestCase.c 

clean:

	rn*.o output