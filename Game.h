#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Deck.h"
#include <iostream>
#include <string>
using namespace std;
const int decksize = 10, spaces = 20;
class Game
{
    private:
        Deck *cards;
        Player *player;
        int numplayers;
    public:
        Game();//constructor
        Game(const Game&); //COPY CONSTRUCTOR
        void operator=(const Game&);
        void shuffleDeck(bool&);
        void determineNumPlayers();
        void newPlayersArray();//dynamically allocates player array on heap
        void playerSort();
        void play();
        void takeTurn(int&, int);
        void switchPlaces(int);
        int findMax(int);
        void boardMoves(int);
        void boardConditions(int, int, int);
        void showState(int);
        ~Game();//DESTRUCTOR
};
#endif // GAME_H
