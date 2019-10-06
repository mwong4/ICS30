//Declaring all used libraries
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>   // WinApi header
#include <sstream>
#include <iomanip>
#include <math.h>
#include <conio.h>


using namespace std;

int main()
{
    float currentRotation = 0;
    int faceTowards = 1;

    while(true)
    {
        if((GetKeyState('W') & 0x8000))
        {
            faceTowards = 1;
        }
        else if((GetKeyState('A') & 0x8000))
        {
            faceTowards = 2;
        }
        else if((GetKeyState('S') & 0x8000))
        {
            faceTowards = 3;
        }
        else if((GetKeyState('D') & 0x8000))
        {
            faceTowards = 4;
        }

        if(faceTowards == 1)
        {
            if(currentRotation <= 180)
            {
                if((currentRotation > 0)) currentRotation -= 30;
                else if((currentRotation < 0)) currentRotation += 30;
            }
            if(currentRotation > 180)
            {
                if((currentRotation > 360)) currentRotation -= 30;
                else if((currentRotation < 360)) currentRotation += 30;
                else if(currentRotation == 360) currentRotation = 0;
            }

        }
        else if(faceTowards == 2)
        {
            if((currentRotation > 90)) currentRotation -= 30;
            else if((currentRotation < 90)) currentRotation += 30;
        }
        else if(faceTowards == 3)
        {
            if((currentRotation > 180)) currentRotation -= 30;
            else if((currentRotation < 180)) currentRotation += 30;
        }
        else if(faceTowards == 4)
        {
            if((currentRotation > 270)) currentRotation -= 30;
            else if((currentRotation < 270)) currentRotation += 30;
        }

        cout << "current rotation: " << currentRotation;
        system("CLS");
    }

    return 0;
}
