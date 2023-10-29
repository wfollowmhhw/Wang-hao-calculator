//if you want to see chinese in this program , please use gbk
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include<string>
#include<limits>
#include "notice.hpp"


//���������������������ʱ��˳�򣨼��������ȡ��˳��
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

//��������ڴ������ʽ��ǰ��������������Ƿ�֧��Tree
class Object {//The class used to store the antecedent and consequent of a sequent, with content being branches of Tree
public:
    std::queue<Tree*> front, back;
};

//�����ж�����
inline bool isConnector(char c) {//Used for input validation
    return (c == '!' || c == '&' || c == '|' || c == '>' || c == '=');
}

//���ȼ�����
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


//��������������ڶ�ȡ������߼�����ʽ
//���շ��غ�׺���ʽ
// This function will be used to read logical expressions
// and return the postfix expression
std::string read(std::string midsentense) {
    std::string backsentense;
    //�˴�������֤�߼�ʽ����׺���ʽ
    std::stack<char> pile;//��ջ���ڰ���׺���ʽ��Ϊ��׺���ʽ

    for (char temp : midsentense)
    {
        if (isConnector(temp))
        {
            while (!pile.empty() && pile.top() != '(' && priority(pile.top()) <= priority(temp))
            {
                backsentense.push_back(pile.top());
                pile.pop();
            }
            pile.push(temp);//���������ѹ���
        }
        else if (temp == '(') {
            pile.push(temp);
        }
        else if (temp == ')') {
            while (!pile.empty() && pile.top() != '(') {
                backsentense.push_back(pile.top());
                pile.pop();
            }
            pile.pop();//�����һ��'('����
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

//������������׺���ʽ
//���շ��ؽ����õ����������
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

//����������ڰ��ʼ��������ת��Ϊ���ʽ
Object sequent(Tree* root) {// This function is used to convert the binary tree to a sequent
    Object temp;
    //������'>'ʱ������ֱ�ӵó�ǰ���
    if (root->symbol == '>') {
        temp.front.push(root->left);
        temp.back.push(root->right);
    }
    else {//other situation
        temp.back.push(root);
    }
    return temp;
}

//����������ڰ��������Ϊ��׺���ʽ
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

//�ú��������ж�ǰ����������û�з���
bool noConnector(std::queue<Tree*> sen) {
    while (!sen.empty()) {
        if (isConnector(sen.front()->symbol))
            return 0;
        sen.pop();
    }
    return 1;
}

//�˺������ڴ�ӡǰ���ͺ���Ķ���
void printQueue(const std::queue<Tree*>& q) {// This function is used to print queue
    std::queue<Tree*> temp = q; // �������и�������ı�ԭ����
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

//�ж��Ƿ�Ϊ������
bool trans_check(Object i) {
    std::cout << "front is:";
    printQueue(i.front);
    std::cout << "  back is:";
    printQueue(i.back);
    std::cout << std::endl;

    // Antecedent rules
    if (!noConnector(i.front)) {
        Tree* temp = i.front.front();
        Object i1 = i;
        Object i2 = i;
        i1.front.pop();
        i2.front.pop();

        switch (temp->symbol) {
            case '!':
                i1.back.push(temp->right);
                break;
            case '&':
                i1.front.push(temp->left);
                i1.front.push(temp->right);
                break;
            case '|':
                i1.front.push(temp->left);
                i2.front.push(temp->right);
                return trans_check(i1) && trans_check(i2);
            case '>':
                i1.front.push(temp->right);
                i2.back.push(temp->left);
                return trans_check(i1) && trans_check(i2);
            case '=':
                i1.front.push(temp->left);
                i1.front.push(temp->right);
                i2.back.push(temp->left);
                i2.back.push(temp->right);
                return trans_check(i1) && trans_check(i2);
        }

        return trans_check(i1);
    }

    // Consequent rules
    if (!noConnector(i.back)) {
        Tree* temp = i.back.front();
        Object i1 = i;
        Object i2 = i;
        i1.back.pop();
        i2.back.pop();
        switch (temp->symbol) {
            case '!':
                i1.front.push(temp->right);
                break;
            case '&':
                i1.back.push(temp->left);
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
                i2.back.push(temp->left);
                i2.front.push(temp->right);
                i1.front.push(temp->left);
                i1.back.push(temp->right);
                return trans_check(i1) && trans_check(i2);
        }

        return trans_check(i1);
    }

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
        std::cout << "����������֤���Ķ���" << std::endl;
    }else{
        Tools_notice(lan);
        std::cout <<"Please provide the theorem you would like to prove" << std::endl;
    }
    std::string input;
    std::getline(std::cin, input);
    Tree* new_tree = planttree(read(input));
    //printInfix(new_tree);
    std::cout << trans_check(sequent(new_tree)) << std::endl;
    if(lan){
        std::cout << "���������ַ���������" <<std::endl;
    }else{
        std::cout << "Enter any character to end the program." <<std::endl;
    }
    std::cin >> lan;
}