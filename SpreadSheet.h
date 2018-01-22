#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>
#include <QStringList>

class SpreadSheet: public QTableWidget
{
   public:
      SpreadSheet(QWidget* parent = 0);
      SpreadSheet(int rows, int columns, QWidget* parent = 0);
      void setColumnTitle(int columnIndex, const QString& title);
      void addRow();
      void addColumn(const QString& title = "");
   protected:
      void keyPressEvent(QKeyEvent * event) final;
   private slots:
      void copyCells();
      void cutCells();
      void pasteCells();
      void deleteCells();
   private:
      int currentPasteRow();
      int currentPasteCol();

      QList<QStringList> clipboard;
};

#endif // SPREADSHEET_H
