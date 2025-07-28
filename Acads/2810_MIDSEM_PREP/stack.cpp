#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int precedence(char c)
    {
        if (c == '^')
        {
            return 3;
        }
        else if (c == '*' || c == '/')
        {
            return 2;
        }
        else if (c == '+' || c == '-')
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    // Function to convert an infix expression to a postfix expression.
    string infixToPostfix(string &s)
    {
        stack<char> st1;
        string res = "";
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                st1.push(s[i]);
            }
            else if (s[i] == ')')
            {
                while (!st1.empty() && st1.top() != '(')
                {
                    res += st1.top();
                    st1.pop();
                }
                st1.pop();
            }
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
            {
                while (!st1.empty() && precedence(st1.top()) >= precedence(s[i]))
                {
                    res += st1.top();
                    st1.pop();
                }
                st1.push(s[i]);
            }
            else
            {
                res += s[i];
            }
        }
        while (!st1.empty())
        {
            res += st1.top();
            st1.pop();
        }
        return res;


        // Your code here
    }

    
};