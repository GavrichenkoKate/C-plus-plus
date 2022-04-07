#include <iostream>
#include <string>
#include <map>
#include <stack>
 
std::map<char, char> OpenBracketPair = {
    {')', '('},
    {'}', '{'},
    {']', '['}
};
 
inline bool isOpenBracket(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}
 
inline bool isClosingBracket(char ch) {
    return ch == ')' || ch == '}' || ch == ']';
}
 
bool areParenthesesGood(std::string& str)
{
    std::stack<char> st;
    for (auto ch : str) {
        if (isOpenBracket(ch)) st.push(ch);
        else if (isClosingBracket(ch)) {
            if (!st.empty() && st.top() == OpenBracketPair[ch])
                st.pop();
            else 
                return false;
        }
    }
    return st.empty();
}
 
int main()
{
    std::string s = "{{}}(";
    (areParenthesesGood(s)) ? std::cout << "1" : std::cout << "0";
    system("pause");
    return 0;
}
