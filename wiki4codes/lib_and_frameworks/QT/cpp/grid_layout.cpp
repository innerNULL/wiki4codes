
#include <fstream>
#include <string>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <string>
#include <QtWidgets>


int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  QWidget window;
  window.resize(200, 50);
  window.setWindowTitle("button example");

  QGridLayout *grid = new QGridLayout();

  for (int32_t row = 0; row < 3; ++row) {
    for (int32_t col = 0; col < 6; ++col) {
      std::string value = "(row=" + std::to_string(row) 
          + ", col=" + std::to_string(col) + ")";
      QPushButton *button = new QPushButton(value.c_str());
      grid->addWidget(button, row, col, 1, 1);
    }
  }

  window.setLayout(grid);
  window.show();
  return app.exec();
}
