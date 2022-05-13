# file: install_flink.sh


set -x

TASK=$1


CURR_PATH=$(pwd)
FLINK_ROOT="./_flink"
FLINK_URL="https://dlcdn.apache.org/flink/flink-1.15.0/flink-1.15.0-bin-scala_2.12.tgz"
FLINK_BIN=${FLINK_ROOT}/flink-*/bin



download() {
  rm -rf ${FLINK_ROOT} && mkdir -p ${FLINK_ROOT}
  cd ${FLINK_ROOT} 
  wget ${FLINK_URL} && tar -xvzf ./flink-*.tgz
  #cd flink-* && ls -lh
  cd ${CURR_PATH}
}


start_local_cluster() {
  ${FLINK_BIN}/start-cluster.sh
}


stop_local_cluster() {
  ${FLINK_BIN}/stop-cluster.sh
}


main() {
  if [ "${TASK}" = "" ];
  then 
    echo "Empty argument"
  elif [ "${TASK}" = "download" ]
  then 
    download
  elif [ "${TASK}" = "start_local_cluster" ]
  then 
    start_local_cluster
  elif [ "${TASK}" = "stop_local_cluster" ]
  then 
    stop_local_cluster
  else
    echo "Wrong arguments"
  fi
}


main
