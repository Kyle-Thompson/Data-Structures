from random import shuffle
num = 10
a = range(num)
shuffle(a)
#a = [3, 4, 5, 0, 1, 2]
#a = [5, 2, 3, 1, 0, 4]
print a, '\n'
def merge_sort(arr):
    #swap = lambda a, b: arr[a], arr[b] = arr[b], arr[a]
    def display(b, m, e, l, r):
        s = ''
        s += '[' + ' '.join([str(x) for x in arr[b:m]]) + '] '
        s += '[' + ' '.join([str(x) for x in arr[m:e]]) + ']'
        print s, l, r

    def merge(l, e):
        s = l

        r = int((l+e)/2) 
        if r != e-1:
            r += 1 if arr[r] > arr[r+1] else 0
        mid = r
        display(s, mid, e, l, r)
        for n in range(l, e-1):
            if r == e or arr[l] < arr[r]:
                arr[n], arr[l] = arr[l], arr[n]
                if (n < mid and l < mid) or r == e or (l >= mid and l+1 != r):
                    l += 1
                if l == n:
                    display(s, mid, e, l, r)
                    #print arr[s:e],'\n', l, r
                    break
                if l == r:
                    r += 1
                    if l == e-1:
                        display(s, mid, e, l, r)
                        #print arr[s:e],'\n', l, r
                        break

            else:
                if l == n and l >= mid and l+1 != r:
                    arr[l], arr[l+1] = arr[l+1], arr[l]
                arr[n], arr[r] = arr[r], arr[n]
                if l < mid:
                    l = r
                if l == n:
                    l += 1
                r += 1
            
            display(s, mid, e, l, r)
            #print arr[s:e],'\n', l, r

        if arr[e-1] < arr[e-2]:
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
