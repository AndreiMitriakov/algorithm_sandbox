def siftDown(a, n, i):
    l = 2*i+1
    r = 2*i+2
    largest = i
    if l < n and a[i] < a[l]:
        largest = l

    if r < n and a[largest] < a[r]:
        largest = r
        
    if largest != i:
        a[i], a[largest] = a[largest], a [i]
        siftDown(a, n,  largest)        
        
def heapify(arr):
    n = len(arr)
    for i in range(n-1, -1, -1):
        print(i)
        siftDown(arr, n, i)

def heapsort(arr):
    heapify(arr)
    for i in range(len(arr)-1, -1, -1):
        arr[i], arr[0] = arr[0], arr[i]
        siftDown(arr, i, 0)
        
if __name__ == '__main__':
    arr = [2,5,4,1,3,0,7,8,9,5,1,4,56,3]
    print(len(arr))
    heapsort(arr)
    print(arr)


