#!/bin/sh

if [ -f 'cscope.files' ] 
then
  rm -f 'cscope.files'
fi

find src/ -name '*.cc'   > 'cscope.files'
find src/ -name '*.cpp' >> 'cscope.files'
find src/ -name '*.h'   >> 'cscope.files'
cscope -b
