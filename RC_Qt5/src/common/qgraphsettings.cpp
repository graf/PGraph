#include "qgraphsettings.h"
#include "globalvariables.h"
#include <QtCore>


QGraphSettings   *globalSettings;

QGraphSettings::QGraphSettings(const QString &configPath)
{
    myConfigPath = configPath;
    myIsParallelSet = false;
    myIsParallel = false;

    myOutputDirectorySet = false;
    myOutputDirectory = "Out/";

    myBaseDirectorySet = false;
    myBaseDirectory = "C/";

    myTemplateDirectorySet = false;
    myTemplateDirectory = "./Templates/";

    myProjectsDirectorySet = false;
    myProjectsDirectory = "./Projects/";
}

QString QGraphSettings::getOutputDirectory()
{
    if (myOutputDirectorySet == false) {
        QSettings c(myConfigPath, QSettings::IniFormat);
        const QString outputDirectory = getProjectsDirectory() + "/" + globalDBManager->getProjectName() + "/" + c.value("Location/OutputDir", myOutputDirectory).toString();
        if (!QDir(outputDirectory).exists())
            QDir().mkpath(outputDirectory);
        myOutputDirectory = QFileInfo(outputDirectory).canonicalFilePath();
        myOutputDirectorySet = true;
    }
    return myOutputDirectory;
}

QString QGraphSettings::getBaseDirectory()
{
    if (myBaseDirectorySet == false) {
        QSettings c(myConfigPath, QSettings::IniFormat);
        const QString baseDirectory = getProjectsDirectory() + "/" + globalDBManager->getProjectName() + "/" + c.value("Location/BaseDir", myBaseDirectory).toString();
        if (!QDir(baseDirectory).exists())
            QDir().mkpath(baseDirectory);
        myBaseDirectory = QFileInfo(baseDirectory).canonicalFilePath();
        myBaseDirectorySet = true;
    }
    return myBaseDirectory;
}

QString QGraphSettings::getTemplateDirectory()
{
    if (myTemplateDirectorySet == false) {
        QSettings c(myConfigPath, QSettings::IniFormat);
        myTemplateDirectory = QFileInfo(c.value("Location/TemplateDir", myTemplateDirectory).toString()).canonicalFilePath();
        myTemplateDirectorySet = true;
    }
    return myTemplateDirectory;
}

QString QGraphSettings::getProjectsDirectory()
{
    if (myProjectsDirectorySet == false) {
        QSettings c(myConfigPath, QSettings::IniFormat);
        myProjectsDirectory = QFileInfo(c.value("Location/ProjectsDir", myProjectsDirectory).toString()).canonicalFilePath();
        myProjectsDirectorySet = true;
    }
    return myProjectsDirectory;
}

bool QGraphSettings::isParallel()
{
    if (myIsParallelSet == false) {
        QSettings c(myConfigPath, QSettings::IniFormat);
        myIsParallel = c.value("Compiler/Parallel", false).toBool();
        myIsParallelSet = true;
    }
    return myIsParallel;
}
