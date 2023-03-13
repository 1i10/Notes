#include "databasehandler.h"


DatabaseHandler::DatabaseHandler()
{

}

void DatabaseHandler::connection()
{

    this->database = QSqlDatabase::addDatabase(this->driverName);
    this->database.setDatabaseName(this->pathToDB);
    if(this->database.open())
    {
        qDebug() << "Вы успешно подключились к базе данных: " + this->database.databaseName();
    }
    else
    {
        qDebug() << "При подключении к базе данных произошла ошибка: " + this->database.lastError().databaseText();
        exit(EXIT_FAILURE);
    }
}

QList<ModelNote*> DatabaseHandler::selectNotes()
{
    QList<ModelNote*> notes;

    QSqlQuery selectQuery(this->database);
    selectQuery.exec("SELECT *FROM Notes");

    while (selectQuery.next())
    {
        int id = selectQuery.value(0).toInt();
        QString title = selectQuery.value(1).toString();
        QString description = selectQuery.value(2).toString();
        QString date = selectQuery.value(3).toString();

        ModelNote *note = new ModelNote(id, title, description, date);
        notes.append(note);
    }

    return notes;
}

bool DatabaseHandler::insertNote(ModelNote note)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Notes (id, title, description, date) VALUES(:id, :title, :description, :date)");
    query.bindValue(":id", note.getIdNote());
    query.bindValue(":title", note.getTitle());
    query.bindValue(":description", note.getDescription());
    query.bindValue(":date", note.getDate());

    return query.exec();
}

bool DatabaseHandler::updateNote(ModelNote note)
{
    QSqlQuery query;

    query.prepare("UPDATE Notes SET title=:title, description=:description, date=:date WHERE id=:id");
    query.bindValue(":id", note.getIdNote());
    query.bindValue(":title", note.getTitle());
    query.bindValue(":description", note.getDescription());
    query.bindValue(":date", note.getDate());

    return query.exec();
}

bool DatabaseHandler::deleteNote(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM Notes WHERE id=:id");
    query.bindValue(":id", id);

    return query.exec();
}
