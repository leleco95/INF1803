#ifndef RSSVIEW_H
#define RSSVIEW_H

#include <QWidget>
#include <QLineEdit>

class RSSView : public QWidget
{
    Q_OBJECT

public:
    RSSView(QWidget *parent = nullptr);

private:
    QLineEdit *m_urlLineEdit;
};

#endif // RSSVIEW_H
