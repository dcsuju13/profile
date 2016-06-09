#pragma once
#include<iostream>
#include "math.h"
#include<vector>

using namespace std;
class matrix
{
public:
	matrix();
	void init(vector<float> a,vector<float> p,int m,int n);//��ʼ��A��b
	void transpose(vector<float> a, int m, int n, vector<float> &b);//�����aת��
	void trmul(vector<float> a, vector<float> b, int m, int n, int k, vector<float> &c);//�������
	int chlk(vector<float> a, int n, int m, vector<float> &d);//ƽ��������Cholesky������ʵ�����ԳƷ�����Ľ�
	void fun(vector<float> r, vector<float> p, int m, int n);//�󳬶����̵���С���˽�
	vector<float> &getX();
	~matrix();
private:
	vector<float> A;//ϵ������A
	int A_row;//A����
	int A_col;//A����
	vector<float> b;
	vector<float> x;//�������
	
};

