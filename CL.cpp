#include <iostream>
#include <stdlib.h>
using namespace std;
double k(int i){	return 54.6 *i;}int main()
{
    for(int i=0;i<100;i++)
           cout<<k(i)<<endl;
    system("pause");
    return 0;
}