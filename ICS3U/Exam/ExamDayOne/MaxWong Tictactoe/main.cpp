#include <cstdlib>
#include <iostream>

using namespace std;

// ===================   Structures   ==================

struct Player
{      string name;
       int score;
       char symbol;
}; //Forgot ; here, syntax
// ================== Prototypes =================

void intro();
void displayBoard();
void checkForWinner(Player);
Player makeMove(Player);


// ================== Global Variables =================
Player player1, player2;
bool gameOn = true;
char board[3][3] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
int scores[3][3] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
// These values are all primes. The products (multiplication) of any of these
// values will produce a unique score for every configuration of the board.
//
// There are only a 8 possible products that represent a winning combination
// Ex:  2 X 3 X 5 = 30 represents a win along the top row. So any score that is
//      divisible by 30 represents a board where the player has won along the top row
// The 8 possible winning values are
//       top row:       2 X 3 X 5 = 30       left column:    2 X 7 X 17 = 238
//       middle row:  7 X 11 X 13 = 1001     middle column: 3 X 11 X 19 = 627
//       bottom row: 17 X 19 X 23 = 7429    right column:   5 X 13 X 23 = 1495
//       diagonal from top left:    2 X 11 X 23 = 506
//       diagonal from top right:   5 X 11 X 17 = 935



// ===================   Definitions   ==================

void checkForWinner(Player _player) // THERE ARE NO ERRORS IN THIS FUNCTION
{    if ((_player.score % 30 == 0) or (_player.score % 1001 ==0)or (_player.score %7429 ==0)or (_player.score %238 ==0)or (_player.score % 627 ==0)or (_player.score % 1495==0)or (_player.score % 506 ==0)or (_player.score %935 ==0))
     {  cout << _player.name << "   WINS!!!!!" << endl;
        gameOn = false;
     }
}

Player makeMove(Player _player)
{    int xcoordinate = 0;
     int ycoordinate = 0;

     //display whose turn it is
     cout <<  "It is " << _player.name << "'s turn (" << _player.symbol<< ")" << endl; // Missing << signs, syntax

     do
     {	cout << "Enter the column in which you want to play " << endl;
       	cout << "(left side = 1,  middle = 2, right side = 3)" ;
       	cin >> ycoordinate; //Missing ; sign, syntax
       	cout << "Enter the row in which you want to play " << endl;
       	cout <<  "(top = 1,  middle = 2, bottom = 3)" ; //Missing << signs, syntax
       	cin >> xcoordinate; //>> signs are in wrong direction, syntax
     }while (board[xcoordinate-1][ycoordinate-1]!=' ');

     board[xcoordinate - 1][ycoordinate - 1] = _player.symbol; //adds the symbol to the board //Used compare (==) instead of assign (=), logic
     _player.score *= scores[xcoordinate - 1][ycoordinate - 1]; //updates the new score
     system("CLS");
     return _player;
}




void displayBoard() // displays the board. Check the functional exe file to see what it should look like
{    for (int i = 0; i < 3; i++) //Should be 3 instead of 2 to get the loop to run 3 times (since it stops once it reaches 2), logic
     {    cout << "-------------" << endl;
          for (int j = 0; j < 3; j++) //Should be 3 instead of 2 to get the loop to run 3 times (since it stops once it reaches 2), logic
          {   cout << "| " << board[i][j] << " ";
          }
          cout << "|" << endl;
     }
     cout << "-------------"<< endl;
}

void intro()
{    cout << "Player 1, what is your name ";
     cin >> player1.name;
     cout << "Player 2, what is your name ";
     cin >> player2.name;

     player1.score = 1;
     player2.score = 1;
     player1.symbol = 'O'; //1 equal sign, not 2 (assign, not compare), logic
     player2.symbol =  'X';
}

int main(int argc, char *argv[])
{   intro(); //Missing () braces, syntax
    displayBoard();

    while (gameOn)
    {     player1 = makeMove(player1);
          displayBoard();
          checkForWinner(player1);
          if (gameOn)
          {  player2 = makeMove(player2);
             displayBoard();
             checkForWinner(player2);
          }
    }

    system("PAUSE");
    return EXIT_SUCCESS;
}
