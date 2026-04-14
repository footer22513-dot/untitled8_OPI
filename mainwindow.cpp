#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qstring>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "secondwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)


{
    secondWindow = new SecondWindow();
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{




    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текст (*.txt);;Все файлы (*)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->listWidget->clear();  // очистить перед загрузкой
            while (!in.atEnd()) {
                QString line = in.readLine().trimmed();
                if (!line.isEmpty())  // пропустить пустые строки
                    ui->listWidget->addItem(line);
            }
            file.close();
        }
    }



}


void MainWindow::on_pushButton_3_clicked()
{
    QMap<QString, double> data;

    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QString text = ui->listWidget->item(i)->text();

        QStringList parts = text.split(" ");
        if (parts.size() == 2)
        {
            QString name = parts[0];
            double value = parts[1].toDouble();

            data[name] = value;
        }
    }

    secondWindow->setData(data);
    secondWindow->show();
}

