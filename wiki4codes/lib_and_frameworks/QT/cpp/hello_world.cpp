
#include <fstream>

#include <QApplication>
#include <QWidget>
#include <QLabel>


int main(int argc, char** argv) {
  QApplication app(argc, argv);
  QWidget window;
  window.resize(200, 50);
  window.setWindowTitle("app");
  QLabel label("Hello, World", &window);
  window.show();
  return app.exec();
}
