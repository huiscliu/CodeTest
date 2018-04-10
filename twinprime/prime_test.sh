# !/bin/bash

numbers=(100000000 200000000 1000000000 2000000000 4000000000 4294967295)

make

# running time for prime_pthread
echo ""
echo ""
echo "time for prime_pthreads"

for ((c = 1; c <= 10; c++)); do
    for m in ${numbers[@]}; do
        echo "time ./prime_pthread -m $m -c $c -q"
        time ./prime_pthread -m $m -c $c -q
        echo ""
    done
done

# running time for prime_mproc
echo ""
echo "time for prime_mproc"
for ((c = 1; c <= 10; c++)); do
    for m in ${numbers[@]}; do
        echo "time ./prime_mproc -m $m -c $c -q"
        time ./prime_mproc -m $m -c $c -q
        echo ""
    done
done
