#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <mach/mach.h>
#include <iostream>

//getrusage(RUSAGE_SELF, &usage);
struct rusage usage;


std::size_t USED_MEMRORY = 0;
void* operator new(std::size_t size){
    USED_MEMRORY = USED_MEMRORY + size;
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info,
            &t_info_count);
    return malloc(size);
}

int main(int argc, char *argv[])
{
    QFile style_sheet_file("resource/stylesheet/Geoo.qss");
    style_sheet_file.open(QFile::ReadOnly);
    QString style_sheet = QLatin1String(style_sheet_file.readAll());
    QApplication a(argc, argv);
    a.setStyleSheet(style_sheet);
    MainWindow w;
    w.show();
    return a.exec();
}
