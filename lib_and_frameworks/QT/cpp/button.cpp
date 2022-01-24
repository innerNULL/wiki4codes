
#include <fstream>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <string>
#include <QtWidgets>

#include "qtools/commons.h"


std::string ICON_PATH = "../materials/qt_logo.png";


/** Naive Example
int main(int argc, char** argv) {
  QApplication app(argc, argv);
  QWidget window;
  window.resize(200, 50);
  window.setWindowTitle("button example");

  QPushButton *btn = new QPushButton("click me", &window);

  QObject::connect(
      btn, 
      &QPushButton::clicked, 
      [=](){ btn->setText("Thank you"); }
  );

  window.show();
  return app.exec();
}
**/


class WindowsWithButton : public QWidget {
  Q_OBJECT
 public:
  WindowsWithButton(QWidget *parent = nullptr);
 private slots:
  void OnPlus();
  void OnMinus();
 private:
  QLabel *label;
};


WindowsWithButton::WindowsWithButton(QWidget *parent) 
    : QWidget(parent) {
  QPushButton *quitBtn = new QPushButton("Quit", this);
  QPushButton *plusBtn = new QPushButton("Plus", this);
  QPushButton *minusBtn = new QPushButton("Minus", this);
  this->label = new QLabel("0", this);

  QGridLayout *grid = new QGridLayout(this);
  
  grid->addWidget(this->label, 2, 1);
  grid->addWidget(quitBtn, 3, 1);
  grid->addWidget(plusBtn, 1, 0);
  grid->addWidget(minusBtn, 1, 2);

  this->connect(quitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));
  this->connect(plusBtn, SIGNAL(clicked()), this, SLOT(OnPlus()));
  this->connect(minusBtn, SIGNAL(clicked()), this, SLOT(OnMinus()));
}


void WindowsWithButton::OnPlus() {
  int val = this->label->text().toInt();
  val++;
  this->label->setText(QString::number(val));
}


void WindowsWithButton::OnMinus() {
  int val = this->label->text().toInt();
  val--;
  this->label->setText(QString::number(val));
}


int main(int argc, char** argv) {
  QApplication app(argc, argv);
  WindowsWithButton window;

  window.resize(250, 150);
  qtools::relocate_window_to_centre(&window);
  window.setWindowTitle("multi_frame_example");
  window.setToolTip("QWidget_tootip");
  window.setWindowIcon(QIcon(ICON_PATH.c_str())); 

  window.show();
  return app.exec();
}


#include "button.moc"
