#include "MymeshFit.h"


MymeshFit::MymeshFit()
{
}


MymeshFit::~MymeshFit()
{
	
}

void MymeshFit::init(QVector<coor> sample, QVector<coor> tri)
{
	countP = sample.size();

	for (int i = 0; i < MAX_SIZE; i++)//�����ʼ��
	{
		point[i] = (struct node*)malloc(sizeof(struct node));
		point[i]->x = 0;
		point[i]->y = 0;
		point[i]->z = 0;
		point[i]->edgef = NULL;
		point[i]->id = i;
		point[i]->laplace[1, 2, 3] = { 0 };
		point[i]->n[1, 2, 3] = { 0 };
		trimesh[i][0] = 0;
		trimesh[i][1] = 0;
		trimesh[i][2] = 0;
	}
	
	
	//��ʼ��������
	for (int i = 0; i < sample.size(); i++)
	{
		point[i]->x = sample.at(i).x;
		point[i]->y = sample.at(i).y;
		point[i]->z = sample.at(i).z;

		if (abs(point[i]->x) < 1e-4)
				point[i]->x = 0.01;
		if (abs(point[i]->y) < 1e-4)
				point[i]->y = 0.01;
		if (abs(point[i]->z) < 1e-4)
				point[i]->z = 0.01;
		
	}
	//��ʼ������
	for (int i = 0; i < tri.size(); i++)
	{
		trimesh[i][0] = tri.at(i).x;
		trimesh[i][1] = tri.at(i).y;
		trimesh[i][2] = tri.at(i).z;

	}

	return;
}

void MymeshFit::buildmesh()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (trimesh[i][0] + trimesh[i][1] + trimesh[i][2] < 1e-4)
		{
			break;
		}
		//���ν����ߣ���Ӧ���޸ĵ������
		initedge(point[trimesh[i][0]], point[trimesh[i][1]]);
		initedge(point[trimesh[i][1]], point[trimesh[i][0]]);
		initedge(point[trimesh[i][0]], point[trimesh[i][2]]);
		initedge(point[trimesh[i][2]], point[trimesh[i][0]]);
		initedge(point[trimesh[i][1]], point[trimesh[i][2]]);
		initedge(point[trimesh[i][2]], point[trimesh[i][1]]);

	}
	return;
}

void MymeshFit::initedge(struct node *s, struct node *e)   //������������ṹ�ĺ���
{
	struct edge* newedge = (struct edge*)malloc(sizeof(struct edge));
	newedge->start = s;
	newedge->end = e;
	newedge->next = NULL;
	if (s->edgef == NULL)
	{
		s->edgef = newedge;
	}
	else
	{
		struct edge *te;
		te = s->edgef;
		int block = 0;
		if (e->x - s->x >= 0 && e->y - s->y > 0)  block = 1;
		if (e->x - s->x < 0 && e->y - s->y >= 0)  block = 2;
		if (e->x - s->x <= 0 && e->y - s->y < 0)  block = 3;
		if (e->x - s->x > 0 && e->y - s->y <= 0)  block = 4;

		bool firstandbig = false;
		while (true) //���µı߲��뵽��
		{
			//�ȱȽ�block
			int blocke = 0;
			if (te->end->x - s->x >= 0 && te->end->y - s->y > 0)  blocke = 1;
			if (te->end->x - s->x < 0 && te->end->y - s->y >= 0)  blocke = 2;
			if (te->end->x - s->x <= 0 && te->end->y - s->y < 0)  blocke = 3;
			if (te->end->x - s->x > 0 && te->end->y - s->y <= 0)  blocke = 4;

			if (block > blocke)
			if (te->next != NULL)
				te = te->next;
			else
			{
				firstandbig = true;
				break;
			}
			else if (block == blocke)//�ٱȽϽǶ�
			{
				float eorx = abs(e->x - s->x) / sqrt(pow((e->x - s->x), 2) + pow((e->y - s->y), 2));
				float eorxe = abs(te->end->x - s->x) / sqrt(pow((te->end->x - s->x), 2) + pow((te->end->y - s->y), 2));
				if (block == 2 || block == 4)
				if (eorx > eorxe)
				{
					if (te->next != NULL) te = te->next;
					else
					{
						firstandbig = true;
						break;
					}
				}
				else break;
				else
				if (eorx < eorxe)
				{
					if (te->next != NULL) te = te->next;
					else
					{
						firstandbig = true;
						break;
					}
				}
				else break;
			}
			else break;
			//if (te->end != e) te = te->next;
			//else break;
		}
		//������ȷ��λ��
		if (e->id != te->end->id)
		{
			if (firstandbig == true)
				te->next = newedge;
			else if (s->edgef == te)
			{
				s->edgef = newedge;
				newedge->next = te;
			}
			else
			{
				struct edge *ne;
				ne = s->edgef;
				while (true)
				{
					if (ne->next == te)
					{
						ne->next = newedge;
						newedge->next = te;
						break;
					}
					else if (ne->next != NULL) ne = ne->next;
					else break;
				}
			}
		}
		//if(te->end->id != e->id) te->next = newedge;
	}
}

void MymeshFit::mvcoding(struct node *point, float L[MAX_SIZE][MAX_SIZE])    //�������ϡ�����L�ĺ���
{
	if (point->edgef == NULL)
	{
		//��ʼ��laplace����
		point->laplace[0] = 0;
		point->laplace[1] = 0;
		point->laplace[2] = 0;
		printf("��õ�%d��������˹���꣺%4.3f,%4.3f,%4.3f\n", point->id, point->laplace[0], point->laplace[1], point->laplace[2]);
		L[point->id][point->id] = 1;//++
		return;
	}
	//��ÿ���㷨����
	int count = 0;
	float l[3] = { 0 };
	//��ʼ��laplace����
	point->laplace[0] = 0;
	point->laplace[1] = 0;
	point->laplace[2] = 0;
	//��һ�α���1-�ڽӵ㣺���ƽ����l
	struct edge *te = point->edgef;
	while (true)
	{
		count++;
		l[0] += te->end->x;
		l[1] += te->end->y;
		l[2] += te->end->z;
		if (te->next == NULL) break;
		else te = te->next;
	}
	l[0] = l[0] / count;
	l[1] = l[1] / count;
	l[2] = l[2] / count;
	//�ڶ��α���1-�ڽӵ㣺��ⷨ����n
	float n[3] = { 0 };
	te = point->edgef;
	while (true)
	{
		float vj[3], vj1[3] = { 0 };
		vj[0] = te->end->x - l[0];
		vj[1] = te->end->y - l[1];
		vj[2] = te->end->z - l[2];
		if (te->next == NULL)
		{
			vj1[0] = point->edgef->end->x - l[0];
			vj1[1] = point->edgef->end->y - l[1];
			vj1[2] = point->edgef->end->z - l[2];
		}
		else
		{
			vj1[0] = te->next->end->x - l[0];
			vj1[1] = te->next->end->y - l[1];
			vj1[2] = te->next->end->z - l[2];
		}
		n[0] += vj1[1] * vj[2] - vj1[2] * vj[1];
		n[1] += vj1[2] * vj[0] - vj1[0] * vj[2];
		n[2] += vj1[0] * vj[1] - vj1[1] * vj[0];
		if (te->next == NULL) break;
		else te = te->next;
	}
	float sumvjs = sqrt(pow(n[0], 2) + pow(n[1], 2) + pow(n[2], 2));
	//............................
	if (sumvjs > 0)
	{
		n[0] = n[0] / sumvjs;
		n[1] = n[1] / sumvjs;
		n[2] = n[2] / sumvjs;
	}


	//�����α���1-�ڽӵ㣺���Ӧ��1�ױ�����ƽ���ͶӰ
	float d = -(point->x*n[0] + point->y*n[1] + point->z*n[2]);
	te = point->edgef;
	float sumw = 0;
	struct arraylist *ts = NULL;   //���ָ��ͷ���ڴ�������������ڽ�wֵ
	while (true)
	{
		//���Ӧ��1�ױ�����ƽ���ͶӰ
		float dk = n[0] * te->end->x + n[1] * te->end->y + n[2] * te->end->z + d;
		float vjk[3] = { 0 }, vjk0[3] = { 0 }, vjk1[3] = { 0 };
		vjk[0] = te->end->x - dk*n[0] - te->start->x;
		vjk[1] = te->end->y - dk*n[1] - te->start->y;
		vjk[2] = te->end->z - dk*n[2] - te->start->z;
		//��һ���ߵ�ͶӰ
		struct edge * ne = point->edgef;
		if (te == point->edgef) //����м�ı��ǵ�һ���ߵĻ�����һ���߾���ָ���β
		while (true)
		{
			if (ne->next == NULL) break;
			else ne = ne->next;
		}
		else
		while (true)       //���������һ��ָ��
		{
			if (ne->next == te) break;
			else ne = ne->next;
		}
		float dk0 = n[0] * ne->end->x + n[1] * ne->end->y + n[2] * ne->end->z + d;
		vjk0[0] = ne->end->x - dk*n[0] - ne->start->x;
		vjk0[1] = ne->end->y - dk*n[1] - ne->start->y;
		vjk0[2] = ne->end->z - dk*n[2] - ne->start->z;
		//��һ���ߵ�ͶӰ
		if (te->next == NULL) ne = point->edgef; //����м�ı���ָ���β�Ļ�����һ���߾���ָ��ͷ
		else ne = te->next;                      //����˳��ָ����һ����
		float dk1 = n[0] * ne->end->x + n[1] * ne->end->y + n[2] * ne->end->z + d;
		vjk1[0] = ne->end->x - dk*n[0] - ne->start->x;
		vjk1[1] = ne->end->y - dk*n[1] - ne->start->y;
		vjk1[2] = ne->end->z - dk*n[2] - ne->start->z;
		//����ÿ���ߵ�wֵ�����������ݽṹ����L���ṹ��struct arraylist��
		//float agl1 = acos((vjk[0] * vjk0[0] + vjk[1] * vjk0[1] + vjk[2] * vjk0[2]) / sqrtf(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2)) / sqrt(pow(vjk0[0], 2) + pow(vjk0[1], 2) + pow(vjk0[2], 2)));
		//float agl2 = acos((vjk[0] * vjk1[0] + vjk[1] * vjk1[1] + vjk[2] * vjk1[2]) / sqrtf(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2)) / sqrt(pow(vjk1[0], 2) + pow(vjk1[1], 2) + pow(vjk1[2], 2)));
		float agl1 = acos((vjk[0] * vjk0[0] + vjk[1] * vjk0[1] + vjk[2] * vjk0[2]) / (sqrtf(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2)) * sqrt(pow(vjk0[0], 2) + pow(vjk0[1], 2) + pow(vjk0[2], 2))));
		float agl2 = acos((vjk[0] * vjk1[0] + vjk[1] * vjk1[1] + vjk[2] * vjk1[2]) / (sqrtf(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2)) * sqrt(pow(vjk1[0], 2) + pow(vjk1[1], 2) + pow(vjk1[2], 2))));
		float w;

		float a1 = (vjk[0] * vjk0[0] + vjk[1] * vjk0[1] + vjk[2] * vjk0[2]) / (sqrtf(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2)) * sqrt(pow(vjk0[0], 2) + pow(vjk0[1], 2) + pow(vjk0[2], 2)));
		float a2 = (vjk[0] * vjk1[0] + vjk[1] * vjk1[1] + vjk[2] * vjk1[2]) / (sqrtf(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2)) * sqrt(pow(vjk1[0], 2) + pow(vjk1[1], 2) + pow(vjk1[2], 2)));
		//........................
		if ((sqrtf(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2)) != 0) && ((a1 >= -1) && (a1 <= 1)) && ((a2 >= -1) && (a2 <= 1)))
			w = (tan(agl1 / 2) + tan(agl2 / 2)) / sqrt(pow(vjk[0], 2) + pow(vjk[1], 2) + pow(vjk[2], 2));
		else
			w = 0.01;

		struct arraylist *ta = (struct arraylist*)malloc(sizeof(struct arraylist));
		ta->end = te->end;
		ta->l = w;
		sumw += w;
		//������������ݽṹ��
		ta->next = ts;
		ts = ta;
		//ѭ���ṹ��
		if (te->next == NULL) break;
		else te = te->next;
	}
	//����ÿ�����Ȩֵ��laplace����,����������
	float  sumvjl[3] = { 0 };
	while (true)
	{
		float lam;
		if (sumw != 0)
			lam = ts->l / sumw;
		else
			lam = 0;

		L[point->id][ts->end->id] = -lam;//?
		sumvjl[0] += lam*ts->end->x;
		sumvjl[1] += lam*ts->end->y;
		sumvjl[2] += lam*ts->end->z;
		if (ts->next == NULL) break;
		else ts = ts->next;
	}
	L[point->id][point->id] = 1;//++
	point->laplace[0] = point->x - sumvjl[0];
	point->laplace[1] = point->y - sumvjl[1];
	point->laplace[2] = point->z - sumvjl[2];
	printf("��õ�%d��������˹���꣺%4.3f,%4.3f,%4.3f\n", point->id, point->laplace[0], point->laplace[1], point->laplace[2]);
}

void MymeshFit::allMvcoding()//������������б���
{
	////�����������MeanVealue�������----------------------------------------------------------------------------------------------------------
	for (int i = 0; i < MAX_SIZE; i++)
	{
		//if (abs(point[i]->x) + abs(point[i]->x) + abs(point[i]->x) < 1e-4) break;//?
		if (abs(point[i]->x) + abs(point[i]->y) + abs(point[i]->z) < 1e-4) break;
		mvcoding(point[i], arrayl);
	}
}

void MymeshFit::Laplacesmooth()//���������laplaceƽ��
{
	laplacemv.clear();
	//�����������Laplaceƽ��-----------------------------------------------------------------------------------------------------------------
	printf("��ʼƽ��\n");
	float p[MAX_SIZE][3];
	//float q[MAX_SIZE][3];
	float b[MAX_SIZE][3];
	for (int i = 0; i < MAX_SIZE; i++) //�����ʼ��
	{
		coor t;
		t.x = point[i]->x;
		t.y = point[i]->y;
		t.z= point[i]->z;
		laplacemv.push_back(t);
		p[i][0] = 0;
		p[i][1] = 0;
		p[i][2] = 0;
		b[i][0] = 0;
		b[i][1] = 0;
		b[i][2] = 0;
	}
	//printf("ƽ��ǰ��%f,%f,%f\n", q[532][0], q[532][1], q[532][2]);
	for (int t = 0; t < REPEATTIME; t++)   //ƽ���ĵ������� = REPEATTIME
	{
		for (int i = 0; i < laplacemv.size(); i++)
		{
			if (abs(laplacemv[i].x) < 1e-4 && abs(laplacemv[i].y) < 1e-4 && abs(laplacemv[i].z) < 1e-4) break;
			struct edge *te = point[i]->edgef;
			if (te == NULL)	 continue;
			float sum[3] = { 0 };
			int count = 0;
			while (true)
			{
				sum[0] += laplacemv[te->end->id].x;
				sum[1] += laplacemv[te->end->id].y;
				sum[2] += laplacemv[te->end->id].z;
				count++;
				if (te->next != NULL) te = te->next;
				else break;
			}
			p[i][0] = sum[0] / count;
			p[i][1] = sum[1] / count;
			p[i][2] = sum[2] / count;

			b[i][0] = p[i][0] - POB*point[i]->x - (1 - POB)*laplacemv[i].x;
			b[i][1] = p[i][1] - POB*point[i]->y - (1 - POB)*laplacemv[i].y;
			b[i][2] = p[i][2] - POB*point[i]->z - (1 - POB)*laplacemv[i].z;

		}

		for (int i = 0; i <laplacemv.size(); i++)
		{
			if (abs(laplacemv[i].x) < 1e-4 && abs(laplacemv[i].y) < 1e-4 && abs(laplacemv[i].z) < 1e-4) break;
			struct edge *te = point[i]->edgef;
			if (te == NULL)	 continue;
			float sum[3] = { 0 };
			int count = 0;
			while (true)
			{
				sum[0] += b[te->end->id][0];
				sum[1] += b[te->end->id][1];
				sum[2] += b[te->end->id][2];
				count++;
				if (te->next != NULL) te = te->next;
				else break;
			}
			laplacemv[i].x = p[i][0] - POP*b[i][0] - (1 - POP)*sum[0] / count;
			laplacemv[i].y = p[i][1] - POP*b[i][1] - (1 - POP)*sum[1] / count;
			laplacemv[i].z = p[i][2] - POP*b[i][2] - (1 - POP)*sum[2] / count;

			p[i][0] = 0;
			p[i][1] = 0;
			p[i][2] = 0;

			b[i][0] = 0;
			b[i][1] = 0;
			b[i][2] = 0;
		}
		//printf("��%d�α��Σ�%f,%f,%f\n", t, q[532][0], q[532][1], q[532][2]);
	}
	//�����ļ�-------------------------------------------------------------------------------------------------------------------------
	/*
	fpnode = fopen("nodechanged.txt", "w+");
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (abs(q[i][0]) > 1e-4 || abs(q[i][1]) > 1e-4 || abs(q[i][2]) > 1e-4)     //����������Ƚ�
			fprintf(fpnode, "%4.1f %4.1f %4.1f \n", q[i][0], q[i][1], q[i][2]);
		else
		{
			printf("��������%d", i);
			break;
		}
	}
	fclose(fpnode);
	*/
	return;
}

vector<coor> MymeshFit::getlsample()
{
	for (int i = 0; i < countP; i++)
	{
		//fprintf(fpnode, "%4.4f %4.4f %4.4f\n", point[i]->laplace[0], point[i]->laplace[1], point[i]->laplace[2]);
		coor t;
		t.x = point[i]->laplace[0];
		t.y = point[i]->laplace[1];
		t.z = point[i]->laplace[2];

		lsample.push_back(t);

	}

	for (int i = 0; i < lsample.size(); i++)
	{
		cout << lsample[i].x << " " << lsample[i].y << " " << lsample[i].z << endl;
	}

	//����laplace����
	fpnode = fopen("laplacecoding.txt", "w+");
	for (int i = 0; i < lsample.size(); i++)
	{
		//if (abs(lsample[i].x) > 1e-4 || abs(lsample[i].y) > 1e-4 || abs(lsample[i].z) > 1e-4)     //����������Ƚ�
			fprintf(fpnode, "%4.4f %4.4f %4.4f\n", lsample[i].x, lsample[i].y, lsample[i].z);
		//else break;
	}
	fclose(fpnode);
	printf("��д���");
	return lsample;

}

vector<float> MymeshFit::getL()
{
	for (int i = 0; i < countP; i++)
	{
		//for (int j = 0; j < MAX_SIZE; j++)
		for (int j = 0; j <countP; j++)
		{
			Lm.push_back(arrayl[i][j]);
		}
	}
	Lrow = countP;
	Lcol = countP;
	//����L
	fpnode = fopen("arrayl.txt", "w+");
	for (int i = 0; i < countP; i++)
	{
		for (int j = 0; j < countP; j++)
		{
			fprintf(fpnode, "%4.3f ", arrayl[i][j]);
		}
		fprintf(fpnode, "\n");
	}
	fclose(fpnode);
	return Lm;
	
	

}

vector<coor> MymeshFit::getLaplacemv()
{
	return laplacemv;
}



