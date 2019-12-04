from merge_sort.alg import merge_sort
from heapsort.alg import heapsort
from insertion_sort.alg import insertion_sort
from quick_sort.alg import quick_sort
from selection_sort.alg import selection_sort
from timsort.alg import timsort

if __name__ == '__main__':
    arr = [2,5,4,1,3,0,7,8,9,5,1,4,56,3]
    print(arr)
    low = 0
    high = len(arr) - 1 
    n = len(arr)
    # quick_sort(arr, low, high)
    timsort(arr, n)
    print(arr)

