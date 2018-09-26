#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>

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

    connect(this, SIGNAL(starting()), m_rssView, SLOT(load()));
    connect(this, SIGNAL(closing()), m_rssView, SLOT(save()));

    setProgramRSS();
    emit starting();
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit closing();
    event->accept();
}
