#ifndef WEBCRAWLERVIEW_H
#define WEBCRAWLERVIEW_H

#include <QNetworkAccessManager>
#include <QWebEngineView>
#include <QLineEdit>
#include <QWidget>

class WebCrawlerView : public QWidget
{
    Q_OBJECT

public:
    WebCrawlerView(QWidget *parent = nullptr);

private slots:
    void replyFinished(QNetworkReply*);
    void loadFinished();
    void fetchButtonClicked();

private:
    QLineEdit *m_urlLineEdit;
    QNetworkAccessManager *m_manager;
    QWebEngineView *m_webEngineView;
};

#endif // WEBCRAWLERVIEW_H
