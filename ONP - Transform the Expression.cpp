/* SPOJ
Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). Operands: only letters: a,b,...,z. Assume that there is only one RPN form (no expressions like a*b*c).

Input
t [the number of expressions <= 100]
expression [length <= 400]
[other expressions]
Text grouped in [ ] does not appear in the input file.

Output
The expressions in RPN form, one per line.
Example
Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))

Output:
abc*+
ab+zx+*

*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

string to_ONP(string expresion);


int main()
{
    size_t t;
    cin >> t;
    
    string input;
    for (size_t i = 0; i < t; i++)
    {
        cin >> input;
        cout << to_ONP(input) << endl;
    }
    
}

string to_ONP(string expresion)
{
    string result{};
    stack <char> myStack;
    for (auto var : expresion)
    {
        if (var >= 'a' && var <= 'z') {
            result += var;
        }
        else if (var == '(') myStack.push(var);
        else if (var == ')') {
            
            if (myStack.empty()) return "Mismatched parenthesis";

            while (myStack.top()!='(')
            {
                result += myStack.top();
                myStack.pop();
                if (myStack.empty()) return "Mismatched parenthesis";
            }
            myStack.pop();
        }
        else if (var=='^') {

            while (!myStack.empty() && myStack.top() == '^')
            {
                result += myStack.top();
                myStack.pop();
            }
            myStack.push(var);

        }
        else if (var == '*' || var == '/') {
            while (!myStack.empty() && (myStack.top() == '^' || myStack.top() == '*' || myStack.top() == '/' ))
            {
                result += myStack.top();
                myStack.pop();
            }
            myStack.push(var);
        }

        else if (var == '+' || var == '-') {
            while (!myStack.empty() && (myStack.top() == '^' || myStack.top() == '*' || myStack.top() == '/'|| myStack.top() == '+' || myStack.top() == '-'))
            {
                result += myStack.top() ;
                myStack.pop();
            }
            myStack.push(var);
        }

    }

    while (!myStack.empty()) // adding the remaining symbols form stack to result
    {
        result += myStack.top();
        myStack.pop();
    }


    return result;
}