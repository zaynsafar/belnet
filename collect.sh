#!/bin/bash

set -e
docker create --name belnet-static belnet-static-image 
rm -rf belnet_deps
mkdir belnet_deps

docker cp belnet-static-image:/usr/src/app/build belnet_deps/

cp belnet_deps/build/daemon/belnet* belnet_deps/

rm -rf belnet_deps/build

docker container rm belnet-static