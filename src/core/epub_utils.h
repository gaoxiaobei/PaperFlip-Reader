#pragma once

#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>

class EPUBUtils {
public:
    static bool isValidEPUB(const QString& filePath);
    static QString extractTextFromHTML(const QString& htmlContent);
    static QStringList getChapterTitles(const QString& containerXml);
    static QByteArray getFileContent(const QString& filePath, const QString& internalPath);
    static QString getContainerXMLPath();
    static QString getOpfPath(const QString& containerXml);
    static QStringList getContentFiles(const QString& opfContent);
};