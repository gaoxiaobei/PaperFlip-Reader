#include "ReaderWidget.h"
#include "../core/EPUBManager.h"
#include "Views/PreviewBar.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

ReaderWidget::ReaderWidget(QWidget *parent)
    : QWidget(parent)
    , m_contentLabel(new QLabel(this))
    , m_previewBar(new PreviewBar(this))
    , m_previewTimer(new QTimer(this))
{
    setMinimumSize(400, 300);
    
    m_contentLabel->setWordWrap(true);
    m_contentLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_contentLabel->setStyleSheet("QLabel { background-color: white; padding: 20px; }");
    
    m_previewBar->setVisible(false);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_contentLabel, 1);
    layout->addWidget(m_previewBar);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_previewTimer->setInterval(16); // ~60 FPS
    connect(m_previewTimer, &QTimer::timeout, this, &ReaderWidget::onPreviewUpdate);
    
    setStyleSheet("background-color: #f5f5f5;");
}

void ReaderWidget::loadBook(const QString &filePath)
{
    qDebug() << "Loading book:" << filePath;
    
    EPUBManager epubManager;
    
    // 加载IPUB内容
    epubManager.loadEPUB(filePath);
    
    // 获取真实内容
    int totalPages = epubManager.getTotalPages();
    for (int i = 0; i < totalPages; i++) {
        PageInfo page;
        page.pageNumber = i;
        page.chapterTitle = "章节 " + QString::number(i / 8 + 1);
        page.content = epubManager.getPageContent(i);
        page.hasImages = (i % 5 == 0);
        m_pages.append(page);
    }
    
    qDebug() << QString("Loaded %1 pages").arg(m_pages.size());
}

void ReaderWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_pages.size() > 0) {
        m_isDragging = true;
        m_lastMousePos = event->pos();
        m_targetOffset = m_previewOffset;
        
        if (!m_isInPreviewMode) {
            m_isInPreviewMode = true;
            m_previewBar->setVisible(true);
            m_previewBar->setCurrentPage(m_currentPage);
            m_previewTimer->start();
        }
    }
    
    QWidget::mousePressEvent(event);
}

void ReaderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging && m_pages.size() > 0) {
        int deltaX = event->pos().x() - m_lastMousePos.x();
        m_targetOffset += deltaX * 0.02; // Adjust sensitivity
        m_targetOffset = qBound(0.0, m_targetOffset, (double)(m_pages.size() - 1));
        
        m_lastMousePos = event->pos();
        update();
    }
    
    QWidget::mouseMoveEvent(event);
}

void ReaderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isDragging && m_pages.size() > 0) {
        m_isDragging = false;
        
        // Round to nearest page
        m_currentPage = qRound(m_targetOffset);
        m_currentPage = qBound(0, m_currentPage, m_pages.size() - 1);
        
        m_isInPreviewMode = false;
        m_previewBar->setVisible(false);
        m_previewTimer->stop();
        
        renderCurrentPage();
    }
    
    QWidget::mouseReleaseEvent(event);
}

void ReaderWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    
    if (m_isInPreviewMode && m_pages.size() > 0) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        int previewWidth = width() * 0.8;
        int previewHeight = 80;
        int previewX = (width() - previewWidth) / 2;
        int previewY = height() - previewHeight - 20;
        
        // Draw preview background
        painter.setBrush(QColor(0, 0, 0, 180));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(previewX, previewY, previewWidth, previewHeight, 10, 10);
        
        // Draw pages preview
        int centerPage = qRound(m_previewOffset);
        int visiblePages = 5;
        int pageWidth = previewWidth / visiblePages;
        
        for (int i = -2; i <= 2; ++i) {
            int pageIndex = centerPage + i;
            if (pageIndex < 0 || pageIndex >= m_pages.size()) continue;
            
            int x = previewX + ((i + 2) * pageWidth) + (pageWidth / 4);
            int y = previewY + 10;
            int w = pageWidth / 2;
            int h = previewHeight - 20;
            
            QRect pageRect(x, y, w, h);
            
            if (i == 0) {
                painter.setBrush(QColor(255, 255, 255, 255)); // Current page highlighted
            } else {
                painter.setBrush(QColor(200, 200, 200, 200));
            }
            
            painter.setPen(QColor(100, 100, 100, 255));
            painter.drawRect(pageRect);
            
            // Draw page number
            painter.setPen(Qt::white);
            painter.drawText(pageRect, Qt::AlignCenter, QString::number(pageIndex + 1));
        }
        
        // Draw chapter info
        if (m_pages.size() > centerPage) {
            QString chapterInfo = m_pages[centerPage].chapterTitle;
            painter.setPen(Qt::white);
            QFont font = painter.font();
            font.setBold(true);
            font.setPointSize(10);
            painter.setFont(font);
            painter.drawText(previewX + 10, previewY - 5, chapterInfo);
        }
    }
}

void ReaderWidget::onPreviewUpdate()
{
    // Smooth transition using easing
    const double easing = 0.1;
    m_previewOffset += (m_targetOffset - m_previewOffset) * easing;
    
    if (qAbs(m_previewOffset - m_targetOffset) < 0.01) {
        // Consider this frame as landable
    }
    
    update();
    
    if (m_isInPreviewMode) {
        int centerPage = qRound(m_previewOffset);
        m_previewBar->setCurrentPage(centerPage);
    }
}

void ReaderWidget::renderCurrentPage()
{
    if (m_currentPage < m_pages.size()) {
        QString displayText = m_pages[m_currentPage].content;
        m_contentLabel->setText(displayText);
    }
}

void ReaderWidget::resizeEvent(QResizeEvent *event)
{
    renderCurrentPage();
    QWidget::resizeEvent(event);
}