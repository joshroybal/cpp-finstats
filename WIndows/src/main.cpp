#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "csv.hpp"
#include "stats.hpp"

int main(int argc, char *argv[])
{
   if (argc < 3) {
      std::cerr << "Usage: " << argv[0] << "file1 file2\n";
      return 1;
   }
   
   std::string infile1(argv[1]);
   std::string infile2(argv[2]);

   std::map<std::string, double> xmap;
   std::map<std::string, double> ymap;
   std::string line;
   std::ifstream ifstr;

   ifstr.open(infile1.c_str(), std::ifstream::in);
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

   ifstr.open(infile2.c_str(), std::ifstream::in);
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

   std::vector<double> x;
   std::vector<double> y;

   std::map<std::string, double>::iterator xmit;
   std::map<std::string, double>::iterator ymit;
   
   // first process each data set individually
   for (xmit = xmap.begin(); xmit != xmap.end(); xmit++) 
      x.push_back(xmit->second);

   for (ymit = ymap.begin(); ymit != ymap.end(); ymit++)
      y.push_back(ymit->second);
   
   Stats xStats(x);
   Stats yStats(y);  
   
   x.clear();
   y.clear();

   for (xmit = xmap.begin(); xmit != xmap.end(); xmit++) {
      ymit = ymap.find(xmit->first);
      if ( ymit != ymap.end() ) {
         x.push_back(xmit->second);
         y.push_back(ymit->second);
      }
   }

   coStats xyStats(x, y);

   const std::string label1("X = " + infile1.substr(0, infile1.length()-4));
   const std::string label2("Y = " + infile2.substr(0, infile2.length()-4));

   // display x data summary
   xStats.displayReport(label1);
   // display y data summary
   yStats.displayReport(label2);
   // display merged data summary
   xyStats.displayReport();

   return 0;
}
