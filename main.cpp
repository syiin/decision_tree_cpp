#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <array>
#include <functional>

enum terrain { HILLY, FLAT };
typedef std::array <float, 9> datarow;
typedef std::vector <datarow> datavec;

float 
calcSingleEntropy(datavec dataVec,
    float klassIdx,
    float klass)
{
  int n = 0;
  for (auto const& dataRow: dataVec){
    if (dataRow[klassIdx] == klass){
      n++;
    }
  }
  float p = (float) n / (float) dataVec.size();
  return -(p) * log2(p); 
}

datavec
splitVec(datavec dataVector, 
    unsigned int paramIdx,
    std::function<bool (float)> testFunc)
{  
  datavec outputVec;
  for (auto const& dataRow: dataVector){
    if (testFunc(dataRow[paramIdx])){
      outputVec.push_back(dataRow);
    }
  }
  return outputVec;
}


std::function<bool (float)>
eqtY(float y)
{
 return [y](float x){ return x == y; };
}

std::function<bool (float)>
gtY(float y)
{
 return [y](float x){ return x > y; };
}

int
main()
{
  datavec testVec;
  datarow testRow1 = {1,1,1,1,1,1,1,1,9};
  datarow testRow2 = {-1,1,1,1,1,1,1,1,8};
  datarow testRow3 = {1,1,1,1,1,1,1,1,8};

  testVec.push_back(testRow1);
  testVec.push_back(testRow2);
  testVec.push_back(testRow3);
  
  datavec testoVec;
  testoVec = splitVec(testVec, 0, gtY(0));
  float S = calcSingleEntropy(testVec, 1, 1);
  S = calcSingleEntropy(testVec, 0, 1);
}
