#include "MyLabel.h"
#include "global.h"


MyLabel::MyLabel(QWidget *parent)
{
	
}


MyLabel::~MyLabel()
{
}

void MyLabel::LiveWire(QString filename)
{
	string s = filename.toStdString();
	RGB = imread(s);

	Mat RGB2;
	RGB.convertTo(RGB2, CV_32FC3);
	for (int i = 0; i < RGB.rows; i++)
	{
		for (int j = 0; j < RGB.cols; j++)
		{
			RGB2.at<Vec3f>(i, j)[0] = RGB2.at<Vec3f>(i, j)[0] / 255.0;
			//float t = RGB2.at<Vec3f>(i, j)[0];
			RGB2.at<Vec3f>(i, j)[1] = RGB2.at<Vec3f>(i, j)[1] / 255.0;
			RGB2.at<Vec3f>(i, j)[2] = RGB2.at<Vec3f>(i, j)[2] / 255.0;
		}

	}

	//RGB.convertTo(RGB,CV_32F);
	//float e = RGB.at<Vec3b>(10, 40)[1];
	OUT1 = Mat(RGB.rows, RGB.cols, CV_8UC1, Scalar(0));
	G = Mat(RGB.rows, RGB.cols, CV_32FC1, Scalar(0));
	F = Mat(RGB.rows, RGB.cols, CV_32FC3, Scalar(0, 0, 0));
	Mat UX = Mat(RGB.rows, RGB.cols, CV_32FC3, Scalar(0, 0, 0));
	Mat UY = Mat(RGB.rows, RGB.cols, CV_32FC3, Scalar(0, 0, 0));


	//canny算子
	Mat dst = RGB.clone();
	cvtColor(dst, dst, CV_BGR2GRAY);
	blur(dst, dst, Size(3, 3));
	Canny(dst, dst, 25, 25 * 3, 3);
	//imshow("dst",dst);
	Mat aCANNY(dst.rows, dst.cols, CV_32F);
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (dst.at<uchar>(i, j) == 0)
				aCANNY.at<float>(i, j) = 1;
			else
				aCANNY.at<float>(i, j) = 0;
		}
	}
	CANNY = aCANNY.clone();
	//LOG
	Mat dst1 = RGB.clone();
	GaussianBlur(dst1, dst1, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(dst1, dst1, CV_BGR2GRAY);
	Laplacian(dst1, dst1, RGB.depth(), 3, 1, 0, BORDER_DEFAULT);
	//imshow("dst", dst);
	Mat aLOG(dst1.rows, dst1.cols, CV_32F);
	for (int i = 0; i < dst1.rows; i++)
	{
		for (int j = 0; j < dst1.cols; j++)
		{
			if (dst1.at<uchar>(i, j) == 0)
				aLOG.at<float>(i, j) = 1;
			else
				aLOG.at<float>(i, j) = 0;
		}
	}
	LOG = aLOG.clone();
	float t;
	float r, rd, u, ru, l, d, ld, lu;
	for (int i = 0; i < RGB.rows; i++)
	{
		for (int j = 0; j < RGB.cols; j++)
		{
			for (int k = 2; k >= 0; k--)
			{
				if (j == 0)
				{
					if (i == 0)
					{
						d = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j)[k];
						r = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j + 1)[k];
						rd = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j + 1)[k];
						UX.at<Vec3f>(i, j)[k] = (-r * 2 - rd) / 3.0;
						UY.at<Vec3f>(i, j)[k] = (-d * 2 - rd) / 3.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
					else if (i == RGB2.rows - 1)
					{
						r = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j + 1)[k];
						u = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j)[k];
						ru = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j + 1)[k];
						UX.at<Vec3f>(i, j)[k] = (-r * 2 - ru) / 3.0;
						UY.at<Vec3f>(i, j)[k] = (u * 2 + ru) / 3.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
					else
					{
						r = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j + 1)[k];
						u = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j)[k];
						ru = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j + 1)[k];
						d = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j)[k];
						rd = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j + 1)[k];
						UX.at<Vec3f>(i, j)[k] = (-r * 2 - rd - ru) / 4.0;
						UY.at<Vec3f>(i, j)[k] = (-d * 2 - rd + u * 2 + ru) / 6.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
				}
				else if (j == RGB2.cols - 1)
				{
					if (i == 0)
					{
						l = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j - 1)[k];
						d = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j)[k];
						ld = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j - 1)[k];
						UX.at<Vec3f>(i, j)[k] = (l * 2 + ld) / 3.0;
						UY.at<Vec3f>(i, j)[k] = (-d * 2 - ld) / 3.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
					else if (i == RGB2.rows - 1)
					{
						l = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j - 1)[k];
						u = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j)[k];
						lu = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j - 1)[k];
						UX.at<Vec3f>(i, j)[k] = (l * 2 + lu) / 3.0;
						UY.at<Vec3f>(i, j)[k] = (u * 2 + lu) / 3.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
					else
					{
						u = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j)[k];;
						lu = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j - 1)[k];
						l = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j - 1)[k];
						d = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j)[k];
						ld = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j - 1)[k];
						UX.at<Vec3f>(i, j)[k] = (l * 2 + ld + lu) / 4.0;
						UY.at<Vec3f>(i, j)[k] = (u * 2 + lu - d * 2 + ld) / 6.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
				}
				else
				{
					if (i == 0)
					{
						r = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j + 1)[k];
						l = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j - 1)[k];
						d = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j)[k];
						rd = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j + 1)[k];
						ld = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j - 1)[k];
						UX.at<Vec3f>(i, j)[k] = (-r * 2 - rd + l * 2 + ld) / 6.0;
						UY.at<Vec3f>(i, j)[k] = (-d * 2 - ld - rd) / 4.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
					else if (i == RGB2.rows - 1)
					{
						r = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j + 1)[k];
						l = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j - 1)[k];
						u = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j)[k];
						lu = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j - 1)[k];
						ru = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j + 1)[k];
						UX.at<Vec3f>(i, j)[k] = (-r * 2 - ru + l * 2 + lu) / 6.0;
						UY.at<Vec3f>(i, j)[k] = (u * 2 + lu + ru) / 6.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
					else
					{
						u = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j)[k];;
						lu = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j - 1)[k];
						l = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j - 1)[k];
						d = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j)[k];
						ld = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j - 1)[k];
						r = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i, j + 1)[k];
						u = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j)[k];
						ru = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i - 1, j + 1)[k];
						rd = RGB2.at<Vec3f>(i, j)[k] - RGB2.at<Vec3f>(i + 1, j + 1)[k];
						UX.at<Vec3f>(i, j)[k] = (-r * 2 - rd - ru + l * 2 + lu + ld) / 8.0;
						UY.at<Vec3f>(i, j)[k] = (u * 2 + lu + ru - d * 2 - ld - rd) / 8.0;
						//t = UX.at<Vec3f>(i, j)[k];
					}
				}
			}
			Mat D = Mat(3, 2, CV_32FC1, Scalar(0));
			float ad;
			D.at<float>(0, 0) = UX.at<Vec3f>(i, j)[2];
			D.at<float>(0, 1) = UY.at<Vec3f>(i, j)[2];
			D.at<float>(1, 0) = UX.at<Vec3f>(i, j)[1];
			D.at<float>(1, 1) = UY.at<Vec3f>(i, j)[1];
			D.at<float>(2, 0) = UX.at<Vec3f>(i, j)[0];
			D.at<float>(2, 1) = UY.at<Vec3f>(i, j)[0];
			ad = D.at<float>(0, 0);
			ad = D.at<float>(0, 1);
			ad = D.at<float>(1, 0);
			ad = D.at<float>(1, 1);
			ad = D.at<float>(2, 0);
			ad = D.at<float>(2, 1);
			Mat S = Mat(3, 3, CV_32FC1, Scalar(0));
			Mat V = Mat(3, 2, CV_32FC1, Scalar(0));
			Mat AT = Mat(2, 2, CV_32FC1, Scalar(0));
			SVD::compute(D, V, S, AT, SVD::FULL_UV);
			//cv::SVDecomp(D, V, S, AT, SVD::FULL_UV);
			float maxeig = V.at<float>(0, 0);
			float maxlocation = 0;
			if (maxeig < V.at<float>(1, 0))
			{
				maxeig = V.at<float>(1, 0);
				maxlocation = 1;
			}
			if (maxeig <= 0)
				G.at<float>(i, j) = 0.0001;
			else
				G.at<float>(i, j) = sqrtf(maxeig);
			float t = G.at<float>(i, j);
			Mat A = AT.t();
			for (int ii = 0; ii< A.rows; ii++)
			{
				F.at<Vec3f>(i, j)[ii] = A.at<float>(ii, maxlocation);
				//t = F.at<Vec3f>(i, j)[ii];
			}
			if (G.at<float>(i, j) > gmax)
				gmax = G.at<float>(i, j);

		}

	}

}
void MyLabel::GetPointAndCaculate(QPoint p)
{
	Mat A(1, 2, CV_32FC1, Scalar(0));

	float mindist = 0;
	if (mindist == 0)
	{
		A.at<float>(0, 0) = p.x() - f_o.x();
		A.at<float>(0, 1) = p.y() - f_o.y();
		mindist = sqrtf(A.dot(A)) / 3.0;
	}
	//double maxg = G.at<float>(p.x()-1, p.y()-1);
	double maxg = G.at<float>(p.y() - 1, p.x() - 1);
	float x = p.x();
	float y = p.y();
	for (int i = -8; i <= 8; i++)
	{
		for (int j = -8; j <= 8; j++)
		{
			if (G.at<float>(p.y() + j - 1, p.x() + i - 1)>maxg)
			{
				maxg = G.at<float>(p.y() + j - 1, p.x() + i - 1);
				x = x + i;
				y = y + j;
			}
		}
	}
	int n = F.rows;
	int m = F.cols;
	OUT1.at<uchar>(p.y() - 1, p.x() - 1) = 1;
	//三个方向都要找
	float lastx, lasty;
	Mat vector(1, 2, CV_32FC1, Scalar(0));
	int floori, topi, floorj, topj;
	for (int h = 1; h <= 3; h++)
	{
		lastx = p.x();
		lasty = p.y();
		x = p.x();
		y = p.y();
		float fd, fg, fl, fc;
		float gos, c;
		int floori, topi, floorj, topj;
		for (int g = 1; g <= 1000; g++)
		{
			//确定区域，使得向花心延伸
			int vec[2] = {0};
			vec[0] = x - f_o.x();
			vec[1] = y - f_o.y();
			if (abs(vec[0]) == 0)
				vec[0] = 1;
			if (((-vec[1] / vec[0] )>= 1) || ((-vec[1] / vec[0]) <= -1))//区域1、3
			{
				if (-vec[1] >= 0)//区域1
				{
					floori = -1;
					topi = 1;
					floorj = 0;
					topj = 1;
				}
				else//区域3
				{
					floori = -1;
					topi = 1;
					floorj = -1;
					topj = 0;
				}
			}
			else//区域2、4
			{
				if (vec[0] <= 0)//区域2
				{
					floori = 0;
					topi = 1;
					floorj = -1;
					topj = 1;
				}
				else//区域4
				{
					floori = -1;
					topi = 0;
					floorj = -1;
					topj = 1;

				}
			}

			int minc = 7;
			Mat locationc(1, 2, CV_32FC1, Scalar(0));
			locationc.at<int>(0, 0) = x;
			locationc.at<int>(0, 1) = y;
			for (int i = floori; i <= topi; i++)
			{
				for (int j = floorj; j <= topj; j++)
				{
					if ((i != 0 || j != 0) && (x + i != lastx || y + j != lasty) && (x + i>0) && (x + i<m - 1) && (y + j>0) && (y + j<n - 1))
					{
						float t1 = G.at<float>(y - 1, x - 1);
						float t2 = G.at<float>(y + j - 1, x + i - 1);
						float t3 = F.at<Vec3f>(y - 1, x - 1)[0];
						float t4 = F.at<Vec3f>(y + j - 1, x + i - 1)[0];
						float t5 = F.at<Vec3f>(y - 1, x - 1)[1];
						float t6 = F.at<Vec3f>(y + j - 1, x + i - 1)[1];
						float t7 = F.at<Vec3f>(y - 1, x - 1)[0] / G.at<float>(y - 1, x - 1)*F.at<Vec3f>(y + j - 1, x + i - 1)[0] / G.at<float>(y + j - 1, x + i - 1) + F.at<Vec3f>(y - 1, x - 1)[1] / G.at<float>(y - 1, x - 1)*F.at<Vec3f>(y + j - 1, x + i - 1)[1] / G.at<float>(y + j - 1, x + i - 1);
						if ((t7<-1) || (t7>1))
							fd = 0;
						else
							fd = acos(F.at<Vec3f>(y - 1, x - 1)[0] / G.at<float>(y - 1, x - 1)*F.at<Vec3f>(y + j - 1, x + i - 1)[0] / G.at<float>(y + j - 1, x + i - 1) + F.at<Vec3f>(y - 1, x - 1)[1] / G.at<float>(y - 1, x - 1)*F.at<Vec3f>(y + j - 1, x + i - 1)[1] / G.at<float>(y + j - 1, x + i - 1)) / PI;

						fg = 1 - G.at<float>(y + j - 1, x + i - 1) / gmax;
						fl = LOG.at<float>(y + j - 1, x + i - 1);
						fc = CANNY.at<float>(y + j - 1, x + i - 1);
						gos = (0.5*OUT1.at<uchar>(y + j + j - 1, x + i - 1) + 0.5*OUT1.at<uchar>(y + j - 1, x + i + i - 1) + 1 * OUT1.at<uchar>(y + j + j - 1, x + i - i - 1) + 1 * OUT1.at<uchar>(y + j - j - 1, x + i + i - 1) + 1.5*OUT1.at<uchar>(y + j - j - 1, x + i - 1) + 1.5*OUT1.at<uchar>(y + j - 1, x + i - i - 1)) / 5.0;
						c = 5 * fg + 1 * fd + 1 * fl + 1 * fc + 4 * gos;
						if ((i != 0) && (j != 0))
						{
							c = c*(sqrtf(2));
						}
						if ((OUT1.at<uchar>(y + j - 1, x + i - 1) == 0) && (c < minc))
						{
							minc = c;
							locationc.at<int>(0, 0) = x + i;
							locationc.at<int>(0, 1) = y + j;
						}
					}
				}
			}
			OUT1.at<uchar>(locationc.at<int>(0, 1) - 1, locationc.at<int>(0, 0) - 1) = 1;

			//比较得到权值最小的点添加到OUT中，并在图上标记
			if (minc < 7)
			{
				lastx = x;
				lasty = y;
				x = locationc.at<int>(0, 0);
				y = locationc.at<int>(0, 1);
				QPoint b = QPoint(x, y);
				a = b;

				if (option == PROFILE)
					c_profile.push_back(a);
				else if (option == CONTOUR)
					contour.push_back(a);
				//update();//画点
			}
			else //若最小权值大于预值，或最小值点位于边缘上（不是上一个点）则退出循环
			{
				//检测断点周围的点数，如果等于1，证明该点未连接，
				//plot(locationc(1), locationc(2), 'ko', 'MarkerSize', 1, 'MarkerEdgeColor', 'g', 'MarkerFaceColor', 'g');
				sp = QPoint(locationc.at<int>(0, 0), locationc.at<int>(0, 1));
				break;
			}

			A.at<float>(0, 0) = locationc.at<int>(0, 0) - f_o.x();
			A.at<float>(0, 1) = locationc.at<int>(0, 1) - f_o.y();
			if (sqrtf(A.dot(A)) < mindist)
				break;
		}

	}
	getflag = 0;
	update();
}

void MyLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);//先调用父类的paintEvent为了显示'背景'!!!
	QPainter painter(this);

	if (option == CENTER)//花心
	{
		getflag = 0;

		f_o = a;
		painter.setPen(QPen(Qt::blue, 15));
		painter.drawPoint(f_o);
		option = CENTER_H;//点出花心后,接下来点中轴高点
		

	}
	else if (option == CENTER_H)//中轴高点
	{
		getflag = 0;

		fh_o = a;
		painter.setPen(QPen(Qt::blue, 10));
		painter.drawPoint(fh_o);
		painter.setPen(QPen(Qt::blue, 15));
		painter.drawPoint(f_o);

		//option = PROFILE;//点出中轴后接下来点出侧面曲线
		centered = true;

	}
	else if (option == PROFILE)//侧曲线
	{
		//getflag = 1;

		//绘制已经点出的点
		if (centered)
		{
			painter.setPen(QPen(Qt::blue, 15));
			painter.drawPoint(f_o);
			painter.setPen(QPen(Qt::blue, 10));
			painter.drawPoint(fh_o);
		}
		if (contoured)
		{
			painter.setPen(QPen(Qt::red, 1));
			painter.drawPoints(contour);

		}
		if (tipped)
		{
			painter.setPen(QPen(Qt::green, 10));
			painter.drawPoints(tippoint);
		}

		c_profile.push_back(a);
		painter.setPen(QPen(Qt::red,1));
		painter.drawPoints(c_profile);

		if (getflag != 0)
			GetPointAndCaculate(a);

		profeiled = true;
	}
	else if (option == CONTOUR)//单个花瓣轮廓
	{
		//getflag = 1;

		//绘制已经点出的点
		if (centered)
		{
			painter.setPen(QPen(Qt::blue, 15));
			painter.drawPoint(f_o);
			painter.setPen(QPen(Qt::blue, 10));
			painter.drawPoint(fh_o);
		}
		if (profeiled)
		{
			painter.setPen(QPen(Qt::red, 1));
			painter.drawPoints(c_profile);

		}
		if (tipped)
		{
			painter.setPen(QPen(Qt::green, 10));
			painter.drawPoints(tippoint);
		}
		

		contour.push_back(a);
		painter.setPen(QPen(Qt::red, 1));
		painter.drawPoints(contour);

		if (getflag != 0)
			GetPointAndCaculate(a);

		contoured = true;
	}
	else if (option == TIP)//剩余花瓣顶点
	{
		getflag = 0;

		//绘制已经点出的点
		if (centered)
		{
			painter.setPen(QPen(Qt::blue, 15));
			painter.drawPoint(f_o);
			painter.setPen(QPen(Qt::blue, 10));
			painter.drawPoint(fh_o);
		}
		if (profeiled)
		{
			painter.setPen(QPen(Qt::red, 1));
			painter.drawPoints(c_profile);

		}
		if (contoured)
		{
			painter.setPen(QPen(Qt::red, 1));
			painter.drawPoints(contour);
		}

		tippoint.push_back(a);
		painter.setPen(QPen(Qt::green, 10));
		painter.drawPoints(tippoint);

		tipped = true;
		
	}

}

void MyLabel::canKeyPoint()
{
	if ((!contour.empty()) && (!c_profile.empty()))
		KeyPoint();
}

void MyLabel::KeyPoint()
{	
	QVector<QPoint> c1;

	QVector<QPoint>::iterator it;
	int a1[2] = {f_o.x(),f_o.y()};
	int a2[2] = { 0 };

	//花瓣轮廓顺序存储
	int min_dist=RGB.rows*RGB.cols;
	QVector<QPoint>::iterator min_it;
	for (it = contour.begin(); it != contour.end(); ++it)//找出距离f_o最小的点
	{
		a2[0] = it->x();
		a2[1] = it->y();
		int dist = (a2[0] - a1[0])*(a2[0] - a1[0]) + (a2[1] - a1[1])*(a2[1] - a1[1]);

		if (dist<min_dist)
		{
			min_dist = dist;
			min_it = it;
		}
	}
	c1.push_back(*min_it);
	min_it=contour.erase(min_it);
	//if (min_it == contour.end())
		//min_it = contour.begin();

	OrderPoint(c1,contour);
	//for (int i = 0; i < c1_contour.size(); i++)
		//c1.push_back(c1_contour.at(i));
	contour.clear();
	contour = c1;
	


	//侧曲线顺序存储,从高到低
	c1.clear();
	a1[0] = f_o.x();
	a1[1] = f_o.y();
	int max_dist = 0;
	QVector<QPoint>::iterator max_it;
	for (it = c_profile.begin(); it != c_profile.end(); ++it)
	{
		a2[0] = it->x();
		a2[1] = it->y();
		int dist = (a2[0] - a1[0])*(a2[0] - a1[0]) + (a2[1] - a1[1])*(a2[1] - a1[1]);

		if (dist>max_dist)
		{
			max_dist = dist;
			max_it = it;
		}

	}
	c1.push_back(*max_it);
	max_it = c_profile.erase(max_it);
	//if (max_it == c_profile.end())
		//max_it = c_profile.begin();

	//按顺序依次向下找点
	OrderPoint(c1,c_profile);
	//for (int i = 0; i < c1_profile.size(); i++)
		//c1.push_back(c1_profile.at(i));
	c_profile.clear();
	c_profile = c1;


	//求解中轴和y轴反向夹角,逆时针旋转所有点使得中轴和y轴反向重合
	float ap[2] = { fh_o.x()-f_o.x(),fh_o.y() - f_o.y() };
    float by[2] = {0,-1};
	angle = calangle(ap,by);//求解中轴和y轴反向夹角
	rotatePoints();//旋转轮廓点和侧曲线点

	c1.clear();
	c1 = deleteRepeat(contour);//删去轮廓点中重复点
	contour.clear();
	contour = c1;
	//从contour中找到花瓣顶点tip_p
	min_dist = 0;
	for (int i = 0; i < contour.size(); i++)
	{
		int d = (contour.at(i).x() - f_o.x())*(contour.at(i).x() - f_o.x()) + (contour.at(i).y() - f_o.y())*(contour.at(i).y() - f_o.y());
		if (min_dist < d)
		{
			min_dist = d;
			tip_p = contour.at(i);
		}
	}

	c1.clear();
	c1 = deleteRepeat(c_profile);//删去侧曲线点中重复点
	c_profile.clear();
	c_profile = c1;
	h = c_profile.at(0).y();//高度为最高点的y


	//花瓣轮廓旋转至和中轴重合作为模板
	float ax[2] = { tip_p.x() - f_o.x(), tip_p.y() - f_o.y() };
	float bx[2] = { fh_o.x() - f_o.x(), fh_o.y() - f_o.y() };
	double agl =2*PI- calangle(ax, bx);//求解花瓣中轴和圆锥中轴逆时针旋转角(由于坐标已经变化，故反向)
	//旋转整个花瓣轮廓和tip_p
	tip_p = rotate(tip_p, agl);

	c1.clear();
	for (int i = 0; i < contour.size(); i++)//旋转花瓣轮廓
	{
		QPoint t = rotate(contour.at(i), agl);
		c1.push_back(t);
	}
	contour.clear();
	contour = c1;

	//求解半径组
	radius.clear();
	radius = calradius();


	//花瓣曲线拟合
	c1.clear();//重新保存拟合后的花瓣轮廓
	c1.push_back(tip_p);
	  //contour分为左右两边，并且将大小伸缩变换为和h一致
	float scale = h / (1.0*tip_p.y());//变换系数

	contour_l.clear();//原始左轮廓
	contour_r.clear();//原始右轮廓
	bool totip = false;
	for (int i = 0; i < contour.size(); i++)
	{
		if (contour.at(i) == tip_p)
		{
			totip = true;

			QPoint t = QPoint(tip_p.x(), tip_p.y()*scale);
			contour_r.push_back(t);
			contour_l.push_back(t);
			continue;
		}
		if (totip)//已达到顶点，之后归入右轮廓
		{
			QPoint t = QPoint(contour.at(i).x()*scale, contour.at(i).y()*scale);
			contour_r.push_back(t);
		}
		else//未到达顶点，归入左轮廓
		{
			QPoint t = QPoint(contour.at(i).x()*scale, contour.at(i).y()*scale);
			contour_l.push_back(t);
		}
	}
	QPoint o = QPoint(0,0);
	contour_l.push_back(o);
	contour_r.push_back(o);

	  //左轮廓拟合曲线
	FittingCurve fcl = FittingCurve(contour_l);
	fcl.CurveFit();
	double* indexcl = new double[3];
	indexcl = fcl.getP();//左边曲线方程的系数
	  //右轮廓拟合曲线
	FittingCurve fcr = FittingCurve(contour_r);
	fcr.CurveFit();
	double* indexcr = new double[3];
	indexcr = fcr.getP();//右边曲线方程的系数
	  //曲线拟合后的花瓣轮廓
	contour.clear();
	  //顶点伸缩至指定大小
	tip_p.setX(tip_p.x()*scale);
	tip_p.setY(tip_p.y()*scale);
	contour.push_back(tip_p);//轮廓点从高到低，左右存储


	//求解offset
	double agloffset = 0;
	if (agl > PI)
		agloffset = 2 * PI - agl;
	else
		agloffset = agl;
	offset = agloffset * 20;
	
	for (int i = h-5; i >0; i = i-5)
	{
		
		//QPoint tl = QPoint(indexcl[0] * i*i + indexcl[1] * i + indexcl[2]+offset, i);//......
		QPoint tl = QPoint(indexcl[0] * i*i + indexcl[1] * i  + offset, i);//......
		contour.push_back(tl);//高度为i的左轮廓点

		
		//QPoint tr = QPoint(indexcr[0] * i*i + indexcr[1] * i + indexcr[2]-offset, i);//......
		QPoint tr = QPoint(indexcr[0] * i*i + indexcr[1] * i  - offset, i);//......
		contour.push_back(tr);//高度为i的右轮廓点
	}
	QPoint t = QPoint(0,0);
	contour.push_back(t);//轮廓最后的点
	
	return;
	

}

void MyLabel::OrderPoint(QVector<QPoint> &c1,QVector<QPoint> &pointset)
{
	//QVector<QPoint> c1;

	QVector<QPoint>::iterator it;
	int a1[2] = { 0 };
	int a2[2] = { 0 };

	int min_dist = RGB.rows*RGB.cols;
	QVector<QPoint>::iterator min_it;
	
	while (!pointset.empty())//依次找出连续的点
	{
		int min_dist = RGB.rows*RGB.cols;
		QVector<QPoint>::iterator min_it;
		a1[0] = c1.back().x();
		a1[1] = c1.back().y();
		a2[0] = 0;
		a2[1] = 0;
		//int count = 0;
		for (it = pointset.begin(); it != pointset.end(); ++it)//找出距离a1最小的点
		{

			a2[0] = it->x();
			a2[1] = it->y();
			int dist = (a2[0] - a1[0])*(a2[0] - a1[0]) + (a2[1] - a1[1])*(a2[1] - a1[1]);

			if (dist <= min_dist)
			{
				min_dist = dist;
				min_it = it;
			}

		}
		int b[2] = { min_it->x(), min_it->y() };
		c1.push_back(*min_it);
		min_it = pointset.erase(min_it);
		//if (min_it == pointset.end())
			//min_it = pointset.begin();

		//删去a1周围除了min_it的点，确定不回走
		for (it = pointset.begin(); it != pointset.end();)
		{
			a2[0] = it->x();
			a2[1] = it->y();
			int dist = (a2[0] - a1[0])*(a2[0] - a1[0]) + (a2[1] - a1[1])*(a2[1] - a1[1]);
			if ((dist <= 2) && (a2 != b))
			{
				
				it = pointset.erase(it);
				if (it == pointset.end())
					break;
			}
			else
				it++;

		}

	}

	//删除c1中最后重复的部分
	min_dist = 0;
	for (it = c1.begin(); it != c1.end(); ++it)
	{
		QVector<QPoint>::iterator it_n = it;
		it_n++;
		if (it_n == c1.end())
			break;
		int dist = (it->x() - it_n->x())*(it->x() - it_n->x()) + (it->y() - it_n->y())*(it->y() - it_n->y());
		if ((dist > min_dist) && (dist>10))
		{
			min_dist = dist;
			min_it = it;
		}

	}
	it = c1.erase(min_it, c1.end());
	return;
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
	a = event->pos();
	if ((option==PROFILE)||(option==CONTOUR))
	   getflag = 1;
	update();
}

double MyLabel::calangle(float a[2], float b[2])
{
	double mult = sqrtf(a[0] * a[0] + a[1] * a[1])*sqrtf(b[0] * b[0] + b[1] * b[1]);
	mult = (a[0] * b[0] + a[1] * b[1]) / (1.0*mult);

	double rangle;
	if (fabs(mult - 1) <= 0.0001)
		rangle = 0;
	else if (fabs(mult + 1) <= 0.0001)
		rangle = PI;
	else
	{
		rangle = acos(mult);//逆时针旋转夹角弧度
		double cross = a[0] * b[1] - b[0] * a[1];
		if (cross > 0)
			rangle = 2 * PI - rangle;
	}

	return rangle;
}

void MyLabel::rotatePoints()
{
    //step1:先把花心f_o移动到原点（0,0）,contour和c_profile也相应移动，并且修改坐标
	//坐标转为正常坐标系，将图片左下角视为原点，y轴向上,x轴向右，即y轴修正

	int h = RGB.rows;
	//先将所有y坐标修正
	f_o.setY(h-1*f_o.y());

	//再根据f_o移动到原点，所有点均平移
	int move[2] = { f_o.x(), f_o.y() };

	f_o.setX(0);
	f_o.setY(0);

	fh_o.setX(fh_o.x()-move[0]);
	fh_o.setY(h-1*fh_o.y()-move[1]);

	tip_p.setX(tip_p.x()-move[0]);
	tip_p.setY(h-1*tip_p.y()-move[1]);

	//step2:旋转所有点
	f_o = rotate(f_o, angle);
	fh_o = rotate(fh_o, angle);
	tip_p = rotate(tip_p, angle);

	//contour,c_contour,tippoint将step1和step2一起做
	QVector<QPoint> c;
	for (int i = 0; i < contour.size(); i++)//contour
	{
		QPoint t(contour.at(i).x() - move[0], h - 1 * contour.at(i).y() - move[1]);
		t = rotate(t,angle);
		c.push_back(t);
	}
	contour.clear();
	contour = c;

	c.clear();
	for (int i = 0; i < c_profile.size(); i++)//c_profile
	{
		QPoint t(c_profile.at(i).x() - move[0], h - 1 * c_profile.at(i).y() - move[1]);
		t = rotate(t, angle);
		c.push_back(t);
	}
	c_profile.clear();
	c_profile = c;

	c.clear();
	for (int i = 0; i < tippoint.size(); i++)
	{
		QPoint t(tippoint.at(i).x() - move[0], h - 1 * tippoint.at(i).y() - move[1]);
		t = rotate(t, angle);
		c.push_back(t);
	}
	tippoint.clear();
	tippoint = c;

	return;

}

QPoint MyLabel::rotate(QPoint src, double rangle)
{
	float t[3] = { src.x(), src.y(), 0 };
	Mat vsrc=Mat(1,3,CV_32FC1,t);

	int ax = 0;
	int ay = 0;
	int az = 1;

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
	Mat M = mA + cos(rangle)*IA + sin(rangle)*mB;
	Mat Mt = M.t();
	Mat vdst = vsrc*Mt;

	QPoint dst(vdst.at<float>(0,0), vdst.at<float>(0,1));
	return dst;

}

QVector<QPoint> MyLabel::deleteRepeat(QVector<QPoint> pointset)
{
	QVector<QPoint> c;
	int y = 0;
	if (!pointset.empty())
		c.push_back(pointset.at(0));
	y = c.back().y();

	for (int i = 1; i < pointset.size(); i++)
	{
		if (pointset.at(i).y() != y)
		{
			c.push_back(pointset.at(i));
			y = pointset.at(i).y();
		}
			
	}
	return c;
}

QVector<int> MyLabel::calradius()
{
	QVector<int> r1;

	FittingCurve fc = FittingCurve(c_profile);
	fc.CurveFit();
	double* indexr = new double[3];
	indexr = fc.getP();//侧曲线方程的系数
	//以5为梯度依次下降求解半径
	r1.push_back(abs(indexr[0] * h*h + indexr[1] * h + indexr[2]));//最高点的半径

	for (int i = h - 5; i > 0; i = i - 5)
	{
		r1.push_back(abs(indexr[0] * i*i + indexr[1] * i + indexr[2]));
	
	}
	r1.push_back(abs(indexr[2]));//高度为0的半径

	//使得高度为0的为0
	for (int i = 0; i < r1.size(); i++)
		r1[i] = r1[i] - r1.back();
	

	return r1;
}

QVector<QPoint> MyLabel::getContour()
{
	return contour;
}

QVector<int> MyLabel::getRadius()
{

	return radius;
}

QVector<QPoint> MyLabel::getContour_l()
{
	return contour_l;
}

QVector<QPoint> MyLabel::getContour_r()
{
	return contour_r;
}

QVector<QPoint> MyLabel::getTippoint()
{
	return tippoint;
}