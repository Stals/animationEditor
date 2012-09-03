#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    animation(new Animation),
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

    /* Animation */
    animation->addFrame(new Frame);
    showCurrentFrame();
}


MainWindow::~MainWindow(){
    delete frameNumber;
    delete animation;
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
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Animation"), "",
                                                    tr("(*.ae)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        /*
            TODO DO STUFF HERE
        */



        file.close();
    }
}

void MainWindow::load(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load Animation"), "",
                                                    tr("(*.ae)"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        /*
            TODO DO STUFF HERE
        */

        QDomDocument doc("mydocument");
        if (!doc.setContent(&file)) {
            file.close();
            return;
        }
        file.close();

        // print out the element names of all elements that are direct children
        // of the outermost element.
        QDomElement docElem = doc.documentElement();

        QDomNode n = docElem.firstChild();
        while(!n.isNull()) {
            QDomElement e = n.toElement(); // try to convert the node to an element.
            // TODO call e.attribute("x"); to get 'x'
            if(!e.isNull()) {
                std::cout<<(qPrintable(e.tagName()))<<std::endl; // the node really is an element.
            }
            n = n.nextSibling();
        }

        // Here we append a new element to the end of the document
        QDomElement elem = doc.createElement("img");
        elem.setAttribute("src", "myimage.png");
        docElem.appendChild(elem);


    }
}


//        // TODO load file and show first frame
//        // TODO i will need to clear all the current animation and then add new
//        // animation.clear();
//        // //make frame from file
//        // animation.addFrame(frame);
//        this->setWindowTitle("animationEditor - " + filename);
//        currentFrameNumber = 1;
//        showCurrentFrame();



//    }
//}

void MainWindow::nextFrame(){
    // reset 'from' node
    graphWidget->from = NULL;
    ++currentFrameNumber;
    //if there are no such frame - create new frame
    if(animation->frames.size() < currentFrameNumber){
        animation->addFrame(new Frame);
    }
    showCurrentFrame();
}

void MainWindow::prevFrame(){
    // reset 'from' node
    graphWidget->from = NULL;
    // go to previous frame unless it is the first one
    if(currentFrameNumber > 1){
        --currentFrameNumber;
        showCurrentFrame();
    } // else dont change anything
}

void MainWindow::showCurrentFrame(){
    // claer previous frame
    graphWidget->emptyScene();

    // change frameNumber
    frameNumber->setText(QString::number(currentFrameNumber));

    // show current frame
    graphWidget->showFrame(animation->frames[currentFrameNumber - 1]);
}

void MainWindow::on_checkBox_toggled(bool checked){
    graphWidget->addEdges = checked;

    // If is was turned off - reset 'from'
    if (checked == false)
        graphWidget->from = NULL;
}

//TODO take code for loading
//void MainWindow::on_pushButton_clicked()
//{
//    Frame *frame = new Frame;
//    animation->addFrame(frame);

//    Node *node1 = new Node(graphWidget, 100, 100);
//    Node *node2 = new Node(graphWidget, 50, 50);

//    frame->addNode(node1);
//    frame->addNode(node2);

//    Edge *edge = new Edge(graphWidget, node1, node2);

//    frame->addEdge(edge);

//    this->showCurrentFrame();
//}
