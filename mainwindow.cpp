#include "mainwindow.h"
#include "CustomWidgets/noteinlist.h"
#include "ui_mainwindow.h"
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    this->db.connection();
    this->notes = this->db.selectNotes();

    //устанавливаем полученные данные в список ui
    for(int i = 0; i < this->notes.size(); i++)
    {
        addModelNoteInListUI(*this->notes[i]);
    }

    //первая строка (по умолчанию) является selected
    if (ui->listOfNotes->count() > 0)
    {
        ui->listOfNotes->item(0)->setSelected(true);

        ModelNote rowData = getDataInListItem(*ui->listOfNotes->item(0));

        ui->editTitle->setText(rowData.getTitle());
        ui->editDescription->setText(rowData.getDescription());
    }

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(this->notes);
    this->notes.clear();
}

ModelNote MainWindow::getDataInListItem(QListWidgetItem item)
{
    QVariant qRowData = item.data(Qt::UserRole);
    ModelNote rowData = qvariant_cast<ModelNote>(qRowData);

    return rowData;
}

void MainWindow::addModelNoteInListUI(ModelNote note)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, QVariant::fromValue<ModelNote>(note));

    NoteInList *noteWidget = new NoteInList(this);
    noteWidget->setTextTitle(note.getTitle());
    noteWidget->setTextDate(note.getDate());

    item->setSizeHint(noteWidget->size());

    ui->listOfNotes->addItem(item);
    ui->listOfNotes->setItemWidget(item, noteWidget);

    item->setSelected(true);

    //set connect for delete
    connect(noteWidget, &NoteInList::sendDeleteIsClicked, this,
            [this, item](){ deleteNoteInList(item);});
}

void MainWindow::updateListItemUI(QListWidgetItem *item, ModelNote note, int row)
{
    item->setData(Qt::UserRole, QVariant::fromValue<ModelNote>(note));

    NoteInList *noteWidget = new NoteInList(this);
    noteWidget->setTextTitle(note.getTitle());
    noteWidget->setTextDate(note.getDate());

    ui->listOfNotes->insertItem(row,item);
    ui->listOfNotes->setItemWidget(item, noteWidget);

    connect(noteWidget, &NoteInList::sendDeleteIsClicked, this,
            [this, item](){ deleteNoteInList(item);});
}


void MainWindow::onAddButtonClicked()
{
    ui->listOfNotes->clearSelection();

    ui->editTitle->clear();
    ui->editDescription->clear();
    //устанавливаем курсор на title
    ui->editTitle->setFocus();
}


void MainWindow::onSaveButtonClicked()
{
    //забрать данные, в т.ч. время
    //если название темы пустое, то называем "Без названия" (пустое поле описания допускается)
    QString title = ui->editTitle->toPlainText().isEmpty() ? "Без названия" : ui->editTitle->toPlainText();
    QString description = ui->editDescription->toPlainText();
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("dd.MM.yyyy");

    //получить выделенную запись
    QList <QListWidgetItem*> items = ui->listOfNotes->selectedItems();

    ModelNote *note = new ModelNote(-1,title,description,dateTimeString);

    //определить редактирование/добавление
    if(items.isEmpty())//это добавление
    {
        //выдать id (достать последнюю запись и выдать id+1 или 1, если запись единственная)
        int countRow = this->notes.size();
        int id = countRow > 0 ? this->notes[countRow-1]->getIdNote() + 1 : 1;
        note->setIdNote(id);

        //добавить в базу запись
        this->db.insertNote(*note);
        //обновить переменную notes
        this->notes.append(note);
        addModelNoteInListUI(*note);

        ui->statusbar->showMessage("Заметка добавлена!");
    }
    else//обновление
    {
        //достать id
        int id = getDataInListItem(*items[0]).getIdNote();
        note->setIdNote(id);
        //выполнить обновление в бд
        this->db.updateNote(*note);
        //обновить переменную notes
        int row = ui->listOfNotes->row(items[0]);
        this->notes[row] = note;
        //обновить ui
        updateListItemUI(items[0], *note, row);

        ui->statusbar->showMessage("Заметка обновлена!");
    }

    //обновить ui лист
    ui->listOfNotes->update();
}


void MainWindow::on_listOfNotes_itemClicked(QListWidgetItem *item)
{
    ui->statusbar->showMessage("");

    item->setSelected(true);

    ModelNote rowData = getDataInListItem(*item);

    ui->editTitle->setText(rowData.getTitle());
    ui->editDescription->setText(rowData.getDescription());
}

void MainWindow::deleteNoteInList(QListWidgetItem *item)
{
    //получить номер строки
    int row = ui->listOfNotes->row(item);

    //получить ид
    ModelNote note = getDataInListItem(*item);
    int id = note.getIdNote();
    //удалить из бд
    this->db.deleteNote(id);
    //удалить из notes
    this->notes.remove(row);

    //проверить selected строка или нет
    bool isSelected = ui->listOfNotes->item(row)->isSelected();

    //удалить из ui
    delete ui->listOfNotes->takeItem(row);

    //если нет записей, очистить правую часть
    if(ui->listOfNotes->count() < 1)
    {
        ui->editTitle->clear();
        ui->editDescription->clear();
    }
    else
    {
        //если строка выделенная, то смещаем выделение
        if(isSelected)
        {
            if(row - 1 >= 0)
            {
                on_listOfNotes_itemClicked(ui->listOfNotes->item(row-1));
            }
            else
            {
                on_listOfNotes_itemClicked(ui->listOfNotes->item(0));
            }
        }
    }

    ui->statusbar->showMessage("Заметка удалена!");
}
