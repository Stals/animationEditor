#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentFrameNumber(1){

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

    /* GraphWidget */
    graphWidget = new GraphWidget(this);
    // TODO why 410? Причем если менять ошибка только при создании. Тоесть mouse event что-то не так понимает
    graphWidget->setGeometry(0,ui->menuBar->height(),410,410);

    /* frameNumber */
    frameNumber = new QLabel("1", graphWidget);
    // move it in a right up corner
    frameNumber->setAlignment(Qt::AlignRight);
    const int labelIndent = 5;
    const int labelWidth = 20;
    const int labelHeight = 15;
    frameNumber->setGeometry(graphWidget->width() - labelWidth - labelIndent, labelIndent,
                             labelWidth, labelHeight);

}


MainWindow::~MainWindow(){
    delete frameNumber;
    delete graphWidget;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    // A - go to previous frame
    // D - go to next frame
    switch (event->key()) {
        case Qt::Key_A: prevFrame(); break;
        case Qt::Key_D: nextFrame(); break;
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::save(){

}

void MainWindow::load(){
    // get filename from user
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Load Animation"), "", tr("*.ae"));

    // only if file was opened
    if(filename.size()){
        // TODO load file and show first frame
        this->setWindowTitle("animationEditor - " + filename);
        currentFrameNumber = 1;
        showCurrentFrame();
    }
}

void MainWindow::nextFrame(){
    ++currentFrameNumber;
    //TODO if currentFrameNumber - 1 > animation.frames.length()
        // create new frame
    showCurrentFrame();
}

void MainWindow::prevFrame(){
    // go to previous frame unless it is the first one
    if(currentFrameNumber > 1){
        --currentFrameNumber;
        showCurrentFrame();
    } // else dont change anything
}

void MainWindow::showCurrentFrame(){
    // change frameNumber
    frameNumber->setText(QString::number(currentFrameNumber));

    // TODO get data and show it
        // get it from vector like this animation[currentFrame - 1]
            // Can probably make showCurrentFrame after inheriting GraficsView,
            //(after renameign to to FrameVier) and give this mehid a frame
}

void MainWindow::on_checkBox_toggled(bool checked){
    graphWidget->addEdges = checked;

    // If is was turned off - reset 'from'
    if (checked == false)
        graphWidget->from = NULL;
}
