#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QFileDialog>

#include "gmnode.h"
#include "gmsocket.h"
#include "gmedge.h"
#include "gmqtgraphicscuttingline.h"

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

#include "json/json.hpp"

//extern std::size_t USED_MEMRORY;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    std::cout<<"it start"<<std::endl;
    ui->setupUi(this);
    ui->menubar->setNativeMenuBar(false);
    m_scene = new GMScene();
    GMQtGraphicsCuttingLine* cutting_line = new GMQtGraphicsCuttingLine((GMQtGraphicScene*)m_scene->GetGraphicsScenePtr());
    GMNode* gm_node = new GMNode(m_scene);
    gm_node->SetStockNodePosition(QPointF(50,50));
    GMNode* gm_node2 = new GMNode(m_scene);
    gm_node2->SetStockNodePosition(QPointF(200,200));
    GMNode* gm_node3 = new GMNode(m_scene);
    gm_node3->SetStockNodePosition(QPointF(400,100));
    GMNode* gm_node4 = new GMNode(m_scene);
    gm_node4->SetStockNodePosition(QPointF(300,200));
    new GMEdge(m_scene, gm_node,POSITION::SOUTH_ANCHOR, gm_node2,POSITION::NORTH_ANCHOR);
    new GMEdge(m_scene, gm_node2,POSITION::NORTH_ANCHOR, gm_node3,POSITION::NORTH_ANCHOR);
    new GMEdge(m_scene, gm_node,POSITION::NORTH_ANCHOR, gm_node3,POSITION::NORTH_ANCHOR);
    m_scene->GetGraphicsScenePtr()->setBackgroundBrush(Qt::black);
    m_scene->GetGraphicsScenePtr()->setSceneRect(-100,-100,1000,1000);
    m_scene->DisplayMap();
    this->ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    this->ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    this->ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView->setScene(m_scene->GetGraphicsScenePtr());
    this->ui->graphicsView->SetStockGraphicScene((GMQtGraphicScene*)(m_scene->GetGraphicsScenePtr()));
    this->ui->graphicsView->SetGMQtGraphicsCuttingLine(cutting_line);
    this->ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()),scene,SLOT(advance()));
    //connect(timer, SIGNAL(timeout()),scene,SLOT(update()));
    //connect(timer, SIGNAL(timeout()),this,SLOT(foo()));
    //timer->start(10);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    std::cout<<"mainwindow press event"<<std::endl;
    //std::string memory = std::to_string(USED_MEMRORY);
    //QString message(memory.c_str());
    //ui->statusbar->showMessage(message);
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    std::cout<<"mainwindow move event"<<std::endl;
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    std::cout<<"mainwindow release event"<<std::endl;
    QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::foo()
{


}


void MainWindow::on_actionExit_2_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName();
    //boost::filesystem::path current_path = boost::filesystem::current_path();
    std::ifstream i(file_name.toStdString());
    nlohmann::json json_file;
    i >> json_file;
    i.close();
    m_scene->deserialize(json_file.dump(4));
    for(int ll=0; ll < json_file["node"].size(); ll++ ){
        std::cout<<json_file["node"][ll]["socket1"].dump(8)<<std::endl;
    }
}

void MainWindow::on_actionZoom_In_triggered()
{
     ui->graphicsView->scale(2,2);
}

void MainWindow::on_actionZoom_Out_triggered()
{
     ui->graphicsView->scale(0.5, 0.5);
}

void MainWindow::on_actionSave_triggered()
{
     QString filename = QFileDialog::getSaveFileName(this,"Save Graphical Model","","gm.json");
     std::ofstream seriable;
     seriable.open(filename.toStdString());
     nlohmann::json js;
     seriable<<js.parse(m_scene->serialize()).dump(4)<<std::endl;
     seriable.close();
}

void MainWindow::on_actionClear_triggered()
{
    m_scene->ClearScene();
}
