import csv
import matplotlib.pyplot as plt
import math as m
# Инициализация списков
numeric = []
length = []
mass = []
stiffness = []

L = [4.73,  7.853, 10.996, 14.137, 17.279]


def calculate_sum(base):
    sum = [0] * len(base)
    for i in range(len(base)):
        if i == 0:
            sum[i] = base[i]
        else:
            sum[i] = sum[i-1] + base[i - 1] + base[i]
    return sum

def calculate_multi(one, second):
    return [a * b for a, b in zip(one, second)]

# Чтение данных из CSV-файла
n = 0
with open('rocket_body.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',')  # Используем запятую как разделитель
    next(spamreader)  # Пропускаем заголовок
    for row in spamreader:
        numeric.append(n)
        length.append(float(row[0]))  # Преобразуем значения в float и добавляем в список
        mass.append(float(row[1]))
        stiffness.append(float(row[2]))
        n+=1


m_N = [a * b for a, b in zip(numeric, mass)]

sum_m = calculate_sum(mass)
sum_m_N = calculate_sum(m_N)
Nmid = sum_m_N[-1]/sum_m[-1]

N_Nm  = [x - Nmid for x in numeric]
N_Nm2 = [x ** 2 for x in N_Nm]

preIn = calculate_multi(N_Nm2, mass)
In = calculate_sum(preIn)

rocket_length = 0
rocket_mass = 0
for i in range(len(length)):
    rocket_length += length[i]
    rocket_mass   += mass[i]

a = [x/rocket_length for x in L]
chJ_cosJ = [m.cosh(x)-m.cos(x) for x in L]
shJ_sinJ = [m.sinh(x)-m.sin(x) for x in L]
sinJ_shJ = [m.sin(x)-m.sinh(x) for x in L]
Y = [a / b for a, b in zip(chJ_cosJ, sinJ_shJ)]


f_zero = [0] * 5
f_stiffness = [0] * 5
f_mass = [0] * 5
w_calc = [0] * 5
for i in range(len(f_zero)):
    f_zero[i] = [((m.sin(a[i]*x)+m.sinh(a[i]*x))*Y[i]+(m.cos(a[i]*x)+m.cosh(a[i]*x)))/2 for x in numeric]

w_zero = [m.sqrt(max(stiffness)/(rocket_mass*(10**3)/rocket_length*pow(rocket_length,4)))*(x**2)/(2*m.pi) for x in L]


m_f1 = calculate_multi(mass, f_zero[0])
sum_m_f1 = calculate_sum(m_f1)

value_6_11 = calculate_multi(m_f1, N_Nm)
sum_value_6_11 = calculate_sum(value_6_11)

D1 = - sum_value_6_11[-1]/In[-1]
D2 = - sum_m_f1[-1]/sum_m[-1]

D1_6 = [x*D1 for x in N_Nm]
D2_15 = [D2+x  for x in D1_6]
f1_16 = [a + b for a, b in zip(D2_15, f_zero[0])]

f_mass[0] = [x/max(f1_16) for x in f1_16]

m_f1 = calculate_multi(mass, f_mass[0])
sum_m_f1 = calculate_sum(m_f1)
double_sum_m_f1 = calculate_sum(sum_m_f1)
dm1 = [-x*double_sum_m_f1[-1]/numeric[-1] for x in numeric]
M1x = [a + b for a, b in zip(dm1, double_sum_m_f1)]
M1x_E = [a/b if b != 0 else 0 for a, b in zip(M1x, stiffness)]
sum_M1x_E = calculate_sum(M1x_E)
double_sum_M1x_E = calculate_sum(sum_M1x_E)
double_sum_M1x_E_mass = calculate_multi(double_sum_M1x_E, mass)
summ_13 = calculate_sum(double_sum_M1x_E_mass)

value_13_15 = [a * b for a, b in zip(double_sum_M1x_E_mass, N_Nm)]
sum_13_15 = calculate_sum(value_13_15)

D1 = - sum_13_15[-1]/In[-1]
D2 = - summ_13[-1]/sum_m[-1]

D1_15 = [x*D1 for x in N_Nm]
D2_11 = [a + b + D2 for a, b in zip(double_sum_M1x_E, D1_15)]

f_stiffness[0] = [x/max(D2_11) for x in D2_11]

m_f1 = calculate_multi(mass, f_stiffness[0])
sum_m_f1 = calculate_sum(m_f1)
double_sum_m_f1 = calculate_sum(sum_m_f1)
dm1 = [-x*double_sum_m_f1[-1]/numeric[-1] for x in numeric]
M1x = [a + b for a, b in zip(dm1, double_sum_m_f1)]
M1x2 = [x ** 2 for x in M1x]
M1x2_E = [a/b if b != 0 else 0 for a, b in zip(M1x2, stiffness)]
sum_M1x2_E = calculate_sum(M1x2_E)
f_12 = [x ** 2 for x in f_stiffness[0]]
mf_12 = calculate_multi(f_12, mass)
sum_mf_12 = calculate_sum(mf_12)
w_calc[0] = m.sqrt(sum_mf_12[-1]/(sum_M1x2_E[-1]*1000.0*pow(length[-1]/2,4)))/(2*m.pi)

#######################################################################################
m_f1 = calculate_multi(mass, f_zero[1])
sum_m_f1 = calculate_sum(m_f1)

value_6_11 = calculate_multi(m_f1, N_Nm)
sum_value_6_11 = calculate_sum(value_6_11)


D1 = - sum_value_6_11[-1]/In[-1]
D2 = - sum_m_f1[-1]/sum_m[-1]

D1_6 = [x*D1 for x in N_Nm]
D2_15 = [D2+x  for x in D1_6]
f1_16 = [a + b for a, b in zip(D2_15, f_zero[1])]

f_mass[1] = [x/max(f1_16) for x in f1_16]

m_f1 = calculate_multi(mass, f_mass[1])
sum_m_f1 = calculate_sum(m_f1)
double_sum_m_f1 = calculate_sum(sum_m_f1)
dm1 = [-x*double_sum_m_f1[-1]/numeric[-1] for x in numeric]
M1x = [a + b for a, b in zip(dm1, double_sum_m_f1)]
M1x_E = [a/b if b != 0 else 0 for a, b in zip(M1x, stiffness)]
sum_M1x_E = calculate_sum(M1x_E)
double_sum_M1x_E = calculate_sum(sum_M1x_E)
double_sum_M1x_E_mass = calculate_multi(double_sum_M1x_E, mass)
summ_13 = calculate_sum(double_sum_M1x_E_mass)

value_13_15 =  calculate_multi(double_sum_M1x_E_mass, N_Nm)
sum_13_15 = calculate_sum(value_13_15)

D1 = - sum_13_15[-1]/In[-1]
D2 = - summ_13[-1]/sum_m[-1]

D1_15 = [x*D1 for x in N_Nm]

m_f1_f20 = calculate_multi(f_zero[1], f_stiffness[0])
m_f1_f20_mass = calculate_multi(m_f1_f20, mass)
Value_33 = calculate_multi(m_f1_f20_mass, N_Nm)
sum_Value_33 = calculate_sum(Value_33)

f1_2 = [x**2 for x in f_stiffness[0]]
m_f1_2 = calculate_multi(f1_2,mass)
value_temp = calculate_multi(m_f1_2, N_Nm)
sum_value_temp = calculate_sum(value_temp)

delta = [- a/b if b != 0 else 0 for a, b in zip(sum_Value_33, sum_value_temp)]
deltaf1 = calculate_multi(delta, f_stiffness[0])

D2_11 = [a + b + D2  for a, b in zip(double_sum_M1x_E, D1_15)]
newD2_11 = [a + b for a, b in zip(D2_11, deltaf1)]

f_stiffness[1] = [x/max(newD2_11) for x in newD2_11]


m_f1 = calculate_multi(mass, f_stiffness[1])
sum_m_f1 = calculate_sum(m_f1)
double_sum_m_f1 = calculate_sum(sum_m_f1)
dm1 = [-x*double_sum_m_f1[-1]/numeric[-1] for x in numeric]
M1x = [a + b for a, b in zip(dm1, double_sum_m_f1)]
M1x2 = [x ** 2 for x in M1x]
M1x2_E = [a/b if b != 0 else 0 for a, b in zip(M1x2, stiffness)]
sum_M1x2_E = calculate_sum(M1x2_E)
f_12 = [x ** 2 for x in f_stiffness[1]]
mf_12 = calculate_multi(f_12, mass)
sum_mf_12 = calculate_sum(mf_12)
w_calc[1] = m.sqrt(sum_mf_12[-1]/(sum_M1x2_E[-1]*1000.0*pow(length[-1]/2,4)))/(2*m.pi)
#################################################################################

print(w_zero[1])
print(w_calc[1])
plt.plot(numeric, f_zero[1], 'b')
plt.plot(numeric, f_stiffness[1], 'g')
plt.show()