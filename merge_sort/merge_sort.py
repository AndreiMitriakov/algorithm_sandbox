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



