#include <iostream>

using namespace std;

int main()
{
    //Initial Seed
    srand(327);

    //Define variables
    int randomValue; //This variable is flexible and is used to get a random value when necesary
    int playerPick; //This variable holds the players random choice
    int disabledDoor; //This variable is the# of the disabled door

    bool threeDoors[3]; //This boolean array holds the states of the three doors
    float statistics[4]; //This array holds the 4 statistics being recorded. 0- win, stay  1- lose, stay  2- change, win  3- change, lose

    //reset stats
    for(int i = 0; i < 4; i ++)
    {
        statistics[i] = 0;
    }


    for(int i = 0; i < 10000; i++)
    {
        srand(rand());

        //Set one random door to have the prize
        randomValue = rand() % 3;
        for(int i = 0; i < 3; i++)
        {
            if(i == randomValue)
            {
                threeDoors[i] = true;
            }
            else
            {
                threeDoors[i] = false;
            }
            //cout << "door: " << threeDoors[i] << endl;
        }

        //Get the player to pick a random door
        playerPick = rand() % 3;

        //Dissable one of the doors
        do
        {
            disabledDoor = rand() % 3;
        }while(disabledDoor == playerPick || threeDoors[disabledDoor] == true);

        //cout << "player pick: " << playerPick << endl;
        //cout << "disabledDoor: " << disabledDoor << endl;

        //See if player wants to change
        randomValue = rand() % 2;
        //If randomValue is 0, change input
        if(randomValue == 0)
        {
            do
            {
                randomValue = rand() % 3;
            }while(randomValue == playerPick ||randomValue == disabledDoor );
            playerPick = randomValue;
            randomValue = 4;
        }
        else
        {
            randomValue = 5;
        }

        //cout << "new Player Pick: " << randomValue << endl;

        //If player stays and wins
        if(randomValue == 5 && threeDoors[playerPick] == true)
        {
            statistics[0] += 1;
        }
        //If player stays and loses
        if(randomValue ==5 && threeDoors[playerPick] == false)
        {
            statistics[1] += 1;
        }
        //If player changes and wins
        if(randomValue == 4 && threeDoors[playerPick] == true)
        {
            statistics[2] += 1;
        }
        //If player changes and wins
        if(randomValue == 4 && threeDoors[playerPick] == false)
        {
            statistics[3] += 1;
        }
    }

    cout << "        win   lose " << endl;
    cout << "  stay |" << statistics[0] << " |" << statistics[1] << endl;
    cout << "change |" << statistics[2] << " |" << statistics[3] << endl;

    cout << endl << "The change of winning and staying is : " << statistics[0] / (statistics[0] + statistics[2]) << endl;
    cout << endl << "The change of winning and changing is : " << statistics[2] / (statistics[0] + statistics[2]) << endl;






}
