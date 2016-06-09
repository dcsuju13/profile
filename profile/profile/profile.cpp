#include "profile.h"


profile::profile(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->image = new QImage();
}

profile::~profile()
{

}

void profile::on_Button_scan_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
		this, "open image file",
		".",
		"Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
	ImageName = fileName;
	if (fileName != "")
	{
		if (image->load(fileName))
		{
			//*image = image->scaled(image->width() / 2, image->height() / 2, Qt::KeepAspectRatio);	
			ui.lineEdit_image->setText(fileName);
			g_filedst = fileName;
			ui.label_image->setPixmap(QPixmap::fromImage(*image));
			//ui.label_image = new MyLabel(ui.scrollAreaWidgetContents);
		}
		else
		{
			QMessageBox::information(this,
				tr("��ͼ��ʧ��"),
				tr("��ͼ��ʧ��!"));
			delete image;
			return;

		}


	}

	ui.label_image->LiveWire(g_filedst);
	return;

}

void profile::on_Button_point_clicked()
{
	ui.label_image->option = CENTER;
	return;
}

void profile::on_Button_tip_clicked()
{
	ui.label_image->option = TIP;
	return;
}

void profile::on_Button_curve_clicked()
{
	ui.label_image->option = PROFILE;
	return;
}

void profile::on_Button_contour_clicked()
{
	ui.label_image->option = CONTOUR;
	return;
}

void profile::on_Button_keypoint_clicked()
{
	ui.label_image->canKeyPoint();
	return;
}

void profile::on_Button_petal_clicked()
{
	QVector<QPoint> p = ui.label_image->getContour();//��������
	QVector<QPoint> p_l = ui.label_image->getContour_l();//����������
	QVector<QPoint> p_r = ui.label_image->getContour_r();//����������
	QVector<int> r = ui.label_image->getRadius();//�뾶��
	model mo = model(p,r);
	QVector<coor> con = mo.getContour();//��ȡ������ά����
	cmodel = mo;
	cmodel.setContour_l(p_l);//����ԭʼ������
	cmodel.setContour_r(p_r);//����ԭʼ������

	MyGL *gl = new MyGL(con);
	gl->option = 1;
	ui.sArea_surface->setWidget(gl);

	//��������
	//�������

	return;
}

void profile::on_Button_mesh_clicked()
{
	cmodel.buildmesh();//��������
	//QVector<coor> sample = cmodel.getSample();
	//QVector<coor> tri = cmodel.getTrimesh();
	MyMesh mesh = cmodel.getmesh();

	MyGL *gl = new MyGL();
	gl->setMesh(mesh);
	gl->option = 2;
	ui.sArea_surface->setWidget(gl);

	return;
}

void profile::on_Button_meshfitting_clicked()
{
	cmodel.meshfitting();//�������
	MyMesh mesh = cmodel.getmesh();
	MyGL *gl = new MyGL();
	gl->setMesh(mesh);
	gl->option = 2;
	ui.sArea_surface->setWidget(gl);


	return;
}

void profile::on_Button_all_clicked()
{
	QVector<QPoint> tippoint = ui.label_image->getTippoint();//��ȡ���궥����
	cmodel.setTippoint(tippoint);//���ö�����
	cmodel.buildall();//�������л�������
	MyMesh mesh = cmodel.getAll_mesh();

	MyGL *gl = new MyGL();
	gl->setMesh(mesh);
	gl->option = 2;
	ui.sArea_all->setWidget(gl);
	return;
}