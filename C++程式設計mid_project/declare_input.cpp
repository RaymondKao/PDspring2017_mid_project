    int centerNum = 0;
    int storeNum = 0;
    int cost = 0;
	int setCenterNum = 0;
	int setStoreNum = 0;
    cin >> centerNum >> storeNum >> cost;

	int* price = new int [storeNum];
    int* demandList = new int [storeNum];
    int** storeList = new int* [storeNum];
    int* storeSetCost = new int [storeNum];

    int* storageList = new int [centerNum];
    int** centerList = new int* [centerNum];
    int* centerSetCost = new int [centerNum];


    int** distanceList = new int* [centerNum];
    int** distribution = new int* [centerNum];
	
	int* profitStore = new int [storeNum];
	int* openStore = new int [storeNum];
	
	int* profitCenter = new int [centerNum];
	int* openCenter = new int [centerNum];
		
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
