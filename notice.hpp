#include<iostream>

using namespace std;

void Tools_notice()
{
	cout << "���Ƕ��ڱ�ϵͳ��ʹ��˵��" << endl;
	cout << "ʹ�ô�д��ĸ��ʾ���⡣����ʵСд��ĸҲ�У�" << endl;
	cout << "ʹ�÷��š�!����ʾ�����Ӵʡ�" << endl;
	cout << "ʹ�÷��š�&����ʾ��ȡ���Ӵʡ�" << endl;
	cout << "ʹ�÷��š�|����ʾ��ȡ���Ӵʡ�" << endl;
	cout << "ʹ�÷��š�>����ʾ�Ƶ����Ӵʡ�" << endl;
	cout << "ʹ�÷��š�=����ʾ˫���Ƶ����Ӵʡ�" << endl;
	cout << "���ϸ���ϵͳ˵����������Ҫ����ո�ϵͳ�ǲִټ��������ģ�û���㹻�ļ����ԡ�"<<endl;
	cout << "��ϵͳ���ṩ����ÿһ����ǰ������ʽ���������������ҵ���⣨bushi��"<<endl;
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
