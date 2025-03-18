import time

d = []
x = []
y = []
a = 3.0
N = [10 , 10**6, 10**8]
check = []

start = time.time()

for i in range(len(N)):
    
    for j in range(N[i]):
    
        x.append(0.1)
        y.append(7.1)
        d.append(round(a * x[j] + y[j],1))    

    check.append(all(j == 7.4 for j in d))

end = time.time()

print(check)
print("Running time: ",end - start,"s")
