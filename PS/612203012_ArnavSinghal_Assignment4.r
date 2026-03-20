#Q1
n = 12
p = 0.4
pbinom(3, n, p) #P(X<=3) = 0.2253373
1 - pbinom(7, n, p) #P(X>=8) = 0.05730992
pbinom(6, n, p) - pbinom(3, n, p) #P(4<=X<=6) = 0.6164504
dbinom(6, n, p) #P(X=6) = 0.1765791

#Q2
exp_val = 4
var = 8/3
p = 1 - var/exp_val
n = exp_val/p
pbinom(4, n, p) #P[X<=4] = 0.6315207
1 - pbinom(2, n, p) #P[X>=3] = 0.8188774
rbinom(5, as.integer(n), p) #Sample: [1] 6 1 3 4 3

#Q3
p = 0.01
n = 200
lambda = n * p
1 - ppois(1, lambda) #Probability that there are at least two defectives = 0.5939942

#Q4
n = 8
p = 0.3
k = 0:8
k[as.numeric(substring(as.character(pbinom(k, n, p)), 1, 6)) == 0.2552] #Required value of k = 1

#Q5
rpois(8, 2.5) #Sample = [1] 1 4 3 3 4 1 2 2

#Q6
p = 0.001
n = 2000
lambda = n * p
1 - ppois(1, lambda) #Required probability = 0.5939942

#Q7
p = 0.005
n = 400
lambda = n * p
dpois(1, lambda) #Prob that there will be an accident on one day = 0.2706706
ppois(3, lambda) #Prob that there are at most 3 days with accidents = 0.8571235

#Q8
n = 420
die1 = rep(1:6, each = 6)
die2 = rep(1:6, 6)
totals = die1 + die2
p = sum(totals == 8)/length(die1)
lambda = n * p
ppois(50, lambda) #Prob that total of 8 occurs at least 50 times = 1
ppois(70, lambda) - ppois(49, lambda) #Between 70 and 90 times inclusive = 5.695444e-14
dpois(100, lambda) #Exactly 100 times = 1.840259e-50

#Q9
p = 0.4
n = 100
pbinom(29, n, p) #Prob that fewer than 30 survive = 0.01477532

#Q10
mu = 20
sd = 2
pnorm(2, mu, sd) #P[X<=2] = 1.128588e-19
pnorm(4, mu, sd) #P[X<4] = 6.220961e-16
1 - pnorm(7, mu, sd) #P[X>7] = 1
pnorm(3, mu, sd) - pnorm(3, mu, sd) #P[X=3] = 0 (upper and lower limits of interval taken to be 3)

#Q11
pexp(1, 0.1) #P[X<=1] = 0.09516258
rexp(5, 0.1) #Sample: [1] 4.4891045 3.1272332 0.7349352 0.4252528 2.6702855
