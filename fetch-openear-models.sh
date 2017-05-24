#!/usr/bin/env bash

set -xe

# Fetch openEAR pretrained models
wget https://downloads.sourceforge.net/project/openart/openEAR-0.1.0.tar.gz -O openEAR.tar.gz
tar xvf openEAR.tar.gz openEAR-0.1.0/models/
mv openEAR-0.1.0/models .
rm -r openEAR-0.1.0 openEAR.tar.gz
