#include "model.h"


model::model()
{
}

model::model(QVector<QPoint> c, QVector<int> r)
{
	contourp.clear();
	//��c����Ϊ��ά��
	coor t;
	t.x = c.at(0).x();
	t.y = c.at(0).y();
	t.z = r.at(0);
	contourp.push_back(t);

	for (int i = 1, j = 1; j < r.size() - 1; i = i + 2, j++)
	{
		//�߶�Ϊi��������
		t.x = c.at(i).x();
		t.y = c.at(i).y();
		t.z = r.at(j);
		contourp.push_back(t);

		//�߶�Ϊi��������
		t.x = c.at(i + 1).x();
		t.y = c.at(i + 1).y();
		t.z = r.at(j);
		contourp.push_back(t);
	}
	t.x = 0;
	t.y = 0;
	t.z = 0;
	contourp.push_back(t);

	radius = r;//�뾶��
}

model::~model()
{
}

void model::buildmesh()
{
	petal_mesh.clear();//�������
	if (contourp.empty())
		return;

	meshp.clear();
	meshp = getSamplePoints();//��ȡ������
	trip.clear();
	trip = trimesh();//������������
	
	//ʹ��openmesh����ply�ļ�
	//1........
	//generate vertices
	vector<MyMesh::VertexHandle> vhandle;//��¼��������
	for (int i = 0; i < meshp.size(); i++)
	{
		MyMesh::VertexHandle t;
		t = petal_mesh.add_vertex(MyMesh::Point(meshp.at(i).x, meshp.at(i).y, meshp.at(i).z));
		vhandle.push_back(t);
	}
	// generate faces
	vector<MyMesh::VertexHandle>  face_vhandles;//��¼������������
	for (int i = 0; i < trip.size(); i++)
	{
		face_vhandles.clear();
		int a, b, c;
		//�õ���Ӧvhandles������
		a = trip.at(i).x;
		b = trip.at(i).y;
		c = trip.at(i).z;

		face_vhandles.push_back(vhandle[a]);
		face_vhandles.push_back(vhandle[b]);
		face_vhandles.push_back(vhandle[c]);
		petal_mesh.add_face(face_vhandles);

	}
	// write mesh to output.ply
	//?meshviewer���ܴ�
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
	
	petal_mesh.clear();//�������
	//ʹ��openmesh����ply�ļ�
	//generate vertices
	vector<MyMesh::VertexHandle> vhandle;//��¼��������
	for (int i = 0; i < sample.size(); i++)
	{
		MyMesh::VertexHandle t;
		t = petal_mesh.add_vertex(MyMesh::Point(sample.at(i).x, sample.at(i).y, sample.at(i).z));
		vhandle.push_back(t);
	}
	// generate faces
	vector<MyMesh::VertexHandle>  face_vhandles;//��¼������������
	for (int i = 0; i < trip.size(); i++)
	{
		face_vhandles.clear();
		int a, b, c;
		//�õ���Ӧvhandles������
		a = trip.at(i).x;
		b = trip.at(i).y;
		c = trip.at(i).z;

		face_vhandles.push_back(vhandle[a]);
		face_vhandles.push_back(vhandle[b]);
		face_vhandles.push_back(vhandle[c]);
		petal_mesh.add_face(face_vhandles);

	}
	// write mesh to output.ply
	//?meshviewer���ܴ�
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

	for (int i = 1; i < contourp.size() - 1; i = i + 2)//��ÿ���߶ȵ��������
	{
		//��
		t.x = contourp.at(i).x;
		t.y = contourp.at(i).y;
		t.z = contourp.at(i).z;
		sample.push_back(t);
		//��
		t.x = (contourp.at(i).x + contourp.at(i + 1).x) / 2;
		t.y = (contourp.at(i).y + contourp.at(i + 1).y) / 2;
		t.z = contourp.at(i).z;
		sample.push_back(t);
		//��
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
	//��һ������������
	t.x = 0;
	t.y = 1;
	t.z = 2;
	tri.push_back(t);
	//�ڶ�������������
	t.x = 0;
	t.y = 2;
	t.z = 3;
	tri.push_back(t);

	for (int i = 1; i < meshp.size() - 6; i = i + 3)
	{
		//�����м䲿�֣�ÿ�����ĸ�������
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
	//�����β����������
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
	vector<float> L;//L����
	vector<coor> lsample;//ԭʼ�����������laplace����
	vector<int> H;//H����
	vector<coor> u;//��Ҫ�ƶ��ĵ����λ��
	QVector<coor> newsample = calnewsample(H,u);//�õ�Ŀ��������

	if (u.size() <= 0)
		return 1;

	//�����������

	//2.................
	MymeshFit m = MymeshFit();
	m.init(meshp,trip);//��ʼ���������
	m.buildmesh();//��������
	m.allMvcoding();//mean value����
	L = m.getL();//L����
	lsample = m.getlsample();//ԭʼ�����������Ӧlaplacian����

	//ϵ������Ϊ��L��H
	//ϵ������A�������洢
	vector<float> A;
	for (int i = 0; i < L.size(); i++)
	{
		A.push_back(L[i]);
	}
	for (int i = 0; i < H.size(); i++)
	{
		A.push_back(H[i]);
	}
	int row = lsample.size() + u.size();//A������
	int col = lsample.size();//A������

	//�ұ߾���Ϊ��lsample��u��n+label�У�3�зֱ����
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
	matrix cax = matrix();//�����µ�x����
	cax.init(A, bx, row, col);
	vector<float> px;
	px = cax.getX();
	
	matrix cay = matrix();//�����µ�y����
	cay.init(A, by, row, col);
	vector<float> py;
	py = cay.getX();

	matrix caz = matrix();//�����µ�z����
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
		meshp = mv;//meshp����Ϊ���κ��������
		buildmesh(mv);//������������

		MymeshFit ml = MymeshFit();
		ml.init(meshp, trip);//��ʼ���������
		ml.buildmesh();//��������
		ml.Laplacesmooth();
		vector<coor> laplace= ml.getLaplacemv();
		meshp.clear();
		for (int i = 0; i < laplace.size(); i++)
			meshp.push_back(laplace.at(i));
		buildmesh(meshp);//������������


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

	//Ч�ʲ���
	//���
	for (int i = 0; 3 * i + 1 < meshp.size() - 3;i++)
	{
		int count = 0;//��¼��û��y������ͬ�ĵ�
		int sum = 0;//��¼y��ͬ�ĵ��Ӧx�ĺ�
		int y = newsample.at(3 * i + 1).y;
		for (int j = 0; j < contour_l.size(); j++)//��ԭʼ������Ѱ��ͬ��y�ĵ�
		{
			if (abs(contour_l.at(j).y() - y)<3)
			{
				count++;
				sum = sum + contour_l.at(j).x();
			}
			else if (count && (abs(contour_l.at(j).y() - y)>3))//y��ͬ�ĵ�һ�����������ŵ�
				break;
		}
		if ((count > 0)&&(fabs(sum/count-newsample.at(3*i+1).x)<10))//˵���õ���Ҫ�ƶ�.......
		//if (count > 0) //˵���õ���Ҫ�ƶ�.......
		{	
			coor t;
			t.x = sum/count+offset;
			t.y = y;
			t.z = newsample.at(3 * i + 1).z;
			newsample.erase(&newsample[3 * i + 1]);//ɾȥnewsample��ԭ���ĵ�3 * i + 1����
			newsample.insert(newsample.begin() + 3 * i + 1, t);//�µĵ�i�����滻

			//���H��u��uΪnewsample�к�meshp�в�ͬ�ĵ㣩
			u.push_back(t);//u�м�����Ҫ�޸ĵĵ�
			for (int j = 0; j < meshp.size(); j++)
			{
				if (j == 3 * i + 1)
					H.push_back(1);
				else
					H.push_back(0);
				
			}
		}
	}

	//�ұ�
	for (int i = 1; 3 * i  < meshp.size() - 1; i++)
	{
		int count = 0;//��¼��û��y������ͬ�ĵ�
		int sum = 0;//��¼y��ͬ�ĵ��Ӧx�ĺ�
		int y = newsample.at(3 * i).y;
		for (int j = 0; j < contour_r.size(); j++)//��ԭʼ������Ѱ��ͬ��y�ĵ�
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
			newsample.erase(&newsample[3 * i]);//ɾȥnewsample��ԭ���ĵ�3 * i����
			newsample.insert(newsample.begin() + 3 * i , t);//�µĵ�i�����滻

			//���H��u��uΪnewsample�к�meshp�в�ͬ�ĵ㣩
			u.push_back(t);//u�м�����Ҫ�޸ĵĵ�
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


void model::buildall()//�������л��������
{
	all_mesh.clear();
	//1�����ÿ�������ģ�廨�����ת��
	//2����ģ�廨���������е���ת����Ӧ���㻨�괦
	//3�����ɸû�������
	vector<MyMesh::VertexHandle> vhandle;//��¼��������
	for (int i = 0; i < tippoint.size(); i++)//��i������
	{
		//1�����ÿ�������ģ�廨�����ת��
		float a[2] = {contourp.at(0).x,contourp.at(0).z};//ģ������
		float b[2] = {tippoint.at(i).x,tippoint.at(i).z};//��Ӧ��������
		double angle = calangle(a,b);

		//2����ģ�廨���������е���ת����Ӧ���㻨�괦
		for (int j = 0; j < meshp.size(); j++)
		{
			float a1[2] = { meshp.at(j).x,meshp.at(j).z };
		
			QPoint p = rotate(a1,angle);
			
			MyMesh::VertexHandle t;
			t = all_mesh.add_vertex(MyMesh::Point(p.x(), meshp.at(j).y, p.y()));
			vhandle.push_back(t);
		}
		//3�����ɸû�������
		// generate faces
		vector<MyMesh::VertexHandle>  face_vhandles;//��¼������������
		for (int j = 0; j < trip.size(); j++)
		{
			face_vhandles.clear();
			int a, b, c;
			//�õ���Ӧvhandles������,Ҫ���ǵ�i�����꣬����Ҫ��ƫ��
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
	for (int i = 0; i < tippoint.size(); i++)//����ɨ�趥��ȷ����һ��Ļ�������
	{
		float a[2] = { contourp.at(0).x, contourp.at(0).z };//ģ������
		float b[2] = { tippoint.at(i).x, tippoint.at(i).z };//��Ӧ��������
		double angle = calangle(a, b);

		//���ö��㲻�����˵ĵ㣬��Գ����ӻ��꣬z�ı����
		if (radius.at(0)-fabs(tippoint.at(i).x) - offset > (radius.at(0)/10.0))//�������˵ĵ�
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
			vector<MyMesh::VertexHandle>  face_vhandles;//��¼������������
			for (int j = 0; j < trip.size(); j++)
			{
				face_vhandles.clear();
				int a, b, c;
				//�õ���Ӧvhandles������,Ҫ���ǵ�i�����꣬����Ҫ��ƫ��
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
	//?meshviewer���ܴ�
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

double model::calangle(float a1[2], float a2[2])//��a1��ʱ����ת��a2����ת��
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
		angle = acos(mult);//��ʱ����ת�нǻ���
		double cross = a1[0] * a2[1] - a2[0] * a1[1];
		if (cross > 0)
			angle = 2 * PI - angle;
	}

	return angle;
}

QPoint model::rotate(float src[2], double angle)//����y����ת
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

void model::setTippoint(QVector<QPoint> t)//������л��궥��Ķ�Ӧ��ά����
{
	tippoint.clear();
	int h = contourp.at(0).y;//�߶�
	int r = radius.at(0);
	for (int i = 0; i < t.size(); i++)
	{
		float scale = h / (1.0*t.at(i).y());//����ϵ��
		coor ct;
		ct.x = t.at(i).x()*scale;
		if (fabs(ct.x)>r)//���Ȱ뾶��
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
