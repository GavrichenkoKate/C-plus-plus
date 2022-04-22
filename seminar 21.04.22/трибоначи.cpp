#include <iostream> 
using namespace std;
 
int T(int n) 
{
    if ( n == 0 ) return (0); 
    if ( n == 1 ) return (1); 
    if ( n == 2 ) return (1); 
    return T(n-1) + T(n-2) + T(n-3);
}
 
int main()
{
    int n;    
    cout << "n="; cin >> n;       
    cout <<T(n)<<" ";    
    cout <<endl;
system("pause");
return 0;
}
