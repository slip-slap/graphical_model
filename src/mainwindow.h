#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include "gmscene.h"

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
    StockEdgeInterface* m_gm_edge;



protected slots:
    void foo();
public slots:
    void on_actionExit_2_triggered();
    void on_actionOpen_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionSave_triggered();
    void on_actionClear_triggered();
private slots:
    void on_actionUndo_triggered();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
