#pragma once
#include<iostream>
class LongNum
{
	friend std::ostream& operator<<(std::ostream& ost, const LongNum& num);
public:
	LongNum(LongNum & lfs);//构造函数,可用LongNum,const char*,int类型创建
	LongNum(const char* num);
	LongNum(int num);

	operator int();//自定义数据类型转换为int类型

	~LongNum();//析构函数

	LongNum& operator+=(LongNum &lfs);//重载加法运算符
	LongNum& operator+=(const char * lfs);
	LongNum& operator+=(int num);
	LongNum operator++();//前置版本;
	LongNum operator++(int);//后置版本

	LongNum& operator-=(LongNum &lfs);//
	LongNum& operator-=(const char* lfs);
	LongNum& operator-=(int num);
	LongNum operator--();//前置版本;
	LongNum operator--(int);//后置版本

	LongNum& operator*=(LongNum& lfs);
	LongNum& operator*=(const char* num);
	LongNum& operator*=(int num);

	LongNum& operator/=(LongNum& lfs);
	LongNum& operator/=(const char* lfs);
	LongNum& operator/=(int num);

	LongNum& operator=( LongNum& lfs);
	LongNum& operator=(const char* num);
	LongNum& operator=(int num);

	bool operator<( LongNum& lfs);
	bool operator<=(LongNum& lfs);
	bool operator==( LongNum& lfs);
	bool operator!=(LongNum& lfs);
	bool operator>( LongNum& lfs);
	bool operator>=(LongNum& lfs);

	bool operator<(const char* lfs);
	bool operator<=(const char* lfs);
	bool operator==(const char * lfs);
	bool operator!=(const char* lfs);
	bool operator>(const char* lfs);
	bool operator>=(const char* lfs);

	bool operator<(int num);
	bool operator<=(int num);
	bool operator==(int num);
	bool operator!=(int num);
	bool operator>(int num);
	bool operator>=(int num);


	int& operator[](int index);

	void print(std::ostream& ost = std::cout);

	void push_back(int num);
	void push_front(int num);

	LongNum& spaceSavingMulti(LongNum& lfs);
	LongNum& spaceSavingDivi(LongNum& lfs);
	LongNum& spaceSavingRema(LongNum& lfs);
	int size();//返回实际长度
	int max_size();//返回目前可储存的最大长度

	//迭代器
	int* begin();
	int* end();
	const int* cbegin();
	const int* cend();
	int* rbegin();
	int* rend();

	void debug();
	int* getBinArr();
protected:
	class intToChar//整型转换为字符串
	{
	public:
		intToChar(int num);
		~intToChar();
		operator const char* ();
	private:
		char* re;
	};

private:
	int* data=nullptr;//数据存放位置
	int getLength(const char * T);//获取长度
	int length=0;//长度
	int maxLen=0;//最大长度
	bool sign = false;//默认为正

	LongNum& add(LongNum& lfs);
	LongNum& minus(LongNum& lfs);
	LongNum& absMin(LongNum& lfs);//求绝对值的最小值
	

	void addspace(int num);//增加空间
	void move_back(int num);//后退
	void move_forward(int num);//用于消除前方的0,不会更改任何其他变量
	void clearZero();//清除前缀的0

	int* Iterator_begin = nullptr;//迭代器首
	int* Iterator_end= nullptr;//迭代器尾
	
	void create(const char* num);//创建


};


