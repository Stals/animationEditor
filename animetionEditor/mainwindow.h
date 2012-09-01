#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    // Позволяет сохранить текущую анимацию в выбранный файл
    void save();
    // Позволяет загрузить анимацию из файла
    void load();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QAction *saveAction;
    QAction *loadAction;

};

#endif // MAINWINDOW_H
