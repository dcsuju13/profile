#include "MyGL.h"


MyGL::MyGL()
{
	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;
	translationX = 0;
	translationY = 0;
	translationZ = 0;

}

MyGL::MyGL(QVector<coor> contour)
{
	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;
	translationX = 0;
	translationY = 0;
	translationZ = 0;

	contour_p = contour;
	
}


MyGL::~MyGL()
{
}

void MyGL::initializeGL()
{

	setGeometry(300, 150, 800, 600);//���ô��ڳ�ʼλ�úʹ�С

	//qglClearColor(Qt::black);
	glClearColor(0.0, 0.0, 0.0, 0);
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);//������Ȼ���
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);//������Ȳ�������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//����͸��У��


}

void MyGL::resizeGL(int width, int height)
{
	GLfloat nrange = 400.0f;
	if (0 == height)
		height = 1;//��ֹһ����Ϊ0
	glViewport(0, 0, (GLint)width, (GLint)height);//���õ�ǰ�ӿڣ����������ô��ڵģ�ֻ���������ﱻQt����װ����
	glMatrixMode(GL_PROJECTION);//ѡ��ͶӰ����
	glLoadIdentity();//����ѡ��õ�ͶӰ����
	//�ü�����
	/*if (width <= height)
	glOrtho(-nrange, nrange, -nrange*height / width, nrange*height / width, -nrange, nrange);
	else
	glOrtho(-nrange*width / height, nrange*width / height, -nrange, nrange, -nrange, nrange);
	*/

	gluPerspective(70.0f, (GLfloat)width / (GLfloat)height, 0, 2 * nrange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MyGL::paintGL()
{
	
	

	if (option == 1)//����ӳ��
	{
		drawPetal();
	}
	else if (option == 2)
	{
		drawMesh();
	}
	

	glFlush();
}

void MyGL::drawPetal()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -600);
	glTranslatef(translationX, translationY, translationZ);

	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	glRotatef(rotationZ, 0.0, 0.0, 1.0);


	//����

	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5);
	//�������е�
	for (int i = 0; i < contour_p.size(); i++)
	{
		glBegin(GL_POINTS);
		glVertex3f(contour_p[i].x, contour_p[i].y, contour_p[i].z);
		glEnd;
	}

	glPointSize(1);

	//ʹ���ܹ���ת
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	return;
}

void MyGL::drawMesh()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -600);
	glTranslatef(translationX, translationY, translationZ);

	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	glRotatef(rotationZ, 0.0, 0.0, 1.0);


	//����

	glColor3f(1.0f, 1.0f, 1.0f);
	//�������е�
	/*
	for (int i = 0; i < trip.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(meshp.at(trip.at(i).x).x, meshp.at(trip.at(i).x).y, meshp.at(trip.at(i).x).z);
		glVertex3f(meshp.at(trip.at(i).y).x, meshp.at(trip.at(i).y).y, meshp.at(trip.at(i).y).z);
		glEnd;

		glBegin(GL_LINES);
		glVertex3f(meshp.at(trip.at(i).x).x, meshp.at(trip.at(i).x).y, meshp.at(trip.at(i).x).z);
		glVertex3f(meshp.at(trip.at(i).z).x, meshp.at(trip.at(i).z).y, meshp.at(trip.at(i).z).z);
		glEnd;

		glBegin(GL_LINES);
		glVertex3f(meshp.at(trip.at(i).y).x, meshp.at(trip.at(i).y).y, meshp.at(trip.at(i).y).z);
		glVertex3f(meshp.at(trip.at(i).z).x, meshp.at(trip.at(i).z).y, meshp.at(trip.at(i).z).z);
		glEnd;
	}
	*/
	for (auto it = petal_mesh.halfedges_begin(); it != petal_mesh.halfedges_end(); ++it)
	{
		auto fromv = petal_mesh.from_vertex_handle(it.handle());

		auto tov = petal_mesh.to_vertex_handle(it.handle());

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f((GLfloat)petal_mesh.point(fromv).data()[0], (GLfloat)petal_mesh.point(fromv).data()[1], (GLfloat)petal_mesh.point(fromv).data()[2]);
		glVertex3f((GLfloat)petal_mesh.point(tov).data()[0], (GLfloat)petal_mesh.point(tov).data()[1], (GLfloat)petal_mesh.point(tov).data()[2]);
		glEnd();

	}

	glPointSize(1);

	//ʹ���ܹ���ת
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	return;
}

void MyGL::setMesh(MyMesh mesh)
{
	
	petal_mesh = mesh;

	return;
}


void MyGL::mousePressEvent(QMouseEvent *event)
{

	lastPos = event->pos();
}


void MyGL::mouseMoveEvent(QMouseEvent *event)
{
	GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
	GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
	if (event->buttons() & Qt::LeftButton){
		rotationX += 180 * dy;
		rotationY += 180 * dx;
		updateGL();
	}
	else if (event->buttons() & Qt::RightButton){
		rotationX += 180 * dy;
		rotationZ += 180 * dx;
		updateGL();
	}
	lastPos = event->pos();

}

void MyGL::wheelEvent(QWheelEvent *e)
{
	if (e->buttons()&Qt::MiddleButton)
	{
		int numDegrees = e->delta()/8;

		if (numDegrees>0)
		{
			translationZ -= 5*numDegrees;
			updateGL();
		}
		else
		{
			translationZ += 5*numDegrees;
			updateGL();
		}
	}
	return;
}

