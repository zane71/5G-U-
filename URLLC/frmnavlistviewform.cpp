#include "frmnavlistviewform.h"
#include "ui_frmnavlistviewform.h"
#include "qabstractitemmodel.h"
#include "qdebug.h"
#include "QFile"
#include "QFileDialog"

frmNavListViewForm::frmNavListViewForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmNavListViewForm)
{
	ui->setupUi(this);
//    m_logo = new LoginWidget;
//    m_logo->show();
//    // 注意，这个信号槽的作用就是激活主窗口的，我们已经让主窗口不可以自动打开，
//    // 必须通过登录窗口中登录按钮发出的信号槽的信号才能打开
//    connect(m_logo,SIGNAL(login()),this,SLOT(show()));
	this->initForm();
    this->setWindowIcon(QIcon(":/image/logo.png"));
    setWindowTitle("工业5G-U 实验平台");
}

frmNavListViewForm::~frmNavListViewForm()
{
	delete ui;
}

void frmNavListViewForm::initForm()
{
	ui->listView->setIcoColorBg(false);
	ui->listView->setColorLine(QColor(32, 53, 74));
	ui->listView->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
	ui->listView->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));

	//设置数据方式
	QStringList listItem;
    listItem.append("主界面||0|SIA");
    listItem.append("高级参数配置||0|");

    listItem.append("源文件||0|");

    listItem.append("远程访问||0|");
    //listItem.append("防区信息|参数配置||");
    //listItem.append("位置调整|参数配置||");
    //listItem.append("地图编辑|参数配置||");
/*
	listItem.append("警情查询||0|");
	listItem.append("记录查询|警情查询||");
	listItem.append("图像查询|警情查询||");
	listItem.append("视频查询|警情查询||");
	listItem.append("数据回放|警情查询||");

	listItem.append("信息管理||0|");
	listItem.append("学生管理|信息管理|0|");
	listItem.append("教师管理|信息管理|0|");
	listItem.append("成绩管理|信息管理|0|");

	listItem.append("帮助文档||1|");
    */

	ui->listView->setData(listItem);

	//加载xml文件形式
    //ui->listView->readData(":/image/config.xml");
}

void frmNavListViewForm::on_listView_pressed()
{
	QModelIndex index = ui->listView->currentIndex();
    ui->stackedWidget->setCurrentIndex(0);
    QString text = index.data().toString();
    ui->stackedWidget->setCurrentIndex(0);
	if (text == "主界面") {
		ui->stackedWidget->setCurrentIndex(0);
    } else if (text == "高级参数配置") {
		ui->stackedWidget->setCurrentIndex(1);
    } else if (text == "源文件") {
		ui->stackedWidget->setCurrentIndex(2);
    }
    else if (text == "远程访问") {
        ui->stackedWidget->setCurrentIndex(3);
        QString localhostName = QHostInfo::localHostName();
        QHostInfo info = QHostInfo::fromName(localhostName);
        //返回值是该主机名的信信息
        //获取主机名关联的IP地址
         for(QHostAddress address:info.addresses())
            {
                if(address.protocol()==QAbstractSocket::IPv4Protocol)
                {
                    QString ip= address.toString();
                    //qDebug()<<ip;
                    ui->ipEdit->setText(ip);

                }
            }

    }
}

//=============================
struct config
{
    char *name;
    char *value;
    struct config *next;
};
//修改文件
typedef struct configl
{
    char *fn;//文件描述符
    struct config *confs;
} config_t;

//读 配置
config_t *confRead(const char *file_name);
config *newInsert(config *head,const char *key, const char *val);
//提交修改
int confWrite(config_t *one);
//析构
void confDestory(config_t *one);

const char *confGet(const config_t *one, const char *key);
int confSet(config_t *one, const char *key, const char *val);
void confDel(config_t *one, const char *key);


static void freeConfigOne(struct config **one)
{
    struct config *tmp = *one;

    if (!tmp) {
        return;
    }
    if (tmp->name) {
        free(tmp->name);
        tmp->name = NULL;
    }
    if (tmp->value) {
        free(tmp->value);
        tmp->value = NULL;
    }

    *one = tmp->next;
    free(tmp);

    return;
}

static struct config **findNode(const config_t *one, const char *key)
{
    if (!one) {
        return NULL;
    }
    if (!one->confs) {
        return NULL;
    }
    if (!key) {
        return NULL;
    }

    if (!strcmp(one->confs->name, key)) {
        return (struct config **)&one->confs;
    }

    for (struct config *tmp = one->confs; tmp; tmp = tmp->next) {
        if (tmp->next && !strcmp(tmp->next->name, key)) {
            return (struct config **)&tmp->next;
        }
    }

    return NULL;
}

struct config *newConfig(const char *key, const char *val)
{
    size_t keyLen = strlen(key) + 1;
    size_t valLen = strlen(val) + 1;
    if (keyLen <= 1 || valLen <= 1) {
        return NULL;
    }

    struct config *one = (config *)malloc(sizeof(struct config));
    if (one) {
        one->next = NULL;

        one->name = (char *)malloc(keyLen);
        if (!one->name) {
            free(one);
            return NULL;
        }
        strcpy(one->name, key);

        one->value = (char *)malloc(valLen);
        if (!one->value) {
            free(one->name);
            free(one);
            return NULL;
        }
        strcpy(one->value, val);
    }

    return one;
}

config_t *newConfigl(const char *file_name, size_t len)
{
    config_t *one = (config_t *)malloc(sizeof(struct configl));
    if (!one) {
        return NULL;
    }

    one->fn = (char *)malloc(len+1);
    if (!one->fn) {
        free(one);
        return NULL;
    }
    strcpy(one->fn, file_name);
    one->confs = NULL;

    return one;
}

void confDestory(config_t *one)
{
    if (!one) {
        return;
    }
    if (one->fn) {
        free(one->fn);
        one->fn = NULL;
    }
    while (one->confs) {
        freeConfigOne(&one->confs);
    }
    free(one);
    one = NULL;
}
//---------------------------------------插入新点建立链表
config *newInsert(config *head,const char *key, const char *val)
{
    struct config *node = newConfig(key, val);
    if (!node) {
        return NULL;
    }
    if(head){
        node->next=head;
    }
    head = node;
    return head;
}
//---------------------------------------

int confSet(config_t *one, const char *key, const char *val)
{
    if (!one) {
        return 0;
    }

    struct config **tmp = findNode(one, key);
    if (tmp) {
        size_t ol = strlen((*tmp)->value);
        size_t nl = strlen(val);
        if (nl > ol) {
            char *tp = (char *)malloc(nl);
            if (!tp) {
                return -2;
            }
            free((*tmp)->value);
            (*tmp)->value = tp;
        }
        strcpy((*tmp)->value, val);
        return 0;
    }
    one->confs=newInsert(one->confs,key, val);

    return 0;
}


const char *confGet(const config_t *one, const char *key)
{
    struct config **tmp = findNode(one, key);
    if (!tmp) {
        return NULL;
    }

    return (const char *)(*tmp)->value;
}

void confDel(config_t *one, const char *key)
{
    struct config **tmp = findNode(one, key);
    if (tmp) {
        freeConfigOne(tmp);
    }

    return;
}

int confWrite(config_t *one)
{
    char arr[9]="ue_slots";
    if (!one) {
        return -1;
    }
    if (!one->fn) {
        return -1;
    }

    FILE *fp = fopen(one->fn, "w");
    if (NULL == fp) {
        return -1;
    }

   char version[8]="version";
  char str1[6]="eIOT:";
  fprintf(fp, "%s\n", str1);
  char str2[2]="{";
  fprintf(fp, "%s\n", str2);
    for (struct config *tmp = one->confs; tmp; tmp = tmp->next) {
        if(strcmp(tmp->name,version)==0){
               continue;
        }
        if (tmp->name && tmp->value) {

            fprintf(fp, "  %s = %s", tmp->name, tmp->value);
            if (strcmp(tmp->name, arr)) {
                char str4[2]=";";
                fprintf(fp, "%s\n", str4);
            }
            else{
                fprintf(fp, "%s", "\n");

            }
        }
    }

  char str3[3] ="};";
  fprintf(fp, "%s\n", str3);
    fclose(fp);

    return 0;
}

config_t *confRead(const char *file_name)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    size_t palen = strlen(file_name);
    if (palen <= 0) {
        return NULL;
    }

    FILE *fp = fopen(file_name, "r");
    if (NULL == fp) {
        return NULL;
    }

    config_t *one = newConfigl(file_name, palen);
    if (!one) {
        fclose(fp);
        return NULL;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        char *tmp = NULL, *space = NULL;
        char *key = NULL, *val = NULL;
        unsigned char stat = 0; //鐘舵€佹満
        char str[6]="eIOT:";
        if (!strcmp(str, line)) {
            continue;
        }
        char arr[9]="ue_slots";
        for (tmp = line; *tmp; ++tmp) {
            if ((key && 0!=strcmp(key,arr) &&';'== *tmp) || '/' == *tmp || 0x0a == *tmp || 0x0d == *tmp ||'}' == *tmp || '{' == *tmp) {
                if (space) {
                    *space = 0;
                } else {
                    *tmp = 0;
                }
                break;
            } else if (isspace(*tmp)) {
                if (1 == stat) {
                    stat = 2;
                    space = tmp;
                } else if (4 == stat) {
                    stat = 5;
                    space = tmp;
                }
                continue;
            } else if ('=' == *tmp) {
                stat = 3;
                if (space) {
                    *space = 0;
                    space = NULL;
                } else {
                    *tmp = 0;
                }
                continue;
            }

            if (0 == stat) {
                stat = 1;
                key = tmp;
                continue;
            }
            if (3 == stat) {
                stat = 4;
                val = tmp;
                continue;
            }
            if (3 > stat) {
                stat = 1;
                space = NULL;
            } else if (5 == stat) {
                stat = 4;
                space = NULL;
            }
        }

        // 键值对有效 就配置该选项
        if (key && val) {
            confSet(one, key, val);
        }
    }

    free(line);
    fclose(fp);

    return one;
}


//=============================

void frmNavListViewForm::on_confWrite_clicked()
{

    //power
    QString power = ui->powerfactor->text();
    std::string power1 = power.toStdString();
    const char* POWER = power1.c_str();
    //TranMode
    QString tranmode = ui->TranMode->currentText();
    std::string tranmode1 = tranmode.toStdString();
    const char* TMode = tranmode1.c_str();
    //LCh0_TransType
    QString L0_type = ui->LCh0_TransType->currentText();
    std::string L0_type1 = L0_type.toStdString();
    const char* L0TYPE = L0_type1.c_str();
    //tx_freq
    QString tx = ui->tx_freq->text();
    std::string tx1 = tx.toStdString();
    const char* Tx_freq = tx1.c_str();
    //rx_freq
    QString rx = ui->rx_freq->text();
    std::string rx1 = rx.toStdString();
    const char* Rx_freq = rx1.c_str();
    //ue_slots
    QString slot = ui->ue_slots->currentText();
    std::string slot1 = slot.toStdString();
    const char* SLOTs = slot1.c_str();
    //LCh0_Src_ip
    QString sip = ui->LCh0_Src_ip->text();
    std::string sip1 = sip.toStdString();
    const char* SIP = sip1.c_str();
    //LCh0_Src_port
    QString sport = ui->LCh0_Src_port->text();
    std::string sport1 = sport.toStdString();
    const char* SPORT = sport1.c_str();
    //LCh0_Dst_ip
    QString dip = ui->LCh0_Dst_ip->text();
    std::string dip1 = dip.toStdString();
    const char* DIP = dip1.c_str();
    //LCh0_Dst_port
    QString dport = ui->LCh0_Dst_port->text();
    std::string dport1 = dport.toStdString();
    const char* DPORT = dport1.c_str();

    config_t *myconf = confRead("/home/zhun/project/5GU_QT/confl.config");
    //confWrite(myconf);
    confSet(myconf, "powerfactor",POWER);
    confSet(myconf, "rx_freq",Rx_freq);
    confSet(myconf,"tx_freq",Tx_freq);
    confSet(myconf,"LCh0_TransType",L0TYPE);
    confSet(myconf,"TranMode",TMode);//2T2R:3 1T1R:1  2T1R:2  使用2T2R时TX.RX需要单独绑定cpu核
    confSet(myconf,"ue_slots",SLOTs);
    confSet(myconf, "LCh0_Src_ip",SIP);
    confSet(myconf, "LCh0_Src_port",SPORT);
    confSet(myconf,"LCh0_Dst_ip",DIP);
    confSet(myconf,"LCh0_Dst_port",DPORT);
     //完成修改后  提交按钮 选项接口


    confWrite(myconf);
    confDestory(myconf);
    ui->confWrite->setDisabled(false);

}


//Page3读取写入文件
void frmNavListViewForm::on_readButton_clicked()
{
    //获取文件路径及名称
    //QString path = QFileDialog::getOpenFileName(this,"打开文件","/home/zhun/project/5GU_QT","所有文件(*.*);;"
    //                                                            "程序文件(*.h *.cpp);;");
    QString source = ui->Source->currentText();
    //qDebug() << source;
    if(source == "参数源码")
    {
        QString path = "/home/zhun/project/5GU_QT/confl.config" ;
        //判断路径是否为空
        if(path.isEmpty() == false)
        {
             //指定文件路径
            QFile file(path);
            //检查文件打开情况
            bool isOk = file.open(QIODevice::ReadOnly);
            if(isOk == true)
            {
                //读文件 内容放到字节组
                QByteArray array = file.readAll();
                //显示到界面文本框
                ui->SourceEdit->setText(array);
            }
            //文件关闭
            file.close();
        }
    }
    else if(source == "传输层源码")
    {
        QString path = "/home/zhun/project/5GU_QT/data_trans.c" ;
        //判断路径是否为空
        if(path.isEmpty() == false)
        {
             //指定文件路径
            QFile file(path);
            //检查文件打开情况
            bool isOk = file.open(QIODevice::ReadOnly);
            if(isOk == true)
            {
                //读文件 内容放到字节组
                QByteArray array = file.readAll();
                //显示到界面文本框
                ui->SourceEdit->setText(array);
            }
            //文件关闭
            file.close();
        }
    }
    else {
        //设置文件保存路径及文件名
        QString path = QFileDialog::getOpenFileName(this,"打开文件","/home/zhun/project","所有文件(*.*)");
        //判断路径是否为空
        if(path.isEmpty() == false)
        {
             //指定文件路径
            QFile file(path);
            //检查文件打开情况
            bool isOk = file.open(QIODevice::ReadOnly);
            if(isOk == true)
            {
                //读文件 内容放到字节组
                QByteArray array = file.readAll();
                //显示到界面文本框
                ui->SourceEdit->setText(array);
            }
            //文件关闭
            file.close();
        }
    }

}

void frmNavListViewForm::on_writeButton_clicked()
{
    //设置文件保存路径及文件名
    QString path = QFileDialog::getSaveFileName(this,"保存文件","/home/zhun/project/5GU_QT","所有文件(*.*)");
    //检查路径是否为空
    if(path.isEmpty() == false)
    {
    //设置文件文路径
        QFile file;
        file.setFileName(path);
        //判断文件打开
        bool ret = file.open(QIODevice::WriteOnly);
        if(ret == true)
        {
        //讲文本框内容添加至文件
            QString str =ui->SourceEdit->toPlainText();
            file.write(str.toUtf8());
        }
        //关闭文件
        file.close();
    }
}


void frmNavListViewForm::on_netCheckBox_stateChanged(int arg1)
{
    //开启Internet远程访问

    //qDebug()<<arg1;
    if(arg1 == 0){
        ui->dkEdit->setEnabled(true);
    }
    else {
        ui->dkEdit->setEnabled(false);
    }
}

