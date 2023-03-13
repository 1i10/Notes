#ifndef NOTEINLIST_H
#define NOTEINLIST_H

#include <QWidget>

namespace Ui {
class NoteInList;
}

class NoteInList : public QWidget
{
    Q_OBJECT

public:
    explicit NoteInList(QWidget *parent = nullptr);
    ~NoteInList();

    void setTextTitle(const QString& text);
    void setTextDate(const QString& text);

 signals:
    void sendDeleteIsClicked();

private slots:
    void onDeleteButtonClicked();

private:
    Ui::NoteInList *ui;
};

#endif // NOTEINLIST_H
