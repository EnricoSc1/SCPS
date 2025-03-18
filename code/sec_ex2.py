import time

N = [10,100,1000]
a = 3.0
b = 7.1

check = []
start = time.time()

for k in range(len(N)):
    
    A = []
    B = []
    C = []
    D = []

    for i in range(N[k]):
        row_A = []
        row_B = []
        for j in range(N[k]):
            row_A.append(a)
            row_B.append(b)
        A.append(row_A)
        B.append(row_B)

    for i in range(N[k]):
        row_C = []
        for j in range(N[k]):
            Cij = 0 
            for l in range(N[k]):
                Cij += A[i][l]*B[l][j]
            row_C.append(round(Cij,1))
        C.append(row_C)
     
    for l in range(N[k]):
        for z in range(N[k]):
            D.append(C[l][z])
        
    check.append(all( _ == round(21.3 * N[k],1) for _ in D))

print(check)
end = time.time()

print("Running time:",end - start,"s")
