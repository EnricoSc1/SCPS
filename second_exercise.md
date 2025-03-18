# Second Exercise :pencil:
The second exercise of the course deal with Linear Algebra, in particular vector sum and matrix multiplication handling via compiler and interpreter. Speaking of them, the choices I made for the languages are:
- Compiler: **C**, 
- Interpreter: **Python**.

Here is the complete request:

![SecondExercise](https://raw.githubusercontent.com/EnricoSc1/SCPS/refs/heads/main/images/Task_2.png)
## First: Vector Sum in Python
The [code](https://github.com/EnricoSc1/SCPS/blob/main/code/sec_ex.py) I made for solving the point 1) is the following:
![VecPython](https://raw.githubusercontent.com/EnricoSc1/SCPS/refs/heads/main/images/second_exercise_pt1_python.png)

To build the arrays I use the python function **append()** and to check the correctness of the result I use **all()**. The code is working, but it relies on built-in functions. A simple task like this is coded in almost **43 s**, which is not very promising. 
## Second: Vector Sum in C
In point 2) I translate the Python code in C, shown [here](https://github.com/EnricoSc1/SCPS/blob/main/code/sec_ex.c):
![VecC](https://raw.githubusercontent.com/EnricoSc1/SCPS/refs/heads/main/images/second_exercise_pt1_C.png)

I struggle a bit to end up with the correct assignment due to two reasons:
- **Floating point** inaccuracy: solved by introducing a precision threshold in order to have a  consistent check condition, 
- Memory allocation for arrays of huge dimension: partially fixed using **dynamic memory allocation** provided by **chatGPT**, as I lack time to improve my knowledge of **pointers** in C.

The dominance of a Compiler over an Interpreter for heavy computation is crystal clear here, in fact this task is coded in only **1.59 s**.
## Third: Matrix Multiplication in Python
Here is my [code](https://github.com/EnricoSc1/SCPS/blob/main/code/sec_ex2.py) for point 3):
![MatPython](https://raw.githubusercontent.com/EnricoSc1/SCPS/refs/heads/main/images/second_exercise_pt2_python.png)

To code the matrix multiplication I used built-in functions together with arithmetic operators. Also, I did not reach dimension **10000** due to the slowness of it, indeed the coding time with N=500 is **14.8 s** and it gets worse quickly (for N = 1000 it takes 120 s). 
## Fourth: Matrix Multiplication in C
The last point of the exercise is coded [here](https://github.com/EnricoSc1/SCPS/blob/main/code/sec_ex2.c):
![MatC](https://raw.githubusercontent.com/EnricoSc1/SCPS/refs/heads/main/images/second_exercise_pt2_C.png)

To make a fair comparison with Python I used the same values for N, and the code is done in **0.49 s**. However I tried also to implement N = 10000, but I receive a **segmentation** error due to fixed memory allocation. In this case I was not able to improve the code for matrices having entries allocated dynamically.

### Time Stamps
![time](https://raw.githubusercontent.com/EnricoSc1/SCPS/refs/heads/main/images/TimeEx2.png)

