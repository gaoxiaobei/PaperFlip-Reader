#include "MainWindow.h"
#include "ReaderWidget.h"
#include "EPUBManager.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_readerWidget(new ReaderWidget(this))
    , m_epubManager(new EPUBManager(this))
{
    setWindowTitle("PaperFlip - MVP");
    resize(1000, 700);

    createMenu();
    createToolbar();

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(m_readerWidget);
    setCentralWidget(centralWidget);

    statusBar()->showMessage("Ready");
}

void MainWindow::createMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *openAction = fileMenu->addAction("&Open...");
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addSeparator();
    QAction *exitAction = fileMenu->addAction("E&xit");
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    QMenu *helpMenu = menuBar()->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::createToolbar()
{
    QToolBar *toolbar = addToolBar("Main");
    toolbar->setMovable(false);
    toolbar->addAction("Open", this, &MainWindow::openFile);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open EPUB File",
        QString(),
        "EPUB Files (*.epub)");
    
    if (!fileName.isEmpty()) {
        m_readerWidget->loadBook(fileName);
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About PaperFlip", "PaperFlip - MVP Version 0.1");
}