#!/bin/sh
set -e -x

cat << EOF > configure/RELEASE
EPICS_BASE=$HOME/epics-base
EOF

# use default selection for MSI
sed -i -e '/MSI/d' configure/CONFIG_SITE

git clone --depth 10 --branch $BASE_BRANCH https://github.com/epics-base/epics-base.git $HOME/epics-base

EPICS_HOST_ARCH=`sh $HOME/epics-base/startup/EpicsHostArch`

case "$STATIC" in
static)
    cat << EOF >> "$HOME/epics-base/configure/CONFIG_SITE"
SHARED_LIBRARIES=NO
STATIC_BUILD=YES
EOF
    ;;
*) ;;
esac

case "$CXX" in
clang++)
  echo "Host compiler is clang"
  cat << EOF >> $HOME/epics-base/configure/os/CONFIG_SITE.Common.$EPICS_HOST_ARCH
GNU         = NO
CMPLR_CLASS = clang
CC          = clang
CCC         = clang++
EOF
  ;;
*) echo "Host compiler is default";;
esac

make -C "$HOME/epics-base" -j
