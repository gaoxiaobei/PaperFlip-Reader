  #include "EPUBManager.h"
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QDir>
#include <QTextCodec>
#include <QRegularExpression>
#include <utility> // For std::as_const

EPUBManager::EPUBManager(QObject *parent)
    : QObject(parent)
{
}

bool EPUBManager::loadEPUB(const QString &filePath)
{
    m_bookFilePath = filePath;
    m_pages.clear();
    m_metadata = BookMetadata();
    m_manifest.clear();
    m_spine.clear();

    QuaZip zip(filePath);
    if (!zip.open(QuaZip::mdUnzip)) {
        emit loadError("Failed to open EPUB file. Error code: " + QString::number(zip.getZipError()));
        return false;
    }

    if (!parseContainerXml(zip)) {
        emit loadError("Failed to parse container.xml.");
        zip.close();
        return false;
    }

    if (!parseOpf(zip)) {
        emit loadError("Failed to parse OPF file.");
        zip.close();
        return false;
    }

    paginateContents(zip);

    zip.close();

    if(m_pages.isEmpty()){
        emit loadError("No content found in EPUB after parsing.");
        return false;
    }

    emit bookLoaded();
    return true;
}

bool EPUBManager::parseContainerXml(QuaZip& zip)
{
    const QString containerPath = "META-INF/container.xml";
    if (!zip.setCurrentFile(containerPath)) {
        qWarning() << "META-INF/container.xml not found in EPUB.";
        return false;
    }

    QuaZipFile file(&zip);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open container.xml for reading.";
        return false;
    }

    QXmlStreamReader xml(file.readAll());
    file.close();

    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name().toString() == "rootfile") {
            m_opfPath = xml.attributes().value("full-path").toString();
            if (!m_opfPath.isEmpty()) {
                m_contentBasePath = QFileInfo(m_opfPath).path();
                if(m_contentBasePath == "."){
                    m_contentBasePath = "";
                } else {
                    m_contentBasePath += "/";
                }
                return true;
            }
        }
    }

    qWarning() << "Could not find rootfile path in container.xml.";
    return false;
}

bool EPUBManager::parseOpf(QuaZip& zip)
{
    if (!zip.setCurrentFile(m_opfPath)) {
        qWarning() << "OPF file not found at:" << m_opfPath;
        return false;
    }

    QuaZipFile file(&zip);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open OPF file for reading:" << m_opfPath;
        return false;
    }

    QXmlStreamReader xml(file.readAll());
    file.close();

    bool inMetadata = false;
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        if (xml.isStartElement()) {
            QString name = xml.name().toString();

            if (name == "metadata") inMetadata = true;

            if (inMetadata) {
                if (name == "title") {
                    m_metadata.title = xml.readElementText();
                } else if (name == "creator") {
                    m_metadata.author = xml.readElementText();
                }
            }
            if (name == "item") {
                QString id = xml.attributes().value("id").toString();
                QString href = xml.attributes().value("href").toString();
                if (!id.isEmpty() && !href.isEmpty()) {
                    QString fullPath = m_contentBasePath + href;
                    m_manifest[id] = QDir::cleanPath(fullPath);
                }
            } else if (name == "itemref") {
                QString idref = xml.attributes().value("idref").toString();
                if (!idref.isEmpty()) {
                    m_spine.append(idref);
                }
            }
        }
        if(xml.isEndElement()){
            if(xml.name().toString() == "metadata") inMetadata = false;
        }
    }

    if (m_spine.isEmpty()) {
        qWarning() << "No spine items found in OPF file.";
        return false;
    }

    return true;
}

void EPUBManager::paginateContents(QuaZip& zip)
{
    QString fullBookContent;
    for (const QString &idref : std::as_const(m_spine)) {
        if (m_manifest.contains(idref)) {
            QString chapterPath = m_manifest.value(idref);

            if(!zip.setCurrentFile(chapterPath)){
                qWarning() << "Could not find chapter file in zip:" << chapterPath;
                continue;
            }
            QuaZipFile file(&zip);
            if (!file.open(QIODevice::ReadOnly)) {
                qWarning() << "Could not open chapter file for reading:" << chapterPath;
                continue;
            }

            QString htmlContent = readTextFromEntry(file);
            file.close();
            fullBookContent += htmlToText(htmlContent) + "\n\n";
        }
    }

    if (fullBookContent.trimmed().isEmpty()) {
        qWarning() << "No text content could be extracted from the EPUB spine.";
        return;
    }

    // Simple pagination logic
    int charsPerPage = 800;
    int totalPages = (fullBookContent.length() + charsPerPage - 1) / charsPerPage;

    for (int i = 0; i < totalPages; ++i) {
        EPUBPage page;
        page.pageNumber = i;
        page.chapterTitle = m_metadata.title; // Simplified for now
        page.content = fullBookContent.mid(i * charsPerPage, charsPerPage);
        m_pages.append(page);
    }
}

QString EPUBManager::readTextFromEntry(QuaZipFile& file)
{
    QByteArray data = file.readAll();
    QTextCodec *codec = QTextCodec::codecForHtml(data);
    return codec->toUnicode(data);
}

QString EPUBManager::htmlToText(const QString& html)
{
    QString text = html;
    text.remove(QRegularExpression("<[^>]*>"));
    text.replace("&nbsp;", " ");
    text.replace("&amp;", "&");
    text.replace("&lt;", "<");
    text.replace("&gt;", ">");
    text.replace("&quot;", "\"");
    return text.simplified();
}

BookMetadata EPUBManager::getMetadata() const
{
    return m_metadata;
}

QString EPUBManager::getPageContent(int pageIndex) const
{
    if (pageIndex >= 0 && pageIndex < m_pages.size()) {
        return m_pages[pageIndex].content;
    }
    return "Page not found";
}

int EPUBManager::getTotalPages() const
{
    return m_pages.size();
}
