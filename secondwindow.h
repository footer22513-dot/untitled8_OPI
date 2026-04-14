#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QMap>
#
class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    void setData(const QMap<QString, double>& newData);
    ~SecondWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, double> data; // категории и значения
    void loadDataFromFile();

};

#endif // SECONDWINDOW_H