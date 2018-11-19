#include "paintwidget.h"
#include <iostream>

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground (true);
    setPalette (QPalette(Qt::white));

    newCanvas();
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

        if (shape == None || shape == erase) {
            tmp = new QList<QPoint>();
            tmp->append(startPoint);
        }
    }

}

void PaintWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        endPoint = e->pos();
        if (shape == None || shape == erase) {
            drawing = false;
            tmp->append(endPoint);
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

        if (shape == None || shape == erase) {
            tmp->append(e->pos());
            Shape* shp = new Shape(*tmp, shape);
            stack.push(shp);
        }else {
            Shape* shp = new Shape(startPoint, endPoint, shape);
            stack.push(shp);
        }

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

void PaintWidget::undo() {
    if (stack.isEmpty()) {
        return;
    }

    canvas = QImage(1000, 1000, QImage::Format_RGB32);
    backgroundColor = qRgb(255, 255, 255);
    canvas.fill(backgroundColor);

    redoStack.push(stack.pop());
    drawing = false;
    foreach(Shape* s, stack) {
        shape = s->getShape();
        if (shape == None || shape == erase) {
            QList<QPoint> freeLine = s->getLine();
            startPoint = freeLine[0];
            for (int i = 1; i < freeLine.size(); i++) {
                endPoint = freeLine[i];
                paint(canvas);
            }
        }else {
            startPoint = s->getStart();
            endPoint = s->getEnd();
            paint(canvas);
        }
    }
    update();
}

void PaintWidget::redo() {
    if (redoStack.isEmpty()) {
        return;
    }
    Shape *s = redoStack.top();
    stack.push(redoStack.pop());

    shape = s->getShape();
    drawing = false;
    if (shape == None || shape == erase) {
        QList<QPoint> freeLine = s->getLine();
        startPoint = freeLine[0];
        for (int i = 1; i < freeLine.size(); i++) {
            endPoint = freeLine[i];
            paint(canvas);
        }
    }else {
        startPoint = s->getStart();
        endPoint = s->getEnd();
        paint(canvas);
    }
}

void PaintWidget::clear() {
    while (!stack.isEmpty()) {
        redoStack.push(stack.pop());
    }

    canvas = QImage(1000, 1000, QImage::Format_RGB32);
    backgroundColor = qRgb(255, 255, 255);
    canvas.fill(backgroundColor);
    update();
}

void PaintWidget::newCanvas() {
    canvas = QImage(1000, 1000, QImage::Format_RGB32);
    backgroundColor = qRgb(255, 255, 255);
    canvas.fill(backgroundColor);

    drawing = false;
    modified = false;
    penColor = Qt::black;
    fillColor = Qt::black;
    penWidth = 3;
    penStyle = Qt::SolidLine;
    shape = None;

    stack.clear();
    redoStack.clear();

    update();
}

void PaintWidget::save(const QString&fileName,const char*fileFormat) {
    canvas.save(fileName, fileFormat);
}

void PaintWidget::open(const QString&fileName) {
    canvas.load(fileName);
    update();
}
