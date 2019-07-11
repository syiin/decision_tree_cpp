#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <array>

enum terrain { HILLY, FLAT };
typedef std::array <float, 9> datarow;
typedef std::vector <datarow> datavec;

int calcEntropy(std::map <terrain, int> classCounts, int totalCount){
  int idxScore = 0;
  for (auto const& numOfClass: classCounts){
    int p = (numOfClass.second / totalCount);
    idxScore += log2(p) * -(p);
  }
  return idxScore;
} 

int calcGini(std::map<terrain, int> classCounts, int totalCount){
  int idxScore = 0;
  for (auto const& numOfClass: classCounts){
    idxScore += (numOfClass.second / totalCount);
  }
  return idxScore;
}

datavec splitVec(datavec dataVector, unsigned int paramIdx, 
  bool (*testFunc)(float paramVal)){
  datavec outputVec;
  for (auto const& dataRow: dataVector){
    if (testFunc(dataRow[paramIdx])){
      outputVec.push_back(dataRow);
    }
  }
  return outputVec;
}

bool gt3(float x){
  return x > 0;
}

int main(){
  datavec testVec;
  datarow testRow1 = {1,1,1,1,1,1,1,1,9};
  datarow testRow2 = {-1,1,1,1,1,1,1,1,8};
  datarow testRow3 = {1,1,1,1,1,1,1,1,8};

  testVec.push_back(testRow1);
  testVec.push_back(testRow2);
  testVec.push_back(testRow3);
  
  datavec testoVec;
  testoVec = splitVec(testVec, 0, gt3);
//  splitVec(testVec, 0, [](float x)->bool{ return x > 3 });
}






