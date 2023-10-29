# Wang-hao-calculator
a homework , use wang hao algorithm automaticly proof logical expression

本程序使用时间复杂度为O（2^n）的算法做自动证明，只需输入逻辑表达式即可<br>
相比于之前两位同学的代码，我的代码可能称不上是 100% 原创 ，实际上，我是在理解了前两位同学的思路后，对代码做出了自己的改进

**目录**
- [Wang-hao](#wang-hao-calculator)
  - [代码思路简述](#代码思路简述)
  - [代码实现](#代码实现)
    - [表达式转化为二叉树形式储存](#表达式转化为二叉树形式储存)
    - [对二叉树做前后件分离](#对二叉树做前后件分离)
    - [王浩算法](#王浩算法)
      - [优先化简](#优先化简)
      - [化简完成后进行命题比较](#化简完成后进行命题比较)
   -[输入与输出](#输入与输出)
  - [感谢列表](#感谢列表)
  - [总结](#总结)
## 代码思路简述
1.将逻辑表达式转化为二叉树的运算形式储存<br>
2.拆分二叉树，把二叉树分支内容存入前后件之中<br>
3.不断解除二叉树的分支内容，最终达到不存在连结词的前后件形式<br>
4.将后件与前件比较，返回该分支是否为公理<br>
5.如果所有分支均为公理，则原逻辑表达式为重言式<br>

## 代码实现

### 表达式转化为二叉树形式储存
两个函数，分别把中缀表达式转变为后缀表达式，把后缀表达式转化为二叉树
```cpp

std::string read(std::string midsentense)；
Tree* planttree(const std::string sen)；

```

### 对二叉树做前后件分离
如果输入表达式本身能得出一个相继式，那么树根应为‘->’<br>
所以，如果树根是‘>’则把左孩子作为前件，右孩子作为后件<br>
如果树根是其它东西，则直接把逻辑表达式放入后件即可。
```cpp

Object sequent(Tree* root) {
    Object temp;
    //树根是'>'时，可以直接得出前后件
    if (root->symbol == '>') {
        temp.front.push(root->left);
        temp.back.push(root->right);
    }else {//other situation
        temp.back.push(root);
    }
    return temp;
}

```
### 王浩算法

#### 优先化简
在输入了前后件后，优先对前后件进行化简，化简目标是写成由一个个单个命题组成的相继式，即没有联结词<br>
化简方法来自于王浩算法的10种推理规则<br>
```cpp

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

    // 后件规则
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

```
#### 化简完成后进行命题比较
命题比较实际上就是把前件列表与后件列表的元素作比较<br>
此时应当注意，如果前件不存在，则非重言式，因此取前件元素与后件作比较
```cpp

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

```
### 输入与输出
1.输入： 按照规则，输入对应的逻辑表达式，形如：
```
((P|Q)&(P>R)&(Q>S))>(S|R)

```
2.输出：输出每一步推导的前后件，并给出最终结论，1表示是定理，2表示不是定理
## 感谢列表
首先要感谢最先完成的两位同学，实际上我自己的数据结构的水平极为有限，在开始写代码的时候我并不知道什么是 **二叉树** ，最先完成的两位同学给我提供了很宝贵的思路<br>
其次要感谢章明星老师的指导，让我接触到了如此优美的证明方法<br>
然后要感谢的是CSDN中文博客，是众多博客让我理解了二叉树的构建，从而充分理解了两位同学的计算方法，进而有了自己的思考<br>
此处是有关二叉树的CSDN博客 "https://blog.csdn.net/weixin_45796387/article/details/114994648?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169850350216777224439293%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169850350216777224439293&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-114994648-null-null.142^v96^pc_search_result_base3&utm_term=%E4%BA%8C%E5%8F%89%E6%A0%91&spm=1018.2226.3001.4187" <br>
最后要感谢GPT GLM等大模型，它通过为许多我读不懂的代码添加注释，让我理解了自动证明算法的思路<br>

## 总结
应当说本次编程给我最大的教育就是学会了二叉树的数据结构，进而通过这种数据结构实现了优美的递归调用。<br>
不过回想起我在学习过程中所遇到的困难，我还是不由得想起一句话：<br>
 “世界上最讨厌的两种人，一种是不写注释的人，一种是让我写注释的人” <br>
所以我的代码会尽力的添加注释含量，让之后写自动证明的同学能更方便地理解王浩算法的内涵，我觉得这是十分有益的。
