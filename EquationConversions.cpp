#include <iostream>
#include <string>
#include <cmath> 

using namespace std;


// Node structure for float stack
struct FloatNode {
    float data;
    FloatNode* next;
};


// Float stack class
class FloatStack {
public:
    FloatNode* top;

    FloatStack() : top(nullptr) {}

    void push(float x) {
        FloatNode* newNode = new FloatNode();
        newNode->data = x;
        newNode->next = top;
        top = newNode;
    }

    float pop() {
        if (top == nullptr) {
            cout << "Stack Underflow" << endl;
            return 0;
        }
        float popped = top->data;
        FloatNode* temp = top;
        top = top->next;
        delete temp;
        return popped;
    }

    float peek() {
        return top ? top->data : 0;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


// Node structure for char stack
struct CharNode {
    char data;
    CharNode* next;
};


// Char stack class
class CharStack {
public:
    CharNode* top;

    CharStack() : top(nullptr) {}

    void push(char x) {
        CharNode* newNode = new CharNode();
        newNode->data = x;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (top == nullptr) {
            cout << "Stack Underflow" << endl;
            return '\0';
        }
        char popped = top->data;
        CharNode* temp = top;
        top = top->next;
        delete temp;
        return popped;
    }

    char peek() {
        return top ? top->data : '\0';
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Node structure for string stack
struct StringNode {
    string data;
    StringNode* next;
};

// String stack class
class StringStack {
public:
    StringNode* top;

    StringStack() : top(nullptr) {}

    void push(string x) {
        StringNode* newNode = new StringNode();
        newNode->data = x;
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (top == nullptr) {
            cout << "Stack Underflow" << endl;
            return "";
        }
        string popped = top->data;
        StringNode* temp = top;
        top = top->next;
        delete temp;
        return popped;
    }

    string peek() {
        return top ? top->data : "";
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


int precedence(char op) {  // function to check precedence of operators
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}


bool isDigit(char ch) {  // function to check if the character is a digit
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}




bool isOperator(char c) {  // function to check if the character is an operator
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}


bool isOperand(char c) {  // function to check if the character is an operand
    return isdigit(c) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}


string infixToPostfix(const string& infix) {  // function to convert infix to postfix
    CharStack opStack;
    string postfix;

    for (int i = 0; i < infix.length(); i++) {  // loop to iterate through the infix expression
        char c = infix[i];

        if (isOperand(c)) {
            postfix += c;
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                postfix += opStack.pop();
            }
            opStack.pop();  // Pop '('
        } else if (isOperator(c)) {
            while (!opStack.isEmpty() && precedence(opStack.peek()) >= precedence(c)) {
                postfix += opStack.pop();
            }
            opStack.push(c);
        }
    }

    while (!opStack.isEmpty()) {
        postfix += opStack.pop();
    }

    return postfix;
}


string reverseString(const string& str) {  // function to reverse a string
    string reversed = str;
    int n = reversed.length();
    for (int i = 0; i < n / 2; i++) {
        swap(reversed[i], reversed[n - i - 1]);
    }
    return reversed;
}


string infixToPrefix(const string& infix) {  // function to convert infix to prefix
    string reversedInfix = reverseString(infix);

    for (int i = 0; i < reversedInfix.length(); i++) {
        if (reversedInfix[i] == '(') reversedInfix[i] = ')';
        else if (reversedInfix[i] == ')') reversedInfix[i] = '(';
    }

    string postfix = infixToPostfix(reversedInfix);
    return reverseString(postfix);
}


string prefixToPostfix(const string& prefix) {  // function to convert prefix to postfix
    StringStack s;
    int n = prefix.length();

    for (int i = n - 1; i >= 0; i--) {
        char c = prefix[i];

        if (isOperand(c)) {
            s.push(string(1, c));
        } else if (isOperator(c)) {
            string op1 = s.pop();
            string op2 = s.pop();
            string postfix = op1 + op2 + c;
            s.push(postfix);
        }
    }

    return s.pop();
}

string prefixToInfix(const string& prefix) {    // function to convert prefix to infix
    StringStack s;
    int n = prefix.length();

    for (int i = n - 1; i >= 0; i--) {
        char c = prefix[i];

        if (isOperand(c)) {
            s.push(string(1, c));
        } else if (isOperator(c)) {
            string op1 = s.pop();
            string op2 = s.pop();
            string infix = "(" + op1 + c + op2 + ")";
            s.push(infix);
        }
    }

    return s.pop();
}


string postfixToPrefix(const string& postfix) {    // function to convert postfix to prefix
    StringStack s;
    int n = postfix.length();

    for (int i = 0; i < n; i++) {
        char c = postfix[i];

        if (isOperand(c)) {
            s.push(string(1, c));
        } else if (isOperator(c)) {
            string op2 = s.pop();
            string op1 = s.pop();
            string prefix = c + op1 + op2;
            s.push(prefix);
        }
    }

    return s.pop();
}


string postfixToInfix(const string& postfix) {  // function to convert postfix to infix
    StringStack s;
    int n = postfix.length();

    for (int i = 0; i < n; i++) {
        char c = postfix[i];

        if (isOperand(c)) {
            s.push(string(1, c));
        } else if (isOperator(c)) {
            string op2 = s.pop();
            string op1 = s.pop();
            string infix = "(" + op1 + c + op2 + ")";
            s.push(infix);
        }
    }

    return s.pop();
}






string checkTypeOfEquation(const string& exp) {  // function to check the type of equation
    if (isOperand(exp[0]) && isOperand(exp[exp.length() - 1] || exp[0] == '(' && exp[exp.length() - 1] == ')') || isOperand(exp[0]) && exp[exp.length() - 1] == ')') {
        return "Infix";
    } else if (isOperator(exp[0]) && isOperand(exp[exp.length() - 1])) {
        return "Prefix";
    } else if (isOperand(exp[0]) && isOperator(exp[exp.length() - 1])) {
        return "Postfix";
    } else {
        return "Invalid equation";
    }
}


float evalExpression(float val1, float val2, char op) {  // function to evaluate the expression
    switch (op) {
        case '+': return val1 + val2;
        case '-': return val1 - val2;
        case '*': return val1 * val2;
        case '/': return val1 / val2;
        case '^': return pow(val1, val2);
        default: return 0;
    }
}


float evalInfix(const string& exp) {  // function to evaluate infix expression
    FloatStack valStack;  
    CharStack opStack;    

    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];

        if (isdigit(c)) {
            valStack.push(c - '0'); 
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                char op = opStack.pop();
                float val2 = valStack.pop();
                float val1 = valStack.pop();
                valStack.push(evalExpression(val1, val2, op)); 
            }
            opStack.pop(); // Remove '('
        } else if (isOperator(c)) {
            while (!opStack.isEmpty() && precedence(opStack.peek()) >= precedence(c)) {
                char op = opStack.pop();
                float val2 = valStack.pop();
                float val1 = valStack.pop();
                valStack.push(evalExpression(val1, val2, op));
            }
            opStack.push(c);
        }
    }

    while (!opStack.isEmpty()) {
        char op = opStack.pop();
        float val2 = valStack.pop();
        float val1 = valStack.pop();
        valStack.push(evalExpression(val1, val2, op));
    }

    return valStack.pop(); 

}


float evalPrefix(const string& exp) {  // function to evaluate prefix expression
    FloatStack valStack;

    for (int i = exp.length() - 1; i >= 0; i--) {
        char c = exp[i];

        if (isdigit(c)) {
            valStack.push(c - '0'); 
        } else if (isOperator(c)) {
            float val1 = valStack.pop();
            float val2 = valStack.pop();
            float result = evalExpression(val1, val2, c);
            valStack.push(result);
        }
    }

    return valStack.pop();
}


float evalPostfix(const string& exp) {    // function to evaluate postfix expression
    FloatStack valStack;

    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];

        if (isdigit(c)) {
            valStack.push(c - '0'); 
        } else if (isOperator(c)) {
            float val2 = valStack.pop();
            float val1 = valStack.pop();
            float result = evalExpression(val1, val2, c);
            valStack.push(result);
        }
    }

    return valStack.pop();
}


int main() {
    cout << "Enter expression for evaluation: ";
    string exp;
    cin >> exp;

    if (checkTypeOfEquation(exp) == "Infix") {
        cout << "Infix to Postfix: " << infixToPostfix(exp) << endl;
        cout << "Infix to Prefix: " << infixToPrefix(exp) << endl;
        cout << "Evaluation of infix expression is: " << evalInfix(exp) << endl;

    } else if (checkTypeOfEquation(exp) == "Prefix") {
        cout << "Prefix to Postfix: " << prefixToPostfix(exp) << endl;
        cout << "Prefix to Infix: " << prefixToInfix(exp) << endl;
        cout << "Evaluation of prefix expression is: " << evalPrefix(exp) << endl;
    } else {
        cout << "Postfix to Prefix: " << postfixToPrefix(exp) << endl;
        cout << "Postfix to Infix: " << postfixToInfix(exp) << endl;
        cout << "Evaluation of postfix expression is: " << evalPostfix(exp) << endl;
    }

    return 0;
}
