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
				tr("打开图像失败"),
				tr("打开图像失败!"));
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
	QVector<QPoint> p = ui.label_image->getContour();//花瓣轮廓
	QVector<QPoint> p_l = ui.label_image->getContour_l();//花瓣左轮廓
	QVector<QPoint> p_r = ui.label_image->getContour_r();//花瓣左轮廓
	QVector<int> r = ui.label_image->getRadius();//半径组
	model mo = model(p,r);
	QVector<coor> con = mo.getContour();//获取花瓣三维轮廓
	cmodel = mo;
	cmodel.setContour_l(p_l);//设置原始左轮廓
	cmodel.setContour_r(p_r);//设置原始右轮廓

	MyGL *gl = new MyGL(con);
	gl->option = 1;
	ui.sArea_surface->setWidget(gl);

	//生成网格
	//网格变形

	return;
}

void profile::on_Button_mesh_clicked()
{
	cmodel.buildmesh();//生成网格
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
	cmodel.meshfitting();//网格变形
	MyMesh mesh = cmodel.getmesh();
	MyGL *gl = new MyGL();
	gl->setMesh(mesh);
	gl->option = 2;
	ui.sArea_surface->setWidget(gl);


	return;
}

void profile::on_Button_all_clicked()
{
	QVector<QPoint> tippoint = ui.label_image->getTippoint();//获取花瓣顶点组
	cmodel.setTippoint(tippoint);//设置顶点组
	cmodel.buildall();//生成所有花瓣网格
	MyMesh mesh = cmodel.getAll_mesh();

	MyGL *gl = new MyGL();
	gl->setMesh(mesh);
	gl->option = 2;
	ui.sArea_all->setWidget(gl);
	return;
}