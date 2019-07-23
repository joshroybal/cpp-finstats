#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include "csv.hpp"
#include "stats.hpp"

void statReport(const Stats&, const Stats&);

int main(int argc, char *argv[])
{
   if (argc < 3) {
      std::cerr << "Usage: " << argv[0] << "file1 file2\n";
      return 1;
   }
   
   std::vector<double> x;
   std::vector<double> y;
   std::map<std::string, double> xmap;
   std::map<std::string, double> ymap;
   std::string line;   
   std::ifstream ifstr;
   
   ifstr.open(argv[1], std::ifstream::in);
   if (ifstr.fail()) {
      std::cerr << "failure opening file " << argv[1] << std::endl;
      return 1;
   }
   std::getline(ifstr, line); // eat header record
   while ( std::getline(ifstr, line) ) {
      csvRecord record(line);
      std::string date(record.getField(1));
      std::istringstream isstr(record.getField(6));
      double r;
      if ( isstr >> r ) {
         std::pair<std::string, double> item(date, r);
         xmap.insert(item);
      }
   }
   ifstr.close();

   ifstr.open(argv[2], std::ifstream::in);
   if (ifstr.fail()) {
      std::cerr << "failure opening file " << argv[2] << std::endl;
      return 1;
   }   
   std::getline(ifstr, line); // eat header record
   while ( std::getline(ifstr, line) ) {
      csvRecord record(line);
      std::string date(record.getField(1));
      std::istringstream isstr(record.getField(6));
      double r;
      if ( isstr >> r ) {
         std::pair<std::string, double> item(date, r);
         ymap.insert(item);
      }
   }
   ifstr.close();

   
   std::map<std::string, double>::iterator xmit;
   std::map<std::string, double>::iterator ymit;

   for (xmit = xmap.begin(); xmit != xmap.end(); xmit++) {
      ymit = ymap.find(xmit->first);
      if ( ymit != ymap.end() ) {
         x.push_back(xmit->second);
         y.push_back(ymit->second);
      }
   }

   coStats xyStats(x, y);
   std::cout << "n = " << x.size() << std::endl;
   std::cout << "cov(X,Y) = " << xyStats.CoVariance() << std::endl;
   std::cout << "corr(X,Y) = " << xyStats.Correlation() << std::endl;
   std::cout << std::endl;
   statReport(xyStats.xStats, xyStats.yStats);

   return 0;
}

void statReport(const Stats& x, const Stats& y)
{
   const int w = 12;

   std::cout << std::left;
   std::cout << std::setw(20) << "STAT";
   std::cout << std::right;
   std::cout << std::setw(w) << "X" << std::setw(w) << "Y" << std::endl;

   std::cout << std::fixed << std::setprecision(3);
   
   std::cout << std::left;
   std::cout << std::setw(20) << "minimum";
   std::cout << std::right;
   std::cout << std::setw(w) << x.Minimum();
   std::cout << std::setw(w) << y.Minimum() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "maximum";
   std::cout << std::right;
   std::cout << std::setw(w) << x.Maximum();
   std::cout << std::setw(w) << y.Maximum() << std::endl;   

   std::cout << std::left;
   std::cout << std::setw(20) << "median";
   std::cout << std::right;
   std::cout << std::setw(w) << x.Median();
   std::cout << std::setw(w) << y.Median() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "mean";
   std::cout << std::right;
   std::cout << std::setw(w) << x.Mean();
   std::cout << std::setw(w) << y.Mean() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "popvar";
   std::cout << std::right;
   std::cout << std::setw(w) << x.PopVar();
   std::cout << std::setw(w) << y.PopVar() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "popstd";
   std::cout << std::right;
   std::cout << std::setw(w) << x.PopStd();
   std::cout << std::setw(w) << y.PopStd() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "samvar";
   std::cout << std::right;
   std::cout << std::setw(w) << x.SamVar();
   std::cout << std::setw(w) << y.SamVar() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "samstd";
   std::cout << std::right;
   std::cout << std::setw(w) << x.SamStd();
   std::cout << std::setw(w) << y.SamStd() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "mean deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << x.MeanDeviation();
   std::cout << std::setw(w) << y.MeanDeviation() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "median deviation";
   std::cout << std::right;
   std::cout << std::setw(w) << x.MedianDeviation();
   std::cout << std::setw(w) << y.MedianDeviation() << std::endl;

   std::cout << std::left;
   std::cout << std::setw(20) << "skewness";
   std::cout << std::right;
   std::cout << std::setw(w) << x.Skewness();
   std::cout << std::setw(w) << y.Skewness() << std::endl;
}
