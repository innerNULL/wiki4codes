# file: build.sh
# date: 2022-07-08


set -x


main() {
  rm -rf ./qmf
  git clone https://github.com/innerNULL/qmf.git
  cd ./qmf && mkdir build && cd build
  cmake ../ && make -j8
  cd ../../
}


main
