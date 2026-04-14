#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButton_clicked();  // уже есть — отлично

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    SecondWindow *secondWindow;  // добавь это
};

#endif // MAINWINDOW_H