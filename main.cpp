#include "Game.h"
#include "Player.h"
#include "Deck.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main() {
    Game g1;
    g1.play();
    Game g2;
    g2.operator=(g1); //Operator= overloading for Game object.
    return 0;
}   //There is still a segmentation fault that I cannot figure out whenever the switch function is called.
