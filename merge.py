from random import shuffle
num = 6
a = range(num)
shuffle(a)
#a = [3, 4, 5, 0, 1, 2]
#a = [5, 2, 3, 1, 0, 4]
print a, '\n'
def merge_sort(arr):
    
    def merge(l, e):
        s = l

        r = int((l+e)/2) 
        if r != e-1:
            r += 1 if arr[r] > arr[r+1] else 0
        mid = r
        print arr[l:e],'\n', l, r
        for n in range(l, e-1):
            if r == e or arr[l] < arr[r]:
                arr[n], arr[l] = arr[l], arr[n]
                if n < mid and l < mid:
                    l += 1
                if l == r:
                    r += 1
                    if l == e-1:
                        print arr[s:e],'\n', l, r
                        break

            else:
                arr[n], arr[r] = arr[r], arr[n]
                if l < mid:
                    l = r
                if l == n:
                    l += 1
                r += 1

            print arr[s:e],'\n', l, r

        if e-l > 1 and arr[e-1] < arr[e-2]:
            arr[e-1], arr[e-2] = arr[e-2], arr[e-1]
        print
    
    def rec_helper(start, end):
        if start == end:
            return

        mid = int((start+end)/2)
        rec_helper(start, mid)
        rec_helper(mid+1, end)

        merge(start, end+1)

    rec_helper(0, len(arr)-1)

merge_sort(a)
print a == range(num)
print a
