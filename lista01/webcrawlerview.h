#ifndef WEBCRAWLERVIEW_H
#define WEBCRAWLERVIEW_H

#include <QWidget>
#include <QLineEdit>

class WebCrawlerView : public QWidget
{
    Q_OBJECT

public:
    WebCrawlerView(QWidget *parent = nullptr);

private:
    QLineEdit *m_urlLineEdit;
};

#endif // WEBCRAWLERVIEW_H
