// color your text in Windows console mode
// colors are 0=black 1=blue 2=green and so on to 15=white
// colorattribute = foreground + background * 16
// to get red text on yellow use 4 + 14*16 = 228
// light red on yellow would be 12 + 14*16 = 236
// a Dev-C++ tested console application by  vegaseat  07nov2004
#include <iostream>
#include <windows.h>   // WinApi header

using namespace std;    // std::cout, std::cin
int main()
{


int d = 1;
float result = 0;

result = (d * 100)/300;

cout << result << endl;

cout << 1/3 << endl;



  return 0;
}
