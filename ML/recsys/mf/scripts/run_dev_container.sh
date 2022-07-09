# file: run_dev_container.sh
# date: 2022-07-08


set -x


sudo docker rm -f wiki4codes_dev

sudo docker run -it --privileged \
    --name wiki4codes_dev \
    -v $(pwd):/workspace \
    --net=host \
    wiki4codes:v0.0.0 \
    bash
