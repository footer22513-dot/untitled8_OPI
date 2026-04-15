#include "secondwindow.h"

#include <QPainter>
#include <QFile>
#include <QTextStream>
#
SecondWindow::SecondWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Круговая диаграмма");
    resize(600, 400);

    loadDataFromFile();
    // paintEvent();
}

SecondWindow::~SecondWindow() {}

void SecondWindow::loadDataFromFile()
{
    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString name;
        double value;
        in >> name >> value;
        data[name] = value;
    }

    file.close();
}

void SecondWindow::setData(const QMap<QString, double>& newData)
{
    data = newData;
    update(); // перерисовать
}



void SecondWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF rect(100, 50, 300, 300); // область круга

    double total;

    total = 0;
    for (auto v : data)
        total += v;

    int startAngle = 0;

    int colorIndex = 0;
    QList<QColor> colors = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan};

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        double value = it.value();

        // угол сектора
        int spanAngle = static_cast<int>(360.0 * value / total * 16);

        painter.setBrush(colors[colorIndex % colors.size()]);
        painter.drawPie(rect, startAngle, spanAngle);


        double angle = (startAngle + spanAngle / 2) / 16.0;
        double rad = angle * M_PI / 180.0;

        int x = rect.center().x() + 120 * cos(rad);
        int y = rect.center().y() - 120 * sin(rad);

        QString text = QString("%1 (%2%)")
                           .arg(it.key())
                           .arg(value / total * 100, 0, 'f', 1);

        painter.drawText(x, y, text);

        startAngle += spanAngle;
        colorIndex++;
    }
}