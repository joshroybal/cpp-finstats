# cpp-finstats
C++ securities statistical summary generator
This program will generate a statistical summary comparing price movements of two securities or indices.
It will sample and compare only dates both securities traded.
Source files can be downloaded from yahoo finance.
See example run of program below for S&P 500 index and 10 year U.S. Treasury note yields.

Linux format source files and GNU Makefile are in folder Linux.
Windows format source files and nmake makefile are in folder Windows.

D:\programming\C++\secstats\bin>secstats "^GSPC.csv" "^TNX.csv"
n = 14367
cov(X,Y) = -1368.75
corr(X,Y) = -0.654675

STAT                           X           Y
minimum                   52.320       1.366
maximum                 3014.300      15.840
median                   356.940       5.894
mean                     703.775       6.142
popvar                523077.450       8.355
popstd                   723.241       2.891
samvar                523113.861       8.356
samstd                   723.266       2.891
mean deviation           614.040       2.293
median deviation         271.250       1.864
skewness                   1.439       0.257
