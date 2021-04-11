#include "mainwindow.h"
#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "ui_mainwindow.h"
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto tabs = new QTabWidget(this);
  setCentralWidget(tabs);
  tabs->insertTab(0, new Lab1(this), "Lab1");
  tabs->insertTab(1, new Lab2(this), "Lab2");
  tabs->insertTab(2, new Lab3(this), "Lab3");
}

MainWindow::~MainWindow() { delete ui; }
