#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "resultlogger.h"

class MainView : public QObject
{
    Q_OBJECT
private:
    QQmlApplicationEngine mEngine;
    ResultLogger mLogger;
    bool mLastView;
public:
    explicit MainView(QObject *parent = 0);

    void show();

signals:
    void setSource(QVariant source);
    void setErrorText(QVariant source);

public slots:
    void handleReloadDone();
    void handleFinishTest(const QVariant& info);
    void infoSubmitted(const QVariant& result);

};

#endif // MAINVIEW_H
