#include "webcrawlerview.h"
#include <QXmlStreamReader>
#include <QModelIndexList>
#include <QWebEnginePage>
#include <QNetworkReply>
#include <QTextDocument>
#include <QDomDocument>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QBoxLayout>
#include <QSettings>
#include <QLabel>
#include <QList>

WebCrawlerView::WebCrawlerView(QWidget *parent) :
    QWidget(parent)
{
    QBoxLayout *mainLayout;
    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(2);
    mainLayout->addLayout(gridLayout);

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    m_webEngineView = new QWebEngineView(this);
    m_webEngineView->load(QUrl("about:blank"));
    connect(m_webEngineView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished()));

    m_urlLineEdit = new QLineEdit("");

    QPushButton *fetchButton = new QPushButton(tr("Fetch"));
    connect(fetchButton, SIGNAL(clicked(bool)), this, SLOT(fetchButtonClicked()));

    int row = 0;
    gridLayout->addWidget(new QLabel("URL"), row, 0);
    gridLayout->addWidget(m_urlLineEdit, row, 1);
    gridLayout->addWidget(fetchButton, row++, 2);
//    gridLayout->addWidget(m_webEngineView, row++, 0, 1, 2);
}

void WebCrawlerView::loadFinished()
{
    qDebug() << m_webEngineView->page()->findChildren<QWidget*>("a").isEmpty();
}

void WebCrawlerView::replyFinished(QNetworkReply * netReply)
{
//    QString pageContent = QString::fromStdString(netReply->readAll().toStdString());
    QTextStream textStream(netReply->readAll());
    while(!textStream.atEnd()) {
        QString line = textStream.readLine();
        if(line.contains("href"))
            qDebug() << line;
    }

//    QTextDocument textDoc;
//    textDoc.setHtml(pageContent);
////    qDebug() << textDoc.toPlainText();

//    QXmlStreamReader xmlReader(pageContent);
//    while(!xmlReader.atEnd()) {
//        xmlReader.readNext();
////        qDebug() << xmlReader.name();
//        if(xmlReader.isStartElement()) {
//            if(xmlReader.name() == "a")
//                qDebug() << xmlReader.attributes().value("href").toString();
//        }
//    }
}

void WebCrawlerView::fetchButtonClicked()
{
//    m_manager->get(QNetworkRequest(QUrl(m_urlLineEdit->text())));
    m_webEngineView->load(QUrl(m_urlLineEdit->text()));
}
