#include "main_window.h"
#include "./ui_main_window.h"
#include <QDir>
#include <QFileInfo>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto model = new EmojiPickerModel(this);

  QStringList iconPaths;

  // find all paths in images folder
  QDir dir("images");
  QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files);
  for (auto fileInfo : fileInfoList) {
    iconPaths.append(fileInfo.absoluteFilePath());
  }
  QList<EmojiData> emojis;

  for (const auto &iconPath : iconPaths) {
    emojis.append(EmojiData(iconPath, iconPath, QList<QString>()));
  }

  EmojiCategory category = EmojiCategory("Category A", emojis);
  model->setColumnCount(7);
  model->appendRow(category);
  category.name = "Category B";
  model->appendRow(category);

  ui->treeView->setModel(model);
}

MainWindow::~MainWindow() { delete ui; }
