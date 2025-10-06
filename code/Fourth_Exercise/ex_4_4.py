import numpy
from scipy import integrate

I_TRUE = (numpy.exp(numpy.pi / 2) - 1) / 2

content = numpy.loadtxt("ex4_data.txt")

x = content[:,0]
y = content[:,1]

result_trapz = numpy.trapz(y,x)
result_simps = integrate.simps(y,x)

print("The numerical integration with the trapezoidal method returns I_t =",result_trapz,"with relative error",result_trapz/I_TRUE - 1)
print("The numerical integration with Simpson's rules is I_s =",result_simps,"with relative error",result_simps/I_TRUE - 1)
