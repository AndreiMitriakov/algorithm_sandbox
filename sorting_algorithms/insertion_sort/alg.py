def insertion_sort(arr, left=0, right=-1):
	if right == -1:
	    right = len(arr)-1
	for i in range(left+1, right+1):
		key = arr[i]
		j = i - 1
		while j>=left and key<arr[j]:
			arr[j+1] = arr[j]
			j -= 1
		arr[j+1] = key

if __name__ == '__main__':
    arr = [12, 11, 13, 5, 6] 
    insertion_sort(arr) 
    print(arr) 
