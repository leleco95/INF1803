#include "webcrawlerview.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QBoxLayout>
#include <QLabel>

WebCrawlerView::WebCrawlerView(QWidget *parent) :
    QWidget(parent)
{
    QBoxLayout *mainLayout;
    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    QGridLayout *gridLayout = new QGridLayout;
    mainLayout->addLayout(gridLayout);

    m_urlLineEdit = new QLineEdit();

    int row = 0;
    gridLayout->addWidget(new QLabel("URL"), row, 0);
    gridLayout->addWidget(m_urlLineEdit, row++, 1);
}
