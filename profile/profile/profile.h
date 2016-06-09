#pragma once
#ifndef PROFILE_H
#define PROFILE_H

#include <QtWidgets/QMainWindow>
#include <QGraphicsView>  
#include <QGraphicsScene> 
#include <QGraphicsSceneMouseEvent>  
#include <QImage>  
#include <QGraphicsScene> 
#include <QFileDialog>  
#include <QMessageBox>
#include "MyLabel.h"
#include "global.h"
#include "MyGL.h"
#include "model.h"

#include "ui_profile.h"

// -------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
// ----------------------------------------------------------------------------
typedef OpenMesh::TriMesh_ArrayKernelT<>  MyMesh;

class profile : public QMainWindow
{
	Q_OBJECT

public:
	profile(QWidget *parent = 0);
	~profile();

private slots:
	void on_Button_scan_clicked();
	void on_Button_point_clicked();
	void on_Button_tip_clicked();
	void on_Button_curve_clicked();
	void on_Button_contour_clicked();
	void on_Button_keypoint_clicked();
	void on_Button_petal_clicked();
	void on_Button_mesh_clicked();
	void on_Button_meshfitting_clicked();
	void on_Button_all_clicked();
private:
	Ui::profileClass ui;
	QImage *image;//Í¼Æ¬
	QString ImageName;//Í¼Æ¬Ãû³Æ
	model cmodel;
	



};

#endif // PROFILE_H
