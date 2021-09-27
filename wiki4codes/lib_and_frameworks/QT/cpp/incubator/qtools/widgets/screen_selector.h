/// file: screen_selector.h
/// date: 2021-08-16


#include <QDialog>
#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <QRect>
#include <QPaintEvent>
#include <QMainWindow>
#include <QImage>


namespace qtools {


QPixmap grabScreenshot() {
  QPixmap desktopPixmap = QPixmap(QApplication::desktop()->geometry().size());
  QPainter painter(&desktopPixmap);
  for (QScreen* screen : QApplication::screens()) {
    painter.drawPixmap(screen->geometry().topLeft(), screen->grabWindow(0));
  }
  return desktopPixmap;
}


class ScreenSelector : public QDialog {
  //Q_OBJECT
 public:
  QPixmap selected_pixmap;
  explicit ScreenSelector(QWidget* parent = nullptr);

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

 private:
  QPixmap desktopPixmap;
  QRect selectedRect;
};


ScreenSelector::ScreenSelector(QWidget* parent) 
    : QDialog(parent, Qt::FramelessWindowHint) {
  setAttribute(Qt::WA_TranslucentBackground);
  setGeometry(QApplication::desktop()->geometry());
  desktopPixmap = grabScreenshot();
}


void ScreenSelector::mousePressEvent(QMouseEvent* event) {}


void ScreenSelector::mouseReleaseEvent(QMouseEvent* event) {} 


void ScreenSelector::mouseMoveEvent(QMouseEvent* event) {}


void ScreenSelector::paintEvent(QPaintEvent* event) {
  
}


} // namespace qtools
