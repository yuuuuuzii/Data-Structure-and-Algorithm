gcc main.c -o main
gcc test.c -o data_gen

count=0
while true; do
    ./data_gen > input
    timeout 3s ./main < input > /dev/null

    if [ $? -ne 0 ]; then
        echo "Time Limit Exceeded"
        break
    fi
    
    echo -e "Test $count: OK"
    count=$((count+1))
done