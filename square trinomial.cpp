#include <cmath>

using namespace std;
int main()
{
    float x1, x2, a, b, c, D;
    std::cout << "enter a";

    std::cout << "enter b" << ;
    std::cout << "enter c" << ;
    D = b * b - 4 * a * c;
    if (D > 0)
    {
        x1 = ((-b) + sqrt(D)) / (2 * a);
        x2 = ((-b) - sqrt(D)) / (2 * a);
        cout << "x1 = " << x1;
        cout << "x2 = " << x2;
    }
    if (D == 0)
    {
        x1 = x2 = (-(b)) / (2 * a);
        cout << "x1 = x2 = " << x1;
    }
    if (D < 0)
    {
        cout "D < 0, no roots";
    }
    return (0);
}