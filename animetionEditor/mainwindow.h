#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>

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
    // go to previous frame
    void prevFrame();

    // displays current frame and updates frameNumeber
    void showCurrentFrame();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QAction *saveAction;
    QAction *loadAction;

    int currentFrameNumber;

};

#endif // MAINWINDOW_H
