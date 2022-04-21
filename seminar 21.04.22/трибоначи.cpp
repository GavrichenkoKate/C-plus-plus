#include <iostream> 
using namespace std;
 
int f(int n) 
{
    if ( n == 0 ) return (0); 
    if ( n == 1 ) return (1); 
    if ( n == 2 ) return (1); 
    return f(n-1) + f(n-2) + f(n-3);
}
 
int main()
{
    int n;    
    cout << "n="; cin >> n;       
    cout <<f(n)<<" ";    
    cout <<endl;
system("pause");
return 0;
}
