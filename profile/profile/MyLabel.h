#pragma once
#include "qlabel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FittingCurve.h"
#include "global.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
//���״̬
#define CENTER 0//�㻨��
#define CENTER_H 1//����ߵ�
#define PROFILE 2//������
#define CONTOUR 3//������������
#define TIP 4//����
#define PI 3.1415926


class MyLabel :
	public QLabel
{
public:
	MyLabel(QWidget *parent);
	~MyLabel();
	int option;//����ѡ��
	bool centered = false;//�Ƿ�������
	bool keyed = false;//�Ƿ�ִ��keypoint
	int getflag = 0;//����Ƿ�ִ��GetPointAndCaculate(QPoint p);

	void LiveWire(QString filename);
	void canKeyPoint();
	QVector<QPoint> getContour();//���ػ�������
	QVector<int> getRadius();//���ذ뾶��
	QVector<QPoint> getContour_l();//����ԭʼ������
	QVector<QPoint> getContour_r();//����ԭʼ������
	QVector<QPoint> getTippoint();//���ػ��궥����

private:
	
	void GetPointAndCaculate(QPoint p);
	void KeyPoint();//��˳��Բ����ߺͻ�������������
	void OrderPoint(QVector<QPoint> &c1,QVector<QPoint> &pointset);

	double calangle(float a[2], float b[2]);//���������y�ᷴ��н�
	void rotatePoints();//��ת���������Ͳ����ߵ������y��ƽ��
	QPoint rotate(QPoint src,double rangle);//��ת���������
	QVector<QPoint> deleteRepeat(QVector<QPoint> pointset);//ɾȥ�߶���ͬ�ĵ㣬��ÿ���߶�ֻ����һ����
	QVector<int> calradius();//���뾶��

	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	QString fileimage;//ͼƬ·��
	QPoint a;//��ǰ����
	QPoint f_o;//����
	QPoint fh_o;//����ߵ�
	QPoint tip_p = QPoint();//��������Ķ���
	QPoint sp = QPoint();
	QVector<QPoint> contour;//������(����-->�Ӹߵ�������������)
	QVector<QPoint> contour_l;//ԭʼ������
	QVector<QPoint> contour_r;//ԭʼ������
	QVector<QPoint> c_profile;//������
	QVector<QPoint> tippoint;//����
	QVector<int> radius;//�뾶��
	Mat RGB;
	Mat OUT1;
	Mat G;
	Mat F;
	double gmax = 0;
	Mat CANNY;
	Mat LOG;
	double angle;//�����y�ᷴ��н�
	int h;//�߶�

	bool profeiled = false;//�Ƿ���ȡ��������
	bool contoured = false;//�Ƿ���ȡ������
	bool tipped = false;//�Ƿ������ж���


};

