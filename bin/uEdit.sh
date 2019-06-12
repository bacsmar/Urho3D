#!/usr/bin/env bash
if [[ $# -eq 0 ]]; then OPT1="-w -s"; fi
$(dirname $0)/Urho3DPlayer Data/AUI/UEdit/Scripts/uEdit.as $OPT1 $@ -p "Data;CoreData;Data/AUI;Data/AUI/UEdit"
