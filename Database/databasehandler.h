#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <Models/modelnote.h>

class DatabaseHandler
{
private:
    QString driverName = "QSQLITE";
    QString pathToDB = "./../Notes/Database/Notes.db";

    QSqlDatabase database;

public:
    DatabaseHandler();
    void connection();
    QList<ModelNote*> selectNotes();
    bool insertNote(ModelNote note);
    bool updateNote(ModelNote note);
    bool deleteNote(int id);
};

#endif // DATABASEHANDLER_H
