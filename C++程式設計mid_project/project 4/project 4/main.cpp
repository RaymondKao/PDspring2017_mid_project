#include <iostream>
#include <cmath>
using namespace std;

void StoreProfitFind(int storeNum, int centerNum, int cost, int* price, int** distanceList, int** distribution, int* profitStore){
    for(int i = 0; i < storeNum; i++)
    {
        int earning = 0;
        for(int j = 0; j < centerNum; j++)
        {
            int profit = (price[i] - cost * distanceList[j][i]) * distribution[j][i];
            earning += profit;
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
            int profit = (price[j] - cost * distanceList[i][j]) * distribution[i][j];
            earning += profit;
        }
        profitCenter [i] = earning;
    }
}


void UselessStore(int storeNum, int centerNum, int* profitStore, int* storeSetCost, int** distribution, int* storageList, int* demandList){
    for(int i = 0; i < storeNum; i++)
    {
        if(profitStore[i] < storeSetCost[i])
        {
            for(int j = 0; j < centerNum; j++){
                storageList[j] += distribution[j][i];
                demandList[i] -= distribution[j][i];
                distribution[j][i] = 0;
            }
        }
    }
    
}

void UselessCenter(int storeNum, int centerNum, int* profitCenter, int* centerSetCost, int** distribution, int* storageList, int* demandList){
    for(int i = 0; i < centerNum; i++)
    {
        if(profitCenter[i] < centerSetCost[i])
        {
            for(int j = 0; j < storeNum; j++){
                storageList[i] -= distribution[i][j];
                demandList[j] += distribution[i][j];
                distribution[i][j] = 0;
            }
            
        }
    }
    
}

int MyAlgorithm(int storeNum, int centerNum, int* demandList, int* storageList, int** distanceList, int** distribution)
{
    int nearestCenter = -1;
    int nearestStore = -1;
    int smallestDistance = 401;
    for (int j = 0; j < storeNum; j++){
        if (demandList[j] > 0){
            
            int storeNearestCenter = -1;
            int storeSmallestDistance = 401;
            
            for (int i = 0; i < centerNum; i++){
                
                if (storageList[i] > 0){
                    if (distanceList[i][j] >= 0){
                        if (distanceList[i][j] < storeSmallestDistance){
                            storeNearestCenter = i;
                            storeSmallestDistance = distanceList[i][j];
                        }else if (distanceList[i][j] == storeSmallestDistance){
                            if (storageList[i] > storageList[storeNearestCenter])
                                storeNearestCenter = i;
                        }
                    }
                }
            }
            
            if (storeNearestCenter != -1){
                if (storeSmallestDistance < smallestDistance){
                    nearestCenter = storeNearestCenter;
                    nearestStore = j;
                    smallestDistance = storeSmallestDistance;
                }else if (storeSmallestDistance == smallestDistance){
                    if (demandList[j] > demandList[nearestStore]){
                        nearestCenter = storeNearestCenter;
                        nearestStore = j;
                    }
                }
            }
            
            
        }
        
    }
    
    if (nearestCenter == -1){
        return 0;
    }else{
        int distributionNum = min(demandList[nearestStore], storageList[nearestCenter]);
        distribution[nearestCenter][nearestStore] = distributionNum;
        storageList[nearestCenter] -= distributionNum;
        demandList[nearestStore] -= distributionNum;
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
    
    int* price = new int [storeNum];  // every store's price
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
        cin >> centerList[i][0] >> centerList[i][1];
    }
    for (int i = 0; i < storeNum; i++)
    {
        storeList[i] = new int [2];
        cin >> storeList[i][0] >> storeList[i][1];
    }
    for (int i = 0; i < storeNum; i++)
    {
        cin >> demandList[i];
    }
    for (int i = 0; i < storeNum; i++)
    {
        cin >> storeSetCost[i];
    }
    for (int i = 0; i < storeNum; i++)
    {
        cin >> price[i];
    }
    for (int i = 0; i < centerNum; i++)
    {
        cin >> centerSetCost[i];
    }
    for (int i = 0; i < centerNum; i++)
    {
        cin >> storageList[i];
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
            int newDistance = abs(centerList[i][0] - storeList[j][0]) + abs(centerList[i][1] - storeList[j][1]);
            if (price[j] - cost*newDistance > 0)
                distanceList[i][j] = newDistance;
            else
                distanceList[i][j] = -1;
        }
    }
    
    for (int i = 0; i < centerNum; i++){
        if(centerSetCost[i] > 180000){
            storageList[i] = 0;
        }
    }
    
    for (int i = 0; i < storeNum; i++){
        if(storeSetCost[i] > 180000){
            demandList[i] = 0;
        }
    }
    
    
    for(int i = 0; i < 10; i++){
        int tag = MyAlgorithm(storeNum, centerNum, demandList, storageList, distanceList, distribution);
        
        while(tag){
            tag = MyAlgorithm(storeNum, centerNum, demandList, storageList, distanceList, distribution);
        }
        
        StoreProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitStore);
        
        UselessStore(storeNum, centerNum, profitStore, storeSetCost, distribution, storageList, demandList);
        
        CenterProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitCenter);
        
        UselessCenter(storeNum, centerNum, profitCenter, centerSetCost, distribution, storageList, demandList);
    }
    
    StoreProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitStore);
   	for(int i = 0; i < storeNum; i++)
    {
        if(profitStore[i] >= storeSetCost[i])
        {
            openStore[setStoreNum] = i+1;
            setStoreNum++;
        }
    }
    
    CenterProfitFind(storeNum, centerNum, cost, price, distanceList, distribution, profitCenter);
    for(int i = 0; i < centerNum; i++)
    {
        if(profitCenter[i] >= centerSetCost[i])
        {
            openCenter[setCenterNum] = i+1;
            setCenterNum++;
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

