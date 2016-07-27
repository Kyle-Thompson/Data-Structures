from random import shuffle
a = range(50)
shuffle(a)

def merge_sort(arr):
    def merge(l, e):

        r = int((l+e)/2) 
        if r != e-1:
            r += 1 if arr[r] > arr[r+1] else 0
        
        while r != e:
            if arr[r] < arr[l]:
                arr[l], arr[r] = arr[r], arr[l]
            
            if r-l < 2: r += 1
            else: l += 1
    
    def rec_helper(start, end):
        if start == end:
            return

        mid = int((start+end)/2)
        rec_helper(start, mid)
        rec_helper(mid+1, end)

        merge(start, end)

    rec_helper(0, len(arr)-1)

merge_sort(a)
print a == range(500)
print a
