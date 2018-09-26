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

public slots:
    void load();
    void save();

private slots:
    void replyFinished(QNetworkReply*);
    void addButtonClicked();
    void removeButtonClicked();
    void loadButtonClicked();
    void clearButtonClicked();
    void elementsIndexChanged(int);

private:
    QLineEdit *m_urlLineEdit;
    QComboBox *m_urls;
    QComboBox *m_elements;
    QNetworkAccessManager *m_manager;
    QWebEngineView *m_webEngineView;
};

#endif // RSSVIEW_H
