#include "mainwindow.h"

#include <QApplication>

void View_allNetworkInterface();
void View_checkIP(QString name);
void SetIP(QString name,QString ip);

void View_allNetworkInterface()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();//获取所有网络接口的列表
    //foreach(QNetworkInterface aInterface,list)//foreach遍历
    for(int i=0;i<list.count();i++)
    {
        QNetworkInterface aInterface=list.at(i);
        if(!aInterface.isValid())
            continue;
        qDebug() << "**************************************************************************";
        qDebug() <<"Device: "<<aInterface.humanReadableName();
        qDebug() <<"Hardware Address: "<<aInterface.hardwareAddress();
        QList<QNetworkAddressEntry> entryList= aInterface.addressEntries();//获取每个接口的地址列表
        for(int j=0;j<entryList.count();j++)
        {
            QNetworkAddressEntry aEntry=entryList.at(j);
            if(aEntry.ip().protocol()==QAbstractSocket::IPv4Protocol)  //获取IPv4的地址
            {
                qDebug() <<"IPV4: "<<aEntry.ip().toString();
                qDebug() <<"Netmask: "<<aEntry.netmask().toString();
                qDebug() <<"Broadcast: "<<aEntry.broadcast().toString();
            }
        }
    }
}

void View_checkIP(QString name)
{
    int FoundFlag=0;//是否查询到指定名称设备的标志位
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int i=0;i<list.count();i++)
    {
        QNetworkInterface aInterface=list.at(i);
        if(!aInterface.isValid())
            continue;
//        qDebug() << typeid (aInterface.humanReadableName()).name();
        if(aInterface.humanReadableName()==name)
        {
            FoundFlag=1;
            qDebug() << "**************************************************************************";
            qDebug() <<"Device: "<<aInterface.humanReadableName();
            qDebug() <<"Hardware Address: "<<aInterface.hardwareAddress();
            QList<QNetworkAddressEntry> entryList= aInterface.addressEntries();//获取每个接口的地址列表
            for(int j=0;j<entryList.count();j++)
            {
                QNetworkAddressEntry aEntry=entryList.at(j);
                if(aEntry.ip().protocol()==QAbstractSocket::IPv4Protocol)  //获取IPv4的地址
                {
                    qDebug() <<"IPV4: "<<aEntry.ip().toString();
                    qDebug() <<"Netmask: "<<aEntry.netmask().toString();
                    qDebug() <<"Broadcast: "<<aEntry.broadcast().toString();
                }
            }
            break;
        }
    }
    if(FoundFlag==0)
    {
        qDebug() << "Not Found";
    }
}

void SetIP(QString name,QString ip)
{
    QProcess process;
    QString cmd = "netsh interface ip set address ";
//    cmd +="\"VMware Network Adapter VMnet1\" ";//网卡名称要加双引号
    cmd += "\""+name+"\" ";
    cmd += "static ";
    cmd += ip;
    cmd += " 255.255.255.0 ";
    cmd += "192.168.10.1";
    qDebug() << "**************************************************************************";
    qDebug()<<"cmd = "<<cmd;
    process.start(cmd);
    process.waitForFinished();
}

int main(int argc, char *argv[])
{
    //显示所有网络接口及相关信息
    View_allNetworkInterface();
    //查看指定名称设备的信息
    View_checkIP("VMware Network Adapter VMnet1");
    //修改指定名称设备的IP地址
    SetIP("VMware Network Adapter VMnet1","192.168.10.1");
    View_checkIP("VMware Network Adapter VMnet1");

    QApplication a(argc, argv); //定义实例a,并创建应用程序
    MainWindow w;               //定义并创建窗口
    w.show();                   //显示窗口
    return a.exec();            //启动应用程序执行,开始应用程序的消息循环与事件处理
}
