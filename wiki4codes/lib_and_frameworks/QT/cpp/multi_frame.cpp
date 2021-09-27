/// file: first_program.cpp


#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QFrame>
#include <QGridLayout>

#include "qtools/commons.h"


std::string ICON_PATH = "../materials/qt_logo.png";


class Cursors : public QWidget {
 public:
  Cursors(QWidget *parent = 0);
};

Cursors::Cursors(QWidget *parent)
    : QWidget(parent) {
    
  QFrame *frame1 = new QFrame(this);
  frame1->setFrameStyle(QFrame::Box);
  frame1->setCursor(Qt::SizeAllCursor);

  QFrame *frame2 = new QFrame(this);
  frame2->setFrameStyle(QFrame::Box);
  frame2->setCursor(Qt::WaitCursor);

  QFrame *frame3 = new QFrame(this);
  frame3->setFrameStyle(QFrame::Box);
  frame3->setCursor(Qt::PointingHandCursor);

  QGridLayout *grid = new QGridLayout(this);
  grid->addWidget(frame1, 0, 0);
  grid->addWidget(frame2, 0, 1);
  grid->addWidget(frame3, 0, 2);

  setLayout(grid);
}


int main(int argc, char** argv) {
  QApplication app(argc, argv);
  //QWidget window;
  Cursors window;

  window.resize(250, 150);
  qtools::relocate_window_to_centre(&window);
  window.setWindowTitle("multi_frame_example");
  window.setToolTip("QWidget_tootip");
  window.setWindowIcon(QIcon(ICON_PATH.c_str())); 

  window.show();
  return app.exec();
}
