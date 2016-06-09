/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <MyLabel.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_profileClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_pre;
    QGridLayout *gridLayout_3;
    QPushButton *Button_tip;
    QPushButton *Button_curve;
    QLineEdit *lineEdit_image;
    QPushButton *Button_contour;
    QPushButton *Button_point;
    QScrollArea *sArea_image;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    MyLabel *label_image;
    QPushButton *Button_scan;
    QPushButton *Button_keypoint;
    QWidget *tab_surface;
    QGridLayout *gridLayout_5;
    QPushButton *Button_mesh;
    QScrollArea *sArea_surface;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *Button_petal;
    QPushButton *Button_meshfitting;
    QWidget *tab_all;
    QGridLayout *gridLayout_6;
    QScrollArea *sArea_all;
    QWidget *scrollAreaWidgetContents_3;
    QPushButton *Button_all;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *profileClass)
    {
        if (profileClass->objectName().isEmpty())
            profileClass->setObjectName(QStringLiteral("profileClass"));
        profileClass->resize(651, 625);
        centralWidget = new QWidget(profileClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_pre = new QWidget();
        tab_pre->setObjectName(QStringLiteral("tab_pre"));
        gridLayout_3 = new QGridLayout(tab_pre);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        Button_tip = new QPushButton(tab_pre);
        Button_tip->setObjectName(QStringLiteral("Button_tip"));

        gridLayout_3->addWidget(Button_tip, 1, 2, 1, 1);

        Button_curve = new QPushButton(tab_pre);
        Button_curve->setObjectName(QStringLiteral("Button_curve"));

        gridLayout_3->addWidget(Button_curve, 2, 1, 1, 1);

        lineEdit_image = new QLineEdit(tab_pre);
        lineEdit_image->setObjectName(QStringLiteral("lineEdit_image"));

        gridLayout_3->addWidget(lineEdit_image, 1, 0, 1, 1);

        Button_contour = new QPushButton(tab_pre);
        Button_contour->setObjectName(QStringLiteral("Button_contour"));

        gridLayout_3->addWidget(Button_contour, 2, 2, 1, 1);

        Button_point = new QPushButton(tab_pre);
        Button_point->setObjectName(QStringLiteral("Button_point"));

        gridLayout_3->addWidget(Button_point, 1, 1, 1, 1);

        sArea_image = new QScrollArea(tab_pre);
        sArea_image->setObjectName(QStringLiteral("sArea_image"));
        sArea_image->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 605, 416));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_image = new MyLabel(scrollAreaWidgetContents);
        label_image->setObjectName(QStringLiteral("label_image"));

        gridLayout_4->addWidget(label_image, 0, 0, 1, 1);

        sArea_image->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(sArea_image, 0, 0, 1, 3);

        Button_scan = new QPushButton(tab_pre);
        Button_scan->setObjectName(QStringLiteral("Button_scan"));

        gridLayout_3->addWidget(Button_scan, 2, 0, 1, 1);

        Button_keypoint = new QPushButton(tab_pre);
        Button_keypoint->setObjectName(QStringLiteral("Button_keypoint"));

        gridLayout_3->addWidget(Button_keypoint, 3, 1, 1, 2);

        tabWidget->addTab(tab_pre, QString());
        tab_surface = new QWidget();
        tab_surface->setObjectName(QStringLiteral("tab_surface"));
        gridLayout_5 = new QGridLayout(tab_surface);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        Button_mesh = new QPushButton(tab_surface);
        Button_mesh->setObjectName(QStringLiteral("Button_mesh"));

        gridLayout_5->addWidget(Button_mesh, 2, 1, 1, 1);

        sArea_surface = new QScrollArea(tab_surface);
        sArea_surface->setObjectName(QStringLiteral("sArea_surface"));
        sArea_surface->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 605, 445));
        sArea_surface->setWidget(scrollAreaWidgetContents_2);

        gridLayout_5->addWidget(sArea_surface, 1, 0, 1, 2);

        Button_petal = new QPushButton(tab_surface);
        Button_petal->setObjectName(QStringLiteral("Button_petal"));

        gridLayout_5->addWidget(Button_petal, 2, 0, 1, 1);

        Button_meshfitting = new QPushButton(tab_surface);
        Button_meshfitting->setObjectName(QStringLiteral("Button_meshfitting"));

        gridLayout_5->addWidget(Button_meshfitting, 3, 1, 1, 1);

        tabWidget->addTab(tab_surface, QString());
        tab_all = new QWidget();
        tab_all->setObjectName(QStringLiteral("tab_all"));
        gridLayout_6 = new QGridLayout(tab_all);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        sArea_all = new QScrollArea(tab_all);
        sArea_all->setObjectName(QStringLiteral("sArea_all"));
        sArea_all->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 605, 474));
        sArea_all->setWidget(scrollAreaWidgetContents_3);

        gridLayout_6->addWidget(sArea_all, 0, 0, 1, 1);

        Button_all = new QPushButton(tab_all);
        Button_all->setObjectName(QStringLiteral("Button_all"));

        gridLayout_6->addWidget(Button_all, 1, 0, 1, 1);

        tabWidget->addTab(tab_all, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        profileClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(profileClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 651, 23));
        profileClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(profileClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        profileClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(profileClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        profileClass->setStatusBar(statusBar);

        retranslateUi(profileClass);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(profileClass);
    } // setupUi

    void retranslateUi(QMainWindow *profileClass)
    {
        profileClass->setWindowTitle(QApplication::translate("profileClass", "profile", 0));
        Button_tip->setText(QApplication::translate("profileClass", "\347\202\271\345\207\272\350\212\261\347\223\243\351\241\266\347\202\271", 0));
        Button_curve->setText(QApplication::translate("profileClass", "\344\276\247\350\276\271\346\233\262\347\272\277", 0));
        Button_contour->setText(QApplication::translate("profileClass", "\350\212\261\347\223\243\350\275\256\345\273\223", 0));
        Button_point->setText(QApplication::translate("profileClass", "\347\202\271\345\207\272\344\270\255\350\275\264\347\202\271", 0));
        label_image->setText(QString());
        Button_scan->setText(QApplication::translate("profileClass", "\351\200\211\346\213\251\345\233\276\347\211\207", 0));
        Button_keypoint->setText(QApplication::translate("profileClass", "\345\244\204\347\220\206\346\225\260\346\215\256", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_pre), QApplication::translate("profileClass", "preprocess", 0));
        Button_mesh->setText(QApplication::translate("profileClass", "\346\250\241\346\235\277\350\212\261\347\223\243\347\275\221\346\240\274", 0));
        Button_petal->setText(QApplication::translate("profileClass", "\346\250\241\346\235\277\350\212\261\347\223\243\350\275\256\345\273\223\346\230\240\345\260\204", 0));
        Button_meshfitting->setText(QApplication::translate("profileClass", "\346\250\241\346\235\277\350\212\261\347\223\243\347\275\221\346\240\274\345\217\230\345\275\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_surface), QApplication::translate("profileClass", "surface fitting", 0));
        Button_all->setText(QApplication::translate("profileClass", "\345\256\214\346\225\264\347\275\221\346\240\274", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_all), QApplication::translate("profileClass", "all petals", 0));
    } // retranslateUi

};

namespace Ui {
    class profileClass: public Ui_profileClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
