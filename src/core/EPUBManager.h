#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include "quazip.h"
#include "quazipfile.h"

struct EPUBPage {
    QString content;
    QString chapterTitle;
    bool hasImages = false;
    int pageNumber = 0;
};

struct BookMetadata {
    QString title;
    QString author;
    QString coverImagePath;
    QVector<QString> chapterList;
};

class EPUBManager : public QObject
{
    Q_OBJECT

public:
    explicit EPUBManager(QObject *parent = nullptr);

    bool loadEPUB(const QString &filePath);
    BookMetadata getMetadata() const;
    QString getPageContent(int pageIndex) const;
    int getTotalPages() const;

signals:
    void bookLoaded();
    void loadError(const QString &error);

private:
    bool parseContainerXml(QuaZip& zip);
    bool parseOpf(QuaZip& zip);
    void paginateContents(QuaZip& zip);
    QString readTextFromEntry(QuaZipFile& file);
    QString htmlToText(const QString& html);

    QString m_opfPath;
    QString m_contentBasePath;
    QVector<QString> m_spine;
    QMap<QString, QString> m_manifest;

    QVector<EPUBPage> m_pages;
    BookMetadata m_metadata;
    QString m_bookFilePath;
};
