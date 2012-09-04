#include "mainwindow.h"
#include "ui_mainwindow.h"

const int graphWidth = 400;
const int graphHeight = 400;

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
    graphWidget = new GraphWidget(this, graphWidth, graphHeight);
    graphWidget->setGeometry(0, ui->menuBar->height(), graphWidth + 10, graphHeight + 10);

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

// TODO move save() and load() into separate file
void MainWindow::save(){
    // Get fileName from user
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

        QDomDocument doc;

        QDomElement animationElem = doc.createElement("animation");
        doc.appendChild(animationElem);

        for(std::vector<Frame*>::iterator frameIt = animation->frames.begin(); frameIt != animation->frames.end(); ++frameIt){
            QDomElement frameElem = doc.createElement("frame");
            animationElem.appendChild(frameElem);

            QDomElement nodesElem = doc.createElement("nodes");
            frameElem.appendChild(nodesElem);
            QDomElement edgesElem = doc.createElement("edges");
            frameElem.appendChild(edgesElem);


            // get nodes and edges and save them one after another
            QList<Node*> nodes;
            QList<Edge*> edges;
            foreach (QGraphicsItem *item, (*frameIt)->items) {
                if (Node *node = qgraphicsitem_cast<Node*>(item))
                    nodes << node;
                else if (Edge *edge = qgraphicsitem_cast<Edge*>(item))
                    edges << edge;
            }
            foreach (Node *node, nodes){
                QDomElement nodeElem = doc.createElement("node");
                nodeElem.setAttribute("id", node->id);
                nodeElem.setAttribute("x", node->x());
                nodeElem.setAttribute("y", node->y());
                nodesElem.appendChild(nodeElem);
            }
            foreach (Edge *edge, edges){
                QDomElement edgeElem = doc.createElement("edge");
                edgeElem.setAttribute("node1", edge->sourceNode()->id);
                edgeElem.setAttribute("node2", edge->destNode()->id);
                edgesElem.appendChild(edgeElem);
            }

        }

        // save doc to selected file
        QTextStream TextStream(&file);
        TextStream << doc.toString();

        file.close();
    }
}

void MainWindow::load(){
    // Get fileName from user
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

        QDomDocument doc;
        if (!doc.setContent(&file)) {
            file.close();
            return;
        }
        file.close();

        //delete previus animation and load new one
        delete animation;
        animation = new Animation;
        QDomElement docElem = doc.documentElement();

        QDomNode frameNode = docElem.firstChild();
        while(!frameNode.isNull()) {
            Frame *frame = new Frame;

                // for each node in frame
                QDomNode nodesNode = frameNode.firstChild();
                if(!nodesNode.isNull()){
                    QDomNode nodeNode = nodesNode.firstChild();
                    while(!nodeNode.isNull()){
                        QDomElement nodeElem = nodeNode.toElement();
                        //get info about the node
                        qreal x = nodeElem.attribute("x").toDouble();
                        qreal y = nodeElem.attribute("y").toDouble();
                        // create new node
                        Node *node = new Node(graphWidget, x, y);
                        // add node to the frame
                        frame->addNode(node);
                        // go to next node
                        nodeNode = nodeNode.nextSibling();
                    }

                }

                // for each edge in frame
                QDomNode edgesNode = nodesNode.nextSibling();
                if(!edgesNode.isNull()){
                    QDomNode edgeNode = edgesNode.firstChild();
                    while(!edgeNode.isNull()){
                        QDomElement edgeElem = edgeNode.toElement();
                        //get info about the edge
                        int id1 = edgeElem.attribute("node1").toInt();
                        int id2 = edgeElem.attribute("node2").toInt();
                        // create new edge from id's
                        frame->addEdge(graphWidget, id1, id2);
                        // go to next edge
                        edgeNode = edgeNode.nextSibling();
                    }
                }

            // add frame to animation
            animation->addFrame(frame);
            // go to next frame
            frameNode = frameNode.nextSibling();
        }

        // show loaded animation
        currentFrameNumber = 1;
        showCurrentFrame();

    }
}

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
