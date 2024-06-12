#include <bits/stdc++.h>

using namespace std;

double crossValidation(vector<vector<double>> &data, vector<int> &currentFeatures, int featuretoAdd, int whichAlgorithm)
{
    int number_correctly_classified = 0;
    for(int i = 0; i < data.size(); i++){
        int objectLabel = data[i][0];

        double nearest_neighbor_distance = numeric_limits<double>::max();
        int nearest_neighbor_location = numeric_limits<int>::max();
        int nearest_neighbor_label = 0;

        for(int j = 0; j < data.size(); j++)
        {
            double distance = 0;
            if (j != i)
            {
                for(int k = 0; k < currentFeatures.size(); k++){
                    distance += pow(data[i][currentFeatures[k]] - data[j][currentFeatures[k]], 2);
                }

                if (whichAlgorithm == 1)
                {
                    distance += (pow(data[i][featuretoAdd] - data[j][featuretoAdd], 2.0));
                }

                distance = sqrt(distance);

                if (distance < nearest_neighbor_distance)
                {
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_location = j;
                    nearest_neighbor_label = data[nearest_neighbor_location][0];
                }
            }
        }
        if (objectLabel == nearest_neighbor_label)
        {
            number_correctly_classified++;
        }
    }
   
    return (double)number_correctly_classified/data.size()*100;
}

void forward(vector<vector<double>> &data, int whichAlgorithm)
{
    clock_t tStart = clock();
    vector<int> current_set_of_features;
    vector<int> bestFeatureSet;

    double bestOverallAccuracy = 0;
    double localBestAccuracy = 0;

    for(int i = 1; i < data[i].size(); i++){
        
        int feature_to_add_at_this_level;
        double bestAccuracy = 0;
        vector<int> outputfeature;
        
        for (int j = 1; j < data[j].size(); j++)
        {
            if (!(find(current_set_of_features.begin(), current_set_of_features.end(), j) != current_set_of_features.end()))
            {
                
                double accuracy = crossValidation(data, current_set_of_features, j, whichAlgorithm);

                outputfeature = current_set_of_features;
                outputfeature.push_back(j);

                cout << "Using features(s) {";

                for (int i = 0; i < outputfeature.size(); i++)
                {
                    cout << outputfeature[i];
                    if(i != outputfeature.size()-1)
                    {
                        cout << ",";
                    }
                }

                cout << "} accuracy is "<< accuracy <<"%"<<endl;
                
                if (accuracy > bestAccuracy)
                {
                    bestAccuracy = accuracy;
                    localBestAccuracy = bestAccuracy;
                    feature_to_add_at_this_level = j;
                }
            }
        }

        if (bestAccuracy > bestOverallAccuracy)
        {
            bestOverallAccuracy = bestAccuracy;
            bestFeatureSet.push_back(feature_to_add_at_this_level);
        }

        current_set_of_features.push_back(feature_to_add_at_this_level);

        if (localBestAccuracy < bestOverallAccuracy)
        {
            cout << "\n(Warning, Accuracy has decreased! Continuing search in case of local maxima)";
        }

        cout << "\nFeature set {";

        for (int i = 0; i < current_set_of_features.size(); i++)
        {
            cout << current_set_of_features[i];
            if(i != current_set_of_features.size()-1)
            {
                cout << ",";
            }
        }

        cout <<"} was best, accuracy is "<<localBestAccuracy<<"%\n\n";

    }

    cout <<"Finished search!! The best feature subset is {";
    for (int i = 0; i < bestFeatureSet.size(); i++)
    {
            cout << bestFeatureSet[i];
            if(i != bestFeatureSet.size()-1)
            {
                cout << ",";
            }
    }
    cout << "}, which has an accuracy of " << bestOverallAccuracy << "%\n";
    printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

void backward(vector<vector<double>> &data, vector<int> &currFeatures, int whichAlgorithm)
{
    clock_t tStart = clock();
    int feature_to_remove;
    vector<int> bestFeatureSet;
    double bestOverallAccuracy = 0;
    double localBestAccuracy = 0;
    vector<int> outputfeature;

    while(currFeatures.size() > 1)
    {
       double bestAccuracy = 0;
    for(int i = 0; i < currFeatures.size(); i++)
    {
        
        outputfeature = currFeatures;
        outputfeature.erase(outputfeature.begin()+i);
        double accuracy = crossValidation(data, outputfeature, whichAlgorithm, whichAlgorithm);

        cout << "Using features(s) {";

        for (int i = 0; i < outputfeature.size(); i++)
        {
            cout << outputfeature[i];
            if(i != outputfeature.size()-1)
            {
                cout << ",";
            }
        }

        cout << "} accuracy is "<< accuracy <<"%"<<endl;

        if (accuracy > bestAccuracy)
        {
            bestAccuracy = accuracy;
            localBestAccuracy = bestAccuracy;
            feature_to_remove = i;
            
        }

        if(bestAccuracy > bestOverallAccuracy)
        {
            bestOverallAccuracy =bestAccuracy;
            bestFeatureSet = outputfeature;
        }

    }
    
    currFeatures.erase(currFeatures.begin() + feature_to_remove);

    if (localBestAccuracy < bestOverallAccuracy)
    {
        cout << "\n(Warning, Accuracy has decreased! Continuing search in case of local maxima)";
    }

     cout << "\nFeature set {";

        for (int i = 0; i < currFeatures.size(); i++)
        {
            cout << currFeatures[i];
            if(i != currFeatures.size()-1)
            {
                cout << ",";
            }
        }

    cout <<"} was best, accuracy is "<<localBestAccuracy<<"%\n\n";
    }

    cout <<"Finished search!! The best feature subset is {";
    for (int i = 0; i < bestFeatureSet.size(); i++)
    {
            cout << bestFeatureSet[i];
            if(i != bestFeatureSet.size()-1)
            {
                cout << ",";
            }
    }
    cout << "}, which has an accuracy of " << bestOverallAccuracy << "%\n";
    printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

int main(){

    vector<vector<double>> dataSet; // small 17 large 95 
    string filename;
    int choice;
    int choice2;
    cout<<"-------------------------------------------------------------------------------------\n";
    cout<< "Welcome to David Liu's Feature Selection Algorithm.\nSelect the file you want to test:\n1. CS205_small_Data__17.txt\n2. CS205_large_Data__47.txt\n3. NEW_DataSet.txt\n\n";
    cin >> choice;
    if (choice == 1)
    {
        filename = "CS205_small_Data__17.txt";
    }
    else if (choice == 2)
    {
        filename = "CS205_large_Data__47.txt";
    }
    else if (choice == 3)
    {
        filename = "new.txt";
    }
    cout<< "Type the number of the algorithm you want to run\n\n1) Forward Selection\n2) Backward Elimination\n\n";
    cin >> choice2;

    ifstream myfile(filename);  
    string content;
    double value; 
    while(getline(myfile, content)){
        stringstream row(content); 
        vector<double> temp;
        while(row >> value){
            temp.push_back(value);
        }
        dataSet.push_back(temp);
    }
    myfile.close();

    cout << "\nThis dataset has " << dataSet[0].size()-1 << " features (not including the class attribute), with " << dataSet.size() << " instances.\n\n";

    vector<int> temp2;
    vector<int> temp3;
    for (int i = 1; i < dataSet[i].size(); i++)
    {
        temp2.push_back(i);
    }
    double firstAccuracy = crossValidation(dataSet, temp2, temp2.size(), 2);
    cout << "Running nearest neighbor with all features, using \"leaving-one-out\" evaluation, I get an accuracy of " << firstAccuracy<<"%\n\n";

    if (choice2 == 1)
    {
        forward(dataSet, choice2);
    }
    else if (choice2 == 2)
    {
        backward(dataSet, temp2, choice2);
    }
    
    return 0;
}