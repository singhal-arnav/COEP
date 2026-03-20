#Q1
#Here we want to test Ho: median = 20 vs H1: median > 20
x = c(17, 15, 20, 20, 32, 28, 12, 26, 25, 25, 35, 24)
wilcox.test(x, alternative = "greater", mu = 20)
#Conclusion: Here we observe that the given level of significance 5% is less than p-value = 0.06906, so we accept Ho. Hence we conclude that median waiting time is 20 minutes.

#Q2
#Here we want to test Ho: median = 625 vs H1: median > 625
library(BSDA)
x = c(612,619,631,628,643,640,655,649,670,663)
SIGN.test(x, alternative = "greater", mu = 625)
#Conclusion: Here we observe that the given level of significance 5% is greater than p-value = 0.0009766, so we reject Ho. Hence we conclude that the population median fatigue life is greater than 625.

#Q3
#Here we want to test Ho: median = 1.8 vs H1: median is not equal to 1.8
x = c(1.5, 2.2, 0.9, 1.3, 2.0, 1.6, 1.8, 1.5, 2.0, 1.2, 1.7)
wilcox.test(x, alternative = "two.sided", mu = 1.8)
#Conclusion: Here we observe that the given level of significance 5% is less than p-value = 0.1522, so we accept Ho. Hence we conclude that the median number of hours for which the trimmer operates before requiring a recharge is not 1.8.

#Q4
#Here we want to test Ho: median = 41 vs H1: median is not equal to 41
x = c(25, 19, 38, 52, 57, 39, 46, 46, 30, 49, 27, 39, 44, 63, 31, 67, 42)
SIGN.test(x, mu = 41)
#Conclusion: Here we observe that the given level of significance 5% is greater than p-value = 1.526e-05, so we reject Ho. Hence we conclude that the median age of tourists is not 41 years.

#Q5
#Here we want to test Ho: median = 700 vs H1: median is not equal to 700
x = c(700, 650, 800, 975, 855, 785, 759, 640, 950, 715, 825, 980, 895, 1025, 850, 915, 740, 985, 770, 785, 700, 925)
SIGN.test(x, mu = 700, conf.level = 0.9)
#Conclusion: Here we observe that the given level of significance 10% is greater than p-value = 4.768e-07, so we reject Ho. Hence we conclude that the median rental rate is not $700.