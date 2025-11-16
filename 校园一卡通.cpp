#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>  // 需包含此头文件以使用异常类
using namespace std;

// 系统常量
const double FEE_RATE = 0.02;          // 充值手续费率
const double WARNING_BALANCE = 10.0;   // 低余额警戒值

// 学生一卡通账户结构体
struct Card
{
	int    id;            // 学号
	string name;          // 姓名
	double balance;       // 当前余额
	int    transactions;  // 交易次数
};

namespace card
{
	// 打印分隔线
	void printLine(char c = '-', int len = 60)
	{
		for (int i = 0; i < len; ++i)
		{
			cout << c;
		}
		cout << endl;
	}

	// 打印标题
	void title(const string& s)
	{
		cout << "\n==== " << s << " ====\n";
	}
}

// 保留带异常处理的版本
Card* createCards(int n)
{
	try
	{
		Card* p = new Card[n];
		return p;
	}
	catch (const bad_alloc& e)
	{
		cerr << "内存分配失败：" << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void destroyCards(Card* p)
{
	delete[] p;
}

// 保留带异常处理的版本
void inputCards(Card* arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << "请输入学号、姓名和初始余额：";
		try
		{
			cin >> arr[i].id >> arr[i].name >> arr[i].balance;

			if (cin.fail())                    // 非法输入检测
			{
				cin.clear();
				cin.ignore(1000, '\n');
				throw runtime_error("输入格式错误，请输入正确的数据类型。");
			}

			if (arr[i].balance < 0)            // 余额校验
			{
				throw invalid_argument("初始余额不能为负数！");
			}

			arr[i].transactions = 0;
		}
		catch (const exception& e)
		{
			cout << "输入异常：" << e.what() << endl;
			i--;  // 重新输入当前账户信息
		}
	}
}

// 充值函数（带默认参数）
void deposit(Card& c, double amount, double fee = FEE_RATE)
{
	c.balance += amount * (1.0 - fee);
	c.transactions++;
}

// 消费函数（函数重载）
bool spend(Card& c, double cost)
{
	if (c.balance >= cost)
	{
		c.balance -= cost;
		c.transactions++;
		return true;
	}
	return false;
}

// 保留带异常处理的版本
bool spend(Card& c, double cost, const string& item)
{
	cout << "消费项目：" << item << endl;

	try
	{
		if (cost < 0)
		{
			throw invalid_argument("消费金额不能为负数！");
		}

		if (c.balance < cost)
		{
			throw runtime_error("余额不足，消费失败！");
		}

		c.balance -= cost;
		c.transactions++;
		return true;
	}
	catch (const exception& e)
	{
		cout << "异常提示：" << e.what() << endl;
		return false;
	}
}

// 常引用：用于防止数据被修改
void showBalance(const Card& c)
{
	cout << c.name << " 当前余额为：" << c.balance << endl;
}

// 指向常量的指针：可访问但不能修改指向值
void viewStudentID(const Card* p)
{
	cout << "账户ID为：" << p->id << endl;
}

int toCent(double amount)
{
	return static_cast<int>(amount * 100);
}

void printReport(const Card* arr, int n)
{
	using card::printLine;
	printLine('=');
	cout << left << setw(8) << "ID"
		<< setw(12) << "Name"
		<< right << setw(14) << "Balance"
		<< setw(14) << "Transactions" << endl;
	printLine('-');

	cout.setf(ios::fixed);
	cout << setprecision(2);

	for (int i = 0; i < n; ++i)
	{
		cout << left << setw(8) << arr[i].id
			<< setw(12) << arr[i].name
			<< right << setw(14) << arr[i].balance
			<< setw(14) << arr[i].transactions << endl;
	}
	printLine('=');
}

int main()
{
	using card::title;
	using card::printLine;

	title("Campus Card System");

	int n;
	cout << "请输入学生数量：";
	cin >> n;

	Card* users = createCards(n);
	inputCards(users, n);

	deposit(users[0], 100.0);
	spend(users[0], 8.5, "食堂午餐");

	showBalance(users[0]);
	viewStudentID(&users[0]);

	cout << "换算为分：" << toCent(users[0].balance) << endl;

	printReport(users, n);
	destroyCards(users);

	system("pause");

	return 0;
}