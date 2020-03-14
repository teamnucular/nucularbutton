#!/bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")

ln -sfT $SCRIPTPATH/minirc.nucularbutton ~/.minirc.dfl

