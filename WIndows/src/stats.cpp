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

// class methods
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
   int n = std::min(x.size(), y.size());

   double sum = 0.;
   for (int i = 0; i < n; i++)
      sum += (x[i] - xStats.Mean()) * (y[i] - yStats.Mean());
   cov = sum / (n - 1);
   corr = cov / (xStats.SamStd() * yStats.SamStd());
}
