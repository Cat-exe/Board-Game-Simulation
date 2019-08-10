#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

//This function accepts players' names and locations of the board are set to 0.
Player::Player()
{
    cout << "Enter name: ";
    cin >> name;
    location = 0;
}
//This function sets the name of the player.
void Player::setName(string n)
{
    name = n;
}
//This function moves the location of the player on the board.
void Player::moveLocation(int n)
{
    int iniposition = location;
    location+= n;
    if (location > iniposition)
        cout << name << " moved " << n << " spaces." << endl;
}
//This function is used by the Game::switchPlaces() function.
void Player::setLocation(int i)
{
    location = i;
}
Player::~Player()
{
    delete [] this;
}
