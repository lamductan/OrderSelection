offset=$1

for (( i = 0; i < 20; i++ )); do
    python gen.py --n 10 --m 5 > in$(($i+$offset))
done

for (( i = 20; i < 40; i++ )); do
    python gen.py --n 10 --m 10 > in$(($i+$offset))
done

for (( i = 40; i < 60; i++ )); do
    python gen.py --n 10 --m 15 > in$(($i+$offset))
done

for (( i = 60; i < 80; i++ )); do
    python gen.py --n 50 --m 5 > in$(($i+$offset))
done

for (( i = 80; i < 100; i++ )); do
    python gen.py --n 50 --m 10 > in$(($i+$offset))
done

for (( i = 100; i < 120; i++ )); do
    python gen.py --n 50 --m 15 > in$(($i+$offset))
done

for (( i = 120; i < 140; i++ )); do
    python gen.py --n 100 --m 5 > in$(($i+$offset))
done

for (( i = 140; i < 160; i++ )); do
    python gen.py --n 100 --m 10 > in$(($i+$offset))
done

for (( i = 160; i < 180; i++ )); do
    python gen.py --n 100 --m 15 > in$(($i+$offset))
done