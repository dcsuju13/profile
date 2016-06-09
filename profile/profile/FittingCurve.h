#pragma once
#include <QVector>
#include <QPoint>

class FittingCurve
{
public:
	FittingCurve(QVector<QPoint> points);
	~FittingCurve();
	double* getP();
	bool CurveFit();//�������

private:
	void Matrix_T(double *K, int m, int n, double *KT);//���ؾ���K��ת��KT.k[m][n]
	void Matrix_Mul(double *Mul1, int Mul1_m, double *Mul2, int Mul2_n, int nm, double *Mul);////Mul1[Mul1_m][nm]*Mul2[nm][Mul2_n]=Mul������ĳ˷�
	bool Matrix_LU(double *K, int n, double *L, double *U);//�Է���K����LU�ֽ�.�ֽ�ʧ�ܷ���False.�ɹ�����True�Լ��ֽ�õ���L��U
	bool Matrix_Inv(double *K, int n, double *InvK);//����LU�ֽⷽ������K����InvK,K[n][n]
	bool Matrix_Solve(double *K, double *B, int m, int n, double *x);//Kx=B���x��K[m][n]������������С���˽�,B[m][1]
	bool Matrix_PolyFit(double *x, double *y, int X_Y_Number, int Fit_N, double *ks);

	double* p=new double[3];//��������ϵ��
	QVector<QPoint> vec;
};

