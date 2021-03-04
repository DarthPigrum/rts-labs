#include "mainwindow.h"
#include "lab1.h"
#include "ui_mainwindow.h"
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto tabs = new QTabWidget(this);
  setCentralWidget(tabs);
  tabs->insertTab(0, new Lab1(this), "Lab1");
}

MainWindow::~MainWindow() { delete ui; }
