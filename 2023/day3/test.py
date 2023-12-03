with open("input.txt") as f:
    ls = f.read().splitlines()

def get_num(l, x):
    s = e = x
    while s >= 0 and l[s].isdigit():
        s -= 1
    while e < len(l) and l[e].isdigit():
        e += 1
    return int(l[s + 1 : e])


sum = 0
for y, l in enumerate(ls):
    sum2 = 0
    for x, c in enumerate(l):
        if c == "*":
            s = list(
                {
                    get_num(ls[i], j)
                    for i in range(max(0, y - 1), min(len(ls) + 1, y + 2))
                    for j in range(max(0, x - 1), min(len(l) + 1, x + 2))
                    if ls[i][j].isdigit()
                }
            )
            if len(s) == 2:
                sum2 += s[0] * s[1]
                sum += s[0] * s[1]
    print(f'Line{y}: {sum2}')

print(sum)

