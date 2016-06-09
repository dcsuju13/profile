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

	void buildmesh();//��������
	int meshfitting();//�������
	void buildall();//�������л��������

	QVector<coor> getContour();//��ȡcontourp
	void setContour_l(QVector<QPoint> c);//����ԭʼ������
	void setContour_r(QVector<QPoint> c);//����ԭʼ������
	void setTippoint(QVector<QPoint> t);//���û��궥������ά����
	QVector<coor> getSample();//��ȡ������
	QVector<coor> getTrimesh();//��ȡ����
	MyMesh getmesh();//��ȡ����
	MyMesh getAll_mesh();//��ȡ����
private:
	QVector<coor> getSamplePoints();//��ò�����
	QVector<coor> trimesh();//��������

	QVector<coor> calnewsample(vector<int> &H,vector<coor> &u);//���µ�������
	void buildmesh(QVector<coor> sample);//��������(���أ�ָ��������)

	
	double calangle(float a1[2],float a2[2]);//��a1��ʱ����ת��a2����ת��
	QPoint rotate(float src[2],double angle);//����y����ת

	QVector<coor> contourp;//��������������
	QVector<QPoint> contour_l, contour_r;//ԭʼ��������
	QVector<coor> meshp;//�������������
	QVector<coor> trip;//������������
	QVector<int> radius;//�뾶��
	QVector<coor> tippoint;//���궥������ά����
	MyMesh petal_mesh;//��������ֻ���浱ǰ����
	MyMesh all_mesh;//��������

};

