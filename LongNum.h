#pragma once
#include<iostream>
class LongNum
{
	friend std::ostream& operator<<(std::ostream& ost, const LongNum& num);
public:
	LongNum(LongNum & lfs);//���캯��,����LongNum,const char*,int���ʹ���
	LongNum(const char* num);
	LongNum(int num);

	operator int();//�Զ�����������ת��Ϊint����

	~LongNum();//��������

	LongNum& operator+=(LongNum &lfs);//���ؼӷ������
	LongNum& operator+=(const char * lfs);
	LongNum& operator+=(int num);
	LongNum operator++();//ǰ�ð汾;
	LongNum operator++(int);//���ð汾

	LongNum& operator-=(LongNum &lfs);//
	LongNum& operator-=(const char* lfs);
	LongNum& operator-=(int num);
	LongNum operator--();//ǰ�ð汾;
	LongNum operator--(int);//���ð汾

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
	int size();//����ʵ�ʳ���
	int max_size();//����Ŀǰ�ɴ������󳤶�

	//������
	int* begin();
	int* end();
	const int* cbegin();
	const int* cend();
	int* rbegin();
	int* rend();

	void debug();
	int* getBinArr();
protected:
	class intToChar//����ת��Ϊ�ַ���
	{
	public:
		intToChar(int num);
		~intToChar();
		operator const char* ();
	private:
		char* re;
	};

private:
	int* data=nullptr;//���ݴ��λ��
	int getLength(const char * T);//��ȡ����
	int length=0;//����
	int maxLen=0;//��󳤶�
	bool sign = false;//Ĭ��Ϊ��

	LongNum& add(LongNum& lfs);
	LongNum& minus(LongNum& lfs);
	LongNum& absMin(LongNum& lfs);//�����ֵ����Сֵ
	

	void addspace(int num);//���ӿռ�
	void move_back(int num);//����
	void move_forward(int num);//��������ǰ����0,��������κ���������
	void clearZero();//���ǰ׺��0

	int* Iterator_begin = nullptr;//��������
	int* Iterator_end= nullptr;//������β
	
	void create(const char* num);//����


};


