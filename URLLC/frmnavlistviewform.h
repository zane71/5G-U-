#ifndef FRMNAVLISTVIEWFORM_H
#define FRMNAVLISTVIEWFORM_H
#include "QDebug"
#include <string>
#include <QMainWindow>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;
#include <iostream>
#include <QLabel>
#include <QWidget>
#include <QtNetwork/QHostInfo>
//#include <loginwidget.h>

namespace Ui {
class frmNavListViewForm;
}

class frmNavListViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavListViewForm(QWidget *parent = 0);
    ~frmNavListViewForm();

private slots:
    void initForm();
    void on_listView_pressed();

    void on_confWrite_clicked();
    void on_readButton_clicked();
    void on_writeButton_clicked();

    void on_netCheckBox_stateChanged(int arg1);

private:
    QLabel *m_logo;
    Ui::frmNavListViewForm *ui;
};

#endif // FRMNAVLISTVIEWFORM_H
