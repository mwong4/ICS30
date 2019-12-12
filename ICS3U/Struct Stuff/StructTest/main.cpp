#include <iostream>
#include <tgmath.h> //For floor function

using namespace std;

struct Card{
    char cardSuit; //Card suit saved as char
    string cardRank; //Card rank saved as string
    int cardValue; //Card value saved as integer
    int identity; //Card indetity saved as integer
} myCards[52]; //Have an array of structures/cards

int main()
{
    int cool[4] = {1,2,3,4};

    cout << floor(15/13) << endl;
    int num = floor(15/13);

    cout << cool[num] << endl;
    return 0;
}
