#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
private:
	double a, b, c; 
	// 判断边长是否为正数
	bool isPositive() const {
		return (a > 0) && (b > 0) && (c > 0);
	}

	// 获取最长边
	double getMaxSide() const {
		double max = a;
		if (b > max) max = b;
		if (c > max) max = c;
		return max;
	}

public:
	void Init(double sideA, double sideB, double sideC) {
		a = sideA;
		b = sideB;
		c = sideC;
	}

	// 读取边长
	double getSideA() const { return a; }
	double getSideB() const { return b; }
	double getSideC() const { return c; }

	// 设置边长
	void setSideA(double sideA) { a = sideA; }
	void setSideB(double sideB) { b = sideB; }
	void setSideC(double sideC) { c = sideC; }

	// 判断能否构成三角形
	bool isTriangle() const {
		if (!isPositive()) return false;  
		
		return (a + b > c) && (a + c > b) && (b + c > a);
	}

	// 计算周长
	double perimeter() const {
		if (isTriangle()) {
			return a + b + c;
		}
		return 0;  
	}

	// 计算面积
	double area() const {
		if (!isTriangle()) return 0; 

		double p = perimeter() / 2;  
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

	// 判断三角形类型
	int typeTriangle() const {
		if (!isTriangle()) return 0;

		double max = getMaxSide();
		double squareMax = max * max;
		double squareOther = 0;

		// 计算除最长边外另两边的平方和
		if (max == a) {
			squareOther = b * b + c * c;
		}
		else if (max == b) {
			squareOther = a * a + c * c;
		}
		else {
			squareOther = a * a + b * b;
		}

		// 判断类型
		if (fabs(squareMax - squareOther) < 1e-6) { 
			return 1;  // 直角三角形
		}
		else if (squareOther > squareMax) {
			return 2;  // 锐角三角形
		}
		else {
			return 3;  // 钝角三角形
		}
	}
};

// 
int main2() {
	Triangle t;

	// 测试直角三角形
	t.Init(3, 4, 5);
	cout << "三角形(3,4,5):\n";
	cout << "是否为三角形: " << (t.isTriangle() ? "是" : "否") << endl;
	cout << "周长: " << t.perimeter() << endl;
	cout << "面积: " << t.area() << endl;
	switch (t.typeTriangle()) {
	case 1: cout << "类型: 直角三角形\n"; break;
	case 2: cout << "类型: 锐角三角形\n"; break;
	case 3: cout << "类型: 钝角三角形\n"; break;
	default: cout << "类型: 非三角形\n";
	}
	cout << endl;

	// 测试锐角三角形
	t.Init(5, 5, 6);
	cout << "三角形(5,5,6):\n";
	cout << "是否为三角形: " << (t.isTriangle() ? "是" : "否") << endl;
	cout << "周长: " << t.perimeter() << endl;
	cout << "面积: " << t.area() << endl;
	switch (t.typeTriangle()) {
	case 1: cout << "类型: 直角三角形\n"; break;
	case 2: cout << "类型: 锐角三角形\n"; break;
	case 3: cout << "类型: 钝角三角形\n"; break;
	default: cout << "类型: 非三角形\n";
	}
	cout << endl;

	// 测试钝角三角形
	t.Init(2, 3, 4);
	cout << "三角形(2,3,4):\n";
	cout << "是否为三角形: " << (t.isTriangle() ? "是" : "否") << endl;
	cout << "周长: " << t.perimeter() << endl;
	cout << "面积: " << t.area() << endl;
	switch (t.typeTriangle()) {
	case 1: cout << "类型: 直角三角形\n"; break;
	case 2: cout << "类型: 锐角三角形\n"; break;
	case 3: cout << "类型: 钝角三角形\n"; break;
	default: cout << "类型: 非三角形\n";
	}
	cout << endl;

	// 测试非三角形
	t.Init(1, 2, 3);
	cout << "三角形(1,2,3):\n";
	cout << "是否为三角形: " << (t.isTriangle() ? "是" : "否") << endl;
	cout << "周长: " << t.perimeter() << endl;
	cout << "面积: " << t.area() << endl;
	switch (t.typeTriangle()) {
	case 1: cout << "类型: 直角三角形\n"; break;
	case 2: cout << "类型: 锐角三角形\n"; break;
	case 3: cout << "类型: 钝角三角形\n"; break;
	default: cout << "类型: 非三角形\n";
	}

	return 0;
}