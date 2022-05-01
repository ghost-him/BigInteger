
#pragma once
#include <deque>
#include <string>
#include <algorithm>

typedef long long VALID_INDEX;     // 用来描述可以被表示的范围

class BigInteger {
    friend std::ostream& operator<< (std::ostream&, BigInteger&);
    friend std::ostream& operator<< (std::ostream&, const BigInteger&);
    friend const BigInteger operator+ (BigInteger&, BigInteger&);
    friend const BigInteger operator- (BigInteger&, BigInteger&);
    friend const BigInteger operator* (BigInteger&, BigInteger&);
    friend const BigInteger operator/ (BigInteger&, BigInteger&);
    friend const BigInteger operator% (BigInteger&, BigInteger&);

    friend bool operator==(BigInteger&, BigInteger&);
    friend bool operator>(BigInteger&, BigInteger&);
    friend bool operator>=(BigInteger&, BigInteger&);
    friend bool operator<(BigInteger&, BigInteger&);
    friend bool operator<=(BigInteger&, BigInteger&);

public:
    // 构造函数
    BigInteger();
    BigInteger(const BigInteger&);
    BigInteger(const std::string&);
    BigInteger(const char*);
    BigInteger(const long long);
    // 析构函数
    ~BigInteger();
    // 加法运算
    void operator+= (BigInteger&);
    void operator+= (long long);
    BigInteger operator++(void);         // 前置运算符
    BigInteger operator++(int);    // 后置运算符
    // 减法运算
    void operator-= (BigInteger&);
    void operator-= (long long);
    BigInteger operator--(void);         // 前置运算符
    BigInteger operator--(int);    // 后置运算符
    // 乘法运算
    void operator*= (BigInteger&);
    void operator*= (long long);
    // 除法运算
    void operator/= (BigInteger&);
    void operator/= (long long);
    // 取余运算符
    void operator%= (BigInteger&);
    void operator%= (long long);
    // 重载运算符
    inline short& operator[](VALID_INDEX);
    // 自定义类型转换
    operator long long();
    // 其他函数
    inline VALID_INDEX size();     // 返回当前的长度


private:
    // 检查输入是否合法
    int check_is_valid(const std::string&, VALID_INDEX& valid_index);
    void regular();                     // 用于规范自身数字的合法性
    inline void set_size(VALID_INDEX size);
    inline void resize(int size, short);

    BigInteger add(BigInteger&, BigInteger&);
    BigInteger minus(BigInteger&, BigInteger&);
    BigInteger mul(BigInteger&, BigInteger&);
    BigInteger div(BigInteger&, BigInteger&, BigInteger&);

    inline void pop_back();        // 删除最高次数
    inline void pop_front();       // 删除个位
    inline void push_back(short);  // 添加最高次数
    inline void push_front(short); // 添加最后的次数

    bool abs_compare(BigInteger&);     // 若大于,则返回true

    VALID_INDEX _size = 0;
    std::deque<short> _point;     // 指向在堆中的数组
    int _expansion_rate = 2;        // 扩张速率, 默认为2
    bool _sign = false;              // 符号的标记, false为正, true为负

};

std::ostream& operator<< (std::ostream&, BigInteger&);
std::ostream& operator<< (std::ostream&, const BigInteger&);

const BigInteger operator+ (BigInteger&, BigInteger&);
const BigInteger operator- (BigInteger&, BigInteger&);
const BigInteger operator* (BigInteger&, BigInteger&);
const BigInteger operator/ (BigInteger&, BigInteger&);
const BigInteger operator% (BigInteger&, BigInteger&);

const BigInteger operator+ (BigInteger&, long long);
const BigInteger operator- (BigInteger&, long long);
const BigInteger operator* (BigInteger&, long long);
const BigInteger operator/ (BigInteger&, long long);
const BigInteger operator% (BigInteger&, long long);

bool operator==(const BigInteger&, BigInteger&);
bool operator>(const BigInteger&, BigInteger&);
bool operator>=(const BigInteger&, BigInteger&);
bool operator<(const BigInteger&, BigInteger&);
bool operator<=(const BigInteger&, BigInteger&);

bool operator==(const BigInteger&, long long);
bool operator>(const BigInteger&, long long);
bool operator>=(const BigInteger&, long long);
bool operator<(const BigInteger&, long long);
bool operator<=(const BigInteger&, long long);

bool operator==(BigInteger&, BigInteger&);
bool operator>(BigInteger&, BigInteger&);
bool operator>=(BigInteger&, BigInteger&);
bool operator<(BigInteger&, BigInteger&);
bool operator<=(BigInteger&, BigInteger&);

bool operator==(BigInteger&, long long);
bool operator>(BigInteger&, long long);
bool operator>=(BigInteger&, long long);
bool operator<(BigInteger&, long long);
bool operator<=(BigInteger&, long long);
