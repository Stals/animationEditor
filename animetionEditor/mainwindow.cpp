#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
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
    switch (event->key()) {
            case Qt::Key_A: prevFrame(); break;
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
    ui->label->setText("next");
}

void MainWindow::prevFrame(){
    ui->label->setText("prev");

}
