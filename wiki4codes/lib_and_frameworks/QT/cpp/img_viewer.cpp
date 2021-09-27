
#include <fstream>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <string>
#include <QtWidgets>
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QSizePolicy>
#include <QPalette>
#include <QPainter>

#include "qtools/commons.h"


class ImageViewer : public QWidget {
 public:
  ImageViewer(QWidget *parent = nullptr);

 protected:
  void imgLabelInit();
  void click_img2text();
  void click_screenshot();
  void click_loadimg();

 private:
  QDesktopWidget* desktop = QApplication::desktop();
  QPixmap* pixmap = new QPixmap();
  QScreen* screen = QGuiApplication::primaryScreen();
  QPainter* painter = new QPainter();

  QLabel* img_label = new QLabel();
  QLabel* text_label = new QLabel();
  QPushButton *quitBtn = new QPushButton("Quit", this);
  QPushButton *screenshotBtn = new QPushButton("Screenshot", this);
  QPushButton *img2textBtn = new QPushButton("ToText", this);
  QPushButton *loadimgBtn = new QPushButton("LoadImg", this);
};


ImageViewer::ImageViewer(QWidget *parent) 
    : QWidget(parent) {
  this->imgLabelInit();
  this->img_label->setPixmap(*pixmap);
  this->text_label->setText("OCR Area");

  QGridLayout *grid = new QGridLayout(this);
  grid->addWidget(this->img_label, 0, 0, 6, 5);
  grid->addWidget(this->text_label, 6, 0, 5, 0);
  grid->addWidget(this->quitBtn, 5, 5);
  grid->addWidget(this->screenshotBtn, 3, 5);
  grid->addWidget(this->img2textBtn, 4, 5);
  grid->addWidget(this->loadimgBtn, 2, 5);

  this->connect(this->quitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));
  this->connect(this->img2textBtn, &QPushButton::clicked, this, 
      [=](){ this->click_img2text(); } );
  this->connect(this->screenshotBtn, &QPushButton::clicked, this, 
      [=](){ this->click_screenshot(); this->show(); } );
  this->connect(this->loadimgBtn, &QPushButton::clicked, this, 
      [=](){ this->click_loadimg(); } );

  this->setLayout(grid);
}


void ImageViewer::imgLabelInit() {
  this->img_label->setBackgroundRole(QPalette::Base);
  this->img_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  this->img_label->setScaledContents(true);
}


void ImageViewer::click_loadimg() {
  this->pixmap->load("../materials/qt_logo.png");
  this->img_label->setPixmap(*pixmap);
}


void ImageViewer::click_screenshot() {
  auto geom = this->screen->geometry();
  //setWindowFlags(Qt::FramelessWindowHint);
  //setAttribute(Qt::WA_TranslucentBackground);

  *(this->pixmap) = this->screen->grabWindow(0, 
      geom.x(), geom.y(), geom.width(), geom.height());
  
  this->img_label->setPixmap(*pixmap);
}


void ImageViewer::click_img2text() {
  this->text_label->setText("Not supporting OCR for now...comming soon.");
}


int main(int argc, char** argv) {
  QApplication app(argc, argv);
  ImageViewer window;
  
  window.resize(250, 150);
  qtools::relocate_window_to_centre(&window);
  window.setWindowTitle("img_viewer");

  window.show();
  return app.exec();
}
