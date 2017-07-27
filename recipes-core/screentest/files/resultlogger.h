#ifndef RESULTLOGGER_H
#define RESULTLOGGER_H

#include <QObject>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QProcess>

class ResultLogger : public QObject
{
    Q_OBJECT

private:
    QString mFilename="ColorTest.txt";
    QFile*  mFile;
    QProcess* mProcess;
    QJsonObject mLogInfo
    {
        {"red" , "nok"},
        {"blue", "nok"},
        {"black", "nok"},
        {"green", "nok"}
   };

public:
    explicit ResultLogger(QObject *parent = 0);
    ~ResultLogger();
    QJsonObject logInfo() { return mLogInfo; }
    void SendFile();

signals:
    void infoSubmitted(const QVariant& result);

public slots:
    void handleSubmitInfo(const QVariant& info);
    void printOutput();
    void printError();
    void stateChanged(QProcess::ProcessState state);
};

#endif // RESULTLOGGER_H
