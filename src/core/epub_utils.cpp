#include "epub_utils.h"
#include <QRegularExpression>
#include "quazip.h"
#include "quazipfile.h"
#include <QBuffer>
#include <QIODevice>

bool EPUBUtils::isValidEPUB(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;
    
    // 检查是否是ZIP格式并且包含mimetype文件
    QuaZip zip(filePath);
    if (!zip.open(QuaZip::mdUnzip)) return false;
    
    bool hasMimetype = false;
    if (zip.setCurrentFile("mimetype")) {
        QuaZipFile mimetypeFile(&zip);
        if (mimetypeFile.open(QIODevice::ReadOnly)) {
            QByteArray mimeData = mimetypeFile.readAll();
            QString mime = QString::fromUtf8(mimeData).trimmed();
            if (mime == "application/epub+zip") {
                hasMimetype = true;
            }
            mimetypeFile.close();
        }
    }
    
    zip.close();
    return hasMimetype;
}

QString EPUBUtils::extractTextFromHTML(const QString& htmlContent) {
    QString text = htmlContent;
    
    // 移除脚本和样式标签
    text.remove(QRegularExpression("<script[^>]*>.*?</script>", QRegularExpression::CaseInsensitiveOption));
    text.remove(QRegularExpression("<style[^>]*>.*?</style>", QRegularExpression::CaseInsensitiveOption));
    
    // 移除所有HTML标签
    text.remove(QRegularExpression("<[^>]*>"));
    
    // 转换HTML实体
    text.replace("&nbsp;", " ");
    text.replace("&#160;", " ");
    text.replace("&amp;", "&");
    text.replace("&lt;", "<");
    text.replace("&gt;", ">");
    text.replace("&quot;", "\"");
    text.replace("&#39;", "'");
    
    // 清理多余空白
    text = text.simplified();
    
    return text;
}

QStringList EPUBUtils::getChapterTitles(const QString& containerXml) {
    QStringList chapters;
    QXmlStreamReader xml(containerXml);
    
    while (!xml.atEnd()) {
        if (xml.readNext() == QXmlStreamReader::StartElement) {
            if (xml.name() == QStringLiteral("navLabel") || xml.name() == QStringLiteral("title")) {
                QString title = xml.readElementText().trimmed();
                if (!title.isEmpty()) {
                    chapters.append(title);
                }
            }
        }
    }
    
    if (chapters.isEmpty()) {
        // 如果没有找到章节标题，创建默认章节
        chapters << "第一章" << "第二章" << "第三章" << "第四章" << "第五章";
    }
    
    return chapters;
}

QByteArray EPUBUtils::getFileContent(const QString& filePath, const QString& internalPath) {
    QuaZip zip(filePath);
    if (!zip.open(QuaZip::mdUnzip)) return QByteArray();
    
    if (!zip.setCurrentFile(internalPath)) {
        zip.close();
        return QByteArray();
    }
    
    QuaZipFile file(&zip);
    if (!file.open(QIODevice::ReadOnly)) {
        zip.close();
        return QByteArray();
    }
    
    QByteArray content = file.readAll();
    file.close();
    zip.close();
    return content;
}

QString EPUBUtils::getContainerXMLPath() {
    return "META-INF/container.xml";
}

QString EPUBUtils::getOpfPath(const QString& containerXml) {
    QXmlStreamReader xml(containerXml);
    while (!xml.atEnd()) {
        if (xml.readNext() == QXmlStreamReader::StartElement) {
            if (xml.name() == QStringLiteral("rootfile")) {
                return xml.attributes().value("full-path").toString();
            }
        }
    }
    return "content.opf";
}

QStringList EPUBUtils::getContentFiles(const QString& opfContent) {
    QStringList contentFiles;
    QXmlStreamReader xml(opfContent);
    
    while (!xml.atEnd()) {
        if (xml.readNext() == QXmlStreamReader::StartElement) {
            if (xml.name() == QStringLiteral("item") || xml.name() == QStringLiteral("manifest")) {
                QString id = xml.attributes().value("id").toString();
                QString href = xml.attributes().value("href").toString();
                if (id.contains("chapter", Qt::CaseInsensitive) || 
                    href.endsWith(".html", Qt::CaseInsensitive) || 
                    href.endsWith(".xhtml", Qt::CaseInsensitive)) {
                    contentFiles.append(href);
                }
            }
        }
    }
    
    return contentFiles;
}