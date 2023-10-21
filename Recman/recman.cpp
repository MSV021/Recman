#include "recman.h"
#include "ui_recman.h"

#include "html/Element.hpp"

#include <QPushButton>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

#include <iostream> 
#include <sstream> 

Recman::Recman(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Recman)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Recman::onSearch);
}

Recman::~Recman()
{
    delete ui;
}

void Recman::onSearch() {
    while(QLayoutItem* child = ui->verticalLayout->takeAt(0)) 
        delete child;

    auto search = ui->textEdit->toPlainText().toStdString(); 
    auto encodedSearch = search; std::replace(encodedSearch.begin(), encodedSearch.end(), ' ', '+');
    auto url = "https://www.mobygames.com/search/?q=" + encodedSearch + "&type=game";

    curlpp::Cleanup cleanup; 
    std::ostringstream os;
    os << curlpp::options::Url(url);
    auto str = os.str();

    auto elements = html::Element::get(str);

    for(size_t i = 0; i < elements.size(); i++) {
        if(elements[i].content == "GAME:") {
            auto title = elements[i+2].content;
            auto iter = std::search(title.begin(), title.end(), search.begin(), search.end());
            if(iter != title.end()) {
                ui->verticalLayout->addWidget(new QPushButton(QString(title.c_str()), nullptr), 0, Qt::AlignTop);
            }
        }
    }
}