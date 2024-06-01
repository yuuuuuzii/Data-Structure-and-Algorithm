gcc main.c -o main

count=0
while true; do
    python gen.py > input.txt
    
    timeout 5s ./main < input.txt > /dev/null
    result=$?

    if [ $result -ne 0 ]; then
        echo "Time Limit Exceeded on test $count" 
        break
    fi

    echo -e "Test $count: OK"
    count=$((count+1))
done