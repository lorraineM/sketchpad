#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include "paintwidget.h"

class MainWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();

    void redo();
    void undo();
    void clear();

private:
    PaintWidget *canvasArea;

private:
    QMenuBar *mainMenuBar;
    QToolBar *topToolBar, *sideToolBar;
    QMenu *fileMenu, *editMenu, *helpMenu;

    QList<QAction*> fileActions, editActions;
    QAction *newCanvasAction, *openCanvasAction, *saveCanvasAction, *saveCanvasAsAction;
    QAction *redoAction, *undoAction, *clearAction;

    QList<QAction*> shapeActions;
    QAction *penColorAction, *fillColorAction, *penWidthAction, penStyleAction;
};

#endif // MAINWINDOW_H