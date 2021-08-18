from math import *
f = factorial
C = lambda n, k: f(n) // f(k) // f(n - k)
MOD = 1000000007
def ans(r):
    res = 0
    n = len(r)
    for i in range(1, n):
        res += C(i + 8, 8)
        res %= MOD
    for i in range(n - 1, 0, -1):
        x = min(r[i - 1], r[i])
        r = r[:i - 1] + x + r[i:] # 242324389 -> 222223389
    if r[0] == '0':
        return res

    big = 1
    for i in range(n):
        cur_digit = int(r[i])
        size = cur_digit
        if size >= 0:
            big *= C(n - i + size, size)

    res = (res + big) % MOD
    return res


l = input()
r = input()
a = ans(r) - ans(str(int(l) - 1))
a %= MOD
print(a)

'''
cnt = 0
for a in range(1, 10):
 for b in range(1, 10):
  for c in range(1, 10):
   for d in range(1, 10):
    for e in range(1, 10):
     for f in range(1, 10):
      cnt += (a <= b <= c <= d <= e <= f)

print(cnt)

> 9, 45, 165, 495, 1287
https://oeis.org/search?q=9%2C+45%2C+165%2C+495%2C+1287&sort=&language=english&go=Search
Wow!


dp[k][j] = dp[k - 1][i], i from 0 to j
'''
