#include <iostream>

using namespace std;

int main()
{
   int numBase=0;
   int newBase=0;
   int num=1;
   int num1=0;
   int remainder, i=1;
   int rem=1; //
   int dec=0; //
   long bin=0;
   int base=1; //


   cout << "Enter the base you're starting number is in" << endl;
   cin >> numBase;
   cout << "Enter the number you want to convert" << endl;
   cin >> num1;
   cout << "Enter the new base" << endl;
   cin >> newBase;

   while (num1 > 0)
    {
        rem = num1 % 10;
        dec = dec + rem * base;
        base = base * numBase;
        num1 = num1 / 10;
    }


   int n = dec;
   int m=0;


   while (n!=0)
           {
               remainder = n%newBase;
               n /= newBase;
               m += remainder*i;
               i *= 10;
           }

   cout << "You're number is " << m << endl;

   }
