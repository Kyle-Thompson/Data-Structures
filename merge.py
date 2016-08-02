from random import shuffle
from math import sqrt
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

    def mannila_merge(start, mid, end):
        """ This is an attempted replication of the in-place merge algorithm
            by Mannila and Ukkomen.
        """
        buff = int(start + sqrt(mid-start))
        blocks = range(start, mid, buff) + mid
        for i in range(1, buff):
            last = arr[blocks[i]-1]
            if last < arr[mid]:
                blocks.append(mid)
            elif last > arr[-1]:
                blocks.append(end-1)
            else: #improve run time of this
                for j in range(blocks[-1], end):
                    if arr[j] < last and last <= arr[j+1]:
                        blocks.append(j)
                        break




    def rec_helper(start, end):
        if start == end:
            return

        mid = int((start+end)/2) 
        if mid != e-1:
            mid += 1 if arr[mid] > arr[mid+1] else 0
        rec_helper(start, mid)
        rec_helper(mid, end)

        mannila_merge(start, mid, end)

    rec_helper(0, len(arr))

merge_sort(a)
print a == range(num)
print a
