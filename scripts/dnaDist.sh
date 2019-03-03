./dnaDist ../data/test.fa > tmp.out
DIFF=$(diff tmp.out ../data/dnaDist.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist)\t\tpass\n"
else
    printf "Test(dnaDist)\t\tfail\n"
    echo ${DIFF}
fi

./dnaDist -r ../data/test.fa > tmp.out
DIFF=$(diff tmp.out ../data/dnaDistR.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist, -r)\tpass\n"
else
    printf "Test(dnaDist, -r)\tfail\n"
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

