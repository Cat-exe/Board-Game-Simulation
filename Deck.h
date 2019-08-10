#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
class Deck
{
    private:
        int cardnum;
    public:
        int getCardNum() {return cardnum;}
        template <class T> //Uses a template function enabling use of ints, doubles, longs, floats, etc.
        void setCardNum(T variable) {cardnum = variable;} //However, in this case it should only be used with ints.

};
#endif // DECK_H
