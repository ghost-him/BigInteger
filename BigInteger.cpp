#include "BigInteger.h"
BigInteger::BigInteger() {
    // 默认初始值为 0
    std::string temp = "0";
    new (this)BigInteger((std::string)temp);
}

BigInteger::BigInteger(const BigInteger& input_parameters) {
    // 完全复制输入的值
    _expansion_rate = input_parameters._expansion_rate;
    _sign = input_parameters._sign;
    _size = input_parameters._size;
    _point = input_parameters._point;
}

BigInteger::BigInteger(const std::string& input_parameters) {
    VALID_INDEX index = 0;
    int sg = 0;
    if ((sg = check_is_valid(input_parameters, index), sg) == -1) {
        throw("invalid numbers!");
    }
    if (sg == 1) {
        _sign = true;
    }
    _point.resize(input_parameters.size() * _expansion_rate);
    VALID_INDEX i, j;
    if (index == input_parameters.size()) {
        _point[0] = 0;
        this->_size = 1;
    }
    else {

        for (i = 0, j = input_parameters.size() - 1; j >= index; j--, i++) {
            _point[i] = input_parameters[j] - '0';
        }
        set_size(i);    // 设置当前的长度
    }
}

BigInteger::BigInteger(const char* input_parameters) {
    std::string temp(input_parameters);
    new (this)BigInteger((std::string)temp);
}

BigInteger::BigInteger(const long long input) {
    // 特殊的构造方法, 用于优化速度
    long long t = input;
    if (t < 0) {
        _sign = true;
        t = -t;
    }
    while (t) {
        (*this).push_back(t % 10);
        t /= 10;
    }
}

BigInteger::~BigInteger() {
    // if (_point != nullptr) {
    //     delete _point;
    //     _point = nullptr;
    // }
}

void BigInteger::operator+= (BigInteger& input_parameters) {
    (*this) = (*this) + input_parameters;
}

void BigInteger::operator+= (long long input_parameters) {
    BigInteger temp = input_parameters;
    (*this) = (*this) + temp;
}

BigInteger BigInteger::operator++(void) {
    (*this) += 1;
    return (*this);
}

BigInteger BigInteger::operator++(int) {
    BigInteger res = (*this);
    (*this) += 1;
    return res;
}

void BigInteger::operator-= (BigInteger& input_parameters) {
    (*this) = (*this) - input_parameters;
}

void BigInteger::operator-= (long long input_parameters) {
    BigInteger temp = input_parameters;
    (*this) = (*this) - temp;
}

BigInteger BigInteger::operator--(void) {
    (*this) -= 1;
    return (*this);
}

BigInteger BigInteger::operator--(int) {
    BigInteger res = (*this);
    (*this) -= 1;
    return res;
}

void BigInteger::operator*= (BigInteger& right) {
    (*this) = (*this) * right;
}

void BigInteger::operator*= (long long right) {
    BigInteger temp = right;
    (*this) = (*this) * temp;
}

void BigInteger::operator/= (BigInteger& right) {
    (*this) = (*this) / right;
}

void BigInteger::operator/= (long long right) {
    BigInteger temp = right;
    (*this) = (*this) / temp;
}

void BigInteger::operator%= (BigInteger& right) {
    (*this) = (*this) % right;
}

void BigInteger::operator%= (long long right) {
    BigInteger temp = right;
    (*this) = (*this) % temp;
}

inline short& BigInteger::operator[](VALID_INDEX index) {
    return _point[index];
}

BigInteger::operator long long() {
    // 可以转换成 long long类型
    long long res = 0;
    for (VALID_INDEX i = _size - 1; i >= 0; i--) {
        res = res * 10 + _point[i];
    }
    if (_sign == true) return -res;
    else return res;
}

inline VALID_INDEX BigInteger::size() {
    return this->_size;
}

int BigInteger::check_is_valid(const std::string& input_parameters, VALID_INDEX& valid_index) {
    /**
     * 检查是否是以0开头, 检查是否拥有除了0以外的数字
     *参数:
     *      input_parameters: 检测的字符串
     *      valid_index: 当前字符串的有效位
     * 返回值:
     *      0: 一切正常, 正数
     *      -1: 无效的数字
     *      1: 一切正常, 负数
     */
     // 初始化
    valid_index = 0;
    VALID_INDEX flag = 0;
    // 判断是否为负数
    if (input_parameters[0] == '-') {
        flag = 1;
    }

    for (VALID_INDEX index = flag, len = input_parameters.size(); index < len; index++) {
        if (input_parameters[index] > '9' || input_parameters[index] < '0') {
            flag = -1;
            return flag;
        }
    }

    valid_index = flag;
    while (input_parameters[valid_index] == '0') {
        valid_index++;
    }
    return flag;
}

void BigInteger::regular() {
    VALID_INDEX size = (*this).size();
    for (VALID_INDEX i = size - 1; i >= 0; i--) {
        if (_point[i] == 0) {
            size--;
        }
        else {
            break;
        }
    }
    if (size == 0) {    // 若全为0, 即整体为0;
        (*this).set_size(1);    // 归为0
        _sign = false;          // 变成正数
    }
    else {
        (*this).set_size(size);
    }
}

inline void BigInteger::set_size(VALID_INDEX size) {
    this->_size = size;
}

inline void BigInteger::resize(int size, short val) {
    _point.resize(size, val);
}

BigInteger BigInteger::add(BigInteger& left, BigInteger& right) {
    /**
    * 内置的函数, 用来计算两个数字的绝对值, 无视正负号
    * 待优化: 如何使用更小的时间开销完成
    */
    if (left.size() < right.size()) return left.add(right, left);

    BigInteger res;
    res.resize(left.size() + 1, 0);
    short progression = 0;
    VALID_INDEX i, len;
    for (i = 0, len = left.size(); i < len; i++) {
        progression += left[i];
        if (i < right.size()) {
            progression += right[i];
        }
        res[i] = progression % 10;
        progression /= 10;
    }
    res.set_size(i + 1);
    if (progression) {
        res[i] = progression;
    }
    res.regular();
    return res;
}

BigInteger BigInteger::minus(BigInteger& left, BigInteger& right) {
    // left >= right >= 0
    BigInteger res;
    VALID_INDEX max_index = left.size() > right.size() ? left.size() : right.size();
    res.resize(max_index, 0);
    short progression = 0;
    for (int i = 0, len = max_index; i < len; i++) {
        progression = left[i] - progression;
        if (i < right.size()) progression -= right[i];
        res[i] = (progression + 10) % 10;
        if (progression < 0)
            progression = 1;
        else
            progression = 0;
    }
    res.set_size(max_index);
    res.regular();
    return res;
}

BigInteger BigInteger::mul(BigInteger& left, BigInteger& right) {
    BigInteger res;
    VALID_INDEX max_size = left.size() + right.size();
    res.resize(max_size + 1, 0);
    for (VALID_INDEX l_index = 0; l_index < left.size(); l_index++) {
        int progression = 0;
        VALID_INDEX res_idx = l_index;
        for (VALID_INDEX r_index = 0; r_index < right.size(); r_index++, res_idx++) {
            progression += right[r_index] * left[l_index];
            progression += res[res_idx];
            res[res_idx] = progression % 10;
            progression /= 10;
        }
        if (progression) {
            res[res_idx] = progression;
        }
    }
    res.set_size(max_size);
    res.regular();
    return res;
}

BigInteger BigInteger::div(BigInteger& left, BigInteger& right, BigInteger& remainder) {
    BigInteger res;
    res.resize(left.size() + 1, 0);
    BigInteger progression = "0";
    for (VALID_INDEX l_index = left.size() - 1; l_index >= 0; l_index--) {
        progression.push_front(left[l_index]);
        progression.regular();
        int val = 0;
        while (progression >= right) {
            val++;
            progression -= right;
        }
        res[l_index] = val;
    }
    res.set_size(left.size() + 1);
    res.regular();
    progression.regular();
    remainder = progression;
    return res;
}

inline void BigInteger::pop_back() {
    _point.pop_back();
    _size--;
}

inline void BigInteger::pop_front() {
    _point.pop_front();
    _size--;
}

inline void BigInteger::push_back(short input) {
    _point.push_back(input);
    _size ++;
}

inline void BigInteger::push_front(short input) {
    _point.push_front(input);
    _size ++;
}

bool BigInteger::abs_compare(BigInteger& right) {
    if ((*this).size() != right.size()) {
        return (*this).size() > right.size();
    }
    for (int i = (*this).size() - 1; i >= 0; i--) {
        if ((*this)[i] != right[i])
            return (*this)[i] > right[i];
    }
    // 若完全一样, 则为false
    return false;
}

std::ostream& operator<< (std::ostream& outstream, const BigInteger& output) {
    BigInteger temp = output;
    return operator<<(outstream, temp);
}

std::ostream& operator<< (std::ostream& outstream, BigInteger& output) {
    std::string temp(output.size(), '0');
    VALID_INDEX index = 0;
    for (; index < output.size(); index++) {
        temp[index] = output[index] + '0';
    }
    std::reverse(temp.begin(), temp.end());
    if (output._sign) {
        outstream << '-';
    }
    outstream << temp;
    return outstream;
}

const BigInteger operator+ (BigInteger& left, BigInteger& right) {
    BigInteger res;
    if (left._sign == right._sign) {
        res = res.add(left, right);
        res._sign = left._sign;
        res.regular();
        return res;
    }
    else {
        if (left.abs_compare(right)) {  // left > right
            res = res.minus(left, right);
            res._sign = res._sign;
        }
        else {                            // left < right
            res = res.minus(right, left);
            res._sign = !left._sign;
        }
        res.regular();
        return res;
    }
}

const BigInteger operator- (BigInteger& left, BigInteger& right) {
    BigInteger res;
    if (left._sign != right._sign) {
        res = left.add(left, right);
        res._sign = left._sign;
        res.regular();
        return res;
    }
    else {
        if (left.abs_compare(right)) {  // left > right
            res = res.minus(left, right);
            res._sign = left._sign;
        }
        else {                            // left < right
            res = res.minus(right, left);
            res._sign = !left._sign;
        }
        res.regular();
        return res;
    }
}

const BigInteger operator* (BigInteger& left, BigInteger& right) {
    BigInteger res;
    res = res.mul(left, right);
    if (left._sign != right._sign) {    // 若为异号, 则res为负数
        res._sign = true;
    }
    res.regular();
    return res;
}

const BigInteger operator/ (BigInteger& left, BigInteger& right) {
    BigInteger res, re;
    if ((long long)right == 0)
        throw("zero error");
    res = res.div(left, right, re);
    if (left._sign != right._sign)
        res._sign = true;
    return res;
}

const BigInteger operator% (BigInteger& left, BigInteger& right) {
    BigInteger res, re;
    if ((long long)right == 0) throw("zero error");
    res = res.div(left, right, re);
    if (left._sign != right._sign)
        re._sign = true;
    return re;
}

const BigInteger operator+ (BigInteger& left, long long right) {
    BigInteger temp = right;
    return left + temp;
}

const BigInteger operator- (BigInteger& left, long long right) {
    BigInteger temp = right;
    return left - temp;
}

const BigInteger operator* (BigInteger& left, long long right) {
    BigInteger temp = right;
    return left * temp;
}

const BigInteger operator/ (BigInteger& left, long long right) {
    BigInteger temp = right;
    return left / temp;
}

const BigInteger operator% (BigInteger& left, long long right) {
    BigInteger temp = right;
    return left % temp;
}

bool operator==(const BigInteger& left, BigInteger& right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    return temp == right;
}

bool operator>(const BigInteger& left, BigInteger& right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    return temp > right;
}

bool operator>=(const BigInteger& left, BigInteger& right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    return temp >= right;
}

bool operator<(const BigInteger& left, BigInteger& right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    return temp < right;
}

bool operator<=(const BigInteger& left, BigInteger& right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    return temp <= right;
}

bool operator==(const BigInteger& left, long long right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    BigInteger num = right;
    return temp == num;
}

bool operator>(const BigInteger& left, long long right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    BigInteger num = right;
    return temp > num;
}

bool operator>=(const BigInteger& left, long long right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    BigInteger num = right;
    return temp >= num;
}

bool operator<(const BigInteger& left, long long right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    BigInteger num = right;
    return temp < num;
}

bool operator<=(const BigInteger& left, long long right) {
    BigInteger & temp = const_cast<BigInteger &>(left);
    BigInteger num = right;
    return temp <= num;
}

bool operator==(BigInteger& left, BigInteger& right) {
    if (left._sign != right._sign) return false;
    if (left.size() != right.size()) return false;
    for (VALID_INDEX i = 0, len = right.size(); i < len; i++) {
        if (left[i] != right[i])
            return false;
    }
    return true;
}

bool operator>(BigInteger& left, BigInteger& right) {
    if (left._sign != right._sign) {       // 若为异号
        if (left._sign == false)           // 若当前的数为正数
            return true;
        else
            return false;                   // 若当前的数为负数
    }
    else {                                // 若为同号
        if (left._sign == false) {         // 若为正数
            return left.abs_compare(right);

        }
        else {                            // 若为负数
            return !left.abs_compare(right);
        }
    }
    return true;    // 没用, 仅仅是用来消除编译器的警报
}

bool operator>=(BigInteger& left, BigInteger& right) {
    return left == right || left > right;
}

bool operator<(BigInteger& left, BigInteger& right) {
    return !(left >= right);
}

bool operator<=(BigInteger& left, BigInteger& right) {
    return !(left > right);
}

bool operator==(BigInteger& left, long long right) {
    return (long long)left == right;
}

bool operator>(BigInteger& left, long long right) {
    return (long long)left > right;
}

bool operator>=(BigInteger& left, long long right) {
    return (long long)left >= right;
}

bool operator<(BigInteger& left, long long right) {
    return (long long)left < right;
}

bool operator<=(BigInteger& left, long long right) {
    return (long long)left <= right;
}
