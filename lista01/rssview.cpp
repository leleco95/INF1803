#include "rssview.h"
#include <QModelIndexList>
#include <QNetworkReply>
#include <QTextDocument>
#include <QDomDocument>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QBoxLayout>
#include <QSettings>
#include <QLabel>
#include <QDebug>

RSSView::RSSView(QWidget *parent) :
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

    m_urlLineEdit = new QLineEdit("");

    QPushButton *addButton = new QPushButton(tr("Add"));
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addButtonClicked()));

    m_urls = new QComboBox();

    QPushButton *removeButton = new QPushButton(tr("Remove"));
    connect(removeButton, SIGNAL(clicked(bool)), this, SLOT(removeButtonClicked()));

    QPushButton *loadButton = new QPushButton(tr("Load RSS"));
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(loadButtonClicked()));

    QPushButton *clearButton = new QPushButton(tr("Clear"));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonClicked()));

    m_elements = new QComboBox();
    connect(m_elements, SIGNAL(currentIndexChanged(int)), this, SLOT(elementsIndexChanged(int)));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(loadButton);
    buttonsLayout->addWidget(clearButton);

    int row = 0;
    gridLayout->addWidget(new QLabel("New URL"), row, 0);
    gridLayout->addWidget(m_urlLineEdit, row, 1);
    gridLayout->addWidget(addButton, row++, 2);
    gridLayout->addWidget(new QLabel("Database URLs"), row, 0);
    gridLayout->addWidget(m_urls, row, 1);
    gridLayout->addWidget(removeButton, row++, 2);
    gridLayout->addLayout(buttonsLayout, row++, 0, 1, 3);
    gridLayout->addWidget(m_elements, row++, 0, 1, 3);
    gridLayout->addWidget(m_webEngineView, row++, 0, 1, 3);
}

void RSSView::replyFinished(QNetworkReply * netReply)
{
    QDomDocument doc;
    doc.setContent(netReply->readAll(), false);
    QDomElement docElem = doc.documentElement();
    QDomNodeList nodeList = docElem.elementsByTagName("item");

    m_elements->clear();

    QString html = "<table border='1' cellspacing='0' style='border: 1px solid black; text-align: center;'><thead><tr><th>Title</th><th>Author</th><th>Link</th><th>Category</th><th>Publication Date</th><th>Description</th></thead><tbody>";

    for(uint i = 0; i < nodeList.length(); ++i)
    {
        QDomNode node = nodeList.item(i);
        QDomElement e = node.toElement();

        QString elementHtml;

        html += "<tr>";

        QTextDocument textDoc;

        textDoc.setHtml(e.elementsByTagName("title").item(0).firstChild().nodeValue());
        QString strTitle =  textDoc.toPlainText();
        html += "<td>" + strTitle + "</td>" ;

        QString strAuthor = e.elementsByTagName("author").item(0).firstChild().nodeValue();
        if(strAuthor.isEmpty())
            strAuthor = e.elementsByTagName("dc:creator").item(0).firstChild().nodeValue();
        html += "<td>" + strAuthor + "</td>";

        QString strLink = e.elementsByTagName("link").item(0).firstChild().nodeValue();
        html += "<td><a href='" + strLink + "'>Full item</a></td>";

        QString strCategory = e.elementsByTagName("category").item(0).firstChild().nodeValue();
        html += "<td>" + strCategory + "</td>";

        QString strPubDate = e.elementsByTagName("pubDate").item(0).firstChild().nodeValue();
        html += "<td>" + strPubDate + "</td>";

        if(!e.elementsByTagName("description").item(0).isText())
            textDoc.setHtml(e.elementsByTagName("description").item(0).lastChild().nodeValue());
        else
            textDoc.setHtml(e.elementsByTagName("description").item(0).firstChild().nodeValue());
        QString strDescription = textDoc.toPlainText();

        elementHtml += "<b>Title:</b> " + strTitle + "<br/><br/>";
        elementHtml += "<b>Author:</b> " + strAuthor + "<br/><br/>";
        elementHtml += "<b>Category:</b> " + strCategory + "<br/><br/>";
        elementHtml += "<b>Publication Date:</b> " + strPubDate + "<br/><br/>";
        elementHtml += "<b>Description:</b> " + strDescription + "<br/><br/>";
        elementHtml += "<a href='" + strLink + "'>Read full article</a>";

//        html += "<td>" + strDescription + "</td>";
        html += "</tr>";
        m_elements->addItem(strTitle, elementHtml);
    }

    html += "</tbody></table>";
    m_webEngineView->setHtml(m_elements->currentData().toString());
}

void RSSView::addButtonClicked()
{
    m_urls->addItem(m_urlLineEdit->text());
}

void RSSView::removeButtonClicked()
{
    m_urls->removeItem(m_urls->currentIndex());
}

void RSSView::loadButtonClicked()
{
    m_manager->get(QNetworkRequest(QUrl(m_urls->currentText())));
}

void RSSView::clearButtonClicked()
{
    m_webEngineView->load(QUrl("about:blank"));
}

void RSSView::elementsIndexChanged(int)
{
    m_webEngineView->setHtml(m_elements->currentData().toString());
}

void RSSView::save()
{
    QSettings rssFeeds("rss.ini", QSettings::IniFormat);

    rssFeeds.beginWriteArray("Feeds");
    for(int i = 0; i < m_urls->count(); ++i) {
        rssFeeds.setArrayIndex(i);
        rssFeeds.setValue("url", m_urls->itemText(i));
    }
    rssFeeds.endArray();
}

void RSSView::load()
{
    QSettings rssFeeds("rss.ini", QSettings::IniFormat);

    int urlCount = rssFeeds.beginReadArray("Feeds");
    for(int i = 0; i < urlCount; ++i) {
        rssFeeds.setArrayIndex(i);
        m_urls->addItem(rssFeeds.value("url").toString());
    }
    rssFeeds.endArray();
}
