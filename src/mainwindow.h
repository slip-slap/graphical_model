#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <gmscene.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    GMScene* m_scene;


protected:
    void mousePressEvent(QMouseEvent* ) override;
    void mouseMoveEvent(QMouseEvent* ) override;
    void mouseReleaseEvent(QMouseEvent* ) override;

protected slots:
    void foo();
private slots:
    void on_actionExit_2_triggered();
    void on_actionOpen_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionSave_triggered();
    void on_actionClear_triggered();
};
#endif // MAINWINDOW_H
