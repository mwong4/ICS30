#include <iostream>

using namespace std;

int main()
{
    int grouping = 4;
    int groupCounter = 0;
    int counter = 6;

    for(int i = 0; i < 5; i++)
    {
        while(groupCounter != grouping)
        {
            if((groupCounter) == grouping/2)
            {
                counter += 3;
            }
            else if(groupCounter % 2 == 0 && groupCounter != 0)
            {
                counter += 2;
            }
            else
            {
                counter ++;
            }
            groupCounter ++;
            cout << counter << endl;
        }
        grouping += 4;
        groupCounter = 0;
        counter += 3;
    }

    return 0;
}
