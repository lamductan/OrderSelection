import numpy as np
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--n', type=int, default=100)
parser.add_argument('--m', type=int, default=15)
args = parser.parse_args()

n = args.n
m = args.m

object_id_prefix = 'SKU'
order_prefix = 'SO'

values = np.random.randint(low=2, high=200, size=(n))
print(n)
for i in range(n):
    print(object_id_prefix + str(i+1), values[i])

print(m)
size_of_orders = np.random.randint(low=1, high=n, size=(m))
for sz in size_of_orders:
    print(sz, end=' ')
print()
for i in range(m):
    order_id = order_prefix + str(i+1)
    obj_ids = np.random.permutation(n)[:size_of_orders[i]]
    for obj_id in obj_ids:
        obj_id_str = object_id_prefix + str(obj_id + 1)
        value = np.random.randint(low=1, high=(values[obj_id]//2 + 2))
        print(order_id, obj_id_str, value)
