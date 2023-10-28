#include<iostream>

using namespace std;

void Tools_notice()
{
	cout << "这是对于本系统的使用说明" << endl;
	cout << "使用大写字母表示命题。（其实小写字母也行）" << endl;
	cout << "使用符号‘!’表示非连接词。" << endl;
	cout << "使用符号‘&’表示和取连接词。" << endl;
	cout << "使用符号‘|’表示析取连接词。" << endl;
	cout << "使用符号‘>’表示推导连接词。" << endl;
	cout << "使用符号‘=’表示双向推导连接词。" << endl;
	cout << "请严格按照系统说明操作，不要输入空格，系统是仓促间做出来的，没有足够的兼容性。"<<endl;
	cout << "本系统会提供解题每一步的前件与后件式，完美解决您的作业问题（bushi）"<<endl;
}

void Tools_notice(int i) {
    cout << "This is the usage instructions for this system" << endl;
    cout << "Use uppercase letters to represent propositions (lowercase letters are also acceptable)." << endl;
    cout << "Use the '!' symbol to denote the NOT operator." << endl;
    cout << "Use the '&' symbol to denote the AND operator." << endl;
    cout << "Use the '|' symbol to denote the OR operator." << endl;
    cout << "Use the '>' symbol to denote the IMPLICATION operator." << endl;
    cout << "Use the '=' symbol to denote the BICONDITIONAL operator." << endl;
    cout << "Please strictly follow the system instructions, do not input spaces. The system was created hastily and lacks full compatibility." << endl;
	cout << "This system will provide the antecedent and consequent of each step of the solution, perfectly solving your homework problems." << endl;
}

void choose_language(){
	cout <<"please choose language , input 0 means use English ,input others means use Chinese."<<endl;
	cout <<"if you want to use Chinese form , please use gbk" << endl;

} 
