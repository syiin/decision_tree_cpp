#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <array>
#include <functional>
#include <tuple>
#include <string>

enum terrain { HILLY, FLAT };
typedef std::array <float, 9> datarow;
typedef std::vector <datarow> datavec;
typedef std::tuple<datavec, datavec> datavectup;

float 
calcClassEntropy(datavec dataVec,
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

float 
calcClassProp(datavec dataVec,
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
  return p; 
}

float calcGini(datavec dataVec,
    float klassIdx)
{
  float giniSum = 0;
  for (int i = 1; i < 10; i++){
    giniSum =  giniSum + pow(calcClassProp(dataVec, klassIdx, i), 2);
  }

  return 1 - giniSum;
}

std::tuple<datavec, datavec> 
splitVec(datavec dataVector, 
    unsigned int paramIdx,
    std::function<bool (float)> testFunc)
{  
  datavec outputVec1;
  datavec outputVec2;
  for (auto const& dataRow: dataVector){
    if (testFunc(dataRow[paramIdx])){
      outputVec1.push_back(dataRow);
    } else {
      outputVec2.push_back(dataRow);
    }
  }
  return std::make_tuple(outputVec1, outputVec2); 
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

std::vector<float>
getMidPoints(std::vector<float> inpVec)
{
  std::vector<float> outpVec;
  for (int i = 0; i < (inpVec.size()-1); i++){
    float midPoint = ((inpVec[i+1] - inpVec[i]) / 2) + inpVec[i];
    outpVec.push_back(midPoint);
  }
  return outpVec;
}

int
main()
{
  datavec testVec;
  datarow testRow1 = {1,1,1,1,1,1,1,1,1};
  datarow testRow2 = {-1,1,1,1,1,1,1,1,2};
  datarow testRow3 = {1,1,1,1,1,1,1,1,3};
  datarow testRow4 = {1,1,1,1,1,1,1,1,4};
  datarow testRow5 = {1,1,1,1,1,1,1,1,5};
  datarow testRow6 = {1,1,1,1,1,1,1,1,6};
  datarow testRow7 = {1,1,1,1,1,1,1,1,7};
  datarow testRow8 = {1,1,1,1,1,1,1,1,8};
  datarow testRow9 = {1,1,1,1,1,1,1,1,9};

  testVec.push_back(testRow1);
  testVec.push_back(testRow2);
  testVec.push_back(testRow3);
 
  //splitvec test 
  datavec testoVec1;
  datavec testoVec2;
  tie(testoVec1, testoVec2) = splitVec(testVec, 0, gtY(0));
  datavec corrSplitVec1 = {testRow1, testRow3};
  datavec corrSplitVec2 = {testRow2};
  if ((int) (testoVec1 == corrSplitVec1) && (int) (testoVec2 == corrSplitVec2)){
    std::cout << "splitVec(): PASS" << std::endl;
  }

  //calculate cross entropy test
  float S = calcClassEntropy(testVec, 1, 1);
  S = calcClassEntropy(testVec, 0, 1);
  if (std::to_string(S) == "0.389975"){
    std::cout << "calcClassEntropy(): PASS" << std::endl;
  } else {
    std::cout << "calcClassEntropy(): FAIL" << std::endl;
    std::cout << "Got: " << std::to_string(S) << std::endl;
  }
  
  //getmidpoints test
  std::vector <float> mPVec = {1, 3, 5, 7, 9};
  std::vector <float> outmPVec = getMidPoints(mPVec);
  std::vector <float> corrMidPoints = {2, 4, 6, 8};

  if (outmPVec == corrMidPoints){
    std::cout <<  "getMidPoints(): PASS" << std::endl;
  } else {
    std::cout << "getMidPoints():  FAIL" << std::endl;
  }

  //calculate gini index test
  datavec giniVec;
  giniVec.push_back(testRow1);
  giniVec.push_back(testRow2);
  giniVec.push_back(testRow3);
  giniVec.push_back(testRow4);
  giniVec.push_back(testRow5);
  giniVec.push_back(testRow6);
  giniVec.push_back(testRow7);
  giniVec.push_back(testRow8);
  giniVec.push_back(testRow9);

  float giniIdx = calcGini(giniVec, 8);

  if (std::to_string(giniIdx) == "0.888889"){
    std::cout << "calcGini(): PASS" << std::endl;
  } else {
    std::cout << "calcGini(): FAIL" << std::endl;
    std::cout << "Got: " << std::to_string(giniIdx) << std::endl;
  }
}
