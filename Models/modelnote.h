#ifndef MODELNOTE_H
#define MODELNOTE_H

#include <QString>

class ModelNote
{
private:
    int idNote;
    QString title;
    QString description;
    QString date;
public:
    ModelNote();
    ModelNote(int id, QString title, QString description, QString date);
    int getIdNote() const;
    QString getTitle() const;
    QString getDescription() const;
    QString getDate() const;
    void setIdNote(int newIdNote);
};

#endif // MODELNOTE_H
