#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include "stats.hpp"

// Stats class constructor
Stats::Stats(const std::vector<double>& x)
{
   n = x.size();
   double sum = 0.;
   for (int i = 0; i < n; i++) sum += x[i];
   mean = sum / n;
   sum = 0.;
   for (int i = 0; i < n; i++) sum += (x[i] - mean) * (x[i] - mean);
   popvar = sum / n;
   popstd = sqrt(popvar);
   samvar = sum / (n - 1);
   samstd = sqrt(samvar);
   min = quick_select(x, 0);
   max = quick_select(x, n - 1);
   mdn = median(x);
   sum = 0.;
   for (int i = 0; i < n; i++) sum += fabs(x[i] - mean);
   mean_dev = sum / n;
   std::vector<double> dev;
   for (int i = 0; i < n; i++) dev.push_back( fabs(x[i] - mdn ) );
   mdn_dev = median(dev);
   skw = (3 * (mean - mdn)) / samstd;
}

// Stats class methods
// public methods
void Stats::displayReport(const std::string& label) const
{
   const int w = 12;
   const int lw = 20;

   std::cout << ' ' << label << std::endl;
   std::cout << " population size = " << n << std::endl;

   std::cout << std::fixed << std::setprecision(3);

   std::cout << std::left;
   std::cout << std::setw(lw) << " minimum";
   std::cout << std::right;
   std::cout << std::setw(w) << min << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " maximum";
   std::cout << std::right;
   std::cout << std::setw(w) << max << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " median";
   std::cout << std::right;
   std::cout << std::setw(w) << mdn << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " mean";
   std::cout << std::right;
   std::cout << std::setw(w) << mean << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " variance";
   std::cout << std::right;
   std::cout << std::setw(w) << popvar << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " standard deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << popstd << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " mean deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << mean_dev << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " median deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << mdn_dev << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " skewness";
   std::cout << std::right;
   std::cout << std::setw(w) << skw << std::endl << std::endl;
}

// private methods
// C. A. R. (Tony) Hoare's quick selection algorithm. C. E. 1961
double Stats::quick_select(const std::vector<double>& x, int k)
{
    int i, j, left = 0, right = n - 1;
    double pivot;
    // initialize index vector to natural order (zero indexed)
    std::vector<int> idx;
    for (i = 0; i < n; i++) idx.push_back(i);
    while (left < right) {
        pivot = x[idx[k]];
        i = left;
        j = right;
        do {
            while (x[idx[i]] < pivot) i++;
            while (pivot < x[idx[j]]) j--;
            if (i <= j) {
                unsigned idxtmp = idx[i];
                idx[i] = idx[j];
                idx[j] = idxtmp;
                i++;
                j--;
            }
        } while (i <= j);
        if (j < k) left = i;
        if (k < i) right = j;
    }
    return x[idx[k]];
}

double Stats::median(const std::vector<double>& x)
{
    int k = n / 2;
    if (k % n == 0) {
        double p = quick_select(x, n / 2 - 1);
        double q = quick_select(x, n / 2);
        return (p + q) / 2.0;
    }
    else
        return quick_select(x, n/2);
}

// coStats class constructor
coStats::coStats(const std::vector<double>& x, const std::vector<double>& y) :
  xStats(x), yStats(y)
{
   n = std::min(xStats.Size(), yStats.Size());
   double sum = 0.;
   for (int i = 0; i < n; i++)
      sum += (x[i] - xStats.Mean()) * (y[i] - yStats.Mean());
   cov = sum / (n - 1);
   corr = cov / (xStats.SamStd() * yStats.SamStd());
}

// coStats class methods
// public method
void coStats::displayReport() const
{
   const int w = 12;
   const int lw = 20;

   std::cout << " sample size = " << n << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " covariance(X,Y)";
   std::cout << std::right;
   std::cout << std::setw(w) << cov << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " correlation(X,Y)";
   std::cout << std::right;
   std::cout << std::setw(w) << corr << std::endl;

   std::cout << std::right;
   std::cout << std::setw(lw + w) << "X" << std::setw(w) << "Y" << std::endl;

   std::cout << std::fixed << std::setprecision(3);

   std::cout << std::left;
   std::cout << std::setw(lw) << " minimum";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.Minimum();
   std::cout << std::setw(w) << yStats.Minimum() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " maximum";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.Maximum();
   std::cout << std::setw(w) << yStats.Maximum() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " median";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.Median();
   std::cout << std::setw(w) << yStats.Median() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " mean";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.Mean();
   std::cout << std::setw(w) << yStats.Mean() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " variance";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.SamVar();
   std::cout << std::setw(w) << yStats.SamVar() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " standard deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.SamStd();
   std::cout << std::setw(w) << yStats.SamStd() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " mean deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.MeanDeviation();
   std::cout << std::setw(w) << yStats.MeanDeviation() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " median deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.MedianDeviation();
   std::cout << std::setw(w) << yStats.MedianDeviation() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(lw) << " skewness";
   std::cout << std::right;
   std::cout << std::setw(w) << xStats.Skewness();
   std::cout << std::setw(w) << yStats.Skewness() << std::endl;
}
