#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>

class ReaderWidget;
class EPUBManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openFile();
    void showAbout();

private:
    void createMenu();
    void createToolbar();

    ReaderWidget *m_readerWidget;
    EPUBManager *m_epubManager;
};