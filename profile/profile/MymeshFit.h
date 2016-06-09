#pragma once
#include <vector>
#include <iostream>
#include "global.h"

using namespace std;


#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#define MAX_SIZE 2500
#define REPEATTIME 8
#define POB 0.2
#define POP 0.8

static float arrayl[MAX_SIZE][MAX_SIZE];



class MymeshFit
{
	
public:
	int Lrow;//����L������
	int Lcol;//����L������


	MymeshFit();
	void init(QVector<coor> sample, QVector<coor> tri);
	void buildmesh();//���ݵ��������������
	void initedge(struct node *s, struct node *e);  //������������ṹ�ĺ���
	void mvcoding(struct node *point, float L[MAX_SIZE][MAX_SIZE]);   //�������ϡ�����L��laplace����ĺ���
	void allMvcoding();//������������б���
	void Laplacesmooth();//���������laplaceƽ��
	vector<coor> getlsample();
	vector<float> getL();
	vector<coor> getLaplacemv();
	~MymeshFit();
private:
	vector<coor> lsample;//�������laplace���꼯��
	vector<float> Lm;//����L��������ʽ

	vector<coor> laplacemv;//laplaceƽ���������
	
	int countP;//��¼�����ĸ���
	FILE *fpnode, *fptri;//�������ļ��������ļ�
	struct node *point[MAX_SIZE];//�����
	int trimesh[MAX_SIZE][3];//����
};

