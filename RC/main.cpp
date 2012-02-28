#include <QtGui>
#include <QtCore>
#include <time.h>
#include "qmywindow.h"
#include "qdrawwindow.h"
#include "databasemanager.h"
#include "commonutils.h"
#include "md5.h"
#include "logger.h"
#include "globalvariables.h"
#include "compiler.h"

int main(int argc, char *argv[])
{  	
    QApplication::addLibraryPath("./");
    QApplication a(argc, argv);
    a.setApplicationVersion("05.02.2012 19.05");

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    a.installTranslator(&qtTranslator);

    QList<Logger::Output> logOutput;
    logOutput.append(Logger::Console);
    logOutput.append(Logger::Window);
    globalLogger = new Logger(Logger::Debug, logOutput);
    globalDBManager = new DataBaseManager();
//    globalDBManager->openProjectDB(11);

    if (globalDBManager->lastError().type() != QSqlError::NoError) {
        QMessageBox::critical(NULL, QObject::tr("Ошибка"), QObject::tr("Ошибка подключения к базе данных.\n") + globalDBManager->lastError().databaseText(), QMessageBox::Ok);
        return -1;
    }

    TMyWindow w;
    w.showMaximized();

    int result = a.exec();

    delete globalDBManager;
    delete globalLogger;
    return result;
}
