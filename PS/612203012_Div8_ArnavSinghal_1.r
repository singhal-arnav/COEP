#Q1
install.packages(c('plyr', 'MASS', 'ggplot2', 'dplyr')) # Successfully installed

#Q2
log2(2^5) # Output: [1] 5
log(exp(1)*exp(1)) # Output: [1] 2

#Q3

data(iris) #loading the dataset
iris
# Sepal.Length Sepal.Width Petal.Length Petal.Width    Species
# 1            5.1         3.5          1.4         0.2     setosa
# 2            4.9         3.0          1.4         0.2     setosa
# 3            4.7         3.2          1.3         0.2     setosa
# 4            4.6         3.1          1.5         0.2     setosa
# 5            5.0         3.6          1.4         0.2     setosa
# 6            5.4         3.9          1.7         0.4     setosa
# 7            4.6         3.4          1.4         0.3     setosa
# 8            5.0         3.4          1.5         0.2     setosa
# 9            4.4         2.9          1.4         0.2     setosa
# 10           4.9         3.1          1.5         0.1     setosa
# 11           5.4         3.7          1.5         0.2     setosa
# 12           4.8         3.4          1.6         0.2     setosa
# 13           4.8         3.0          1.4         0.1     setosa
# 14           4.3         3.0          1.1         0.1     setosa
# 15           5.8         4.0          1.2         0.2     setosa
# 16           5.7         4.4          1.5         0.4     setosa
# 17           5.4         3.9          1.3         0.4     setosa
# 18           5.1         3.5          1.4         0.3     setosa
# 19           5.7         3.8          1.7         0.3     setosa
# 20           5.1         3.8          1.5         0.3     setosa
# 21           5.4         3.4          1.7         0.2     setosa
# 22           5.1         3.7          1.5         0.4     setosa
# 23           4.6         3.6          1.0         0.2     setosa
# 24           5.1         3.3          1.7         0.5     setosa
# 25           4.8         3.4          1.9         0.2     setosa
# 26           5.0         3.0          1.6         0.2     setosa
# 27           5.0         3.4          1.6         0.4     setosa
# 28           5.2         3.5          1.5         0.2     setosa
# 29           5.2         3.4          1.4         0.2     setosa
# 30           4.7         3.2          1.6         0.2     setosa
# 31           4.8         3.1          1.6         0.2     setosa
# 32           5.4         3.4          1.5         0.4     setosa
# 33           5.2         4.1          1.5         0.1     setosa
# 34           5.5         4.2          1.4         0.2     setosa
# 35           4.9         3.1          1.5         0.2     setosa
# 36           5.0         3.2          1.2         0.2     setosa
# 37           5.5         3.5          1.3         0.2     setosa
# 38           4.9         3.6          1.4         0.1     setosa
# 39           4.4         3.0          1.3         0.2     setosa
# 40           5.1         3.4          1.5         0.2     setosa
# 41           5.0         3.5          1.3         0.3     setosa
# 42           4.5         2.3          1.3         0.3     setosa
# 43           4.4         3.2          1.3         0.2     setosa
# 44           5.0         3.5          1.6         0.6     setosa
# 45           5.1         3.8          1.9         0.4     setosa
# 46           4.8         3.0          1.4         0.3     setosa
# 47           5.1         3.8          1.6         0.2     setosa
# 48           4.6         3.2          1.4         0.2     setosa
# 49           5.3         3.7          1.5         0.2     setosa
# 50           5.0         3.3          1.4         0.2     setosa
# 51           7.0         3.2          4.7         1.4 versicolor
# 52           6.4         3.2          4.5         1.5 versicolor
# 53           6.9         3.1          4.9         1.5 versicolor
# 54           5.5         2.3          4.0         1.3 versicolor
# 55           6.5         2.8          4.6         1.5 versicolor
# 56           5.7         2.8          4.5         1.3 versicolor
# 57           6.3         3.3          4.7         1.6 versicolor
# 58           4.9         2.4          3.3         1.0 versicolor
# 59           6.6         2.9          4.6         1.3 versicolor
# 60           5.2         2.7          3.9         1.4 versicolor
# 61           5.0         2.0          3.5         1.0 versicolor
# 62           5.9         3.0          4.2         1.5 versicolor
# 63           6.0         2.2          4.0         1.0 versicolor
# 64           6.1         2.9          4.7         1.4 versicolor
# 65           5.6         2.9          3.6         1.3 versicolor
# 66           6.7         3.1          4.4         1.4 versicolor
# 67           5.6         3.0          4.5         1.5 versicolor
# 68           5.8         2.7          4.1         1.0 versicolor
# 69           6.2         2.2          4.5         1.5 versicolor
# 70           5.6         2.5          3.9         1.1 versicolor
# 71           5.9         3.2          4.8         1.8 versicolor
# 72           6.1         2.8          4.0         1.3 versicolor
# 73           6.3         2.5          4.9         1.5 versicolor
# 74           6.1         2.8          4.7         1.2 versicolor
# 75           6.4         2.9          4.3         1.3 versicolor
# 76           6.6         3.0          4.4         1.4 versicolor
# 77           6.8         2.8          4.8         1.4 versicolor
# 78           6.7         3.0          5.0         1.7 versicolor
# 79           6.0         2.9          4.5         1.5 versicolor
# 80           5.7         2.6          3.5         1.0 versicolor
# 81           5.5         2.4          3.8         1.1 versicolor
# 82           5.5         2.4          3.7         1.0 versicolor
# 83           5.8         2.7          3.9         1.2 versicolor
# 84           6.0         2.7          5.1         1.6 versicolor
# 85           5.4         3.0          4.5         1.5 versicolor
# 86           6.0         3.4          4.5         1.6 versicolor
# 87           6.7         3.1          4.7         1.5 versicolor
# 88           6.3         2.3          4.4         1.3 versicolor
# 89           5.6         3.0          4.1         1.3 versicolor
# 90           5.5         2.5          4.0         1.3 versicolor
# 91           5.5         2.6          4.4         1.2 versicolor
# 92           6.1         3.0          4.6         1.4 versicolor
# 93           5.8         2.6          4.0         1.2 versicolor
# 94           5.0         2.3          3.3         1.0 versicolor
# 95           5.6         2.7          4.2         1.3 versicolor
# 96           5.7         3.0          4.2         1.2 versicolor
# 97           5.7         2.9          4.2         1.3 versicolor
# 98           6.2         2.9          4.3         1.3 versicolor
# 99           5.1         2.5          3.0         1.1 versicolor
# 100          5.7         2.8          4.1         1.3 versicolor
# 101          6.3         3.3          6.0         2.5  virginica
# 102          5.8         2.7          5.1         1.9  virginica
# 103          7.1         3.0          5.9         2.1  virginica
# 104          6.3         2.9          5.6         1.8  virginica
# 105          6.5         3.0          5.8         2.2  virginica
# 106          7.6         3.0          6.6         2.1  virginica
# 107          4.9         2.5          4.5         1.7  virginica
# 108          7.3         2.9          6.3         1.8  virginica
# 109          6.7         2.5          5.8         1.8  virginica
# 110          7.2         3.6          6.1         2.5  virginica
# 111          6.5         3.2          5.1         2.0  virginica
# 112          6.4         2.7          5.3         1.9  virginica
# 113          6.8         3.0          5.5         2.1  virginica
# 114          5.7         2.5          5.0         2.0  virginica
# 115          5.8         2.8          5.1         2.4  virginica
# 116          6.4         3.2          5.3         2.3  virginica
# 117          6.5         3.0          5.5         1.8  virginica
# 118          7.7         3.8          6.7         2.2  virginica
# 119          7.7         2.6          6.9         2.3  virginica
# 120          6.0         2.2          5.0         1.5  virginica
# 121          6.9         3.2          5.7         2.3  virginica
# 122          5.6         2.8          4.9         2.0  virginica
# 123          7.7         2.8          6.7         2.0  virginica
# 124          6.3         2.7          4.9         1.8  virginica
# 125          6.7         3.3          5.7         2.1  virginica
# 126          7.2         3.2          6.0         1.8  virginica
# 127          6.2         2.8          4.8         1.8  virginica
# 128          6.1         3.0          4.9         1.8  virginica
# 129          6.4         2.8          5.6         2.1  virginica
# 130          7.2         3.0          5.8         1.6  virginica
# 131          7.4         2.8          6.1         1.9  virginica
# 132          7.9         3.8          6.4         2.0  virginica
# 133          6.4         2.8          5.6         2.2  virginica
# 134          6.3         2.8          5.1         1.5  virginica
# 135          6.1         2.6          5.6         1.4  virginica
# 136          7.7         3.0          6.1         2.3  virginica
# 137          6.3         3.4          5.6         2.4  virginica
# 138          6.4         3.1          5.5         1.8  virginica
# 139          6.0         3.0          4.8         1.8  virginica
# 140          6.9         3.1          5.4         2.1  virginica
# 141          6.7         3.1          5.6         2.4  virginica
# 142          6.9         3.1          5.1         2.3  virginica
# 143          5.8         2.7          5.1         1.9  virginica
# 144          6.8         3.2          5.9         2.3  virginica
# 145          6.7         3.3          5.7         2.5  virginica
# 146          6.7         3.0          5.2         2.3  virginica
# 147          6.3         2.5          5.0         1.9  virginica
# 148          6.5         3.0          5.2         2.0  virginica
# 149          6.2         3.4          5.4         2.3  virginica
# 150          5.9         3.0          5.1         1.8  virginica

#Implementing functions

summary(iris)
# Sepal.Length    Sepal.Width     Petal.Length    Petal.Width          Species  
# Min.   :4.300   Min.   :2.000   Min.   :1.000   Min.   :0.100   setosa    :50  
# 1st Qu.:5.100   1st Qu.:2.800   1st Qu.:1.600   1st Qu.:0.300   versicolor:50  
# Median :5.800   Median :3.000   Median :4.350   Median :1.300   virginica :50  
# Mean   :5.843   Mean   :3.057   Mean   :3.758   Mean   :1.199                  
# 3rd Qu.:6.400   3rd Qu.:3.300   3rd Qu.:5.100   3rd Qu.:1.800                  
# Max.   :7.900   Max.   :4.400   Max.   :6.900   Max.   :2.500 

class(iris)
# [1] "data.frame"

typeof(iris)
# [1] "list"

head(iris)
# Sepal.Length Sepal.Width Petal.Length Petal.Width Species
# 1          5.1         3.5          1.4         0.2  setosa
# 2          4.9         3.0          1.4         0.2  setosa
# 3          4.7         3.2          1.3         0.2  setosa
# 4          4.6         3.1          1.5         0.2  setosa
# 5          5.0         3.6          1.4         0.2  setosa
# 6          5.4         3.9          1.7         0.4  setosa

tail(iris)
# Sepal.Length Sepal.Width Petal.Length Petal.Width   Species
# 145          6.7         3.3          5.7         2.5 virginica
# 146          6.7         3.0          5.2         2.3 virginica
# 147          6.3         2.5          5.0         1.9 virginica
# 148          6.5         3.0          5.2         2.0 virginica
# 149          6.2         3.4          5.4         2.3 virginica
# 150          5.9         3.0          5.1         1.8 virginica

str(iris)
# 'data.frame':	150 obs. of  5 variables:
# $ Sepal.Length: num  5.1 4.9 4.7 4.6 5 5.4 4.6 5 4.4 4.9 ...
# $ Sepal.Width : num  3.5 3 3.2 3.1 3.6 3.9 3.4 3.4 2.9 3.1 ...
# $ Petal.Length: num  1.4 1.4 1.3 1.5 1.4 1.7 1.4 1.5 1.4 1.5 ...
# $ Petal.Width : num  0.2 0.2 0.2 0.2 0.2 0.4 0.3 0.2 0.2 0.1 ...
# $ Species     : Factor w/ 3 levels "setosa","versicolor",..: 1 1 1 1 1 1 1 1 1 1 ...

species_habitat = data.frame(Species = c("setosa", "versicolor", "virginica"), Habitat = c("Woodland", "Meadow", "Mountain"))
species_habitat
# Species  Habitat
# 1     setosa Woodland
# 2 versicolor   Meadow
# 3  virginica Mountain

merged_dataset = merge(iris, species_habitat, by = "Species")
merged_dataset
# Species Sepal.Length Sepal.Width Petal.Length Petal.Width  Habitat
# 1       setosa          5.1         3.5          1.4         0.2 Woodland
# 2       setosa          4.9         3.0          1.4         0.2 Woodland
# 3       setosa          4.7         3.2          1.3         0.2 Woodland
# 4       setosa          4.6         3.1          1.5         0.2 Woodland
# 5       setosa          5.0         3.6          1.4         0.2 Woodland
# 6       setosa          5.4         3.9          1.7         0.4 Woodland
# 7       setosa          4.6         3.4          1.4         0.3 Woodland
# 8       setosa          5.0         3.4          1.5         0.2 Woodland
# 9       setosa          4.4         2.9          1.4         0.2 Woodland
# 10      setosa          4.9         3.1          1.5         0.1 Woodland
# 11      setosa          5.4         3.7          1.5         0.2 Woodland
# 12      setosa          4.8         3.4          1.6         0.2 Woodland
# 13      setosa          4.8         3.0          1.4         0.1 Woodland
# 14      setosa          4.3         3.0          1.1         0.1 Woodland
# 15      setosa          5.8         4.0          1.2         0.2 Woodland
# 16      setosa          5.7         4.4          1.5         0.4 Woodland
# 17      setosa          5.4         3.9          1.3         0.4 Woodland
# 18      setosa          5.1         3.5          1.4         0.3 Woodland
# 19      setosa          5.7         3.8          1.7         0.3 Woodland
# 20      setosa          5.1         3.8          1.5         0.3 Woodland
# 21      setosa          5.4         3.4          1.7         0.2 Woodland
# 22      setosa          5.1         3.7          1.5         0.4 Woodland
# 23      setosa          4.6         3.6          1.0         0.2 Woodland
# 24      setosa          5.1         3.3          1.7         0.5 Woodland
# 25      setosa          4.8         3.4          1.9         0.2 Woodland
# 26      setosa          5.0         3.0          1.6         0.2 Woodland
# 27      setosa          5.0         3.4          1.6         0.4 Woodland
# 28      setosa          5.2         3.5          1.5         0.2 Woodland
# 29      setosa          5.2         3.4          1.4         0.2 Woodland
# 30      setosa          4.7         3.2          1.6         0.2 Woodland
# 31      setosa          4.8         3.1          1.6         0.2 Woodland
# 32      setosa          5.4         3.4          1.5         0.4 Woodland
# 33      setosa          5.2         4.1          1.5         0.1 Woodland
# 34      setosa          5.5         4.2          1.4         0.2 Woodland
# 35      setosa          4.9         3.1          1.5         0.2 Woodland
# 36      setosa          5.0         3.2          1.2         0.2 Woodland
# 37      setosa          5.5         3.5          1.3         0.2 Woodland
# 38      setosa          4.9         3.6          1.4         0.1 Woodland
# 39      setosa          4.4         3.0          1.3         0.2 Woodland
# 40      setosa          5.1         3.4          1.5         0.2 Woodland
# 41      setosa          5.0         3.5          1.3         0.3 Woodland
# 42      setosa          4.5         2.3          1.3         0.3 Woodland
# 43      setosa          4.4         3.2          1.3         0.2 Woodland
# 44      setosa          5.0         3.5          1.6         0.6 Woodland
# 45      setosa          5.1         3.8          1.9         0.4 Woodland
# 46      setosa          4.8         3.0          1.4         0.3 Woodland
# 47      setosa          5.1         3.8          1.6         0.2 Woodland
# 48      setosa          4.6         3.2          1.4         0.2 Woodland
# 49      setosa          5.3         3.7          1.5         0.2 Woodland
# 50      setosa          5.0         3.3          1.4         0.2 Woodland
# 51  versicolor          7.0         3.2          4.7         1.4   Meadow
# 52  versicolor          6.4         3.2          4.5         1.5   Meadow
# 53  versicolor          6.9         3.1          4.9         1.5   Meadow
# 54  versicolor          5.5         2.3          4.0         1.3   Meadow
# 55  versicolor          6.5         2.8          4.6         1.5   Meadow
# 56  versicolor          5.7         2.8          4.5         1.3   Meadow
# 57  versicolor          6.3         3.3          4.7         1.6   Meadow
# 58  versicolor          4.9         2.4          3.3         1.0   Meadow
# 59  versicolor          6.6         2.9          4.6         1.3   Meadow
# 60  versicolor          5.2         2.7          3.9         1.4   Meadow
# 61  versicolor          5.0         2.0          3.5         1.0   Meadow
# 62  versicolor          5.9         3.0          4.2         1.5   Meadow
# 63  versicolor          6.0         2.2          4.0         1.0   Meadow
# 64  versicolor          6.1         2.9          4.7         1.4   Meadow
# 65  versicolor          5.6         2.9          3.6         1.3   Meadow
# 66  versicolor          6.7         3.1          4.4         1.4   Meadow
# 67  versicolor          5.6         3.0          4.5         1.5   Meadow
# 68  versicolor          5.8         2.7          4.1         1.0   Meadow
# 69  versicolor          6.2         2.2          4.5         1.5   Meadow
# 70  versicolor          5.6         2.5          3.9         1.1   Meadow
# 71  versicolor          5.9         3.2          4.8         1.8   Meadow
# 72  versicolor          6.1         2.8          4.0         1.3   Meadow
# 73  versicolor          6.3         2.5          4.9         1.5   Meadow
# 74  versicolor          6.1         2.8          4.7         1.2   Meadow
# 75  versicolor          6.4         2.9          4.3         1.3   Meadow
# 76  versicolor          6.6         3.0          4.4         1.4   Meadow
# 77  versicolor          6.8         2.8          4.8         1.4   Meadow
# 78  versicolor          6.7         3.0          5.0         1.7   Meadow
# 79  versicolor          6.0         2.9          4.5         1.5   Meadow
# 80  versicolor          5.7         2.6          3.5         1.0   Meadow
# 81  versicolor          5.5         2.4          3.8         1.1   Meadow
# 82  versicolor          5.5         2.4          3.7         1.0   Meadow
# 83  versicolor          5.8         2.7          3.9         1.2   Meadow
# 84  versicolor          6.0         2.7          5.1         1.6   Meadow
# 85  versicolor          5.4         3.0          4.5         1.5   Meadow
# 86  versicolor          6.0         3.4          4.5         1.6   Meadow
# 87  versicolor          6.7         3.1          4.7         1.5   Meadow
# 88  versicolor          6.3         2.3          4.4         1.3   Meadow
# 89  versicolor          5.6         3.0          4.1         1.3   Meadow
# 90  versicolor          5.5         2.5          4.0         1.3   Meadow
# 91  versicolor          5.5         2.6          4.4         1.2   Meadow
# 92  versicolor          6.1         3.0          4.6         1.4   Meadow
# 93  versicolor          5.8         2.6          4.0         1.2   Meadow
# 94  versicolor          5.0         2.3          3.3         1.0   Meadow
# 95  versicolor          5.6         2.7          4.2         1.3   Meadow
# 96  versicolor          5.7         3.0          4.2         1.2   Meadow
# 97  versicolor          5.7         2.9          4.2         1.3   Meadow
# 98  versicolor          6.2         2.9          4.3         1.3   Meadow
# 99  versicolor          5.1         2.5          3.0         1.1   Meadow
# 100 versicolor          5.7         2.8          4.1         1.3   Meadow
# 101  virginica          6.3         3.3          6.0         2.5 Mountain
# 102  virginica          5.8         2.7          5.1         1.9 Mountain
# 103  virginica          7.1         3.0          5.9         2.1 Mountain
# 104  virginica          6.3         2.9          5.6         1.8 Mountain
# 105  virginica          6.5         3.0          5.8         2.2 Mountain
# 106  virginica          7.6         3.0          6.6         2.1 Mountain
# 107  virginica          4.9         2.5          4.5         1.7 Mountain
# 108  virginica          7.3         2.9          6.3         1.8 Mountain
# 109  virginica          6.7         2.5          5.8         1.8 Mountain
# 110  virginica          7.2         3.6          6.1         2.5 Mountain
# 111  virginica          6.5         3.2          5.1         2.0 Mountain
# 112  virginica          6.4         2.7          5.3         1.9 Mountain
# 113  virginica          6.8         3.0          5.5         2.1 Mountain
# 114  virginica          5.7         2.5          5.0         2.0 Mountain
# 115  virginica          5.8         2.8          5.1         2.4 Mountain
# 116  virginica          6.4         3.2          5.3         2.3 Mountain
# 117  virginica          6.5         3.0          5.5         1.8 Mountain
# 118  virginica          7.7         3.8          6.7         2.2 Mountain
# 119  virginica          7.7         2.6          6.9         2.3 Mountain
# 120  virginica          6.0         2.2          5.0         1.5 Mountain
# 121  virginica          6.9         3.2          5.7         2.3 Mountain
# 122  virginica          5.6         2.8          4.9         2.0 Mountain
# 123  virginica          7.7         2.8          6.7         2.0 Mountain
# 124  virginica          6.3         2.7          4.9         1.8 Mountain
# 125  virginica          6.7         3.3          5.7         2.1 Mountain
# 126  virginica          7.2         3.2          6.0         1.8 Mountain
# 127  virginica          6.2         2.8          4.8         1.8 Mountain
# 128  virginica          6.1         3.0          4.9         1.8 Mountain
# 129  virginica          6.4         2.8          5.6         2.1 Mountain
# 130  virginica          7.2         3.0          5.8         1.6 Mountain
# 131  virginica          7.4         2.8          6.1         1.9 Mountain
# 132  virginica          7.9         3.8          6.4         2.0 Mountain
# 133  virginica          6.4         2.8          5.6         2.2 Mountain
# 134  virginica          6.3         2.8          5.1         1.5 Mountain
# 135  virginica          6.1         2.6          5.6         1.4 Mountain
# 136  virginica          7.7         3.0          6.1         2.3 Mountain
# 137  virginica          6.3         3.4          5.6         2.4 Mountain
# 138  virginica          6.4         3.1          5.5         1.8 Mountain
# 139  virginica          6.0         3.0          4.8         1.8 Mountain
# 140  virginica          6.9         3.1          5.4         2.1 Mountain
# 141  virginica          6.7         3.1          5.6         2.4 Mountain
# 142  virginica          6.9         3.1          5.1         2.3 Mountain
# 143  virginica          5.8         2.7          5.1         1.9 Mountain
# 144  virginica          6.8         3.2          5.9         2.3 Mountain
# 145  virginica          6.7         3.3          5.7         2.5 Mountain
# 146  virginica          6.7         3.0          5.2         2.3 Mountain
# 147  virginica          6.3         2.5          5.0         1.9 Mountain
# 148  virginica          6.5         3.0          5.2         2.0 Mountain
# 149  virginica          6.2         3.4          5.4         2.3 Mountain
# 150  virginica          5.9         3.0          5.1         1.8 Mountain

#Q4
v = seq(52, 80, 2)
a = array(v, dim = c(5,3))
a
# Output:
# [,1] [,2] [,3]
# [1,]   52   62   72
# [2,]   54   64   74
# [3,]   56   66   76
# [4,]   58   68   78
# [5,]   60   70   80

#Q5
vec = seq(-45, 45, 10)
vec
# Output:
#  [1] -45 -35 -25 -15  -5   5  15  25  35  45

#Q6

age = c(22, 27, 31, 41, 30, 25, 19, 20, 23, 35)
age
# Output: [1] 22 27 31 41 30 25 19 20 23 35

age[4] #age of fourth person
# Output: [1] 41

age30 = age[age > 30] #vector with age>30
age30
# Output: [1] 31 41 35

age[8:10] #last 3 persons
# Output: [1] 20 23 35

length(age)
# Output: [1] 10

age[c(-5, -7)]
# Output: [1] 22 27 31 41 25 20 23 35

age2 = age[age > 20 & age < 25]
age2
# Output: [1] 22 23

#Q7

f = factor(c(1,2,3,2,3,1,4,2,3,NA,5,3,2))
f
# Output:
# [1] 1    2    3    2    3    1    4    2    3    <NA> 5    3    2   
# Levels: 1 2 3 4 5

levels(f)
# Output: [1] "1" "2" "3" "4" "5"

#Q8
l = list(15L, 2.5, 9.3, 10L, "probability", FALSE, "Statistics", c(1,2,3), seq(1, 10, 3), TRUE)
l
# Output: 
# [[1]]
# [1] 15
# 
# [[2]]
# [1] 2.5
# 
# [[3]]
# [1] 9.3
# 
# [[4]]
# [1] 10
# 
# [[5]]
# [1] "probability"
# 
# [[6]]
# [1] FALSE
# 
# [[7]]
# [1] "Statistics"
# 
# [[8]]
# [1] 1 2 3
# 
# [[9]]
# [1]  1  4  7 10
# 
# [[10]]
# [1] TRUE

#Q9
library(dplyr)
names(select_if(iris, is.factor))
# Output: [1] "Species"

#Q10

n = c(1:5)
n
# Output: [1] 1 2 3 4 5

m = matrix(seq(1,15), nrow = 5, ncol = 3)
m
# Output: 
# [,1] [,2] [,3]
# [1,]    1    6   11
# [2,]    2    7   12
# [3,]    3    8   13
# [4,]    4    9   14
# [5,]    5   10   15

#Q11

df = data.frame(height = c(140,137,150,147,139,140,150,132,138,140), weight = c(55,57,59,62,61,60,60,58,59,57))
df
# height weight
# 1     140     55
# 2     137     57
# 3     150     59
# 4     147     62
# 5     139     61
# 6     140     60
# 7     150     60
# 8     132     58
# 9     138     59
# 10    140     57

h1 = df$height[df$height>145]
h1
# [1] 150 147 150

h2 = df$height[df$weight>55]
h2
# [1] 137 150 147 139 140 150 132 138 140

h3 = df$height[df$height>140 & df$weight>60]
h3
# [1] 147
