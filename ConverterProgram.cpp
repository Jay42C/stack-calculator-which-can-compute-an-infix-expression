//Jesse Chairez
//Assignment 7 Calculator
//Converts the inflix expression to postfix and will still compute the result. 

#include <iostream>
#include <string>
using namespace std;


class charStack
{
private:
    char *stack;
    int top;
    int max;

public:
    charStack(int size)
    {
        stack = new char[size];
        top = -1;
        max = size;
    }

    void push(char itemType) 
    {
        if (isFull()) 
        {
            cout << "Sorry but the stack is full." << endl; 
            return;
        }
        stack[++top] = itemType; 
    }

    char pop() 
    {
        if (isEmpty()) 
        {
            cout << "The stack is currently empty." << endl; 
            return '\0'; 
        }
        return stack[top--];
    }

    char peek() 
    {
        if (isEmpty()) 
        {
            cout << "The stack is currently empty." << endl; 
            return '\0'; 
        }
        return stack[top]; 
    }

    bool isEmpty() 
    {
        return top == -1;
    }

    bool isFull() 
    {
        return top == max - 1;
    }

    ~charStack()
    {
        delete[] stack;
    }
};

int getOrder(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}


string infixToPostfix(const string &infix)
{
    string postFix = "";
    charStack stack(infix.length()); 

    for (char ch : infix) 
    {
        if (isalnum(ch)) 
        {
            postFix += ch; 
        }
        else if (ch == '(') 
        {
            stack.push(ch);
        }
        else if (ch == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postFix += stack.pop();
            }
            stack.pop();
        }
        else
        {
            while (!stack.isEmpty() && getOrder(ch) <= getOrder(stack.peek()))
            {
                postFix += stack.pop(); 
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty())
    {
        if (stack.peek() == '(')
        {
            cout << "Sorry, please review as we have unbalanced parentheses." << endl;
            return "";
        }
        postFix += stack.pop();
    }

    return postFix;
}

int reviewPostfix(const string &postFix)
{
    charStack stack(postFix.length()); 

    for (char ch : postFix) 
    {
        if (isalnum(ch)) 
        {
            stack.push(ch - '0');
        }
        else 
        {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            switch (ch) 
            {
                case '+':
                    stack.push(operand1 + operand2); 
                    break;
                case '-':
                    stack.push(operand1 - operand2);
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    stack.push(operand1 / operand2);
                    break;
            }
        }
    }

    return stack.pop();
}

int main()
{
    string infixOperation; 
    cout << "Please enter an infix operation and I will try my best to convert to PostFix operation (Please make sure there are no spaces, single digits, balanced parentheses):\n ";
    cin >> infixOperation; 

    string postfixExpression = infixToPostfix(infixOperation);
    if (!postfixExpression.empty())
    {
        cout << "The Postfix expression is: " << postfixExpression << endl; 
        int result = reviewPostfix(postfixExpression); 
        cout << "Here is the result: " << result << endl; 
    }

    return 0;
}
/*
Please enter an infix operation and I will try my best to convert to PostFix operation (Please make sure there are no spaces, single digits, balanced parentheses):
 5+4*7
The Postfix expression is: 547*+
Here is the result: 33

Please enter an infix operation and I will try my best to convert to PostFix operation (Please make sure there are no spaces, single digits, balanced parentheses):
 5+4*7
The Postfix expression is: 547*+
Here is the result: 33


*/