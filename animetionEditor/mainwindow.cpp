#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentFrame(1){
    ui->setupUi(this);

    /* Create fileMenu */
    fileMenu = ui->menuBar->addMenu(tr("&File"));

    // Add save button
    saveAction = new QAction(tr("Save as..."), this);
    fileMenu->addAction(saveAction);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    // Add load button
    loadAction = new QAction(tr("Load"), this);
    fileMenu->addAction(loadAction);
    connect(loadAction, SIGNAL(triggered()), this, SLOT(load()));
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    // A or left arrow key - go to previous frame
    // D or right arrow key - go to next frame
    switch (event->key()) {
        case Qt::Key_Left: //fall throw
        case Qt::Key_A: prevFrame(); break;
        case Qt::Key_Right: //fall throw
        case Qt::Key_D: nextFrame(); break;
    }
}

void MainWindow::save(){

}

void MainWindow::load(){
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open Animation"), "", tr("*.ae"));
}

void MainWindow::nextFrame(){
    ++currentFrame;
    showCurrentFrame();
}

void MainWindow::prevFrame(){
    // go to previous frame unless it is the first one
    if(currentFrame > 1){
        --currentFrame;
        showCurrentFrame();
    } // else dont change anything
}

void MainWindow::showCurrentFrame(){
    // TODO get data and show it

    // change frameNumber
    ui->frameNumber->setText(QString::number(currentFrame));
}
