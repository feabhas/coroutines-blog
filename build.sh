#!/bin/bash
# -----------------------------------------------------------------------------
# build script
#
# DISCLAIMER:
# Feabhas is furnishing this item "as is". Feabhas does not provide any
# warranty of the item whatsoever, whether express, implied, or statutory,
# including, but not limited to, any warranty of merchantability or fitness
# for a particular purpose or any warranty that the contents of the item will
# be error-free.
# In no respect shall Feabhas incur any liability for any damages, including,
# but limited to, direct, indirect, special, or consequential damages arising
# out of, resulting from, or any way connected to the use of the item, whether
# or not based upon warranty, contract, tort, or otherwise; whether or not
# injury was sustained by persons or property or otherwise; and whether or not
# loss was sustained from, or arose out of, the results of, the item, or any
# services that may be provided by Feabhas.
# -----------------------------------------------------------------------------

set -o errexit
set -o nounset
USAGE="Usage: $(basename $0) [-v | --verbose ] [ reset | clean | debug | release ]"

CMAKE=cmake
BUILD=./build
TYPE=DEBUG
BUILD_DIR=$BUILD/debug
CLEAN=
RESET=
VERBOSE=

for arg; do
  case "$arg" in
    --help|-h)    echo $USAGE; exit 0;;
    -v|--verbose) VERBOSE='VERBOSE=1'  ;;
    debug)        TYPE=DEBUG;   BUILD_DIR=$BUILD/debug ;;
    release)      TYPE=RELEASE; BUILD_DIR=$BUILD/release ;;
    clean)        CLEAN=1  ;;
    reset)        RESET=1 ;;
    *)            echo -e "unknown option $arg\n$USAGE" >&2;  exit 1 ;;
  esac
done

[[ -n $RESET && -d $BUILD_DIR ]] && rm -rf $BUILD_DIR
    
$CMAKE -S . -B $BUILD_DIR --warn-uninitialized -DCMAKE_BUILD_TYPE=$TYPE

[[ -n $CLEAN ]] && $CMAKE --build $BUILD_DIR --target clean

$CMAKE --build $BUILD_DIR -- $VERBOSE
