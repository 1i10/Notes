#include "modelnote.h"

ModelNote::ModelNote()
{
}

ModelNote::ModelNote(int id, QString title, QString description, QString date)
{
    this->idNote = id;
    this->title = title;
    this->description = description;
    this->date = date;
}

int ModelNote::getIdNote() const
{
    return idNote;
}

QString ModelNote::getTitle() const
{
    return title;
}

QString ModelNote::getDescription() const
{
    return description;
}

QString ModelNote::getDate() const
{
    return date;
}

void ModelNote::setIdNote(int newIdNote)
{
    idNote = newIdNote;
}
