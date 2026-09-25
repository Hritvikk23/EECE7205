#include <iostream>
#include <vector>
#include <string>
#include <cmath>    
#include <map>
#include <algorithm>
using namespace std;

void heapify(int coord[][2], double dist[], int i, int n){
    while(true){
        int root = i; // assuming that the current node is the root or the largest node
        int left = (2*i) + 1; // Left node index
        int right = (2*i) +2; // Right node index

        if (left < n && dist[left]>dist[root]){ // if left node distance is larger then make the left node the largest
            root = left;
        }
        if (right < n && dist[right]>dist[root]){ // if right node distance is larger then make the right node the largest
            root = right;
        }
        if(root != i){
            swap(coord[i], coord[root]); //swapping the coordinates
            swap(dist[i], dist[root]); //swapping the distances
            i = root;
        }
        else{
            break; //if the current node is already the largest, then break
        }
    }
}

int merge(vector <int> &arr, int low, int mid, int high){
    //this function is to merge the array and also count the inversion during the merge
    vector <int> temp; //a temp array to store the elements
    int i = low; int j = mid +1; //low is the starting index of the left half, mid is the starting index of the right half
    int inversion_count = 0;
    while(i<=mid && j<=high){
        if(arr[i] <= arr[j]){
            temp.push_back(arr[i]); //if the element in the left is smaller, it is added to temp array
            i++;
        }
        else{
            temp.push_back(arr[j]); //if the element in the right is smaller, it is added to temp array
            j++;
            inversion_count += (mid -i +1); 
        }
    }
    while (i<=mid){
        temp.push_back(arr[i]); // add the remaining elements from the left half to the temp array
        i++;
    }
    while(j<=high){
        temp.push_back(arr[j]); // add the remaining elemnets from the right half to the temp array
        j++;
    }
    for(int index =0; index<temp.size(); index++){
        arr[index+low] = temp[index]; //all the sorted elements back in the array
    }
    return inversion_count; //finally return the inversion count
}
int merge_sort(vector <int> &arr, int low, int high){
    //this is where the sort happens
    if (low< high){
        int mid = low + (high-low)/2; //the middle index
        int l_inversion_count = merge_sort(arr, low, mid); //recursively sorting the left half and also counting the inversions
        int r_inversion_count = merge_sort(arr,mid+1,high); //recursively sorting the right half and also coutning the inversions
        int inversion_count = merge(arr,low,mid,high); //merging both the halves and the inversions btwn them

        return l_inversion_count+r_inversion_count+inversion_count; //adding all the inversions and returning the total number of inversions
    }
    return 0;
}

void problem1(){
    int in;
    int temp; //temp variable for sorting
    cout << "Enter number of intervals: "; 
    //Asking the user to enter the number of intervals since arrays are static and have a fixed size, so I am asking to enter the number of intervals
    cin >> in;

    int interval[in][2];

    //Entering the intervals
    for (int i=0; i<in;i++){
        cout <<"Enter the start and end of interval " <<i+1 << ": ";
        //The i+1 is to basically show the interval number they are entering, like interval 1, interval 2 etc..
        cin >> interval[i][0] >> interval[i][1];
    }
    //Sorting - Bubble sort with a temp variable
   for (int i=0; i<in-1;i++){  
    for (int j=0; j<in-1; j++){
        if (interval[j][0] > interval[j+1][0]){ //checking if the value in the previous interval is greater or not
            temp = interval[j][0];
            interval[j][0] = interval[j+1][0];
            interval[j+1][0] = temp;
            //This is for the second value in the interval
            temp = interval[j][1];
            interval[j][1] = interval[j+1][1];
            interval[j+1][1] = temp;            
        }
    }
   }
   //To check for overlaps and merge them
    int merged =0;
    for(int i=1;i<in;i++){
        //If the current merged interval overlaps with the next interval, then it keeps the larger ending value 
        if (interval[merged][1] >= interval[i][0]){
            interval[merged][1] = max(interval[merged][1],interval[i][1]);
        }
        else{
            merged++; //moving to the next position 
            interval[merged][0] = interval[i][0]; //copying the current interval into next merged position
            interval[merged][1] = interval[i][1];
        }
    }

   //To print out the intervals
    for (int i=0; i<=merged; i++){
        cout << "[" <<interval[i][0] << "," <<interval[i][1] <<"]";
        if (i != merged) {
            cout << ",";
        }
    }
}

void problem2(){

    int choice;
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);

    for (int i=0;i<n;i++){
        cout <<"Enter element "<<i+1 <<": ";
        cin >> arr[i];
    }

    cout <<"Enter the number to select the method (1 = Counting based, 2 = One pass DNF Algorithm): ";
    cin >> choice;
    //A menu to choose either Counting based or DNF
    switch(choice){
        case 1: {
        //Counting based
            int count_0 =0; int count_1 = 0; int count_2 = 0;
            //Checking for 0,1,2 in the array, the count of 0 increases whenever it finds 0 in the array and similar for 1,2
            for (int i =0; i<n;i++){
                if(arr[i]==0) count_0++;
                else if(arr[i]==1) count_1++;
                else count_2++;
            }
            //Replacing the elements based on the count of 0s,1s and 2s. 
            int index = 0;
            for (int i=0;i<count_0;i++){
                arr[index++] =0;
            }
            for (int i=0;i<count_1;i++){
                arr[index++] =1;
            }
            for (int i=0;i<count_2;i++){
                arr[index++] =2;
            }

            for (int i=0;i<n;i++){
                cout << arr[i] <<",";
            }

            break;
        }
        case 2: {
            
        //One Pass DNF           
            //Initializing mid,high and low values.
            int mid =0; int high = n-1; int low = 0; int temp;
            while(mid<=high){
                if (arr[mid]==0){
                    temp = arr[low]; //if the middle value is 0, swap the value with the low and increment mid and low
                    arr[low] = arr[mid];
                    arr[mid] = temp;
                    mid++;
                    low++;
                }
                else if (arr[mid]==1) mid++; // if the middle value is 1, no need to swap anything since that's where 1 should be and increment mid
                else{
                    temp = arr[high]; //when value = 2, swap the value with high and decrement high
                    arr[high] = arr[mid];
                    arr[mid] = temp;
                    high--;
                }
            }
            //Printing the array
            for (int i=0;i<n;i++){
                cout << arr[i] << ",";
            }
        }      
        break;
    }

}

void problem3(){
    int n;
    cout << "Enter a number of elements: "; //Entering the number of elementss
    cin >> n;
    vector<int> arr(n);        
    vector<string> string_arr; //Initializing a new string vector
    string temp;

    for (int i =0; i<n;i++){
        cout << "Enter the non-negative integer " <<i+1 <<": "; //Entering the elements 
        cin >> arr[i];
        string_arr.push_back(to_string(arr[i])); //Converting the integer array to string and pushing them into new string vector
    }
    //In this part it checks whether a+b<b+a, if yes it will swap else continues
    //The swap is similar to the swap in bubble sort, only the conidtion is different
    for (int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if((string_arr[j]+string_arr[j+1]) < string_arr[j+1]+string_arr[j])
            {
                temp = string_arr[j];
                string_arr[j] = string_arr[j+1];
                string_arr[j+1] = temp;
            }
        }
    }
    //Printing out the final results
    for(int i=0;i<n;i++){
        cout << string_arr[i];
    }    
}

void problem4(){
    int n;
    string str;
    vector<string> anag;
    cout <<"Enter number of words: ";
    cin >> n;
    string temp;

    for (int i=0;i<n;i++){
        cout << "Enter a word: ";
        cin >> str;
        for (int j=0; j<str.length();j++){        
            str[j] = tolower(str[j]);
        }
        anag.push_back(str); //adding the lowercase to vector
    }
    vector<string> temparr; //a second vector to store the sorted characters

    for(int i=0;i<n;i++ ){
        temp = anag[i]; //the current word is copied into temp
        sort(temp.begin(),temp.end()); // the copied word is sorted alphabetically
        temparr.push_back(temp); //stored in sorted array
    }

    for (int i=0;i<n;i++){ //The words are going to get sorted 
        for (int j=0;j<n-1;j++){
            if (temparr[j] > temparr[j+1]){ // if the current word comes after the sorted word, then swap
                swap(temparr[j],temparr[j+1]);
                swap(anag[j],anag[j+1]); //also swap the original words to match them with their sorted version
            }
        }
    }  
    for (int i=0;i <n; i++){
        cout << anag[i] << " "; //Printing the words in sorted order
    }
}

void problem5(){
    int in;
    int temp; //temp variable for sorting
    cout << "Enter number of intervals: "; 
    //Asking the user to enter the number of intervals since arrays are static and have a fixed size, so I am asking to enter the number of intervals
    cin >> in;
    int interval[in][2];
    //Entering the intervals
    for (int i=0; i<in;i++){
        cout <<"Enter the start and end of interval " <<i+1 << ": ";
        //The i+1 is to basically show the interval number they are entering, like interval 1, interval 2 etc..
        cin >> interval[i][0] >> interval[i][1];    
    }
    //Sorting - Bubble sort with a temp variable
   for (int i=0; i<in-1;i++){  
    for (int j=0; j<in-1; j++){
        if (interval[j][0] > interval[j+1][0]){ //checking if the value in the previous interval is greater or not
            temp = interval[j][0];
            interval[j][0] = interval[j+1][0];
            interval[j+1][0] = temp;
            //Swapping the second value of the interval when the first one swaps
            temp = interval[j][1];
            interval[j][1] = interval[j+1][1];
            interval[j+1][1] = temp;            
        }
    }
   }
   //To check for overlaps
   bool meeting = true;
   for (int j=0; j<in-1;j++){
        if(interval[j][1] > interval[j+1][0]){ // if the second value of the current interval is greater than the first value of next interval then there's an overlap
            meeting = false;
            break; 
        }
    }
    if(meeting){
        cout << "Can attend every meeeting";
    }
    else{
        cout << "Cannot attend every meeting";
    }
}

void problem6(){
    //Initializing the required variables
    int k; int n;
    int x; int y;
    int temp; int choice;
    
    cout << "Enter number of pairs: ";
    cin >> n;

    int coord[n][2];
    double dist[n];

    //To enter the coordinates
    for (int i =0; i<n;i++){
        cout << "Enter pair "<<i+1 <<": ";
        cin >> coord[i][0] >> coord[i][1]; 
    }
    cout << "Enter the integer k: ";
    cin >> k;
    //Using a menu to compare, either normal sorting or heap sort
    cout << "Enter your choice(1. Normal Sorting, 2. Heap Sort): ";
    cin >> choice;

     //Calculating the distance using the formula sqrt(x^2+y^2)
    for (int i=0;i<n;i++){
        dist[i] = sqrt(pow(coord[i][0],2) + pow(coord[i][1],2));
    }


    switch(choice){
        case 1:        
            //Sorting 
            for (int i=0; i<n-1;i++){  
                for (int j=0; j<n-1; j++){
                    if (dist[j] > dist[j+1]){ //checking if x is greater than previous x, if yes swapping
                        temp = coord[j][0];
                        coord[j][0] = coord[j+1][0];
                        coord[j+1][0] = temp;
                    //The y coordinate swaps if x does
                        temp = coord[j][1];
                        coord[j][1] = coord[j+1][1];
                        coord[j+1][1] = temp;   
                    // swapping the distances with the coordinates
                        double temp_dist = dist[j];
                        dist[j] = dist[j+1];
                        dist[j+1] = temp_dist;
                    }
                }
            } 
            for (int i=0; i<k;i++){
                cout << coord[i][0] << "," << coord[i][1] <<endl;
            }
            break;
        case 2:  
            //Heap Sort
            //This case uses a heapify function

            for (int i=(n/2) - 1; i >=0; i--){//
                heapify(coord, dist, i,n);
            }
            for (int i= n-1; i>0; i--){
                swap(coord[0],coord[i]);
                swap(dist[0],dist[i]);
                heapify(coord,dist,0,i);
            }
            for (int i=0; i<k;i++){
                cout << coord[i][0] << "," << coord[i][1] <<endl;
            }
            break;          
    }
}

void problem7(){
    //Initializing the varaibles
    int n; int k;
    cout <<"Enter number of integers: ";
    cin >> n;
    vector <int> arr(n);

    for(int i=0;i<n;i++){
        cout << "Enter number in array: ";
        cin >> arr[i];
    }
    //Asking of the k value
    cout <<"Enter k: ";
    cin >>k;
    

    map<int,int> count;

    for(int i=0;i<n;i++){
        count[arr[i]]++;
    }
    int size = count.size();
    vector <int> val(size);
    vector <int> key(size);
    int index = 0;
    for (auto&p :count){
        val[index] = p.first;
        key[index] = p.second;
        index++;
    }
    for (int i=0; i<size-1;i++){  
        for (int j=0; j<size-1; j++){
            if (key[j] < key[j+1]){ 
                int temp = key[j];
                key[j] = key[j+1];
                key[j+1] = temp;
                //
                int temp2 = val[j];
                val[j] = val[j+1];
                val[j+1] = temp2;
            }
            else if (key[j] == key[j+1] && val[j]>val[j+1]){
                int temp = key[j];
                key[j] = key[j+1];
                key[j+1] = temp;
                //
                int temp2 = val[j];
                val[j] = val[j+1];
                val[j+1] = temp2;
            }
        }
    }  

    for (int i=0;i<k && i<size;i++){
        cout << val[i] << " ";
    }
}

void problem8(){
    int k; int n;

    cout <<"Enter number of arrays: ";
    cin >>k;
    
    vector<vector<int>> arr(k);

    for(int i=0; i<k;i++){
        cout <<"Enter size of array: "<<i+1<<": ";
        cin >>n;

        arr[i].resize(n);

        cout <<"Enter elements in array ";
        for (int j=0;j<n;j++){
            cin >> arr[i][j];
        }
    }
    vector <int> index (k,0);
    vector <int> result;

    while (true){
        int min; int min_arr = -1;
        for(int i=0;i<k;i++){
            if(index[i]<arr[i].size()){
                if (min_arr == -1 || arr[i][index[i]] <min){
                    min = arr[i][index[i]];
                    min_arr = i;
                }
            }
        }
        if (min_arr==-1){
            break;
        }
        result.push_back(min);
        index[min_arr]++;
    }
    for (int val:result){
        cout << val <<" ";
    }       
}

void problem9(){
    int n; int k;
    cout << "Enter number of integers in array: ";
    cin >> n;

    int arr[n];

    cout << "Enter k: ";
    cin >>k;

    //To make sure that the k is not greater than n
    if(n<k){
        cout << "Exceeds the size of the array";
        return;
    }

    for (int i=0;i<n;i++){
        cout << "Enter elements in array: ";
        cin >> arr[i];
    }
    //This is a bubble sort but instead of sorting them in an ascending order they are sorted in a descending order 
    for (int i=0; i<n-1;i++){  
        for (int j=0; j<n-1; j++){
            if (arr[j] < arr[j+1]){ 
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;       
            }
        }      
    }
    //Printing the kth largest element from the sorted array
    cout << arr[k-1] << " is the largest element";
}

void problem10(){
    int n;
    cout <<"Enter number of integers in the array: ";
    cin >> n;

    vector <int> arr(n);

    for (int i =0;i<n;i++){
        cout <<"Enter integer in the array: ";
        cin >> arr[i];
    }

    int count = merge_sort(arr,0,n-1);
    cout << count;

}

int main(){
    int choose;
    cout << "Choose a problem from 1-10: ";
    cin >> choose;

    switch(choose){
        case 1:
            problem1();
            break;
        case 2: 
            problem2(); 
            break;
        case 3: 
            problem3();
            break;
        case 4: 
            problem4(); 
            break;
        case 5: 
            problem5();
            break;
        case 6: 
            problem6();
            break;
        case 7: 
            problem7();
            break;
        case 8: 
            problem8();
            break;
        case 9: 
            problem9();
            break;
        case 10: 
            problem10();
            break;                

    }

}