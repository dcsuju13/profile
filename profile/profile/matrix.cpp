#include "matrix.h"


matrix::matrix()
{
}



matrix::~matrix()
{
	vector <float>().swap(A);
	vector <float>().swap(b);
	vector <float>().swap(x);
}

void  matrix::init(vector<float> a, vector<float> p, int m, int n)
{
	A = a;
	A_row = m;
	A_col = n;
	b = p;

}

//��a�����ת�ã�
//�����������aΪm��n�ף����������n��m�׾���b�
void matrix::transpose(vector<float> a, int m, int n, vector<float> &b)
{
	for (int i = 0; i<n; i++)
	  for (int j = 0; j < m; j++)
		 b.push_back(0);

	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
		{
			b[i*m + j] = a[j*n + i];
		}
}

//������ˣ�
//m��n�׵ľ���a��n��k�׵ľ���b��ˣ��õ�m��k�׵ľ��󱣴���c�У�
void  matrix::trmul(vector<float> a, vector<float> b, int m, int n, int k, vector<float> &c)
{
	int  l, u;
	for (int i = 0; i <= m - 1; i++)
	  for (int j = 0; j <= k - 1; j++)
		  c.push_back(0);
	for (int i = 0; i <= m - 1; i++)
		for (int j = 0; j <= k - 1; j++)
		{
			u = i*k + j;
			c[u] = 0;
			for (l = 0; l <= n - 1; l++)
				c[u] = c[u] + a[i*n + l] * b[l*k + j];
		}
}

//ƽ��������Cholesky������ʵ�����ԳƷ�����Ľ⣻
//����n��n�������Գ�ϵ������a��n��m�׳�������
//���طֽ���U���������ǲ��ִ���a�����̵�m�����������d��
int  matrix::chlk(vector<float> a, int n, int m, vector<float> &d)
{
		int  u, v;
		for (int i = 0; i < m*n; i++)
			d.push_back(0);

		if ((a[0] + 1.0 == 1.0) || (a[0]<0.0))
		{
			printf("fail\n");
			return false;
		}
		a[0] = sqrt(a[0]);
		for (int j = 1; j <= n - 1; j++) 
			a[j] = a[j] / a[0];
		for (int i = 1; i <= n - 1; i++)
		{
			u = i*n + i;
			for (int j = 1; j <= i; j++)
			{
				v = (j - 1)*n + i;
				a[u] = a[u] - a[v] * a[v];
			}
			if ((a[u] + 1.0 == 1.0) || (a[u]<0.0))
			{
				printf("fail\n");
				return false;
			}
			a[u] = sqrt(a[u]);
			if (i != (n - 1))
			{
				for (int j = i + 1; j <= n - 1; j++)
				{
					v = i*n + j;
					for (int k = 1; k <= i; k++)
						a[v] = a[v] - a[(k - 1)*n + i] * a[(k - 1)*n + j];
					a[v] = a[v] / a[u];
				}
			}
		}
		for (int j = 0; j <= m - 1; j++)
		{

			d[j] = d[j] / a[0];
			//d.push_back(d[j] / a[0]);
			for (int i = 1; i <= n - 1; i++)
			{
				u = i*n + i;
				v = i*m + j;
				for (int k = 1; k <= i; k++)
					d[v] = d[v] - a[(k - 1)*n + i] * d[(k - 1)*m + j];
				d[v] = d[v] / a[u];
			}
		}
		for (int j = 0; j <= m - 1; j++)
		{
			u = (n - 1)*m + j;
			d[u] = d[u] / a[n*n - 1];
			for (int k = n - 1; k >= 1; k--)
			{
				u = (k - 1)*m + j;
				for (int i = k; i <= n - 1; i++)
				{
					v = (k - 1)*n + i;
					d[u] = d[u] - a[v] * d[i*m + j];
				}
				v = (k - 1)*n + k - 1;
				d[u] = d[u] / a[v];
			}
		}
		return true;
}

void matrix::fun(vector<float> r, vector<float> p, int m, int n)
{
	int i, j;
	//double *R = new double[m*n];
	//double *P = new double[m * 1];
	//double *RT = new double[n*m];
	//double *a = new double[n*n];
	//double *b = new double[m * 1];
	//float *Q = new float[n * 1];
	vector<float> R;
	vector<float> P;
	vector<float> RT;
	vector<float> a;
	vector<float> tb;
	
	//vector<float> Q;

	for (i = 0; i<r.size(); i++)
	{
		//R[i] = r[i];
		R.push_back(r[i]);
		//P[i] = p[i];
		//P.push_back(p[i]);
	}
	for (i = 0; i < p.size();i++)
		P.push_back(p[i]);


	transpose(R, m, n, RT);
	trmul(RT, R, n, m, n, a);
	trmul(RT, P, n, m, 1, tb);
	int flag= chlk(a, n, 1, tb);

	if (!flag)
		printf("Error!");
	else
		for (i = 0; i < n; i++)
		{
			//x[i] = b[i];
			x.push_back(tb[i]);
		}

	//return Q;
}

vector<float> & matrix::getX()
{
	fun(A, b, A_row, A_col);
	return x;
}

