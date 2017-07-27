#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "mainview.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    MainView mainViewer;

    mainViewer.show();

    return app.exec();
}
