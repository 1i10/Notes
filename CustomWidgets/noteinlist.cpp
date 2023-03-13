#include "noteinlist.h"
#include "ui_noteinlist.h"

NoteInList::NoteInList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteInList)
{
    ui->setupUi(this);
    connect(ui->deleteButton, &QPushButton::clicked, this, &NoteInList::onDeleteButtonClicked);
}

NoteInList::~NoteInList()
{
    delete ui;
}

void NoteInList::setTextTitle(const QString& text)
{
    ui->noteTitle->setText(text);
}

void NoteInList::setTextDate(const QString& text)
{
    ui->noteDate->setText(text);
}


void NoteInList::onDeleteButtonClicked()
{
    emit sendDeleteIsClicked();
}

