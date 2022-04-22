#include "dialog.h"
#include "ui_dialog.h"

#include <QBarSeries>
#include <QBarSet>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QtCharts>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);

  QPieSeries *seriesPie = new QPieSeries();
  seriesPie->append("Cake", 5);
  seriesPie->append("Pizza", 15);
  seriesPie->append("Bacon", 30);
  seriesPie->append("Tuna", 30);
  seriesPie->append("Steak", 20);

  QChart *chartPie = new QChart();
  chartPie->addSeries(seriesPie);
  chartPie->setTitle("Favorite food");

  QChartView *viewPie = new QChartView(chartPie);
  viewPie->setParent(ui->containerPieChart);

  QPieSlice *slice = seriesPie->slices().at(3);
  slice->setExploded();
  slice->setLabelVisible();
  slice->setPen(QPen(Qt::black, 1));
  slice->setBrush(Qt::darkBlue);

  QBarSet *set0 = new QBarSet("Student A");
  QBarSet *set1 = new QBarSet("Student B");
  QBarSet *set2 = new QBarSet("Student C");

  *set0 << 10 << 50 << 20 << 30 << 40 << 40;
  *set1 << 10 << 60 << 30 << 25 << 30 << 20;
  *set2 << 20 << 80 << 20 << 30 << 70 << 60;

  QBarSeries *seriesBar = new QBarSeries();
  seriesBar->append(set0);
  seriesBar->append(set1);
  seriesBar->append(set2);

  QChart *chartBar = new QChart();
  chartBar->addSeries(seriesBar);
  chartBar->setTitle("Favorite Food");
  chartBar->setAnimationOptions(QChart::SeriesAnimations);

  QStringList categories;
  categories << "Cake"
             << "Pizza"
             << "Bacon"
             << "Tuna"
             << "Steak";

  QBarCategoryAxis *axis = new QBarCategoryAxis();
  axis->append(categories);
  chartBar->createDefaultAxes();
  chartBar->setAxisX(axis, seriesBar);

  QChartView *chartView = new QChartView(chartBar);
  chartView->setParent(ui->containerBarChart);
  show();
  viewPie->resize(viewPie->parentWidget()->size());
  chartView->resize(chartView->parentWidget()->size());
}

Dialog::~Dialog() { delete ui; }
