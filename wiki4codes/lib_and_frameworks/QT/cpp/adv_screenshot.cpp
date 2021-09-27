
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


QPixmap grabScreenshot()
{
    QPixmap desktopPixmap = QPixmap(QApplication::desktop()->geometry().size());
    QPainter p(&desktopPixmap);

    for (QScreen* screen : QApplication::screens())
        p.drawPixmap(screen->geometry().topLeft(), screen->grabWindow(0));

    return desktopPixmap;
}


class ScreenshotWidget : public QDialog {
Q_OBJECT
 public:
  explicit ScreenshotWidget(QWidget* parent = nullptr);
  QPixmap* selected_pixmap = new QPixmap();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

 private:
  QPixmap* desktop_pixmap = new QPixmap();
  QRect* selected_rect = new QRect();
  QGridLayout* grid = new QGridLayout(this);
};


ScreenshotWidget::ScreenshotWidget(QWidget* parent) 
    : QDialog(parent, Qt::FramelessWindowHint) {
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setGeometry(QApplication::desktop()->geometry());
  *(this->desktop_pixmap) = grabScreenshot();

  this->setLayout(this->grid);
}


void ScreenshotWidget::mousePressEvent(QMouseEvent* event) {
  this->selected_rect->setTopLeft(event->globalPos());
}


void ScreenshotWidget::mouseMoveEvent(QMouseEvent* event) {
  this->selected_rect->setBottomRight(event->globalPos());
  this->update();
}


void ScreenshotWidget::mouseReleaseEvent(QMouseEvent* event) {
  *(this->selected_pixmap) = this->desktop_pixmap->copy(
      this->selected_rect->normalized());
  this->accept();
}


void ScreenshotWidget::paintEvent(QPaintEvent*) {
  QPainter p(this);
  p.drawPixmap(0, 0, *(this->desktop_pixmap));
  QPainterPath path;
  path.addRect(rect());
  path.addRect(*(this->selected_rect));
  p.fillPath(path, QColor::fromRgb(255,255,255,200));
  p.setPen(Qt::red);
  p.drawRect(*(selected_rect));
}
    

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  ScreenshotWidget window;
  
  //window.resize(250, 150);
  //qtools::relocate_window_to_centre(&window);
  //window.setWindowTitle("img_viewer");

  window.show();

  if (app.exec() == QDialog::Accepted) {
    qApp->clipboard()->setPixmap(*(window.selected_pixmap));
  }
  return 0;

}


#include "adv_screenshot.moc"
