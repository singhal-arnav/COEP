#Q1
x = c(1, 2, 3, 4, 5)
f = c(7, 11, 9, 8, 3)
d = rep(x, f)
#a) 
mean(d) #Mean = 2.710526
#b) 
median(d) #Median = 3
#c) 
t = table(d)
m = names(t)[which(t > 1 & t == max(t))]
m #Mode = 2
#d) 
quantile(d, 0.7) #Seventh decile = 3
#e)
quantile(d, 0.29) #29th percentile = 2 

#Q2
price = c(10, 15, 30, 42, 50, 60)
qty = c(4, 20, 15, 10, 16, 8)
df = data.frame(price, qty)
df #Required dataframe
value = price * qty
df = cbind(df, value)
df #df with vector value = price*qty added

#Q3
age = c(22, 27, 31, 41, 30, 25, 19, 20, 23, 35)
#a)
age[c(-5, -7)] #Ages of persons except 5th and 7th
#b)
age30 = age[age > 30]
age30 #Vector containing ages of persons greater than 30
#c)
age[4:6] #Ages of 4th, 5th and 6th persons
#d)
age2 = age[age >= 20 & age <= 25]
age2 #Vector containing ages of persons between 20 and 25
#e)
age[8 : 10] #Ages of last 3 persons

#Q4
data(iris)
d = iris[-5]
heatmap(as.matrix(d), main = "Heatmap", scale = "column")
heatmap(as.matrix(d), main = "Heatmap", scale = "column", Rowv = NA) #a) without row dendrogram
heatmap(as.matrix(d), main = "Heatmap", scale = "column", Colv = NA) #b) without column dendrogram

#Q5
years = c(1965, 1975, 1985)
depts = c("Arts", "Science", "Commerce","Law")
arts = c(300, 400, 500)
sci = c(180, 300, 380)
com = c(300, 500, 600)
law = c(200, 250, 300)
df = data.frame(arts, sci, com, law)
#Subdivided bar diagram
barplot(t(df), beside = F , names.arg = years, col = 1:4, xlab = "Year", ylab = "Number of students", main = "Student population in various depts in 3 years")
legend("topright" , fill = 1 : 4, legend = depts)
#Multiple bar diagram
barplot(as.matrix(df), beside = T, names.arg = depts, col = 1:3, xlab = "Department", ylab = "Number of students", main = "Student population in 3 years in various depts")
legend("topright" , fill = 1 : 3, legend = years)

#Q6
#a)
name = c("Bhargav Singh", "Sayali Shah", "John Pinto", "Anaya Joshi", "Arnav Singhal")
position = c("Head", "Head", "Manager", "Network architect", "Senior Software Developer")
dept = c("Finance", "Human Resources", "Marketing", "IT", "R&D")
salary = c(2000000, 2200000, 1900000, 1650000, 1850000)
df = data.frame(name, position, dept, salary)
df
summary(df)
#b)
a = array(seq(52, 80, 2), dim = c(5, 3))
a
#c)
v = c(1, 2, 3, 3, 4, NA, 3, 2, 4, 5, NA, 5)
levels(factor(v))
#d)
l = list("Probability", 3.25, 9L, "STATISTICS", c(1, 2, "PS"), 1:3, T, F)
l
#e)
s = sample(-50:50, 10)
s

#Q7
moviesData = read.csv(file = "C:/Users/singh/Documents/moviesData.csv", header = TRUE, stringsAsFactors = FALSE, na.strings = "NA")
#a)
hist(moviesData$imdb_num_votes, xlab = "Number of votes", ylab = "Number of movies", main = "Number of movies by number of votes on IMDB", col = "lightblue", breaks = 5)
#b)
pie(table(moviesData$mpaa_rating), col = 4:9, main = "MPAA Rating Pie Chart")
#c)
m = matrix(moviesData$critics_score[1:10])
barplot(t(m), xlab = "Movie", ylab = "Critics Score", main = "Critics Score Comparison", col = 5, names.arg = moviesData$title[1:10])
#d)
plot(moviesData$imdb_rating, moviesData$imdb_num_votes, main = "Number of votes v/s rating", xlab = "IMDB rating", ylab = "Number of votes")
#e)
x = moviesData$dvd_rel_day
f = fivenum(x)
boxplot(x, main = "Boxplot")
text(rep(1.3, 5), f, labels = c("Minimum", "Lower quartile", "Median", "Upper quartile", "Maximum"))

#Q8
data(CO2)
up = CO2$uptake
#a)
sqrt(var(up)) #Standard deviation = 10.81441
#b)
qd = as.numeric(quantile(up, 0.75) - quantile(up, 0.25))
qd #Quartile deviation = 19.225
#c)
r = max(up) - min(up)
r #Range = 37.8
#d)
t = table(up)
m = names(t)[which(t > 1 & t == max(t))]
m #Mode = [1] "17.9" "32.4"
#e)
coeff = r / (max(up) + min(up))
coeff #Coefficient of range = 0.7105263

