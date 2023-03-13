#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Database/databasehandler.h"
#include "qlistwidget.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ModelNote getDataInListItem(QListWidgetItem item);
    void addModelNoteInListUI(ModelNote note);
    void updateListItemUI(QListWidgetItem *item, ModelNote note, int row);

private slots:
    void onAddButtonClicked();
    void onSaveButtonClicked();
    void on_listOfNotes_itemClicked(QListWidgetItem *item);
    void deleteNoteInList(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    DatabaseHandler db;
    QList<ModelNote*> notes;
};
#endif // MAINWINDOW_H
