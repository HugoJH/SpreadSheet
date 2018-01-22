#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   ui.setupUi(this);
   setCentralWidget(new SpreadSheet(12,12));
}

void MainWindow::changeEvent(QEvent *e)
{
   QMainWindow::changeEvent(e);
   switch (e->type()) {
      case QEvent::LanguageChange:
         ui.retranslateUi(this);
         break;
      default:
         break;
   }
}
