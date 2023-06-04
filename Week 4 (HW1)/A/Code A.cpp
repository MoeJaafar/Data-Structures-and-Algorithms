// Mohammad Jaafar
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_STACK_SIZE = 1000;

// Define an abstract class Stack with pure virtual functions
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

// Define a concrete class ArrayStack that inherits from Stack
class ArrayStack : public Stack
{
public:
    ArrayStack() : Stack() {}
    // Implement push method to add an item to the top of the stack ; Worst case: O(1) ,Average case: O(1) and Amortized case: O(1)
    void push(string item)
    {
        if (top == MAX_STACK_SIZE - 1)
        {
            cout << "Stack overflow" << endl;
            return;
        }
        data[++top] = item;
    }
    // Implement pop method to remove and return the item from the top of the stack ; Worst case: O(1) ,Average case: O(1) and Amortized case: O(1)
    string pop()
    {
        if (isEmpty())
        {
            cout << "Stack underflow" << endl;
            return "";
        }
        return data[top--];
    }
    // Implement peek method to return the item at the top of the stack without removing it ; Worst case: O(1) ,Average case: O(1) and Amortized case: O(1)
    string peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return "";
        }
        return data[top];
    }
    // Implement isEmpty method to check if the stack is empty ; Worst case: O(1) ,Average case: O(1) and Amortized case: O(1)
    bool isEmpty()
    {
        return top == -1;
    }

private:
    string data[MAX_STACK_SIZE];
};

// Declare global variables for the number of open and close tokens
int numOfDelim, numOfLines;

// Declare arrays to store the open, close, and code tokens
string open[1000004], close[1000004], code[1000004];

// Declare a stack object of type ArrayStack
ArrayStack s;

// Define functions to check if a token is an open, close, or matching token

// Check if a token is an open token ; Worst case: O(numOfDelim) ,Average case: O(numOfDelim)
bool isOpen(string token)
{
    for (int i = 0; i < numOfDelim; i++)
    {
        if (token == open[i])
            return true;
    }
    return false;
}

// Check if a token is a close token ; Worst case: O(numOfDelim) ,Average case: O(numOfDelim)
bool isClose(string token)
{
    for (int i = 0; i < numOfDelim; i++)
    {
        if (token == close[i])
            return true;
    }
    return false;
}

// Check if a close token matches the open token at the top of the stack ; Worst case: O(numOfDelim) ,Average case: O(numOfDelim)
bool isCloseOf(string token, string stackTop)
{
    for (int i = 0; i < numOfDelim; i++)
    {
        if (stackTop == open[i] && token == close[i])
            return true;
    }
    return false;
}

// Find the corresponding close token for a given open token ; Worst case: O(numOfDelim) ,Average case: O(numOfDelim)
string closingOf(string token)
{
    for (int i = 0; i < numOfDelim; i++)
    {
        if (token == open[i])
            return close[i];
    }
}

/* Define a function named "solution" that checks if the input code has balanced parentheses
 It takes no arguments and returns a string
Worst case: O(numOfLines * avg_num_of_tokens_per_line * numOfDelim)
Average case: O(numOfLines * avg_num_of_tokens_per_line * numOfDelim), where avg_num_of_tokens_per_line is the average number of tokens per line of code.
In the worst case, each token in each line of code must be compared to every open/close token, which takes O(numOfDelim) time for each token.
*/
string solution()
{
    // Declare a variable to keep track of the column number
    int col;

    // Loop through the lines of code
    for (int i = 0; i < numOfLines; i++)
    {
        col = 1;

        // Use stringstream to extract tokens from the line of code
        stringstream ss(code[i]);
        string token;

        // Loop through the tokens
        while (ss >> token)
        {

            // If the token is an open token, push it to the stack
            if (isOpen(token))
                s.push(token);

            // If the token is a close token
            else if (isClose(token))
            {

                // If the stack is empty, return an error message
                if (s.isEmpty())
                {
                    stringstream pp;
                    pp << "Error in line ";
                    pp << i + 1;
                    pp << ", column " << col;
                    pp << ": unexpected closing token " << token << '.';
                    return pp.str();
                }

                // If the close token does not match the open token at the top of the stack, return an error message
                else if (!isCloseOf(token, s.peek()))
                {
                    stringstream pp;
                    pp << "Error in line ";
                    pp << i + 1;
                    pp << ", column " << col;
                    pp << ": expected " << closingOf(s.peek()) << " but got " << token << ".";
                    return pp.str();
                }

                // Otherwise, pop the top item from the stack
                else
                    s.pop();
            }

            // Update the column number
            col += token.size() + 1;
        }
    }

    // If the stack is not empty, return an error message
    if (!s.isEmpty())
    {
        stringstream pp;
        pp << "Error in line ";
        pp << numOfLines;
        pp << ", column " << col;
        pp << ": expected " << closingOf(s.peek()) << " but got end of input.";
        return pp.str();
    }

    // If the stack is empty, return a message indicating that the input is properly balanced
    return "The input is properly balanced.";
}
/* Define the main function
 The time complexity of the main function depends on the implementation of the solution function,
 so it will be the same as the time complexity of solution
*/

int main()
{
    // Read the number of open and close tokens, and store them in the arrays "open" and "close"
    cin >> numOfDelim >> numOfLines;
    for (int i = 0; i < numOfDelim; i++)
    {
        cin >> open[i] >> close[i];
    }

    // Ignore the newline character after reading the integers
    cin.ignore();

    // Read the lines of code and store them in the array "code"
    for (int i = 0; i < numOfLines; i++)
    {
        getline(cin, code[i]);
    }

    // Call the solution function to check if the input code has balanced parentheses and print the result
    cout << solution();

    // Return 0 to indicate successful execution of the program
    return 0;
}
