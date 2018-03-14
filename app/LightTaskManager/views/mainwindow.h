#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFileDialog>

#include "presenters/mainwindowpresenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpenRepository_triggered();
    void viewDirectory(QString filePath);
    void viewToDo(QStringList todoList);

    void on_taskContainerTableWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    MainWindowPresenter *m_presenter;

    void setupWidgets();
    void setupPresenter();
};

#endif // MAINWINDOW_H
