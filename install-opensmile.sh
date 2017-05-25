#!/usr/bin/env bash

set -xe

OPENSMILE_VERSION=2.3.0
OPENSMILE_URL=http://audeering.com/download/1318/
# Build with installed portaudio
# The prebundled portaudio does not detect any audio devices
OPENSMILE_INSTALL_SCRIPT=buildWithInstalledPortAudio.sh

# Setup install prefix path (i.e. /usr/local or /opt/opensmile)
# The default install path is $(pwd)/opensmile/inst
# Leaving this empty is recommended
if [ -z "$1" ]
then
    PREFIX=""
    SUDO=""
    LOGINSTPREFIX="$(pwd)/opensmile/inst"
else
    PREFIX=$1
    mkdir -p ${PREFIX}
    SUDO="sudo "
    LOGINSTPREFIX=$PREFIX
fi

# install deps
sudo apt-get install -y portaudio19-dev libportaudio2 libasound-dev
sudo apt-get install -y libsvm-dev libsvm3 libsvm-tools

# Fetch opensmile
wget ${OPENSMILE_URL} -O opensmile.tar.gz
tar xvf opensmile.tar.gz
mv opensmile{-$OPENSMILE_VERSION,}
cd opensmile

# Fetch openEAR pretrained models
wget https://downloads.sourceforge.net/project/openart/openEAR-0.1.0.tar.gz -O openEAR.tar.gz
tar xvf openEAR.tar.gz openEAR-0.1.0/models/
mv openEAR-0.1.0/models .
rm -r openEAR-0.1.0 openEAR.tar.gz

# Shorten the turn length for live emotion recognition
cp config/emobase_live4.conf ./emolive.conf
sed -i -e '/maxTurnLength =/ s/= .*/= 1/' emolive.conf
sed -i -e '/maxTurnLengthGrace =/ s/= .*/= 2/' emolive.conf

# set correct flags to build with libsvm support
SET_CPPFLAGS='export CPPFLAGS="-DOPENSMILE_BUILD -DHAVE_PORTAUDIO -DBUILD_LIBSVM -DBUILD_SVMSMO -DBUILD_RNN -DBUILD_WITHOUT_EXPERIMENTAL"'
sed -i "/mkdir inst/a ${SET_CPPFLAGS}" ${OPENSMILE_INSTALL_SCRIPT}

# Run the build script
${SUDO} bash ${OPENSMILE_INSTALL_SCRIPT} ${PREFIX}

echo "Opensmile is installed in ${LOGINSTPREFIX}"

echo "You can set your environmental variables in .bashrc. Run:"
echo "Append ${LOGINSTPREFIX}/bin to PATH"
echo "Append ${LOGINSTPREFIX}/lib to LD_LIBRARY_PATH"

echo "You can test if audio recording is working with:"
echo "\t./SMILExtract -C config/demo/audiorecorder.conf -O record.wav"

echo "You can test live emotion recognition with:"
echo "\t./SMILExtract -C emolive.conf"
