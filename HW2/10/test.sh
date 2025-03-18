gcc main.c -o main
gcc gen.c -o gen

count=0
while true; do
    ./gen > input.txt
    python right.py < input.txt > output.txt

    timeout 3s ./main < input.txt > output_c.txt
    result=$?

    if [ $result -ne 0 ]; then
        echo "Time Limit Exceeded on test $count"
        break
    fi

    if diff output.txt output_c.txt > /dev/null; then 
        echo "Test $count: OK"
    else
        echo "Test $count: Wrong Answer"
        break
    fi
    count=$((count+1))
done