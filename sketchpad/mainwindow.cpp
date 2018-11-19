#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Palette"));
    setMinimumSize(650, 500);

    // menu
    mainMenuBar = menuBar();
    fileMenu = new QMenu(tr("&File"), this);
    editMenu = new QMenu(tr("&Edit"), this);
    helpMenu = new QMenu(tr("&Help"), this);
    mainMenuBar->addMenu(fileMenu);
    mainMenuBar->addMenu(editMenu);
    mainMenuBar->addMenu(helpMenu);

    newCanvasAction = new QAction(tr("&New File"), this);
    openCanvasAction = new QAction(tr("&Open File"), this);
    saveCanvasAction = new QAction(tr("&Save File"), this);
    saveCanvasAsAction = new QAction(tr("&Save File As"), this);
    fileActions.append(newCanvasAction);
    fileActions.append(openCanvasAction);
    fileActions.append(saveCanvasAction);
    fileActions.append(saveCanvasAsAction);

    connect(saveCanvasAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(openCanvasAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveCanvasAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    fileMenu->addActions(fileActions);


    redoAction = new QAction(tr("&Redo"), this);
    undoAction = new QAction(tr("&Undo"), this);
    clearAction = new QAction(tr("&clear"), this);
    editActions.append(redoAction);
    editActions.append(undoAction);
    editActions.append(clearAction);

    connect(redoAction, &QAction::triggered, this, &MainWindow::redo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undo);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clear);
    editMenu->addActions(editActions);

    topToolBar = new QToolBar(this);
    topToolBar->setMovable(false);
    topToolBar->setHidden(false);
    topToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    topToolBar->addAction(newCanvasAction);
    topToolBar->addAction(openCanvasAction);
    topToolBar->addAction(saveCanvasAction);
    topToolBar->addSeparator();
    topToolBar->addAction(redoAction);
    topToolBar->addAction(undoAction);
    topToolBar->addAction(clearAction);

    addToolBar(Qt::TopToolBarArea, topToolBar);

    QAction *shapeNone = new QAction(QIcon(":/images/None.png"),tr("&pen"), this);
    QAction *shapeLine = new QAction(QIcon(":/images/line.png"),tr("&line"), this);
    QAction *shapeCircle = new QAction(QIcon(":/images/circle.png"),tr("&circle"), this);
    QAction *shapeRect = new QAction(QIcon(":/images/rectangle.png"), tr("rect"), this);
    QAction *shapeEraser = new QAction(QIcon(":/images/eraser.png"), tr("&eraser"), this);
    shapeActions.append(shapeNone);
    shapeActions.append(shapeLine);
    shapeActions.append(shapeCircle);
    shapeActions.append(shapeRect);
    shapeActions.append(shapeEraser);

    connect(shapeNone, &QAction::triggered, this, &MainWindow::shapeNoneClicked);
    connect(shapeLine, &QAction::triggered, this, &MainWindow::shapeLineClicked);
    connect(shapeCircle, &QAction::triggered, this, &MainWindow::shapeCircleClicked);
    connect(shapeRect, &QAction::triggered, this, &MainWindow::shapeRectClicked);
    connect(shapeEraser, &QAction::triggered, this, &MainWindow::shapeEraserClicked);

    sideToolBar = new QToolBar(this);
    sideToolBar->setHidden(false);
    sideToolBar->setMovable(false);
    sideToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    sideToolBar->addActions(shapeActions);
    addToolBar(Qt::LeftToolBarArea, sideToolBar);

    canvasArea = new PaintWidget(this);
    setCentralWidget(canvasArea);

    fName = new QString("/Users/maxinyu/Desktop/default.png");
}

void MainWindow::shapeNoneClicked() {
    canvasArea->setShape(None);
}

void MainWindow::shapeLineClicked() {
    canvasArea->setShape(line);
}

void MainWindow::shapeRectClicked() {
    canvasArea->setShape(rectangle);
}

void MainWindow::shapeCircleClicked() {
    canvasArea->setShape(circle);
}

void MainWindow::shapeEraserClicked() {
    canvasArea->setShape(erase);
}

void MainWindow::redo() {
    canvasArea->redo();
}

void MainWindow::undo() {
    canvasArea->undo();
}

void MainWindow::clear() {
    canvasArea->clear();
}

void MainWindow::saveFile() {
    canvasArea->save(*fName, nullptr);
}

void MainWindow::saveFileAs() {
    QFileDialog d(this);
    d.setAcceptMode(QFileDialog::AcceptSave);
    d.setDefaultSuffix(".png");
    const QString fileName = d.getSaveFileName(this, tr("save canvas"), "", tr(".png"));
    fName = new QString(fileName);
    if (!fileName.isEmpty()) {
        canvasArea->save(fileName, nullptr);
    }
}

void MainWindow::openFile() {
    QFileDialog d(this);
    d.setAcceptMode(QFileDialog::AcceptOpen);

    const QString fileName = d.getOpenFileName(this, tr("open canvas"), "", "");
    qInfo() << fileName;
    fName = new QString(fileName);
    if (!fileName.isEmpty()) {
        canvasArea->open(fileName);
    }
}

