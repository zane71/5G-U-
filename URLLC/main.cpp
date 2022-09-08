#include "frmnavlistview.h"
#include "frmnavlistviewform.h"
#include "logindialog.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmNavListViewForm w;
    LoginDialog logIn;

    logIn.setWindowTitle("登录界面");
    logIn.show();

    //w.Run();        // 空函数 备用
    w.resize(1500,750);  // 设置默认窗口初始大小
    //w.show();
    //QObject::connect(&logIn, SIGNAL(login()), &w, SLOT(on_loginButton_clicked()));
    //w.move((QApplication::loginDialog()->width() - w.width()) / 2, (QApplication::desktop()->height() - w.height()) / 2);  // 窗口设置居中显示

        // 通信模块建立tcp长连接 供前端通信使用
        //pstSockCom->sock_init();
        //pthread_t hPth;
        // pthread_create(&hPth, NULL, recv_parse_thread, (void *) pstSockCom);

        return a.exec();

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif

    //frmNavListView w;
    //frmNavListViewForm w;
    //LoginWidget w;
    //w.show();

    //return a.exec();
}
