#include "paintwidget.h"
#include <iostream>

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground (true);
    setPalette (QPalette(Qt::white));

    canvas = QImage(600, 400, QImage::Format_RGB32);
    backgroundColor = qRgb(255, 255, 255);
    canvas.fill(backgroundColor);

    drawing = false;
    modified = false;
    penColor = Qt::black;
    fillColor = Qt::black;
    penWidth = 5;
    penStyle = Qt::SolidLine;
    shape = None;
}

void PaintWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if (drawing) {
        painter.drawImage(0, 0, tmpcanvas);
    }else {
        painter.drawImage(0, 0, canvas);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        startPoint = e->pos();
        drawing = true;
    }
    //std::cout << startPoint.x() << std::endl;
}

void PaintWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        endPoint = e->pos();
        if (shape == None || shape == erase) {
            drawing = false;
            paint(canvas);
        }else {
            tmpcanvas = canvas;
            paint(tmpcanvas);
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        endPoint = e->pos();
        drawing = false;
        paint(canvas);
    }
}

void PaintWidget::paint(QImage& c) {
    QPainter painter(&c);
    QPen pen = QPen();
    pen.setColor(penColor);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);

    painter.setPen(pen);

    switch(shape) {
    case None: {
        painter.drawLine(startPoint, endPoint);
        startPoint = endPoint;
        break;
    }
    case line: {
        painter.drawLine(startPoint, endPoint);
        break;
    }
    case circle: {
        int x = startPoint.x(), y = startPoint.y();
        int w = endPoint.x() - x, h = endPoint.y() - y;
        painter.drawEllipse(x, y, w, h);
        break;
    }
    case rectangle: {
        int x = startPoint.x(), y = startPoint.y();
        int w = endPoint.x() - x, h = endPoint.y() - y;
        painter.drawRect(x, y, w, h);
        break;
    }
    case erase: {
        int x = startPoint.x(), y = startPoint.y();
        QRect rect(startPoint, QPoint(x + 10, y + 10));
        painter.eraseRect(rect);
        startPoint = endPoint;
        break;
    }
    }

    update();
    modified = true;
}

void PaintWidget::setBackgroundColor(QRgb color)
{
    backgroundColor = color;
}

void PaintWidget::setPenColor(QRgb color)
{
    penColor = color;
}

void PaintWidget::setPenWidth(int w)
{
    penWidth = w;
}

void PaintWidget::setPenStyle(Qt::PenStyle s)
{
    penStyle = s;
}

void PaintWidget::setFillColor(QRgb color)
{
    fillColor = color;
}

void PaintWidget::setShape(ShapeType s)
{
    shape = s;
}
