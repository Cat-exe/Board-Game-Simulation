#include "Game.h"
#include "Player.h"
#include "Deck.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

//This function displays the rules, board, and instantiates a deck of cards.
Game::Game()
{
    cout << "Rules:\n 1. Land on a 0, you are safe.\n 2. Land on a number greater than 0, and you move back that many spaces.\n 3. Land on the -1 and you win the game!\n _________________" << endl;
    const int board[spaces] = {0, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0, 2, 0, 0, 3, 0, 0, 5, -1};
    cout << "This is the game board: " << endl;
    for (int i=0; i<spaces; i++)
        cout << board[i] << " ";
    cout << endl;
    cout << "This is the deck: " << endl;
    cards = new Deck[decksize];
    for (int i=0; i<decksize; i++){
        (cards+i)->setCardNum(i);
        cout << (cards+i)->getCardNum() << " ";
    }
    cout << endl;
}
//Copy constructor for game class.
Game::Game(const Game &obj)
{
    cards = new Deck[decksize];
    for (int i=0; i<decksize; i++)
        cards[i] = obj.cards[i];
    player = new Player[numplayers];
    for (int i=0; i<numplayers;i++)
        player[i] = obj.player[i];
}
//Overloading = operator
void Game::operator=(const Game &right)
{

}
//This function shuffles the deck of cards.
void Game::shuffleDeck(bool&shuffled)
{
   srand(time(NULL));
   for (int i=0; i<decksize; i++) {
        int index = rand() % decksize;
        int temp = (cards+i)->getCardNum();
        (cards+i)->setCardNum((cards+index)->getCardNum());
        (cards+index)->setCardNum(temp);
   }
   shuffled = true;
   cout << "Deck has been shuffled. " << endl;
   //Displays the deck for code checking purposes.
    cout << "Deck is now: " << endl;
    for (int i=0; i<decksize; i++)
        cout << (cards+i)->getCardNum() << " ";
    cout << endl;
}
//This function asks the user how many players there will be.
void Game::determineNumPlayers()
{
     cout << "How many players will be playing? Only 2-6 people may play. ";
     cin >> numplayers;
     if (numplayers < 2 || numplayers > 6) {
         cout << "Invalid amount." << endl;
         exit(0);
     }
}
//This function will dynamically allocate a player array for the new game.
void Game::newPlayersArray()
{
    player = new Player[numplayers];
    cout << "Player array successfully dynamically allocated." << endl;
}
//This function determines who goes first based on name length. **FIXED**
void Game::playerSort()
{
   string temp;
   int pass=0;
   bool swapped;
   do {
    pass++;
    swapped = false;
    for (int i=0; i<numplayers-pass;i++) {
        if ((player+i)->getName().length() > (player+i+1)->getName().length()) {
            temp = (player+i)->getName();
            (player+i)->setName((player+i+1)->getName());
            (player+i+1)->setName(temp);
            swapped = true;
        }
    }
   } while (swapped);
   cout << player->getName() << " will go first." << endl;
}
//This function plays the game.
void Game::play()
{
    determineNumPlayers();
    newPlayersArray();
    playerSort();
    bool gameOver = false;
    while (gameOver == false) {
        int deckIndexCt = 10; //How many cards left before shuffling.
        bool shuffled, gameOver=false;
        shuffleDeck(shuffled); //First shuffle of the game.
        do{
            for (int i=0; i<numplayers;i++) {
                cout << (player+i)->getName() << ", make your move." << endl;
                takeTurn(deckIndexCt, i);
                deckIndexCt--;
                boardMoves(i);
                showState(i);
                if ((player+i)->getLocation() >= 20) {
                    cout << (player+i)->getName() << " has won the game!" << endl;
                    gameOver = true;
                    if (gameOver)
                        exit(0);
                }
            }
        } while (shuffled);
        if (deckIndexCt <=0) {
            shuffled = false;
            shuffleDeck(shuffled);
        }
    }
}
//This function does a single turn for a player.
void Game::takeTurn(int&deckIndexCt, int i)
{
    int selectedCard;
    selectedCard = (cards+(deckIndexCt-1))->getCardNum();
    cout << (player+i)->getName() << " has drawn a " << selectedCard << " card." << endl;
    if (selectedCard < 9 && selectedCard > 0 )
            (player+i)->moveLocation(selectedCard);
    else if (selectedCard == 9)
            switchPlaces(i);
    else if (selectedCard == 0) {
            cout << (player+i)->getName() << " has lost a turn." << endl;
            return;
    }
}
//Swaps the locations of the current player with the player who is closest to Home.
void Game::switchPlaces(int i)
{
    int temp=0;
    int j = 0;
    j = findMax(i);
    temp = (player+j)->getLocation();
    (player+j)->setLocation((player+i)->getLocation());
    (player+i)->setLocation(temp);
}
//This function finds the location of the player that is closest to winning.
int Game::findMax(int i)
{
    int j, highest = player->getLocation();
    for (int i=1; i<numplayers;i++)
        if ((player+i)->getLocation() > highest) {
            highest = (player+i)->getLocation();
            j = i;
        }
    return j;
}
//:If the player whose turn it is lands on these spots on the board, they move back x spaces.
void Game::boardMoves(int i) //Applies literals, which represent places on the board.
{
    boardConditions(4, 1, i);
    boardConditions(6,1,i);
    boardConditions(10,2,i);
    boardConditions(13,2,i);
    boardConditions(16,4,i);
    boardConditions(19,5,i);
}
//Function that boardMoves uses to shorten code.
void Game::boardConditions(int a, int b, int i)
{
    if ((player+i)->getLocation() == a) {
        (player+i)->moveLocation(-b);
        cout << (player+i)->getName() << " has landed on location " << a << ", an obstacle, and must move back " << b << " spaces.\n";
    }
}
//Function that prints to the screen the locations of all players.
void Game::showState(int i)
{
    cout << (player+i)->getName() << " is now in location " << (player+i)->getLocation() << endl;
}
//Destructor
Game::~Game()
{
    delete [] player;
    delete [] cards;
}
