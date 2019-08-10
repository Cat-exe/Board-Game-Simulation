#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;
class Player
{
    private:
        string name;
        int location;
    public:
        Player();
        string getName() {return name;}
        int getLocation() {return location;}
        void setName(string);
        void setLocation(int);
        void moveLocation(int);
        ~Player(); //destructor

};
#endif // PLAYER_H
