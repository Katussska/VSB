#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isPalindrome(string s)
{
    stack<char> zasobnik;
    int i = 0;
    for (; i < s.size() / 2; i++)
        zasobnik.push(s[i]);
    if (s.size() % 2 == 1)
        i++;
    while (!zasobnik.empty())
        if (s[i++] == zasobnik.top())
        {
            zasobnik.pop();
        }
        else
            return false;
    return true;
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        bool pal = isPalindrome(argv[i]);
        cout << argv[i] << (pal ? " je" : " neni") << " palindrom\n";
    }
}