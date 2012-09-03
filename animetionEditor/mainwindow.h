#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QtXml/QtXml>

//TODO remove for debug only
#include <iostream>

#include "graphwidget.h"
#include "node.h"
#include "edge.h"
#include "animation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event);
    
private slots:
    // Save animation to a chosen file
    void save();
    // Loads animation from file
    void load();
    // go to next frame
    void nextFrame();
    // go to previous frame (if it is not the first frame)
    void prevFrame();

    // displays current frame and updates frameNumeber
    void showCurrentFrame();

    void on_checkBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    Animation *animation;

    GraphWidget *graphWidget;
    QLabel *frameNumber;
    QMenu *fileMenu;
    QAction *saveAction;
    QAction *loadAction;

    int currentFrameNumber;

};

#endif // MAINWINDOW_H
