#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <QApplication>

#include "mainwindow.h"

TEST(MainWindow, on_actionOpen_triggered)
{

    MainWindow w;
    w.on_actionOpen_triggered();
}


