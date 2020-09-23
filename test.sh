

Test_1 = 1
Test_2 = 2
Test_3 = 3
Test_4 = 4
Test_5 = 5
Test_6 = 6


for i  1  3

echo $i 
for j  3  4
echo $j

for k  5 6 

echo $i,$j,$k
done 

done
done


test_array[3] = 5 6 7
test_array2[3] = 0 1 2 

echo $test_array[0]
echo $test_array[1]
echo $test_array[2]

echo $test_array[$test_array2[2]]
echo $test_array[$test_array2[1]]
echo $test_array[$test_array2[0]]



for IGAIndex  0  2

    echo IGA = $IGAIndex
	for   plane  0   2

    cmode -s $IGAIndex -t1  $Test_1 -t2 $Test_2 -t3 $Test_3 -t4 $Test_4 -t5 $Test_5 -p $test_array[$plane]
    
	done
done





