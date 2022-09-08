#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{

        ui->setupUi(this);
        this->setWindowIcon(QIcon(":/image/logo.png"));
        setWindowTitle("登录");
        // connect 3个信号槽
//            // 触发用户按钮的信号槽连接
//            connect(ui->userButton,SIGNAL(clicked()),this,SLOT(on_userButton_clicked()));
            // 触发登录按钮的信号槽连接
            //connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(on_loginButton_clicked()));
//            // 发出信号后关闭登录窗口的信号槽连接
//            connect(this,SIGNAL(close_window()),this,SLOT(close()));
            ui->lineEdit_pw->setEchoMode(QLineEdit::Password);//输入的时候就显示圆点
            //ui->loginButton->setFocus();    //设置默认焦点
            //ui->loginButton->setShortcut( QKeySequence::InsertParagraphSeparator );  //设置快捷键为键盘的“回车”键
            //ui->loginButton->setDefault();  //设置默认按钮，设置了这个属性，当用户按下回车的时候，就会按下该按钮
            root_password = "123456";
}

        // 清理输入栏
//        void LogWidget::btn_clear_clicked()
//        {
//            ui->edit_pw->clear();
//            ui->edit_name->clear();
//        }

        // 登录按钮触发事件
        void LoginDialog::on_loginButton_clicked()
        {
            // 从输入框获取密码
            QString password = ui->lineEdit_pw->text();

            //账号和密码匹配正确
            if ( password == root_password)
            {
//              this->hide();
                f.show();
                //调用move()函数,j将窗口移动到屏幕中央
                f.move ((QApplication::desktop()->width() - f.width())/2,(QApplication::desktop()->height() - f.height())/2);
                this->close();
            }
            else if ( password == NULL)
                QMessageBox::warning(this, "提示","密码为空！");

            else // 账号或密码错误
                QMessageBox::warning(this, "提示","管理员密码错误！");
        }

        void LoginDialog::on_userButton_clicked()
        {
            f.show();
            f.move ((QApplication::desktop()->width() - f.width())/2,(QApplication::desktop()->height() - f.height())/2);
            this->close();
//            emit(user());
//            emit(close_window());
        }


LoginDialog::~LoginDialog()
{
    delete ui;
}


