#include"LongNum.h"

LongNum::LongNum(const char* num)
{
	create(num);
}

LongNum::LongNum(int num)
{
	intToChar temp (num);
	create(temp);
}

LongNum::LongNum(LongNum& lfs)
{
	data = new int[lfs.length * 2];

	Iterator_begin = data;//初始化所有条件
	Iterator_end = data;
	length = 0;
	maxLen = lfs.length * 2;
	sign = lfs.sign;

	//复制数据
	int* index = Iterator_begin;//创建一个自己的迭代器
	const int* lfdata = lfs.Iterator_begin;//创建一个对方迭代器
	while (lfdata != lfs.Iterator_end)
	{
		*index = *lfdata;
		lfdata++;
		index++;
	}
	*index = 10;
	Iterator_end = index;
	length = lfs.length;
}

LongNum::~LongNum()
{
	delete[] data;
}

LongNum& LongNum::operator+=(LongNum &lfs)
{
	if (sign == lfs.sign)
		return add(lfs);
	if (&absMin(lfs) == this)
		sign = !sign;
	return minus(lfs);
}

LongNum& LongNum::operator+=(int num)
{
	intToChar temp (num);
	LongNum add(temp);
	*this += add;
	return *this;
}

LongNum& LongNum::operator++()
{
	LongNum temp("1");
	*this += temp;
	return *this;
}

LongNum& LongNum::operator++(int)
{
	auto re = *this;
	operator++();
	return re;
}

LongNum& LongNum::operator-=(LongNum& lfs)
{
	auto addr = &absMin(lfs);

	if (sign != lfs.sign)
		return add(lfs);

	if (addr == this)
		sign = !sign;
	return minus(lfs);
}

LongNum& LongNum::operator--()//前置版本;
{
	LongNum temp("1");
	*this -= temp;
	return *this;
}

LongNum& LongNum::operator--(int)//后置版本
{
	auto re = *this;
	operator--();
	return re;
}

LongNum& LongNum::operator*=(LongNum& lfs)
{

	if (*this == "0" || lfs == "0")//判断0的情况
	{
		*this = "0";
		return *this;
	}

	LongNum temp = "0";//进的位
	LongNum tempdata ("0");//运算的结果
	tempdata.addspace(size() + lfs.size()+1);
	int* index = tempdata.Iterator_begin+ size() + lfs.size()+tempdata.size();//index指向结尾
	tempdata.length--;
	tempdata.Iterator_end = index;
	*index = 10;
	index--;

	LongNum num = *this;//当前的值
	num.sign = false;
	int* inend = lfs.rbegin();//乘的位
	LongNum time = "0";//乘的次数

	while (index != tempdata.rend() && inend != lfs.rend())
	{
		num = *this;//初始化num,消除原本的数字
		num.sign = false;
		time = *inend;//乘的次数

		num.spaceSavingMulti(time);
		if (temp != "0")//加上进的位
		{
			num += temp;
			temp = "0";
		}
		*index = *(num.Iterator_end - 1);//等于num的最后一个数

		num.Iterator_end--;//将最后一个数从num中移除
		*num.Iterator_end = 10;
		num.length--;
		if(num.length!=0)
			temp = num;//将num中的数带到下一次计算中
		tempdata.length++;
		inend--;//移动指针
		index--;//移动指针
	}

	if (temp != "0"&&index != tempdata.rend())//乘数已经没了,但是还有溢出
	{
		int* tempindex = temp.rbegin() ;
		while (tempindex != temp.rend())
		{
			*index = *tempindex;
			tempindex--;
			index--;
			tempdata.length++;
		}
	}
	while (index != tempdata.rend())//讲剩余的空位全部变成0
	{
		*index = 0;
		index--;
		tempdata.length++;
	}
	tempdata.clearZero();//清除0
	*this = tempdata;
	return *this;
}

LongNum& LongNum::operator*=(const char* num)
{
	LongNum temp = num;
	*this *= temp;
	return *this;
}

LongNum& LongNum::operator/=(LongNum& lfs)
{
	LongNum answer("0");//被除数
	LongNum divisor = "0";
	auto index = Iterator_begin;
	LongNum tempdivi("0");//临时变量
	while (index != Iterator_end)//遍历被除数
	{
		if (&divisor.absMin(lfs) == &divisor)//当读取的数字小于除数的时候
		{
			divisor *= "10";
			divisor += *index;
			index++;
			continue;
		}
		else
		{
			//temp = divisor;测验
			tempdivi = divisor;
			answer.push_back(tempdivi.spaceSavingDivi(lfs));

			divisor.spaceSavingRema(lfs);
			if (divisor == "0")//正好整除完
			{
				while (index != Iterator_end)
				{
					index++;
					answer.push_back(0);
				}	
				answer.clearZero();
				*this = answer;
				return *this;
			}
		}
	}
	answer.push_back(divisor.spaceSavingDivi(lfs));
	answer.clearZero();
	*this = answer;
	if (lfs.sign == sign)
		sign = false;
	else
		sign = true;
	return *this;

}

LongNum& LongNum::spaceSavingMulti(LongNum& lfs)
{
	LongNum index = "0";
	if (lfs == index)
	{
		*this = "0";
		return *this;
	}

	if (lfs.sign == sign)
		sign = false;
	else
		sign = true;
	index = "1";
	LongNum tempadd = *this;
	while (&index.absMin(lfs)== &index)
	{
		*this += tempadd;
		++index;
	}
	return *this;
}

LongNum& LongNum::spaceSavingDivi(LongNum& lfs)
{
	LongNum index = "0";
	if (lfs == index)
		throw;
	if (lfs.sign == sign)
		sign = false;
	else
		sign = true;
	LongNum tempmin = lfs;
	while (&absMin(tempmin) == &tempmin)
	{
		tempmin.add( lfs);
		++index;
	}
	*this = index;
	return *this;
}

LongNum& LongNum::spaceSavingRema(LongNum& lfs)
{
	if (lfs == "0")
		throw;

	if (lfs.sign == sign)
		sign = false;
	else
		sign = true;

	LongNum tempmin = lfs;
	tempmin.sign = false;

	while (absMin(tempmin) == tempmin)
	{
		tempmin.add(lfs);
	}
	tempmin.minus(lfs);
	minus(tempmin);//bug-1230-(-1200)

	return *this;

}

int& LongNum::operator[](int index)
{
	if (index < length)
		return *(Iterator_begin + index);
	else
		throw;
}

bool LongNum::operator<( LongNum& lfs)
{
	//判断符号

	if (sign == true && lfs.sign == false)
		return true;
	else if (sign == false && lfs.sign == true)
		return false;

	bool re = false;

	if (&absMin(lfs) == this)
		re = true;
	else
		re = false;

	if (sign == true)//如果是负值,则返回相反值
		return !re;
	else
		return re;

}

bool LongNum::operator<=(LongNum& lfs)
{
	if (*this < lfs || *this == lfs)
		return true;
	else
		return false;
}

bool LongNum::operator==( LongNum& lfs)
{
	if (sign != lfs.sign)
		return false;
	if (length != lfs.length)
		return false;
	auto index = Iterator_begin;
	auto lfsindex = lfs.Iterator_begin;
	while (index != Iterator_end)
	{
		if (*index != *lfsindex)
			return false;
		else
		{
			index++;
			lfsindex++;
		}
	}
	return true;
}

bool LongNum::operator!=(LongNum& lfs)
{
	LongNum temp = lfs;
	return !(*this == temp);
}

bool LongNum::operator==(const char* lfs)
{
	LongNum temp = lfs;
	return *this == temp;
}

bool LongNum::operator!=(const char* lfs)
{
	LongNum temp = lfs;
	return *this != temp;
}

bool LongNum::operator>( LongNum& lfs)
{
	return !(operator<(lfs) || operator==(lfs));
}

bool LongNum::operator>=(LongNum& lfs)
{
	if (*this > lfs || *this == lfs)
		return true;
	else
		return false;
}

LongNum& LongNum::operator=( LongNum & lfs)
{
	if (lfs.length >= this->maxLen)
	{
		int* temp = new int[lfs.length * 2];
		int* de = data;//保存原来数据的位置
		data = temp;//指向新的位置

		Iterator_begin = data;//初始化所有条件
		Iterator_end = data;
		length = 0;
		maxLen = lfs.length * 2;
		sign = lfs.sign;

		delete[] de;//删除原来的数据
	}
	//复制数据
	int* index = Iterator_begin;//创建一个自己的迭代器
	const int* lfdata = lfs.Iterator_begin;//创建一个对方迭代器
	while (lfdata != lfs.Iterator_end)
	{
		*index = *lfdata;
		lfdata++;
		index++;
	}
	*index = 10;
	Iterator_end = index;
	length = lfs.length;
	return *this;
}

LongNum& LongNum::operator=(const char* num)
{
	const char* index = num;
	int lengthT = getLength(num);//字符串的长度,也是之后数组的长度
	if (maxLen <= lengthT)
	{
		int* de = data;
		data = new int[lengthT * 2];

		maxLen = lengthT * 2;
		Iterator_begin = data;
		Iterator_end = data;
		delete[] de;
	}

	int* temp = Iterator_begin;
	//判断是否是负数
	if (*index == '-')
	{
		sign = true;//设定为负
		index++;
	}
	int templength = 0;//用来查看长度
	while (*index != '\0')//将数组拷贝
	{
		if (*index >= '0' && *index <= '9')
		{
			*temp = (*index) - 48;
			temp++;
			index++;
			templength++;
		}
		else
		{
			std::cerr << "赋值报错" << std::endl;
			throw;
		}
	}
	*temp = 10;
	Iterator_end = temp;//初始化尾指针
	length = templength;//初始化长度
	return *this;
	clearZero();
}

LongNum& LongNum::operator=(int num)
{
	intToChar temp(num);
	*this = temp;
	return *this;
}

int LongNum::getLength(const char * T)
{
	int num = 0;
	while (*T != '\0')
	{
		T++;
		num++;
	}
	return num;
}

void LongNum::print(std::ostream & ost)
{
	const int* temp = data;
	if (sign)
		ost << '-';
	while (*temp != 10)
	{
		ost << *temp;
		temp++;
	}

}

int LongNum::size()
{
	return length;
}

int LongNum::max_size()
{
	return maxLen;
}

int* LongNum::begin()
{
	return Iterator_begin;
}

int* LongNum::end()
{
	return Iterator_end;
}

const int* LongNum::cbegin()
{
	const int* temp= Iterator_begin;
	return temp;
}

const int* LongNum::cend()
{
	const int* temp = Iterator_end;
	return temp;
}

int* LongNum::rbegin()
{
	int* temp = Iterator_end - 1;
	return temp;
}

int* LongNum::rend()
{
	int* temp = Iterator_begin - 1;
	return temp;
}

void LongNum::addspace(int num)
{

	int* temp = new int[num+size()];
	int* de = data;
	data = temp;
	int* index = data;
	maxLen = num+size();
	while (Iterator_begin != Iterator_end)
	{
		*index = *Iterator_begin;
		Iterator_begin++;
		index ++ ;
	}
	*index = 10;
	Iterator_end = index;
	Iterator_begin = data;
	delete[] de;
}

void LongNum::move_back(int num)
{
	if (num > maxLen - length-1)
		addspace(maxLen * 2);
	auto index = Iterator_end+num-1;
	while (index != Iterator_begin+num-1)
	{
		*index = *(index - num);
		index--;
	}
	for (int i = num-1; i >= 0; i--)
		*(data + i) = 0;
	Iterator_end = Iterator_end + num;
	*Iterator_end = 10;

}

void LongNum::move_forward(int num)
{
	int* index = Iterator_begin;
	while ((index + num) != Iterator_end)
	{
		*index = *(index + num);
		index++;
	}
	*index = 10;

}

LongNum& LongNum::add(LongNum& lfs)
{
	if (lfs.length >= maxLen-1 || length == maxLen-1)
		addspace(lfs.length * 2);

	if (lfs.length > length)
	{
		move_back(lfs.length - length);
		length = lfs.length;
	}
	int* num1 = rbegin();
	int* num2 = lfs.rbegin();
	int overflow = 0;
	while (num1 != rend() && num2 != lfs.rend())
	{
		*(num1) += *(num2);//相加

		if (overflow)//判断是否需要加1
		{
			*(num1) += 1;
			overflow = 0;
		}

		if (*(num1) > 9)//判断是否溢出
		{
			*(num1) -= 10;
			overflow = 1;
		}
		num1--;
		num2--;
	}

	while (overflow && num1 != rend())//判断是否要加1
	{
		if (overflow)//判断是否需要加1
		{
			*(num1) += 1;
			overflow = 0;
		}

		if (*(num1) > 9)//判断是否溢出
		{
			*(num1) -= 10;
			overflow = 1;
		}
		num1--;
	}
	if (overflow && num1 == rend())
	{
		move_back(1);
		*Iterator_begin = 1;
		length++;
	}
	return *this;
}

LongNum& LongNum::minus(LongNum& lfs)
{
	if (lfs.length >= maxLen-1 || length == maxLen-1)
		addspace(lfs.length * 2);
	LongNum* tempMin = &absMin(lfs);
	LongNum* tempMax = &(*tempMin ==lfs?*this:lfs);//temp为最大值

	int* tempdata = new int[tempMax->length+1];//创建一个最大值的数组

	int* index = tempMax->Iterator_begin;//设置两个用来复制的指针
	int* copy = tempdata;

	while (index != tempMax->Iterator_end)//复制
	{
		*copy = *index;
		index++;
		copy++;
	}
	*copy = 10;

	int* tempEnd = copy;//临时数组的结尾

	//进行减法运算
	index = tempMin->rbegin();//减数的逆迭代器
	copy--;//将copy设置为被减数的逆迭代器的首个位置
	int borrow = 0;
	while (copy != (tempdata - 1) && index != tempMin->rend())
	{
		*copy -= *index;

		if (borrow)//判断是否被借位
		{
			*copy -= 1;
			borrow = 0;
		}
		if (*copy < 0)//判断是否需要借位
		{
			borrow = 1;
			*copy += 10;
		}
		copy--;
		index--;
	}
	while (borrow && copy != (tempdata - 1))
	{
		if (borrow)
		{
			*copy -= 1;
			borrow = 0;
		}
		if (*copy < 0)
		{
			*copy += 10;
			borrow = 1;
		}
		copy--;
	}
	int* de = data;
	data = tempdata;
	Iterator_begin = data;
	Iterator_end = tempEnd;
	length = Iterator_end - Iterator_begin;
	delete[] de;
	clearZero();
	return *this;
}

LongNum& LongNum::absMin(LongNum& lfs)
{

	bool re = false;
	//判断绝对值的大小
	if (length < lfs.length)
		re = true;
	else if (length > lfs.length)
		re = false;
	else
	{
		auto index = Iterator_begin;
		auto lfsindex = lfs.Iterator_begin;
		while (index != Iterator_end)
			if (*index < *lfsindex)
			{
				re = true;
				break;
			}
			else if (*index > *lfsindex)
			{
				re = false;
				break;
			}
			else
			{
				index++;
				lfsindex++;
			}
	}
	if (re)
		return *this;
	else
		return lfs;
}

void LongNum::clearZero()
{
	int num = 0;
	int* index = Iterator_begin;
	while (index != Iterator_end)
	{
		if (*index == 0)
			num++;
		else
			break;
		index++;
	}
	if (num == length)//防止所有位数都为0
	{
		num--;
		sign = false;
	}
	move_forward(num);
	length -= num;
	Iterator_end -= num;
	*Iterator_end = 10;
}

void LongNum::debug()
{
	std::cout << "Addr:" << "  " << this << "  ";
	std::cout << "Data Addr:" << "  " << this->data << "  ";
	std::cout << "Data:" << "  " << *this<< "  ";
	std::cout << "Size:" << "  " << this->length << "  ";
	std::cout << "MaxSize:" << "  " << this->maxLen<< "  ";
}

std::ostream& operator<<(std::ostream& ost, const LongNum& num)
{
	const int* temp = num.data;
	if (num.sign)
		ost << '-';
	while (*temp != 10)
	{
		ost << *temp;
		temp++;
	}
	return ost;
}

int* LongNum::getBinArr()
{
	LongNum temp= *this;//temp为当前的值
	temp.sign = false;//取绝对值
	LongNum start = "1";
	LongNum sum = "0";
	long size = 0;

	while (sum < temp)
	{
		sum += start;
		start += start;
		size++;
		std::cout << sum << std::endl;
	}
	int* re = new int[size + 1];
	int* index = (re + size);
	*index = 10;
	index--;
	LongNum bin = "2";
	start.spaceSavingDivi(bin);//初始化start的值
	while (index != re - 1)
	{
		if (temp >= start)
		{
			temp -= start;
			*index = 1;
		}
		else
		{
			*index = 0;
		}
		start.spaceSavingDivi(bin);
		std::cout << *index << std::endl;
		index--;
	}
	return re;
}

void LongNum::create(const char* num)
{
	const char* index = num;
	int lengthT = getLength(num);//字符串的长度,也是之后数组的长度
	data = new int[lengthT * 2];
	Iterator_begin = data;//初始化首指针
	Iterator_end = data;//初始化尾指针
	maxLen = lengthT * 2;//初始化最大长度

	int* temp = Iterator_begin;
	//判断是否是负数
	if (*index == '-')
	{
		sign = true;//设定为负
		index++;
	}
	int templength = 0;//用来查看长度
	while (*index != '\0')//将数组拷贝
	{
		if (*index >= '0' && *index <= '9')
		{
			*temp = (*index) - 48;
			temp++;
			index++;
			templength++;
		}
		else
		{
			std::cerr << "初始化报错:" <<*index<< std::endl;
			throw;
		}
	}
	*temp = 10;
	Iterator_end = temp;//初始化尾指针
	length = templength;//初始化长度
	clearZero();
}

LongNum::operator int()//内置类型转换
{
	return *Iterator_begin;
}

LongNum::intToChar::intToChar(int num)
{
	int length = 0;
	int temp = num;
	while (temp)//获取长度
	{
		temp /= 10;
		length++;
	}
	if (num == 0)
		length = 1;
	re = new char[length+1];
	*(re + length) = '\0';
	length--;
	if (num == 0)
		*re = 48;
	else
	while (num)
	{
		*(re + length) = (num % 10)+48;
		length--;
		num /= 10;
	}

	for (int i = 0; i < length; i++)
		std::cout << *(re + i) << std::endl;

}

LongNum::intToChar::~intToChar()
{
	delete[] re;
}

LongNum::intToChar::operator const char*()
{
	return re;
}

void LongNum::push_back(int num)
{
	length++;
	if (length >= maxLen - 1)
		addspace(length);
	*Iterator_end = num;
	Iterator_end++;
	*Iterator_end = 10;

}

void LongNum::push_front(int num)
{
	move_back(1);
	*Iterator_begin = num;
	length++;
}

LongNum& LongNum::operator+=(const char* lfs)
{
	LongNum temp = lfs;
	*this += temp;
	return *this;
}

LongNum& LongNum::operator-=(const char* lfs)
{
	LongNum temp = lfs;
	*this -= temp;
	return *this;
}

LongNum& LongNum::operator-=(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	*this -= lfs;
	return *this;
}

LongNum& LongNum::operator*=(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	*this *= lfs;
	return *this;
}

LongNum& LongNum::operator/=(const char* lfs)
{
	LongNum temp = lfs;
	*this /= temp;
	return *this;
}

LongNum& LongNum::operator/=(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	*this /= lfs;
	return *this;
}

bool  LongNum::operator<(const char* lfs)
{
	LongNum temp = lfs;
	return *this<temp;
}

bool  LongNum::operator<=(const char* lfs)
{
	LongNum temp = lfs;
	return *this<=temp;
}

bool  LongNum::operator>(const char* lfs)
{
	LongNum temp = lfs;
	return *this>temp;
}

bool LongNum:: operator>=(const char* lfs)
{
	LongNum temp = lfs;
	return *this>=temp;
}

bool LongNum:: operator<(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	return *this<lfs;
}

bool LongNum:: operator<=(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	return *this <= lfs;
}

bool  LongNum::operator==(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	return *this == lfs;
}

bool LongNum:: operator!=(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	return *this != lfs;
}

bool LongNum:: operator>(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	return *this > lfs;
}

bool  LongNum::operator>=(int num)
{
	intToChar temp(num);
	LongNum lfs(temp);
	return *this >= lfs;
}
