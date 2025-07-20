#pragma once

#include <QWidget>

class PreviewBar : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewBar(QWidget *parent = nullptr);

    void setTotalPages(int total);
    void setCurrentPage(int current);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_totalPages = 0;
    int m_currentPage = 0;
};