#include <iostream>
#include <cmath>
using namespace std;

void StoreProfitFind(int storeNum, int centerNum, int cost, int* price, int** distanceList, int** distribution, int* profitStore){
    for(int i = 0; i < storeNum; i++)
    {
        int earning = 0;
        for(int j = 0; j < centerNum; j++)
        {
            int profit = (price[i] - cost * distanceList[j][i]) * distribution[j][i];//calculate the store profit of the product
            earning += profit;//accumulate the store total earnings
        }
        profitStore [i] = earning;
    }
}

void CenterProfitFind(int storeNum, int centerNum, int cost, int* price, int** distanceList, int** distribution, int* profitCenter){
    for(int i = 0; i < centerNum; i++)
    {
        int earning = 0;
        for(int j = 0; j < storeNum; j++)
        {
            int profit = (price[j] - cost * distanceList[i][j]) * distribution[i][j];//calculate the center profit of the product
            earning += profit;//accumulate the center profit of the product
        }
        profitCenter [i] = earning;
    }
}

void UselessStore(int storeNum, int centerNum, int* profitStore, int* storeSetCost, int** distribution){
    for(int i = 0; i < storeNum; i++)
    {
        if(profitStore[i] < storeSetCost[i])
        {
            for(int j = 0; j < centerNum; j++)
                distribution[j][i] = 0;//assign 0 to the useless number of the store
        }
    }
}

void UselessCenter(int storeNum, int centerNum, int* profitCenter, int* centerSetCost, int** distribution){
    for(int i = 0; i < centerNum; i++)
    {
        if(profitCenter[i] < centerSetCost[i])
        {
            for(int j = 0; j < storeNum; j++)
                distribution[i][j] = 0;//assign 0 to the useless number of the center
        }
    }
}

int MyAlgorithm(int storeNum, int centerNum, int* demandList, int* storageList, int** distanceList, int** distribution)
{
    int nearestCenter = -1;
    int nearestStore = -1;
    int smallestDistance = 401;//the largest distance in the area
    for (int j = 0; j < storeNum; j++){
        if (demandList[j] > 0){
            
            int storeNearestCenter = -1;
            int storeSmallestDistance = 401;
            
            for (int i = 0; i < centerNum; i++){
                if (storageList[i] > 0){
                    if (distanceList[i][j] >= 0){
                        if (distanceList[i][j] < storeSmallestDistance){
                            storeNearestCenter = i;
                            storeSmallestDistance = distanceList[i][j];//find the smallest distance between center i and store j
                        }
                        else if (distanceList[i][j] == storeSmallestDistance){
                            if (storageList[i] > storageList[storeNearestCenter])
                                storeNearestCenter = i;//select the center with the larger capacity while the same distance
                        }
                    }
                }
            }
            
            if (storeNearestCenter != -1){
                if (storeSmallestDistance < smallestDistance){
                    nearestCenter = storeNearestCenter;//select the nearist center i
                    nearestStore = j;//select the nearist store j
                    smallestDistance = storeSmallestDistance;//the smallest distance between center i and store j
                }
                else if (storeSmallestDistance == smallestDistance){
                    if (demandList[j] > demandList[nearestStore]){
                        nearestCenter = storeNearestCenter;//select the nearist center i
                        nearestStore = j;//select the nearist store j
                    }
                }
            }
        }
    }
    
    if (nearestCenter == -1){
        return 0;
    }
    else{
        int distributionNum = min(demandList[nearestStore], storageList[nearestCenter]);
        distribution[nearestCenter][nearestStore] = distributionNum;
        storageList[nearestCenter] -= distributionNum;//distribute the amount and reduce the storage
        demandList[nearestStore] -= distributionNum;//distribute the amount and reduce the demand
        return 1;
    }
}

int main(){
    
    int centerNum = 0; // the number of center will be considered
    int storeNum = 0;  // the number of store will be considered
    int cost = 0;  // distribution cost per mile
    int setCenterNum = 0; // the number of center we have decided to built
    int setStoreNum = 0;  // the number of store we have decided to built
    cin >> centerNum >> storeNum >> cost;
    
    int* price = new int [storeNum];  // every store's unit price
    int* demandList = new int [storeNum];  // every store's demand
    int** storeList = new int* [storeNum];  //  store's location
    int* storeSetCost = new int [storeNum];  //store's everyday setting cost
    
    int* storageList = new int [centerNum]; // center's capacity
    int** centerList = new int* [centerNum]; // center's location
    int* centerSetCost = new int [centerNum]; // center's everyday setting cost
    
    
    int** distanceList = new int* [centerNum];  //record the distance between center i to store j
    int** distribution = new int* [centerNum]; // two-dim array to record the distribution amount center i to store j
    
    int* profitStore = new int [storeNum];  // the total profit of each store can earn
    int* openStore = new int [storeNum];  // the stores we have decided to built
    
    int* profitCenter = new int [centerNum]; // the total profit of each center can earn
    int* openCenter = new int [centerNum];// the centers we have decided to built
    
    for (int i = 0; i < centerNum; i++)
    {
        centerList[i] = new int [2];
        cin >> centerList[i][0] >> centerList[i][1];//cin the center's location
    }
    for (int i = 0; i < storeNum; i++)
    {
        storeList[i] = new int [2];
        cin >> storeList[i][0] >> storeList[i][1];//cin the store's location
    }
    for (int i = 0; i < storeNum; i++)
    {
        cin >> demandList[i];//cin every store's demand
    }
    for (int i = 0; i < storeNum; i++)
    {
        cin >> storeSetCost[i];//cin store's everyday setting cost
    }
    for (int i = 0; i < storeNum; i++)
    {
        cin >> price[i];//cin store's unit price
    }
    for (int i = 0; i < centerNum; i++)
    {
        cin >> centerSetCost[i];//cin center's everyday setting cost
    }
    for (int i = 0; i < centerNum; i++)
    {
        cin >> storageList[i];//cin center's capacity
    }
    
    for(int i = 0; i < centerNum; i++)
    {
        distanceList[i] = new int [storeNum];
        distribution[i] = new int [storeNum];
        for(int j = 0; j < storeNum; j++)
        {
            distanceList[i][j] = 0;
            distribution[i][j] = 0;
        }
    }
    
    for (int i = 0; i < centerNum; i++){
        for (int j = 0; j < storeNum; j++){
            int newDistance = abs(centerList[i][0] - storeList[j][0]) + abs(centerList[i][1] - storeList[j][1]);//calculate the distance between center i and store j
            if (price[j] - cost * newDistance > 0)
                distanceList[i][j] = newDistance;//if it's profitable, input the distance
            else
                distanceList[i][j] = -1;//otherwise, input -1
        }
    }
    
    int tag = MyAlgorithm(storeNum, centerNum, demandList, storageList, distanceList, distribution);
    
    while(tag){
        tag = MyAlgorithm(storeNum, centerNum, demandList, storageList, distanceList, distribution);
    }
    
    StoreProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitStore);
    
    UselessStore(storeNum, centerNum, profitStore, storeSetCost, distribution);
    
    CenterProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitCenter);
    
    UselessCenter(storeNum, centerNum, profitCenter, centerSetCost, distribution);
    
    
    StoreProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitStore);
   	for(int i = 0; i < storeNum; i++)
    {
        if(profitStore[i] >= storeSetCost[i])
        {
            openStore[setStoreNum] = i+1;//if it's profitable, build the store
            setStoreNum++;//count the store number
        }
    }
    
    CenterProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitCenter);
    for(int i = 0; i < centerNum; i++)
    {
        if(profitCenter[i] >= centerSetCost[i])
        {
            openCenter[setCenterNum] = i+1;//if it's profitable, build the center
            setCenterNum++;//count the center number
        }
    }
    
    
    
    cout << setCenterNum;
    for(int i = 0; i < setCenterNum; i++)
        cout << " " << openCenter[i];
    cout << endl;
    
    cout << setStoreNum;
    for(int i = 0; i < setStoreNum; i++)
        cout << " " << openStore[i];
    cout << endl;
    
    for(int i = 0; i < storeNum; i++)
    {
        for(int j = 0; j < centerNum; j++)
            cout << distribution[j][i] << " ";
        cout << endl;
    }
    
    return 0;
}
