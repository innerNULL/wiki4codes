

#include <iostream>

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QSize>
#include <QPixmap>
#include <QPainter>


namespace qtools {


void relocate_window_to_centre(QWidget* window) {
  QSize size = window->size();
  int32_t window_height = size.height();
  int32_t window_width = size.width();
  QDesktopWidget* desktop = QApplication::desktop();
  int32_t screen_width = desktop->width();
  int32_t screen_height = desktop->height(); 

  int32_t x = (screen_width - window_width) / 2;
  int32_t y = (screen_height - window_height) / 2;
  printf("window_width: %i, window_height: %i, screen_width: %i, screen_height: %i\n", 
      window_width, window_height, screen_width, screen_height);
  printf("x: %i, y: %i\n", x, y);
  window->move(x, y);
}


} // namespace qtools
