#include "gmqtlistwidget.h"


GMQtListWidget::GMQtListWidget(QWidget *parent): QListWidget(parent)
{
    this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    QListWidgetItem* item = new QListWidgetItem("Add", this);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}
