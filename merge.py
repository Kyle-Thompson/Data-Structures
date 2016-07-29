# the entire issue is determining where l should go next. Might be impossible to do in constant time.

from random import shuffle
num = 10
a = range(num)
shuffle(a)
print a, '\n'
def merge_sort(arr):
    def swap(a, b): arr[a], arr[b] = arr[b], arr[a]
        
    def display(b, m, e, l, r, n):
        index = 0
        s = '['
        for x in arr[b:m]:
            if index == l:
                s += '\033[94m'
            elif index == r:
                s += '\033[92m'
            elif index == n:
                s += '\033[95m'
            elif index < n:
                s += '\033[93m'

            s += str(x)
            if x != arr[m-1]:
                s += ' '
            index += 1
        
            s += '\033[0m'
        s += ']['
        for x in arr[m:e]:
            if index == n:
                s += '\033[95m'
            elif index < n:
                s += '\033[93m'
            if index == l:
                s += '\033[94m'
            elif index == r:
                s += '\033[92m'

            s += str(x)
            if x != arr[e-1]:
                s += ' '
            index += 1
        
            s += '\033[0m'
        s += ']'

        print s

    def merge(l, e):
        s = l

        r = int((l+e)/2) 
        if r != e-1:
            r += 1 if arr[r] > arr[r+1] else 0
        mid = r
        display(s, mid, e, l, r, 0)
        for n in range(l, e-1):
            if n == r:
                print 'n = r'
                display(s, mid, e, l, r, n)
                break
            elif r == e or arr[l] < arr[r]:
                swap(n, l)
                if (n < mid and l < mid) or r == e or (l >= mid and l+1 != r):
                    l += 1
                elif l > mid and l+1 == r and l-1 != n and arr[l] > arr[l-1]:
                    l -= 1
                if l < n or l == r:
                    print 'l <  n'
                    display(s, mid, e, l, r, n)
                    break

            else:
                if l == n and l >= mid and l+1 != r:
                    swap(l, l+1)
                swap(n, r)
                if l < mid:
                    l = r
                if l == n:
                    l += 1
                r += 1
            
            display(s, mid, e, l, r, n)

        if arr[e-1] < arr[e-2]:
            swap(e-1, e-2)
        print
    
    def merge2(l, e):
        s = l

        r = int((l+e)/2) 
        if r != e-1:
            r += 1 if arr[r] > arr[r+1] else 0
        mid = r
        display(s, mid, e, l, r, 0)
        for n in range(l, e-1):
            if n == r:
                print 'n = r'
                display(s, mid, e, l, r, n)
                break
            elif r == e or arr[l] < arr[r]:
                swap(n, l)
                if (n < mid and l < mid) or r == e or (l >= mid and l+1 != r):
                    l += 1
                elif l > mid and l+1 == r and l-1 != n and arr[l] > arr[l-1]:
                    l -= 1
                if l < n or l == r:
                    print 'l <  n'
                    display(s, mid, e, l, r, n)
                    break

            else:
                if l == n and l >= mid and l+1 != r:
                    swap(l, l+1)
                swap(n, r)
                if l < mid:
                    l = r
                if l == n:
                    l += 1
                r += 1
            
            display(s, mid, e, l, r, n)

        if arr[e-1] < arr[e-2]:
            swap(e-1, e-2)
        print
    
    def rec_helper(start, end):
        if start == end:
            return

        mid = int((start+end)/2)
        rec_helper(start, mid)
        rec_helper(mid+1, end)

        merge2(start, end+1)

    rec_helper(0, len(arr)-1)

merge_sort(a)
print a == range(num)
print a
