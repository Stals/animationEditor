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
    // Позволяет сохранить текущую анимацию в выбранный файл
    void save();
    // Позволяет загрузить анимацию из файла
    void load();
    // Переходит на следующий кадр
    void nextFrame();
    // Переходит на предведущий кадр
    void prevFrame();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QAction *saveAction;
    QAction *loadAction;

};

#endif // MAINWINDOW_H
