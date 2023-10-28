//if you want to see chinese in this program , please use gbk
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include<string>
#include<limits>
#include "notice.hpp"


//这个二叉树用来储存运算时的顺序（即计算机读取的顺序）
class Tree {// This binary tree class is used to store the order in which calculations are performed
public:
    char symbol;
    Tree* left, * right;
    Tree(Tree* _left, char _symbol, Tree* _right) {
        left = _left;
        right = _right;
        symbol = _symbol;
    }
};

//这个类用于储存相继式的前后件，储存内容是分支的Tree
class Object {//The class used to store the antecedent and consequent of a sequent, with content being branches of Tree
public:
    std::queue<Tree*> front, back;
};

//用于判断输入
inline bool isConnector(char c) {//Used for input validation
    return (c == '!' || c == '&' || c == '|' || c == '>' || c == '=');
}

//优先级排序
inline int priority(const char c) {
    switch (c) {
        case '!':
            return 1;
        case '&':
            return 2;
        case '|':
            return 3;
        case '>':
            return 4;
        case '=':
            return 5;
        default:
            return -1;
    }
}

//这个函数将被用于读取输入的逻辑运算式
//最终返回后缀表达式
// This function will be used to read logical expressions
// and return the postfix expression
std::string read(std::string midsentense) {
    std::string backsentense;
    //此处输入需证逻辑式的中缀表达式
    std::stack<char> pile;//堆栈用于把中缀表达式变为后缀表达式

    for (char temp : midsentense)
    {
        if (isConnector(temp))
        {
            while (!pile.empty() && pile.top() != '(' && priority(pile.top()) <= priority(temp))
            {
                backsentense.push_back(pile.top());
                pile.pop();
            }
            pile.push(temp);//把新运算符压入堆
        }
        else if (temp == '(') {
            pile.push(temp);
        }
        else if (temp == ')') {
            while (!pile.empty() && pile.top() != '(') {
                backsentense.push_back(pile.top());
                pile.pop();
            }
            pile.pop();//把最后一个'('弹出
        }
        else {
            backsentense.push_back(temp);
        }
    }
    while (!pile.empty()) {
        backsentense.push_back(pile.top());
        pile.pop();
    }
    return backsentense;
}

//这个函数读入后缀表达式
//最终返回建立好的运算二叉树
// This function reads the postfix expression and returns the constructed binary tree
Tree* planttree(const std::string sen) {
    std::stack<Tree*> treestack;
    for (char temp : sen) {
        if (temp == '!') {
            Tree* top = treestack.top();
            treestack.pop();
            treestack.push(new Tree(nullptr, temp, top));
        }
        else if (temp == '&' || temp == '|' || temp == '>' || temp == '=') {
            Tree* top1 = treestack.top();
            treestack.pop();
            Tree* top2 = treestack.top();
            treestack.pop();
            treestack.push(new Tree(top2, temp, top1));
        }
        else {
            treestack.push(new Tree(nullptr, temp, nullptr));
        }
    }
    return treestack.top();
}

//这个函数用于把最开始建立的数转换为相继式
Object sequent(Tree* root) {// This function is used to convert the binary tree to a sequent
    Object temp;
    //树根是'>'时，可以直接得出前后件
    if (root->symbol == '>') {
        temp.front.push(root->left);
        temp.back.push(root->right);
    }
    else {//other situation
        temp.back.push(root);
    }
    return temp;
}

//这个函数用于把数输出成为中缀表达式
void printInfix(Tree* root) {// This function prints the infix expression of the tree
    if (root != nullptr) {
        if (isConnector(root->symbol)) {
            std::cout << "(";
        }
        printInfix(root->left);
        std::cout << root->symbol;
        printInfix(root->right);
        if (isConnector(root->symbol)) {
            std::cout << ")";
        }
    }
}

//该函数用于判断前件或后件里有没有符号
bool noConnector(std::queue<Tree*> sen) {
    while (!sen.empty()) {
        if (isConnector(sen.front()->symbol))
            return 0;
        sen.pop();
    }
    return 1;
}

//此函数用于打印前件和后件的队列
void printQueue(const std::queue<Tree*>& q) {// This function is used to print queue
    std::queue<Tree*> temp = q; // 创建队列副本以免改变原队列
    if(temp.empty())
    {
        std::cout<<"none";
    }
    while (!temp.empty()) {
        printInfix(temp.front());
        std::cout << ",";
        temp.pop();
    }
}

//本函数是王浩算法的主要实现函数，通过函数内部变形后的递归调用，实现对不同分支的公理变形
//判断是否为公理函数
bool trans_check(Object i) {
    std::cout << "front is:";
    printQueue(i.front);
    std::cout << "  back is:";
    printQueue(i.back);
    std::cout << std::endl;
    //前件规则
    // Antecedent rules
    if (!noConnector(i.front)) {
        Tree* temp = i.front.front();
        Object i1 = i;
        Object i2 = i;
        i1.front.pop();

        switch (temp->symbol) {
            case '!':
                i1.back.push(temp->right);
                break;
            case '&':
                i1.front.push(temp->left);
                i1.front.push(temp->right);
                break;
            case '|':
                i2.front.pop();
                i2.front.push(temp->left);
                i2.front.push(temp->right);
                return trans_check(i1) && trans_check(i2);
            case '>':
                i2.front.pop();
                i2.front.push(temp->right);
                i2.back.push(temp->left);
                return trans_check(i1) && trans_check(i2);
            case '=':
                i2.front.pop();
                i2.front.push(temp->left);
                i2.front.push(temp->right);
                i2.back.push(temp->left);
                i2.back.push(temp->right);
                return trans_check(i1) && trans_check(i2);
        }

        return trans_check(i1);
    }
    //后件规则
    // Consequent rules
    if (!noConnector(i.back)) {
        Tree* temp = i.back.front();
        Object i1 = i;
        Object i2 = i;
        i1.back.pop();

        switch (temp->symbol) {
            case '!':
                i1.front.push(temp->right);
                break;
            case '&':
                i2.back.pop();
                i2.back.push(temp->left);
                i2.back.push(temp->right);
                return trans_check(i1) && trans_check(i2);
            case '|':
                i1.back.push(temp->left);
                i1.back.push(temp->right);
                break;
            case '>':
                i1.front.push(temp->left);
                i1.back.push(temp->right);
                break;
            case '=':
                i2.back.pop();
                i2.back.push(temp->left);
                i2.front.push(temp->right);
                i1.front.push(temp->left);
                i1.back.push(temp->right);
                return trans_check(i1) && trans_check(i2);
        }

        return trans_check(i1);
    }
    //如果程序运行到此处，说明前后件均无联结词，此时判断前后件有无相同命题变项
    // Check for symbols not found in the consequent
    std::queue<Tree*> tempQueue1 = i.front;
    while (!tempQueue1.empty()) {
        char charToFind = tempQueue1.front()->symbol;
        tempQueue1.pop();
        
        std::queue<Tree*> tempQueue2 = i.back;
        while (!tempQueue2.empty()) {
            if (tempQueue2.front()->symbol == charToFind) {
                return true;
            }
            tempQueue2.pop();
        }
    }
    return false;
}

//这三个函数用于提供程序说明，方便user直接使用的时候能了解使用方法
extern void choose_language();
extern void Tools_notice();
extern void Tools_notice(int);

int main() {
    choose_language();
    int lan;
    std::cin>>lan;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(lan){
        Tools_notice();
        std::cout << "请输入您想证明的定理" << std::endl;
    }else{
        Tools_notice(lan);
        std::cout <<"Please provide the theorem you would like to prove" << std::endl;
    }
    std::string input;
    std::getline(std::cin, input);
    Tree* new_tree = planttree(read(input));
    //printInfix(new_tree);
    //输出1，则为重言式，输出0，则不是重言式
    std::cout << trans_check(sequent(new_tree)) << std::endl;
    if(lan){
        std::cout << "输入任意字符结束程序" <<std::endl;
    }else{
        std::cout << "Enter any character to end the program." <<std::endl;
    }
    std::cin >> lan;
}
