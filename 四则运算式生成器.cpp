#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 生成指定范围内的随机数
int generateRand(int minVal, int maxVal) 
{
    return rand() % (maxVal - minVal + 1) + minVal;
}

// 生成加法运算式
string generateAdd() 
{
    int num1 = 0, num2 = 0;
    do
    {
        num1 = generateRand(1, 20);
        num2 = generateRand(1, 20);
    } while (num1 + num2 > 20);
    
    return to_string(num1) + " + " + to_string(num2);
}

// 生成减法运算式
string generateSub() 
{
    int num1 = 0, num2 = 0;
    do
    {
        num1 = generateRand(1, 20);
        num2 = generateRand(1, 20);
    } while (num1 - num2 < 0 || num1 - num2 > 20);

    return to_string(num1) + " - " + to_string(num2);
}

// 随机生成运算符
char generateOperator(int admitOperator)
{
    char operators[] = { '+', '-', '*', '/' };
    return operators[generateRand(0, admitOperator)];
}

// 生成二年级混合运算式
string generateTwoMixed(int numOperator, int maxVal)
{
    string expression;
    int result = 0;

    for (int i = 0; i < numOperator; ++i)
    {
        int num = generateRand(0, maxVal);
        char op;

        if (i == 0)
        {
            result = num;
            expression += to_string(num);
        }
        else
        {
            if (result + num > 50)
            {
                op = '-';
                result -= num;
            }
            else
            {
                op = '+';
                result += num;
            }

            expression += " " + string(1, op) + " " + to_string(num);
        }
    }

    return expression;
}

// 生成三年级混合运算式
string generateThreeMixed(int numOperator, int admitOperator, int maxVal) 
{
    string expression;
    for (int i = 0; i < numOperator; ++i)
    {
        if (i > 0) 
        {
            char op = generateOperator(admitOperator);
            expression += " " + string(1, op) + " ";
        }
        expression += to_string(generateRand(0, maxVal));
    }

    return expression;
}

// 生成四、五、六年级混合运算式
string generateFourMixed(int numOperator, int admitOperator, int maxVal) {
    string expression;
    int result = 0;
    bool hasNegativeResult = false;

    for (int i = 0; i < numOperator; ++i) 
    {
        int num = generateRand(0, maxVal);
        char op = generateOperator(admitOperator);

        if (i > 0) 
        {
            expression += " " + string(1, op) + " ";
        }
        expression += to_string(num);

        if (op == '+')
            result += num;
        else if (op == '-')
            result -= num;
        else if (op == '*')
            result *= num;
        else if (num != 0)
            result /= num;

        if (result < 0)
            hasNegativeResult = true;

        // 随机添加括号
        if (generateRand(0, 1) == 1) 
            expression = "(" + expression + ")";
    }

    // 如果结果为负数，重新生成混合运算式
    if (hasNegativeResult)
        return generateFourMixed(numOperator, admitOperator, maxVal);

    return expression;
}

// 生成四则运算式
string generateExpression(int level) 
{
    switch (level) 
    {
    case 1:
        if (generateRand(0, 1))
            return generateAdd();
        else
            return generateSub();
    case 2:
        return generateTwoMixed(2, 50);
    case 3:
        return generateThreeMixed(3, 2, 1000);
    case 4:
    case 5:
    case 6:
        return generateFourMixed(3, 3, INT_MAX);
    default:
        return "Not Exist This Grade!";
    }
}

int main() 
{
    srand((unsigned)time(nullptr));

    int grade, num;
    cin >> grade;
    if (grade > 6)
    {
        cout << "Not Exist This Grade!" << endl;
        return 1;
    }
    cin >> num;

    cout << "生成的四则运算题目如下：" << endl;
    for (int i = 0; i < num; ++i) 
    {
        cout << generateExpression(grade) << endl;
    }

    return 0;
}