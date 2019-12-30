rem
rem This script takes care only of the mechanical part of the transformation - there is still manual rotation at least for some diodes!
rem 

set inputFile=Common_Rail_MC33816-bottom.pos
set outputFile=Common_Rail_MC33816-cpl.csv

echo "Translating from %inputFile% to %outputFile%"


grep -v Package %inputFile% | grep -v # | gawk '{ sub(/\..*/,"", $6); print $1 "," $4 "mm," $5 "mm,Bottom," $6}' > %outputFile%.temp
sed -f ../../tools/unquote.sed %outputFile%.temp > %outputFile%.all

echo "Designator,Mid X,Mid Y,Layer,Rotation" > %outputFile%

grep -v "L\|D" %outputFile%.all >> %outputFile%


