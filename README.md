# BigInteger

> 主要是看c++没有库来支持高精度, 就自己手搓一个库
>
> 将LongNum更名为BigInteger, 使得与java中的高精度一样



**与上一代的 LongNum库的对比:**

* 代码减少了一半 — LongNum库大概1000行的代码, 重复的代码较多, 效率低下
* 功能更强大 — 不但支持加减乘除还支持取余(均为高精度)



## 实现的逻辑

底层为 `std::deque<short>` 类型的一个容器, 然后以**倒序**存放数字的不同的位数. 即第 0 位存放个位, 第 1 位存放十位 … 



目前支持的函数有:

```
// 加法运算
void operator+= (BigInteger&);
void operator+= (long long);
BigInteger operator++(void);         	// 前置运算符
BigInteger operator++(int);    				// 后置运算符

// 减法运算
void operator-= (BigInteger&);
void operator-= (long long);
BigInteger operator--(void);    			// 前置运算符
BigInteger operator--(int);    				// 后置运算符

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
operator long long();					// 可以将自己转换为一个long long 类型

// 其他函数
inline VALID_INDEX size();     // 返回当前的长度
```

`VALID_INDEX`类型为`long long`类型, 用来描述`deque`中的下标的最大值, 即`BigInteger`类型的**位数**

加 `+` `+=` 减 `-` `-=` 乘 `*` `*=` 除 `/` `/=`  取余 `%` `%=` 均支持 `BigInteger`类型和 `long long`类型

同时: `BigInteger / BigInteger` 的**相除和取余**可以类比为 `int / int` 的**相除和取余**

即,可以实现一下操作

```
BigInteger a = 5, b = "123456";
```

```
// 加
a += b;
a = a + b;
a = a + 123;
a = b + 456;
a ++;
++a;
```

```
// 减
a -= b;
a = a - b;
a = a - 123;
a = b - 456;
a --;
--a;
```

```
// 乘
a *= b;
a = a * b;
a = a * 123;
a = b * 456;
```

```
// 除
a /= b;
a = a / b;
a = a / 123;
a = b / 456;
```

```
取余
a %= b;
a = a % b;
a = a % 123;
a = b % 456;
```

```
// 取得a的位数的长度
VALID_INDEX len = a.size();
// 取得个位数
int a = a[0];	
```

```
// 判断
a >= b
a > b
a == b
a != b
a <= b
a < b
```







