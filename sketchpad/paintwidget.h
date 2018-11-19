#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QStack>
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

class Shape {
public:
    Shape(QPoint s, QPoint e, ShapeType shp) {
        start = s;
        end = e;
        shape = shp;
    }
    Shape(QList<QPoint> ps, ShapeType shp) {
        freeLine = ps;
        shape = shp;
    }
    QPoint getStart() {
        return start;
    }
    QPoint getEnd() {
        return end;
    }
    ShapeType getShape() {
        return shape;
    }
    QList<QPoint> getLine() {
        return freeLine;
    }
private:
    QPoint start;
    QPoint end;
    ShapeType shape;
    QList<QPoint> freeLine;
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

    void undo();
    void redo();
    void clear();

    void save(const QString&fileName,const char*fileFormat);
    void open(const QString&fileName);
    void newCanvas();

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

private:
    QStack<Shape*> stack;
    QStack<Shape*> redoStack;
    QList<QPoint>* tmp;

};

#endif // PAINTWIDGET_H
