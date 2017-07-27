#include "mainview.h"

MainView::MainView(QObject *parent) : QObject(parent), mEngine(), mLogger()
{
    //load the main.qml which holds the loader for other qnml's
    mEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* root = mEngine.rootObjects().first();
    //signal to set source of loader in main.qml
    QObject::connect(this,SIGNAL(setSource(QVariant)), root, SLOT(setSource(QVariant)));
    // signal from main.qml to indicate the loader has been loaded
    QObject::connect(root,SIGNAL(reloadDone()), this, SLOT(handleReloadDone()));

}

void MainView::show()
{
    //start the colortest
    emit setSource("qrc:/ColorTest.qml");
    mLastView = false;
}

void MainView::handleReloadDone()
{
    QObject* root = mEngine.rootObjects().first();
    // check for colortest
    QObject* colorTest = root->findChild<QObject*>("colorTest");
    QObject* expMainView = root->findChild<QObject*>("expMainView");
    QObject* errorView = root->findChild<QObject*>("error");
    if(errorView)
    {
        // set error text
        QObject::connect(this,SIGNAL(setErrorText(QVariant)), errorView, SLOT(setErrorText(QVariant)));
    }
    else
    {
        if(expMainView)
        {
           QObject::connect(expMainView,SIGNAL(finishTest(QVariant)), this, SLOT(handleFinishTest(QVariant)));
        }
        else
        {
            if(colorTest)
            {
                //connect QML signal to c++ slot
                QObject::connect(colorTest,SIGNAL(finishTest(QVariant)), this, SLOT(handleFinishTest(QVariant)));
                //connect c++ signal to QML slot
                QObject::connect(&mLogger,SIGNAL(infoSubmitted(QVariant)), this, SLOT(infoSubmitted(QVariant)));
            }
        }
    }
}
// qml signal from screen touches
void MainView::handleFinishTest(const QVariant& info)
{
    mLogger.handleSubmitInfo(info);
}

void MainView::infoSubmitted(const QVariant& result)
{
    if( result.toString().compare("ok")  == 0 )
    {
       if(mLastView)
       {
           emit setSource("");
           emit setSource("qrc:/Error.qml");
           emit setErrorText("test finished: sending result");
           
           mLogger.SendFile();

//           if( !mLogger.SendFile())
//           {
//               emit setSource("");
//               emit setSource("qrc:/Error.qml");
//               emit setErrorText(result);
//           }
//           else
//           {
//               exit(1);
//           }
       }
       else
       {
            // launch next qml
            mLastView = true;
            emit setSource("");
            emit setSource("qrc:/Qt5_CinematicExperience.qml");
       }
    }
   else
   {
        emit setSource("");
        emit setSource("qrc:/Error.qml");
        emit setErrorText(result);
   }
}
