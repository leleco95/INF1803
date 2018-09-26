#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webcrawlerview.h"
#include <QStackedWidget>
#include <QMainWindow>
#include "rssview.h"
#include "const.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void closeEvent(QCloseEvent *event);

signals:
    void starting();
    void closing();

private slots:
    void setProgramRSS();
    void setProgramWebCrawler();

private:
    Ui::MainWindow *ui;

    QStackedWidget *m_stackedWidget;
    Program m_currentProgram = Program_RSSReader;
    RSSView *m_rssView;
    WebCrawlerView *m_webCrawlerView;
};

#endif // MAINWINDOW_H
