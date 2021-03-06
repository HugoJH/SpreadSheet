#include "SpreadSheet.h"
#include <QKeyEvent>

SpreadSheet::SpreadSheet(QWidget* parent):
   QTableWidget(parent)
{

}

SpreadSheet::SpreadSheet(int numberOfRows, int numberOfColumns, QWidget* parent):
   QTableWidget(parent)

{
   setRowCount(numberOfRows);
   setColumnCount(numberOfColumns);
}

void SpreadSheet::setColumnTitle(int columnIndex, const QString& title)
{
   setHorizontalHeaderItem(columnIndex,
                           new QTableWidgetItem(title, QTableWidgetItem::Type));
}

void SpreadSheet::addRow()
{
   insertRow(rowCount());
   for (int x = 0; x < columnCount(); ++x)
   {
      setItem(rowCount() - 1, x, new QTableWidgetItem);
   }
}

void SpreadSheet::addColumn(const QString& title)
{
   insertColumn(columnCount());
   setHorizontalHeaderItem(columnCount() - 1, new QTableWidgetItem(title));
   for (int x = 0; x < rowCount(); ++x)
   {
      setItem(x, columnCount() - 1, new QTableWidgetItem);
   }
}

void SpreadSheet::copyCells()
{
   clipboard.clear();
   QItemSelectionModel* selection = selectionModel();
   QModelIndexList indexes = selection->selectedIndexes();
   std::sort(indexes.begin(), indexes.end());

   QModelIndex previous = indexes.first();
   indexes.removeFirst();
   QModelIndex current;
   QStringList temp;

   foreach (current, indexes)
   {
      temp << model()->data(previous).toString();
      if (current.row() != previous.row())
      {
         clipboard.push_back(temp);
         temp.clear();
      }
      previous = current;
   }

   temp << model()->data(previous).toString();
   clipboard.push_back(temp);
}

void SpreadSheet::cutCells()
{
   copyCells();
   deleteCells();
}

void SpreadSheet::pasteCells()
{
   QStringList temp;
   int row = currentPasteRow();

   if (row ==-1)
   {
      return;
   }

   int col = currentPasteCol();
   int j = row;

   foreach (temp, clipboard)
   {
      for (int x = 0; x < temp.count(); ++x)
      {
         QTableWidgetItem* newItem = new QTableWidgetItem(temp.at(x));
         setItem(j, x + col, newItem);
      }
      temp.clear();
      ++j;
   }
}

void SpreadSheet::deleteCells()
{
   QTableWidgetItem* item;
   foreach (item,selectedItems())
   {
      item->setText("");
   }
}

void SpreadSheet::keyPressEvent(QKeyEvent* event)
{
   if(event->matches(QKeySequence::Copy))
      copyCells();
   else if (event->matches(QKeySequence::Cut))
      cutCells();
   else if(event->matches(QKeySequence::Paste))
      pasteCells();
   else if(event->matches(QKeySequence::Close))
      close();
   else if(event->matches(QKeySequence::Delete))
      deleteCells();
   else
      QTableWidget::keyPressEvent(event);
}

int SpreadSheet::currentPasteRow()
{
   if (selectedRanges().length()>1)
      return -1;
   return selectedRanges().at(0).topRow();
}

int SpreadSheet::currentPasteCol()
{
   if (selectedRanges().length()>1)
      return -1;
   return selectedRanges().at(0).leftColumn();
}
