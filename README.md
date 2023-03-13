# Приложение Заметки
## Навигация   
[1. Краткое описание](#Description)  
[2. Выполненные функциональные требования](#FunctionalRequirements)  
[3. Структура проекта](#Structure)  
[4. Описание классов](#ClassDescription)  
[5. Таблица БД](#TableDatabase)  
[6. Сборка и настройка](#Build)  
[7. Руководство пользователя](#UserGuide)  
[8. Пример](#Example)  

  
<a name="Description"><h2>Краткое описание</h2></a>
Приложение было разработано на языке C++ в среде QT Creator 9.0.2 с использованием фрейморка QT 6.4.2 и СУБД SQLite для локального хранения данных под ОС Windows.  
Приложение позволяет пользователю выполнять действия с заметками (создание, редактирование, удаление, хранение). 

<a name="FunctionalRequirements"><h2>Выполненные функциональные требования</h2></a>  
* Создание одной простейшей заметки только с текстом;
* Редактирование заметки в окне собственного приложения;
* Сохранение заметки между сеансами приложения, в любом формате;
* При первом запуске, приложение должно иметь одну заметку с текстом;    
* Создание нескольких заметок в приложении;
* Выводить список существующих заметок;
* Возможность редактирования любой заметки из списка;
* Удаление заметок;
* Также сохранять все заметки между сеансами.  

<a name="Structure"><h2>Структура проекта</h2></a> 
* [*CustomWidgets*](https://github.com/1i10/Notes/tree/main/CustomWidgets) - пакет, который содержит в себе созданные пользовательские виджеты; 
* [*Database*](https://github.com/1i10/Notes/tree/main/Database) - пакет, который содержит БД Notes и исходные файлы для подключения и работы с этой БД;
* [*Images*](https://github.com/1i10/Notes/tree/main/Images) - пакет, который содержит изображения, используемые в приложении;
* [*Models*](https://github.com/1i10/Notes/tree/main/Models) - пакет, который содержит исходные файлы модели таблицы БД Notes;
* [*Example*](https://github.com/1i10/Notes/tree/main/Example) - содержит изображения для руководства, примеров и т.д. данного репозитория;
* [*Notes.pro*](https://github.com/1i10/Notes/blob/main/Notes.pro) - файл проекта, используемый qmake для создания приложения;
* *[MainWindow.cpp](https://github.com/1i10/Notes/blob/main/mainwindow.cpp)/[MainWindow.h](https://github.com/1i10/Notes/blob/main/mainwindow.h)* — класс главного окна, вместе с [*MainWindow.ui*](https://github.com/1i10/Notes/blob/main/mainwindow.ui) описывающий видимую часть;
* [*resource.qrc*](https://github.com/1i10/Notes/blob/main/resource.qrc) - файл ресурсов, связанных с приложением.

<a name="ClassDescription"><h2>Описание классов</h2></a> 

<a name="TableDatabase"><h2>Таблица БД</h2></a> 
Ниже представлено описание сущности Notes БД [Notes.db](https://github.com/1i10/Notes/blob/main/Database/Notes.db).  
**Атрибут** | **Описание** | **Тип** | **Возможные значения** |
:---------- | :----------- | :--------------------- | :--------------------- |
id | Идентификатор заметки | INTEGER (PRIMARY) | Целое положительное число |
title | Название темы заметки | TEXT | Любой набор символов |
description | Описание | TEXT | Любой набор символов |
date | Дата создания/редактирования заметки | TEXT | Строка в формате dd.MM.yyyy |  

<a name="Build"><h2>Сборка и настройка</h2></a> 
1. Загрузить проект на локальную машину, воспользовавшись командой git clone https://github.com/1i10/Notes.git  
2. Открыть Notes.pro в Qt Creator  

<a name="UserGuide"><h2>Руководство пользователя</h2></a>
- Для добавления новой записи следует нажать на ![image](https://github.com/1i10/Notes/blob/main/Example/addButton.png)  
- Для просмотра/изменения заметки следует нажать на необходимую запись в списке  
- Удалить заметку можно, нажав на соответствующую кнопку удаления в списке ![image](https://github.com/1i10/Notes/blob/main/Example/deleteButton.png)
- Для сохранения/изменения заметки следует нажать ![image](https://github.com/1i10/Notes/blob/main/Example/saveButton.png)

<a name="Example"><h2>Пример</h2></a>  
![Пример](https://github.com/1i10/Notes/blob/main/Example/exampleWork.gif)  


