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
//标记状态
#define CENTER 0//点花心
#define CENTER_H 1//中轴高点
#define PROFILE 2//侧曲线
#define CONTOUR 3//单个花瓣轮廓
#define TIP 4//顶点
#define PI 3.1415926


class MyLabel :
	public QLabel
{
public:
	MyLabel(QWidget *parent);
	~MyLabel();
	int option;//操作选择
	bool centered = false;//是否点出花心
	bool keyed = false;//是否执行keypoint
	int getflag = 0;//标记是否执行GetPointAndCaculate(QPoint p);

	void LiveWire(QString filename);
	void canKeyPoint();
	QVector<QPoint> getContour();//返回花瓣轮廓
	QVector<int> getRadius();//返回半径组
	QVector<QPoint> getContour_l();//返回原始左轮廓
	QVector<QPoint> getContour_r();//返回原始右轮廓
	QVector<QPoint> getTippoint();//返回花瓣顶点组

private:
	
	void GetPointAndCaculate(QPoint p);
	void KeyPoint();//按顺序对侧曲线和花瓣轮廓走下来
	void OrderPoint(QVector<QPoint> &c1,QVector<QPoint> &pointset);

	double calangle(float a[2], float b[2]);//计算中轴和y轴反向夹角
	void rotatePoints();//旋转花瓣轮廓和侧曲线到中轴和y轴平行
	QPoint rotate(QPoint src,double rangle);//旋转单个点操作
	QVector<QPoint> deleteRepeat(QVector<QPoint> pointset);//删去高度相同的点，即每个高度只保留一个点
	QVector<int> calradius();//求解半径组

	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	QString fileimage;//图片路径
	QPoint a;//当前鼠标点
	QPoint f_o;//花心
	QPoint fh_o;//中轴高点
	QPoint tip_p = QPoint();//完整花瓣的顶点
	QPoint sp = QPoint();
	QVector<QPoint> contour;//轮廓点(无序-->从高到低左右轮廓点)
	QVector<QPoint> contour_l;//原始左轮廓
	QVector<QPoint> contour_r;//原始右轮廓
	QVector<QPoint> c_profile;//侧轮廓
	QVector<QPoint> tippoint;//顶点
	QVector<int> radius;//半径组
	Mat RGB;
	Mat OUT1;
	Mat G;
	Mat F;
	double gmax = 0;
	Mat CANNY;
	Mat LOG;
	double angle;//中轴和y轴反向夹角
	int h;//高度

	bool profeiled = false;//是否提取过侧轮廓
	bool contoured = false;//是否提取过轮廓
	bool tipped = false;//是否点出所有顶点


};

