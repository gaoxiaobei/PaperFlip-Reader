#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QMouseEvent>
#include <QVector>

class EPUBManager;
class ThumbnailView;
class PreviewBar;

struct PageInfo {
    int pageNumber;
    QString chapterTitle;
    QString content;
    bool hasImages;
};

class ReaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderWidget(QWidget *parent = nullptr);
    void loadBook(const QString &filePath);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onPreviewUpdate();

private:
    void performPagination();
    void generateThumbnails();
    void renderCurrentPage();
    void updatePreview();

    QLabel *m_contentLabel;
    PreviewBar *m_previewBar;
    
    QVector<PageInfo> m_pages;
    int m_currentPage = 0;
    bool m_isDragging = false;
    QPoint m_lastMousePos;
    double m_previewOffset = 0.0;
    double m_targetOffset = 0.0;
    
    QTimer *m_previewTimer;
    bool m_isInPreviewMode = false;
};