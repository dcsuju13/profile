#pragma once
#include <QVector>
#include <QPoint>
#include <vector>
#include "global.h"
#include "MymeshFit.h"
#include "matrix.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

// -------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
// ----------------------------------------------------------------------------
typedef OpenMesh::TriMesh_ArrayKernelT<>  MyMesh;

#define PI 3.1415926

class model
{
public:
	model();
	model(QVector<QPoint> c,QVector<int> r);
	~model();

	void buildmesh();//生成网格
	int meshfitting();//网格变形
	void buildall();//生成所有花瓣的网格

	QVector<coor> getContour();//获取contourp
	void setContour_l(QVector<QPoint> c);//设置原始左轮廓
	void setContour_r(QVector<QPoint> c);//设置原始右轮廓
	void setTippoint(QVector<QPoint> t);//设置花瓣顶点组三维坐标
	QVector<coor> getSample();//获取样本点
	QVector<coor> getTrimesh();//获取索引
	MyMesh getmesh();//获取网格
	MyMesh getAll_mesh();//获取网格
private:
	QVector<coor> getSamplePoints();//获得采样点
	QVector<coor> trimesh();//生成索引

	QVector<coor> calnewsample(vector<int> &H,vector<coor> &u);//求新的样本点
	void buildmesh(QVector<coor> sample);//生成网格(重载，指定样本点)

	
	double calangle(float a1[2],float a2[2]);//求a1逆时针旋转到a2的旋转角
	QPoint rotate(float src[2],double angle);//点绕y轴旋转

	QVector<coor> contourp;//单个花瓣轮廓点
	QVector<QPoint> contour_l, contour_r;//原始左右轮廓
	QVector<coor> meshp;//单个花瓣采样点
	QVector<coor> trip;//单个花瓣索引
	QVector<int> radius;//半径组
	QVector<coor> tippoint;//花瓣顶点组三维坐标
	MyMesh petal_mesh;//花瓣网格（只保存当前网格）
	MyMesh all_mesh;//完整网格

};

