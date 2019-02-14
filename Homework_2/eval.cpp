//
//  eval.cpp
//  Homework_2
//
//  Created by Yunus Chang on 1/31/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "Set.h"
#include <stdio.h>
#include <string>
#include <cassert>
#include <cctype>
#include <stack>
#include <iostream>

using namespace std;
bool infixToPostfix(string infix, string &postfix);
char evalOperands(char operand1, char operand2, char operate);
int evalPostFix(string postfix, const Set& trueValues, const Set& falseValues);


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    if(!infixToPostfix(infix, postfix))
    {
        return 1;
    }
    int evalPostFixResult = evalPostFix(postfix, trueValues, falseValues);
    switch(evalPostFixResult)
    {
        case -2:
            return 1;
        case -1:
            result = false;
            return 0;
        case 0:
            result = true;
            return 0;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            return -1;
    }
}

int main()
{
    string x = "ucla";
    string y = "nsxf";
    Set t;
    Set f;
    for(int i = 0;i < x.size();i++)
    {
        t.insert(x[i]);
        f.insert(y[i]);
    }
    string z;
    bool result;
    assert(evaluate("u", t,f,z,result) == 0 && result == true);
    assert(evaluate("u&c&l&a & !(u&s&c)", t,f,z,result) == 0 && result == true);
    assert(evaluate("(n)", t,f,z,result) == 0 && result == false);
    assert(evaluate("a&(s)", t,f,z,result) == 0 && result == false);
    assert(evaluate("a & !s", t,f,z,result) == 0 && result == true);
    assert(evaluate("!(n|u)", t,f,z,result) == 0 && result == false);
    assert(evaluate("!n|u", t,f,z,result) == 0 && result == true);
    assert(evaluate("a|n&n", t,f,z,result) == 0 && result == true);
    assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", t,f,z,result) == 0 && result == true);

    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("(n)(t)", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0 &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cout << "Passed all tests" << endl;
}

bool infixToPostfix(string infix, string &postfix)
{
    postfix = "";
    stack<char> stack;
    int paraCount = 0;
    for(int i = 0;i < infix.size();i++)
    {
        switch(infix[i])
        {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                if(i != 0)
                {
                    if(isalpha(infix[i-1]))
                        return false;
                }
                postfix += infix[i];
                break;
            case '(':
                if(i != 0)
                {
                    if(isalpha(infix[i-1]) || infix[i-1] == ')')
                        return false;
                }
                paraCount++;
                stack.push(infix[i]);
                break;
            case ')':
                if(i != infix.size()-1)
                {
                    if(isalpha(infix[i+1]))
                        return false;
                }
                while(!stack.empty() && stack.top() != '(')
                {
                    postfix += stack.top();
                    stack.pop();
                }
                paraCount--;
                if(!stack.empty())
                    stack.pop();
                break;
            case '!':
                if(i != infix.size()-1)
                {
                    if(infix[i+1] == '&' || infix[i+1] == '|')
                        return false;
                }
                while(!stack.empty() && stack.top() != '(' && stack.top() != '|' && stack.top() != '&' && stack.top() != '!')
                {
                    postfix += stack.top();
                    stack.pop();
                }
                stack.push(infix[i]);
                break;
            case '&':
                while(!stack.empty() && stack.top() != '(' && stack.top() != '|')
                {
                    postfix += stack.top();
                    stack.pop();
                }
                stack.push(infix[i]);
                break;
            case '|':
                while(!stack.empty() && stack.top() != '(')
                {
                    postfix += stack.top();
                    stack.pop();
                }
                stack.push(infix[i]);
                break;
            case ' ':
                for(int j = i;j < infix.size();j++)
                    infix[j] = infix[j+1];
                infix = infix.substr(0,infix.size()-1);
                i--;
                break;
            default:
                return false;
        }
    }
    while(!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
    }
    if(paraCount != 0)
        return false;
    if(postfix.size() == 0)
        return false;
    return true;
}

char evalOperands(char operand1, char operand2, char operate)
{
    int chooser;
    if(operand2 == 't')
    {
        chooser = 0;
        if(operand1 == 'f')
            chooser = 1;
    }
    if(operand2 == 'f')
    {
        chooser = 2;
        if(operand1 == 't')
            chooser = 1;
    }
    if(operate == '|')
    {
        switch(chooser)
        {
            case 0:
                return 't';
            case 1:
                return 't';
            case 2:
                return 'f';
                
        }
    }
    if(operate == '&')
    {
        switch(chooser)
        {
            case 0:
                return 't';
            case 1:
                return 'f';
            case 2:
                return 'f';
        }
    }
    return '0';
}

int evalPostFix(string postfix, const Set& trueValues, const Set& falseValues)
{
    stack<char> stack;
    for(int i = 0;i < postfix.size();i++)
    {
        if(postfix[i] != '!' && postfix[i] != '&' && postfix[i] != '|')
        {
            if(!trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
            {
                return 2;
            }
            if(trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]))
            {
                return 3;
            }
            if(trueValues.contains(postfix[i]))
                stack.push('t');
            if(falseValues.contains(postfix[i]))
                stack.push('f');
        }
      if(postfix[i] == '!')
        {
            if(stack.top() == 't')
            {
                stack.pop();
                stack.push('f');
            }
            else
            {
                if(stack.top() == 'f')
                {
                    stack.pop();
                    stack.push('t');
                }
            }
        }
        if(postfix[i] == '|' || postfix[i] == '&')
        {
        
            char operand2 = ' ';
            char operand1 = ' ';
            if(stack.empty())
                return -2;
            operand2 = stack.top();
            stack.pop();
            if(stack.empty())
                return -2;
            operand1 = stack.top();
            stack.pop();
            stack.push(evalOperands(operand1, operand2, postfix[i]));
        }
    }
    int x = -2;
    if(stack.top() == 't')
        x = 0;
    if(stack.top() == 'f')
        x = -1;
    stack.pop();
    return x;
}
