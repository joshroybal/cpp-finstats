#ifndef STATS_H
#define STATS_H

#include <vector>
#include <cmath>

class Stats
{
   public:
      Stats(const std::vector<double>&);
      int Size() const { return n; }
      double Mean() const { return mean; }
      double PopVar() const { return popvar; }
      double PopStd() const { return popstd; }
      double SamVar() const { return samvar; }
      double SamStd() const { return samstd; }
      double Minimum() const { return min; }
      double Maximum() const { return max; }
      double Median() const { return mdn; }
      double MeanDeviation() const { return mean_dev; }
      double MedianDeviation() const { return mdn_dev; }
      double Skewness() const { return skw; }
   private:
      int n;
      double mean;
      double popvar;
      double popstd;
      double samvar;
      double samstd;
      double min;
      double max;
      double mdn;
      double mean_dev;
      double mdn_dev;
      double skw;
      double quick_select(const std::vector<double>&, int);
      double median(const std::vector<double>&);
};

class coStats
{
   public:
      coStats(const std::vector<double>&, const std::vector<double>&);
      Stats xStats;
      Stats yStats;
      double CoVariance() { return cov; }
      double Correlation() { return corr; }
   private:
      double cov;
      double corr;
};

#endif
