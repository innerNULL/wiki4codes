# file: build_dev_images.sh
# date: 2022-07-08


set -x

docker rmi -f wiki4codes:v0.0.0
docker build -t wiki4codes:v0.0.0 --no-cache ./ 
