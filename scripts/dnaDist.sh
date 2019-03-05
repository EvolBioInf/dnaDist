./dnaDist ../data/test.fa > tmp.out
DIFF=$(diff tmp.out ../data/dnaDist.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist)\t\tpass\n"
else
    printf "Test(dnaDist)\t\tfail\n"
    echo ${DIFF}
fi

./dnaDist -r 1 ../data/test.fa > tmp.out
DIFF=$(diff tmp.out ../data/dnaDistR1.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist, -r 1)\tpass\n"
else
    printf "Test(dnaDist, -r 1)\tfail\n"
    echo ${DIFF}
fi

./dnaDist -r 2 ../data/test.fa > tmp.out
DIFF=$(diff tmp.out ../data/dnaDistR2.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist, -r 2)\tpass\n"
else
    printf "Test(dnaDist, -r 2)\tfail\n"
    echo ${DIFF}
fi

./dnaDist -s 13 -b 10 ../data/test.fa > tmp.out
DIFF=$(diff tmp.out ../data/dnaDistB.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist, -b)\tpass\n"
else
    printf "Test(dnaDist, -b)\tfail\n"
    echo ${DIFF}
fi

./dnaDist -s 13 -p 10 ../data/test.fa > tmp.out
DIFF=$(diff tmp.out ../data/dnaDistP.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist, -p)\tpass\n"
else
    printf "Test(dnaDist, -p)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out

