#include "PreviewBar.h"
#include <QPainter>

PreviewBar::PreviewBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(60);
    setStyleSheet("background-color: #333;");
}

void PreviewBar::setTotalPages(int total)
{
    m_totalPages = total;
    update();
}

void PreviewBar::setCurrentPage(int current)
{
    m_currentPage = current;
    update();
}

void PreviewBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Background
    painter.setBrush(QColor(50, 50, 50));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
    
    if (m_totalPages <= 0) return;
    
    // Progress bar
    int progressWidth = width() - 20;
    int progressHeight = 6;
    int progressY = height() / 2 - progressHeight / 2;
    
    // Background progress
    QRect progressBg(10, progressY, progressWidth, progressHeight);
    painter.setBrush(QColor(100, 100, 100));
    painter.drawRoundedRect(progressBg, 3, 3);
    
    // Current progress
    double progress = (double)m_currentPage / m_totalPages;
    int currentWidth = progressWidth * progress;
    QRect currentProgress(10, progressY, currentWidth, progressHeight);
    painter.setBrush(QColor(0, 120, 215));
    painter.drawRoundedRect(currentProgress, 3, 3);
    
    // Page numbers
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(9);
    painter.setFont(font);
    
    QString pageText = QString("%1 / %2").arg(m_currentPage + 1).arg(m_totalPages);
    painter.drawText(rect(), Qt::AlignCenter, pageText);
}