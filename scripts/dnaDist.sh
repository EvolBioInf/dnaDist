./dnaDist > tmp.out
DIFF=$(diff tmp.out ../data/dnaDist.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(dnaDist)\tpass\n"
else
    printf "Test(dnaDist)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
