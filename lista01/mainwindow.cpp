#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->close();
    QMenuBar *menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QMenu *programsMenu = menuBar->addMenu("Programs");
    programsMenu->addAction("RSS Reader", this, SLOT(setProgramRSS()));
    programsMenu->addAction("Web Crawler", this, SLOT(setProgramWebCrawler()));

    m_rssView = new RSSView();
    m_webCrawlerView = new WebCrawlerView();

    m_stackedWidget = new QStackedWidget();
    m_stackedWidget->addWidget(m_rssView);
    m_stackedWidget->addWidget(m_webCrawlerView);
    setCentralWidget(m_stackedWidget);

    setProgramRSS();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setProgramRSS()
{
    m_currentProgram = Program_RSSReader;
    setWindowTitle("RSS Reader");
    m_stackedWidget->setCurrentWidget(m_rssView);
}

void MainWindow::setProgramWebCrawler()
{
    m_currentProgram = Program_WebCrawler;
    setWindowTitle("Web Crawler");
    m_stackedWidget->setCurrentWidget(m_webCrawlerView);
}
