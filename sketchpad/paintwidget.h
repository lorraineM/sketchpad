#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>

class PaintWidget;

enum ShapeType
{
    None,
    line,
    circle,
    rectangle,
    erase
};

class PaintWidget: public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent);

    void setBackgroundColor(QRgb);
    void setPenColor(QRgb);
    void setPenWidth(int);
    void setPenStyle(Qt::PenStyle);
    void setFillColor(QRgb);
    void setShape(ShapeType);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void paint(QImage &c);

private:
    QImage canvas, tmpcanvas;
    QRgb backgroundColor;
    QPoint startPoint, endPoint;

    QColor penColor, fillColor;

    int penWidth;
    Qt::PenStyle penStyle;
    ShapeType shape;
    bool drawing;
    bool modified;
};

#endif // PAINTWIDGET_H
