
#include <fstream>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <string>
#include <QtWidgets>
#include <QPixmap>
#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>

#include "qtools/widgets/screen_selector.h"


int main(int argc, char** argv) {
  QApplication app(argc, argv);
  //QGuiApplication app(argc, argv);
  QWidget window;
  //qtools::ScreenSelector window;
  window.resize(200, 50);
  window.setWindowTitle("button example");
 
  QScreen *screen;
  QPixmap qpx_pixmap;
  screen = QGuiApplication::primaryScreen();

  auto geom = screen->geometry();
  std::string screenshot_path = "./dev.jpg";

  /// Grab/Crop all of the primary-screen
  qpx_pixmap = screen->grabWindow(0, 
      geom.x(), geom.y(), geom.width(), geom.height());
  //qpx_pixmap = QScreen::grabWindow(QApplication::desktop()->winId());
  //qpx_pixmap = screen->grabWindow(0, QApplication::desktop()->winId());

  QPushButton *btn = new QPushButton("click me", &window);
  QObject::connect(btn, &QPushButton::clicked, 
      [=](){ qpx_pixmap.save(screenshot_path.c_str()); });
  
  //qtools::ScreenSelector screen_selector(&window);
  window.show();
  return app.exec();
}
