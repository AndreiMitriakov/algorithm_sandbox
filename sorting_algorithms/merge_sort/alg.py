def merge(arr, l, m, r):
    l1 = m-l+1
    l2 = r-m
    left = [0 for i in range(l1)]
    right = [0 for i in range(l2)]
    for i in range(l1):
        left[i] = arr[l+i]
    for i in range(l2):
        right[i] = arr[m+1+i]
    i = 0
    j = 0
    k = l
    while i < l1 and j < l2:
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[i]
            j += 1
        k += 1
    while i < l1:
        arr[k] = left[i]
        k += 1
        i += 1
    while j < l2:
        arr[k] = right[j]
        k += 1
        j += 1

def merge_sort(a):
    if len(a) > 1:
        mid = len(a)//2
        lh = a[:mid]
        rh = a[mid:]
        merge_sort(lh)
        merge_sort(rh)
        
        i = 0
        j = 0
        k = 0
        
        while i<len(lh) and j<len(rh):
            if lh[i] < rh[j]:
                a[k] = lh[i]
                i += 1
            else:
                a[k] = rh[j]
                j += 1
            k += 1
        while i<len(lh):
            a[k] = lh[i]
            i += 1
            k += 1
        
        while j<len(rh):
            a[k] = rh[j]
            j += 1
            k += 1
        
if __name__ == '__main__':
    arr = [2,5,4,1,3]
    print(arr)
    merge_sort(arr)
    print(arr)



