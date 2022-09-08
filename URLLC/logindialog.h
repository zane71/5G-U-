#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <frmnavlistviewform.h>
#include <QDesktopWidget>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    //void keyPressEvent(QKeyEvent *event);    //设置回车响应函数
    frmNavListViewForm f;

signals:
    void close_window(); //关闭登录界面信号

private slots:
    void on_userButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
    QString root_password;
};

#endif // LOGINWIDGET_H

