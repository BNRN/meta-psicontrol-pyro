#include "resultlogger.h"
#include <QDir>

ResultLogger::ResultLogger(QObject *parent) : QObject(parent)
{
    //create log file, if not possible, send error to screen
    QDir tempDir("/tmp");

    mFile = new QFile();
    mFile->setFileName(tempDir.absoluteFilePath(mFilename));


     mProcess = new QProcess(this);
     connect (mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
     connect (mProcess, SIGNAL(readyReadStandardError()), this, SLOT(printError()));
     connect(mProcess, SIGNAL(stateChanged(QProcess::ProcessState)), SLOT(stateChanged(QProcess::ProcessState)));

}
ResultLogger::~ResultLogger()
{
    if(mFile)
    {
        mFile->close();
        delete mFile;
    }
    if(mProcess) delete mProcess;
}
void ResultLogger::stateChanged(QProcess::ProcessState state)
{
    qDebug("Process::stateChanged %d", state);
    if( state == 0)
    {
      emit infoSubmitted ("done");
    }
}

void ResultLogger::printOutput()
{

    QByteArray processOutput = mProcess->readAllStandardOutput();
    qDebug ("Process out : ");
    qDebug (processOutput);

    emit infoSubmitted ("ok");
}
void ResultLogger::printError()
{
    QByteArray processOutput = mProcess->readAllStandardError();
    qDebug ("Process error  : ");
    qDebug (processOutput);
    emit infoSubmitted ("Could not reach the server");
}
void ResultLogger::handleSubmitInfo(const QVariant& info)
{
    if(!mFile->isOpen())
    {
        mFile->open(QIODevice::ReadWrite);
    }
    if( mFile->isOpen() )
    {
        qDebug ("handleSubmitInfo");
        QMap<QString,QVariant> map = info.toMap();
        QTextStream  stream(mFile);
        typename QMap<QString, QVariant>::ConstIterator it = map.end();
        typename QMap<QString, QVariant>::ConstIterator begin = map.begin();
        while (it != begin)
        {
            --it;
            stream << it.key() << " " <<  it.value().toString()<< endl;
        }
        emit infoSubmitted ("ok");
    }
    else
    {
        emit infoSubmitted ("Could not open the log file!");
    }
}

void ResultLogger::SendFile()
{
    qDebug ("sendfile");
    mProcess->setWorkingDirectory("");
    mProcess->start("/bin/sh",QStringList() << "SendColorTestResult.sh");
    //return mProcess->waitForStarted();
}
