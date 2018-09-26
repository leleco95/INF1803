#ifndef RSSVIEW_H
#define RSSVIEW_H

#include <QNetworkAccessManager>
#include <QWebEngineView>
#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

class RSSView : public QWidget
{
    Q_OBJECT

public:
    RSSView(QWidget *parent = nullptr);

private slots:
    void replyFinished(QNetworkReply*);
    void addButtonClicked();
    void removeButtonClicked();
    void loadButtonClicked();
    void clearButtonClicked();

private:
    QLineEdit *m_urlLineEdit;
    QComboBox *m_urls;
    QNetworkAccessManager *m_manager;
    QWebEngineView *m_webEngineView;
};

#endif // RSSVIEW_H
