#include "model.h"


model::model()
{
}

model::model(QVector<QPoint> c, QVector<int> r)
{
	contourp.clear();
	//将c保存为三维点
	coor t;
	t.x = c.at(0).x();
	t.y = c.at(0).y();
	t.z = r.at(0);
	contourp.push_back(t);

	for (int i = 1, j = 1; j < r.size() - 1; i = i + 2, j++)
	{
		//高度为i左轮廓点
		t.x = c.at(i).x();
		t.y = c.at(i).y();
		t.z = r.at(j);
		contourp.push_back(t);

		//高度为i右轮廓点
		t.x = c.at(i + 1).x();
		t.y = c.at(i + 1).y();
		t.z = r.at(j);
		contourp.push_back(t);
	}
	t.x = 0;
	t.y = 0;
	t.z = 0;
	contourp.push_back(t);

	radius = r;//半径组
}

model::~model()
{
}

void model::buildmesh()
{
	petal_mesh.clear();//网格更新
	if (contourp.empty())
		return;

	meshp.clear();
	meshp = getSamplePoints();//获取样本点
	trip.clear();
	trip = trimesh();//生成网格索引
	
	//使用openmesh生成ply文件
	//1........
	//generate vertices
	vector<MyMesh::VertexHandle> vhandle;//记录采样点句柄
	for (int i = 0; i < meshp.size(); i++)
	{
		MyMesh::VertexHandle t;
		t = petal_mesh.add_vertex(MyMesh::Point(meshp.at(i).x, meshp.at(i).y, meshp.at(i).z));
		vhandle.push_back(t);
	}
	// generate faces
	vector<MyMesh::VertexHandle>  face_vhandles;//记录三角网格面句柄
	for (int i = 0; i < trip.size(); i++)
	{
		face_vhandles.clear();
		int a, b, c;
		//得到对应vhandles的索引
		a = trip.at(i).x;
		b = trip.at(i).y;
		c = trip.at(i).z;

		face_vhandles.push_back(vhandle[a]);
		face_vhandles.push_back(vhandle[b]);
		face_vhandles.push_back(vhandle[c]);
		petal_mesh.add_face(face_vhandles);

	}
	// write mesh to output.ply
	//?meshviewer不能打开
	try
	{
		if (!OpenMesh::IO::write_mesh(petal_mesh, "mesh.ply"))
		{
			std::cerr << "Cannot write mesh to file 'mesh.ply'" << std::endl;
			//return;
		}
	}
	catch (std::exception& x)
	{
		std::cerr << x.what() << std::endl;
		//return;
	}

	return;
}

void model::buildmesh(QVector<coor> sample)
{
	
	petal_mesh.clear();//网格更新
	//使用openmesh生成ply文件
	//generate vertices
	vector<MyMesh::VertexHandle> vhandle;//记录采样点句柄
	for (int i = 0; i < sample.size(); i++)
	{
		MyMesh::VertexHandle t;
		t = petal_mesh.add_vertex(MyMesh::Point(sample.at(i).x, sample.at(i).y, sample.at(i).z));
		vhandle.push_back(t);
	}
	// generate faces
	vector<MyMesh::VertexHandle>  face_vhandles;//记录三角网格面句柄
	for (int i = 0; i < trip.size(); i++)
	{
		face_vhandles.clear();
		int a, b, c;
		//得到对应vhandles的索引
		a = trip.at(i).x;
		b = trip.at(i).y;
		c = trip.at(i).z;

		face_vhandles.push_back(vhandle[a]);
		face_vhandles.push_back(vhandle[b]);
		face_vhandles.push_back(vhandle[c]);
		petal_mesh.add_face(face_vhandles);

	}
	// write mesh to output.ply
	//?meshviewer不能打开
	try
	{
		if (!OpenMesh::IO::write_mesh(petal_mesh, "mesh.ply"))
		{
			std::cerr << "Cannot write mesh to file 'mesh.ply'" << std::endl;
			//return;
		}
	}
	catch (std::exception& x)
	{
		std::cerr << x.what() << std::endl;
		//return;
	}
	return;
}

QVector<coor> model::getSamplePoints()
{
	QVector<coor> sample;

	coor t;
	t.x = contourp.at(0).x;
	t.y = contourp.at(0).y;
	t.z = contourp.at(0).z;
	sample.push_back(t);

	for (int i = 1; i < contourp.size() - 1; i = i + 2)//在每个高度的中轴采样
	{
		//左
		t.x = contourp.at(i).x;
		t.y = contourp.at(i).y;
		t.z = contourp.at(i).z;
		sample.push_back(t);
		//中
		t.x = (contourp.at(i).x + contourp.at(i + 1).x) / 2;
		t.y = (contourp.at(i).y + contourp.at(i + 1).y) / 2;
		t.z = contourp.at(i).z;
		sample.push_back(t);
		//右
		t.x = contourp.at(i+1).x;
		t.y = contourp.at(i+1).y;
		t.z = contourp.at(i+1).z;
		sample.push_back(t);
	}
	t.x = 0;
	t.y = 0;
	t.z = 0;
	sample.push_back(t);

	return sample;
}
QVector<coor> model::trimesh()
{
	QVector<coor> tri;

	coor t;
	//第一个三角形索引
	t.x = 0;
	t.y = 1;
	t.z = 2;
	tri.push_back(t);
	//第二个三角形索引
	t.x = 0;
	t.y = 2;
	t.z = 3;
	tri.push_back(t);

	for (int i = 1; i < meshp.size() - 6; i = i + 3)
	{
		//花瓣中间部分，每行有四个三角形
		t.x = i;
		t.y = i + 3;
		t.z = i + 4;
		tri.push_back(t);

		t.x = i;
		t.y = i + 4;
		t.z = i + 1;
		tri.push_back(t);

		t.x = i + 1;
		t.y = i + 4;
		t.z = i + 2;
		tri.push_back(t);

		t.x = i + 2;
		t.y = i + 4;
		t.z = i + 5;
		tri.push_back(t);
	}
	//最后收尾的两个三角
	int last = meshp.size() - 1;
	t.x = last;
	t.y = last - 2;
	t.z = last - 3;
	tri.push_back(t);

	t.x = last;
	t.y = last - 1;
	t.z = last - 2;
	tri.push_back(t);

	return tri;
}

int model::meshfitting()
{
	vector<float> L;//L矩阵
	vector<coor> lsample;//原始网格的样本点laplace坐标
	vector<int> H;//H矩阵
	vector<coor> u;//需要移动的点的新位置
	QVector<coor> newsample = calnewsample(H,u);//得到目标样本点

	if (u.size() <= 0)
		return 1;

	//进行网格变形

	//2.................
	MymeshFit m = MymeshFit();
	m.init(meshp,trip);//初始化网格参数
	m.buildmesh();//构造网格
	m.allMvcoding();//mean value编码
	L = m.getL();//L矩阵
	lsample = m.getlsample();//原始样本样本点对应laplacian坐标

	//系数矩阵为上L下H
	//系数矩阵A用向量存储
	vector<float> A;
	for (int i = 0; i < L.size(); i++)
	{
		A.push_back(L[i]);
	}
	for (int i = 0; i < H.size(); i++)
	{
		A.push_back(H[i]);
	}
	int row = lsample.size() + u.size();//A的行数
	int col = lsample.size();//A的列数

	//右边矩阵为上lsample下u，n+label行，3列分别计算
	//bx
	//by
	//bz
	vector<float> bx;
	vector<float> by;
	vector<float> bz;
	for (int i = 0; i < lsample.size(); i++)
	{
		bx.push_back(lsample.at(i).x);
		by.push_back(lsample.at(i).y);
		bz.push_back(lsample.at(i).z);
	}
	for (int i = 0; i < u.size(); i++)
	{
		bx.push_back(u.at(i).x);
		by.push_back(u.at(i).y);
		bz.push_back(u.at(i).z);
	}
	matrix cax = matrix();//计算新的x坐标
	cax.init(A, bx, row, col);
	vector<float> px;
	px = cax.getX();
	
	matrix cay = matrix();//计算新的y坐标
	cay.init(A, by, row, col);
	vector<float> py;
	py = cay.getX();

	matrix caz = matrix();//计算新的z坐标
	caz.init(A, bz, row, col);
	vector<float> pz;
	pz = caz.getX();

	QVector<coor> mv;
	if (px.size() == py.size() && px.size() == pz.size() && px.size() == meshp.size())
	{
		for (int i = 0; i < px.size(); i++)
		{
			coor t;
			t.x = px.at(i);
			t.y = py.at(i);
			t.z = pz.at(i);
			mv.push_back(t);
		}
		meshp.clear();
		meshp = mv;//meshp更新为变形后的样本点
		buildmesh(mv);//重新生成网格

		MymeshFit ml = MymeshFit();
		ml.init(meshp, trip);//初始化网格参数
		ml.buildmesh();//构造网格
		ml.Laplacesmooth();
		vector<coor> laplace= ml.getLaplacemv();
		meshp.clear();
		for (int i = 0; i < laplace.size(); i++)
			meshp.push_back(laplace.at(i));
		buildmesh(meshp);//重新生成网格


		return 1;
	}
	else
		return 0;

	return 1;
}

QVector<coor> model::calnewsample(vector<int> &H,vector<coor> &u)
{
	QVector<coor> newsample=meshp ;
	H.clear();
	u.clear();

	//效率不高
	//左边
	for (int i = 0; 3 * i + 1 < meshp.size() - 3;i++)
	{
		int count = 0;//记录有没有y坐标相同的点
		int sum = 0;//记录y相同的点对应x的和
		int y = newsample.at(3 * i + 1).y;
		for (int j = 0; j < contour_l.size(); j++)//在原始左轮廓寻找同样y的点
		{
			if (abs(contour_l.at(j).y() - y)<3)
			{
				count++;
				sum = sum + contour_l.at(j).x();
			}
			else if (count && (abs(contour_l.at(j).y() - y)>3))//y相同的点一定是连续挨着的
				break;
		}
		if ((count > 0)&&(fabs(sum/count-newsample.at(3*i+1).x)<10))//说明该点需要移动.......
		//if (count > 0) //说明该点需要移动.......
		{	
			coor t;
			t.x = sum/count+offset;
			t.y = y;
			t.z = newsample.at(3 * i + 1).z;
			newsample.erase(&newsample[3 * i + 1]);//删去newsample中原来的第3 * i + 1个点
			newsample.insert(newsample.begin() + 3 * i + 1, t);//新的第i个点替换

			//求出H和u（u为newsample中和meshp中不同的点）
			u.push_back(t);//u中加入需要修改的点
			for (int j = 0; j < meshp.size(); j++)
			{
				if (j == 3 * i + 1)
					H.push_back(1);
				else
					H.push_back(0);
				
			}
		}
	}

	//右边
	for (int i = 1; 3 * i  < meshp.size() - 1; i++)
	{
		int count = 0;//记录有没有y坐标相同的点
		int sum = 0;//记录y相同的点对应x的和
		int y = newsample.at(3 * i).y;
		for (int j = 0; j < contour_r.size(); j++)//在原始左轮廓寻找同样y的点
		{
			if (abs(contour_r.at(j).y() - y)<3)
			{
				count++;
				sum = sum + contour_r.at(j).x();
			}
			else if (count && (abs(contour_r.at(j).y() - y)>3))
				break;
		}
		if ((count > 0) && (fabs(sum / count - newsample.at(3 * i ).x)<10))
		//if (count > 0) 
		{
			
			coor t;
			t.x = sum / count-offset;
			t.y = y;
			t.z = newsample.at(3 * i).z;
			newsample.erase(&newsample[3 * i]);//删去newsample中原来的第3 * i个点
			newsample.insert(newsample.begin() + 3 * i , t);//新的第i个点替换

			//求出H和u（u为newsample中和meshp中不同的点）
			u.push_back(t);//u中加入需要修改的点
			for (int j = 0; j < meshp.size(); j++)
			{
				if (j == 3 * i)
					H.push_back(1);
				else
					H.push_back(0);

			}
		}
	}

	return newsample;
}


void model::buildall()//生成所有花瓣的网格
{
	all_mesh.clear();
	//1、求解每个花瓣和模板花瓣的旋转角
	//2、将模板花瓣网格所有点旋转到对应顶点花瓣处
	//3、生成该花瓣网格
	vector<MyMesh::VertexHandle> vhandle;//记录采样点句柄
	for (int i = 0; i < tippoint.size(); i++)//第i个花瓣
	{
		//1、求解每个花瓣和模板花瓣的旋转角
		float a[2] = {contourp.at(0).x,contourp.at(0).z};//模板中轴
		float b[2] = {tippoint.at(i).x,tippoint.at(i).z};//对应花瓣中轴
		double angle = calangle(a,b);

		//2、将模板花瓣网格所有点旋转到对应顶点花瓣处
		for (int j = 0; j < meshp.size(); j++)
		{
			float a1[2] = { meshp.at(j).x,meshp.at(j).z };
		
			QPoint p = rotate(a1,angle);
			
			MyMesh::VertexHandle t;
			t = all_mesh.add_vertex(MyMesh::Point(p.x(), meshp.at(j).y, p.y()));
			vhandle.push_back(t);
		}
		//3、生成该花瓣网格
		// generate faces
		vector<MyMesh::VertexHandle>  face_vhandles;//记录三角网格面句柄
		for (int j = 0; j < trip.size(); j++)
		{
			face_vhandles.clear();
			int a, b, c;
			//得到对应vhandles的索引,要考虑第i个花瓣，索引要有偏移
			a = trip.at(j).x + i*meshp.size();
			b = trip.at(j).y + i*meshp.size();
			c = trip.at(j).z + i*meshp.size();

			face_vhandles.push_back(vhandle[a]);
			face_vhandles.push_back(vhandle[b]);
			face_vhandles.push_back(vhandle[c]);
			all_mesh.add_face(face_vhandles);
		}

	}

	int count = tippoint.size();
	for (int i = 0; i < tippoint.size(); i++)//重新扫描顶点确定另一半的花瓣网格
	{
		float a[2] = { contourp.at(0).x, contourp.at(0).z };//模板中轴
		float b[2] = { tippoint.at(i).x, tippoint.at(i).z };//对应花瓣中轴
		double angle = calangle(a, b);

		//若该顶点不是两端的点，则对称增加花瓣，z改变符号
		if (radius.at(0)-fabs(tippoint.at(i).x) - offset > (radius.at(0)/10.0))//不是两端的点
		{
			for (int j = 0; j < meshp.size(); j++)
			{
				float a1[2] = { meshp.at(j).x, meshp.at(j).z };

				QPoint p = rotate(a1, angle);

				MyMesh::VertexHandle t;
				t = all_mesh.add_vertex(MyMesh::Point(p.x(), meshp.at(j).y, -p.y()));
				vhandle.push_back(t);
			}

			// generate faces
			vector<MyMesh::VertexHandle>  face_vhandles;//记录三角网格面句柄
			for (int j = 0; j < trip.size(); j++)
			{
				face_vhandles.clear();
				int a, b, c;
				//得到对应vhandles的索引,要考虑第i个花瓣，索引要有偏移
				a = trip.at(j).x + count*meshp.size();
				b = trip.at(j).y + count*meshp.size();
				c = trip.at(j).z + count*meshp.size();

				face_vhandles.push_back(vhandle[a]);
				face_vhandles.push_back(vhandle[b]);
				face_vhandles.push_back(vhandle[c]);
				all_mesh.add_face(face_vhandles);
			}
			count++;

		}
	}
	// write mesh to output.ply
	//?meshviewer不能打开
	try
	{
		if (!OpenMesh::IO::write_mesh(petal_mesh, "allmesh.ply"))
		{
			std::cerr << "Cannot write mesh to file 'allmesh.ply'" << std::endl;
			//return;
		}
	}
	catch (std::exception& x)
	{
		std::cerr << x.what() << std::endl;
		//return;
	}

	return;
}

double model::calangle(float a1[2], float a2[2])//求a1逆时针旋转到a2的旋转角
{
	double angle = 0;

	double mult = sqrtf(a1[0] * a1[0] + a1[1] * a1[1])*sqrtf(a2[0] * a2[0] + a2[1] * a2[1]);
	mult = (a1[0] * a2[0] + a1[1] * a2[1]) / mult;

	if (fabs(mult - 1) <= 0.0001)
		angle = 0;
	else if (fabs(mult + 1) <= 0.0001)
		angle = PI;
	else
	{
		angle = acos(mult);//逆时针旋转夹角弧度
		double cross = a1[0] * a2[1] - a2[0] * a1[1];
		if (cross > 0)
			angle = 2 * PI - angle;
	}

	return angle;
}

QPoint model::rotate(float src[2], double angle)//点绕y轴旋转
{
	float t[3] = { src[0],0, src[1]};
	Mat vsrc = Mat(1, 3, CV_32FC1, t);

	int ax = 0;
	int ay = 1;
	int az = 0;

	float A[3][3] = { ax*ax, ax*ay, ax*az,
		ay*ax, ay*ay, ay*az,
		az*ax, az*ay, az*az
	};
	float B[3][3] = { 0, -az, ay,
		az, 0, -ax,
		-ay, ax, 0
	};
	Mat mA = Mat(3, 3, CV_32FC1, A);
	Mat mB = Mat(3, 3, CV_32FC1, B);
	Mat mI = Mat::eye(3, 3, CV_32FC1);

	Mat IA = mI - mA;
	Mat M = mA + cos(angle)*IA + sin(angle)*mB;
	Mat Mt = M.t();
	Mat vdst = vsrc*Mt;

	QPoint dst(vdst.at<float>(0, 0), vdst.at<float>(0, 2));

	return dst;
}



QVector<coor> model::getContour()
{
	return contourp;
}

void model::setContour_l(QVector<QPoint> c)
{
	contour_l = c;
	return;
}
void model::setContour_r(QVector<QPoint> c)
{
	contour_r = c;
	return;
}

void model::setTippoint(QVector<QPoint> t)//求解所有花瓣顶点的对应三维坐标
{
	tippoint.clear();
	int h = contourp.at(0).y;//高度
	int r = radius.at(0);
	for (int i = 0; i < t.size(); i++)
	{
		float scale = h / (1.0*t.at(i).y());//伸缩系数
		coor ct;
		ct.x = t.at(i).x()*scale;
		if (fabs(ct.x)>r)//若比半径大
			ct.x = ct.x>0?r-offset:-r+offset;//......
		ct.y = h;
		ct.z = sqrtf(r*r-ct.x*ct.x);
		tippoint.push_back(ct);
	}

	return;
}

QVector<coor> model::getSample()
{
	return meshp;
}

QVector<coor> model::getTrimesh()
{
	return trip;
}

MyMesh  model::getmesh()
{
	return petal_mesh;
}

MyMesh model::getAll_mesh()
{
	return all_mesh;
}
