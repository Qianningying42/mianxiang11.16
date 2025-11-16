#include <iostream>
using namespace std;

class Date {
private:
	int year;   
	int month;  
	int date;  

	// 判断是否为闰年
	bool isLeapYear(int y) const {
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}

	// 获取当月天数
	int getDaysInMonth(int y, int m) const {
		if (m == 2) {
			return isLeapYear(y) ? 29 : 28;
		}
		else if (m == 4 || m == 6 || m == 9 || m == 11) {
			return 30;
		}
		else {
			return 31;
		}
	}

public:
	
	Date() : year(2000), month(1), date(1) {}
	void Init(int y, int m, int d) {
		// 验证日期合法性
		if (m < 1 || m > 12) {
			month = 1;
		}
		else {
			month = m;
		}

		year = y;

		// 验证日期
		int maxDay = getDaysInMonth(year, month);
		if (d < 1 || d > maxDay) {
			date = 1;
		}
		else {
			date = d;
		}
	}

	// 读
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDate() const { return date; }

	// 写
	void setYear(int y) { year = y; }
	void setMonth(int m) {
		if (m >= 1 && m <= 12) {
			month = m;
			// 调整日期为合法值
			int maxDay = getDaysInMonth(year, month);
			if (date > maxDay) {
				date = maxDay;
			}
		}
	}
	void setDate(int d) {
		int maxDay = getDaysInMonth(year, month);
		if (d >= 1 && d <= maxDay) {
			date = d;
		}
	}

	// 输出
	void display() const {
		cout << year << "年" << month << "月" << date << "日";
	}

	// 计算星期几（0-6对应星期日到星期六）
	int calWeekday() const {
		int y = year;
		int m = month;
		int d = date;

		// 处理1月和2月的转换
		if (m == 1 || m == 2) {
			m += 12;
			y--;
		}

		// 基姆拉尔森计算公式
		int weekday = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;

		// 确保结果在0-6范围内
		return (weekday + 7) % 7;
	}
};

//
int main() {
	Date d;

	// 测试初始化和显示
	d.Init(2023, 12, 31);
	d.display();
	cout << " 是星期";
	switch (d.calWeekday()) {
	case 0: cout << "日"; break;
	case 1: cout << "一"; break;
	case 2: cout << "二"; break;
	case 3: cout << "三"; break;
	case 4: cout << "四"; break;
	case 5: cout << "五"; break;
	case 6: cout << "六"; break;
	}
	cout << endl;

	// 测试修改日期
	d.setYear(2024);
	d.setMonth(2);
	d.setDate(29);
	d.display();
	cout << " 是星期";
	switch (d.calWeekday()) {
	case 0: cout << "日"; break;
	case 1: cout << "一"; break;
	case 2: cout << "二"; break;
	case 3: cout << "三"; break;
	case 4: cout << "四"; break;
	case 5: cout << "五"; break;
	case 6: cout << "六"; break;
	}
	cout << endl;

	// 测试非法日期处理
	d.Init(2023, 2, 30);
	d.display();
	cout << " 是星期";
	switch (d.calWeekday()) {
	case 0: cout << "日"; break;
	case 1: cout << "一"; break;
	case 2: cout << "二"; break;
	case 3: cout << "三"; break;
	case 4: cout << "四"; break;
	case 5: cout << "五"; break;
	case 6: cout << "六"; break;
	}
	cout << endl;

	return 0;
}