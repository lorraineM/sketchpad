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
    fileMenu->addActions(fileActions);


    redoAction = new QAction(tr("&Redo"), this);
    undoAction = new QAction(tr("&Undo"), this);
    clearAction = new QAction(tr("&clear"), this);
    editActions.append(redoAction);
    editActions.append(undoAction);
    editActions.append(clearAction);
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

    QAction *shapeNone = new QAction(QIcon(tr("&images/None.png")), tr("&pen"), this);
    QAction *shapeLine = new QAction(QIcon(tr("&images/line.png")),tr("&line"), this);
    QAction *shapeRect = new QAction(QIcon(tr("&rectangle.png")), tr("rect"), this);
    shapeActions.append(shapeNone);
    shapeActions.append(shapeLine);
    shapeActions.append(shapeRect);

    sideToolBar = new QToolBar(this);
    sideToolBar->setHidden(false);
    sideToolBar->setMovable(false);
    sideToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    sideToolBar->addActions(shapeActions);
    addToolBar(Qt::LeftToolBarArea, sideToolBar);


    canvasArea = new PaintWidget(this);
    setCentralWidget(canvasArea);
}
