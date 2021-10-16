# LongNum-一个用于高精度整数的计算库

LongNum库是一个用于计算高精度整数的库,目前已实现整数的加减乘除

LongNum的核心思想是将一串数字用数组来储存,并通过模拟手算的方式来实现加减乘除.LongNum具有自动扩展数组长度的功能,因此不必手动进行扩充.同时还模拟了STL标准库的一些功能.

LongNum的接口:

构造函数,允许使用const char* 类型,int类型,以及LongNum类型进行构造

析构函数,用于清理数据

~LongNum();

重载运算符+=,-=,++,--,<,<=,==,>,>=以及[],<<

允许通过使用[]运算符访问单个元素

自定义数据类型的转换,支持将LongNum类型转换成int类型

定义了输出函数,默认为cout,允许更改输出流	void print(std::ostream& ost = std::cout);

定义了在前端插入和后端插入的接口,接收的参数为int类型,注意,前端插入的效率比较低

定义了节省空间版本的乘除和取余,当两个数字的大小比较接近时,运算速度较快,空间复杂度为O(1)
spaceSavingMulti 乘   spaceSavingDivi 除   spaceSavingRema 取余

可以使用size()函数返回当前数字的长度,使用max_size()函数返回最大数字的长度

定义了伪迭代器
模拟了随机访问迭代器,常量迭代器以及反向迭代器.所有的迭代器均返回int* 类型的指针(常量迭代器返回 const int*) Iterator_begin指向数组的第一个,Iterator_end指向数组接下来应该写入的元素.

定义了调试函数,返回当前元素的地址,数据的地址,数据的值,数据的大小和数组的长度

定义了求二进制的函数,返回一个int* 的变量,指向的是int类型的数组的首地址,使用以后要注意delete[] 


