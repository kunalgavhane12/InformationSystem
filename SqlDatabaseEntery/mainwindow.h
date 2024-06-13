#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setUp();

    void showData();

    void on_AddBtn();

    void on_UpdateBtn();

    void on_PrintBtn();

    void on_ResetBtn();

    void on_DeleteBtn();

    void on_ShowBtn();


private:
    Ui::MainWindow *ui;
    QSqlDatabase myDB;
    QString data;
};
#endif // MAINWINDOW_H
