// Mohammad Jaafar
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

const int MAX_STACK_SIZE = 1000;

class Stack
{
public:
    Stack() : top(-1) {}
    virtual void push(string item) = 0;
    virtual string pop() = 0;
    virtual string peek() = 0;
    virtual bool isEmpty() = 0;

protected:
    int top;
};

class ArrayStack : public Stack
{
public:
    ArrayStack() : Stack() {}
    void push(string item)
    {
        if (top == MAX_STACK_SIZE - 1)
        {
            cout << "Stack overflow" << endl;
            return;
        }
        data[++top] = item;
    }
    string pop()
    {
        if (isEmpty())
        {
            cout << "Stack underflow" << endl;
            return "";
        }
        return data[top--];
    }
    string peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return "";
        }
        return data[top];
    }
    bool isEmpty()
    {
        return top == -1;
    }

private:
    string data[MAX_STACK_SIZE];
};

bool isNumber(const string &s)
{
    return !s.empty() && find_if(s.begin(),
                                      s.end(), [](unsigned char c)
                                      { return !isdigit(c); }) == s.end();
}

int getPrecedence(string op)
{
    if (op == "min" || op == "max")
    {
        return 4;
    }
    else if (op == "*" || op == "/")
    {
        return 3;
    }
    else if (op == "+" || op == "-")
    {
        return 2;
    }
    else if (op == "(" || op == ")")
    {
        return 1;
    }
    return 0;
}

bool isOperator(string item)
{
    return item == "+" || item == "-" || item == "*" || item == "/" || item == "min" || item == "max";
}

bool isLeftParenthesis(string item)
{
    return item == "(";
}

bool isRightParenthesis(string item)
{
    return item == ")";
}
bool isComma(string item)
{
    return item == ",";
}

string getPostfix(string infix)
{
    ArrayStack stack;
    string postfix = "";
    string item;
    stringstream ss(infix);

    while (ss >> item)
    {

        if (isNumber(item))
        {
            postfix += item + " ";
        }
        else if (isOperator(item))
        {
            while (!stack.isEmpty() && getPrecedence(stack.peek()) >= getPrecedence(item))
            {
                postfix += stack.pop() + " ";
            }
            stack.push(item);
        }
        else if (isLeftParenthesis(item))
        {
            stack.push(item);
        }
        else if (isRightParenthesis(item))
        {
            while (!stack.isEmpty() && !isLeftParenthesis(stack.peek()))
            {
                postfix += stack.pop() + " ";
            }
            if (!stack.isEmpty() && isLeftParenthesis(stack.peek()))
            {
                stack.pop();
            }
        }
        else if (isComma(item))
        {
            while (!stack.isEmpty() && !isLeftParenthesis(stack.peek()))
            {
                postfix += stack.pop() + " ";
            }
        }
    }
    while (!stack.isEmpty())
    {
        postfix += stack.pop() + " ";
    }
    return postfix;
}

int main()
{
    string infix;
    getline(cin, infix);
    cout << getPostfix(infix) << endl;
    return 0;
}
