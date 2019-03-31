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
	
