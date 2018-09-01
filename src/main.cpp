#include "mainwindow.h"
// For DTK 
// #include <DApplication>
// DWIDGET_USE_NAMESPACE
// Other 
#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QDesktopWidget>
#include <QPropertyAnimation>


int main(int argc, char *argv[])
{
    // For DTK
    // DApplication::loadDXcbPlugin();
    // DApplication a(argc, argv);
    // Other
    QApplication a(argc, argv);

    QSettings settings("ypingcn","p2pchat-qt");

    if(!settings.contains("p2pchat-qt-theme"))
        settings.setValue("p2pchat-qt-theme","default");


    QFile qss(":/theme/"+settings.value("p2pchat-qt-theme").toString()+".qss"); // 加载主题
    if( qss.open(QFile::ReadOnly) )
        qApp->setStyleSheet(qss.readAll());
    qss.close();


    if(!settings.contains("p2pchat-qt-lang"))
        settings.setValue("p2pchat-qt-lang","zh-cn");
    if(!settings.contains("p2pchat-qt-send-message-shortcut"))
        settings.setValue("p2pchat-qt-send-message-shortcut","ctrlenter");

    QTranslator Translator; // 加载翻译文件
    if(QSysInfo::kernelType() == "linux")
        Translator.load("/usr/bin/p2pchat-qt/local/"+settings.value("p2pchat-qt-lang").toString()+".qm");
    else
        Translator.load(settings.value("p2pchat-qt-lang").toString()+".qm");
    a.installTranslator(&Translator);

    MainWindow w;
    w.show();
    w.move(( QApplication::desktop()->width()-w.width() )/2,( QApplication::desktop()->height()-w.height() )/2 );

    QPropertyAnimation startUp(&w,"windowOpacity");
    startUp.setDuration(400);
    startUp.setStartValue(0);
    startUp.setEndValue(1);
    startUp.setEasingCurve(QEasingCurve::Linear);
    startUp.start();

    return a.exec();
}
