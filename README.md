# LongNum-一个用于高精度整数的计算库

LongNum库是一个用于计算高精度整数的库,目前已实现整数的加减乘除

LongNum的核心思想是将一串数字用数组来储存,并通过模拟手算的方式来实现加减乘除.LongNum具有自动扩展数组长度的功能,因此不必手动进行扩充.同时还模拟了STL标准库的一些功能.

LongNum的接口:

构造函数,允许使用const char* 类型,int类型,以及LongNum类型进行构造
LongNum(LongNum & lfs);
LongNum(const char* num);
LongNum(int num);

析构函数,用于清理数据
~LongNum();

