#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <string>
using namespace std;

class TwitterFollowersAnalyzer
{

private:
    unordered_map<int,vector<int>> twitterGraph; // ADJACENCY LIST
    vector<pair<int, int>> followersCount; // HASH TABLE OF THE KEY (INFLUENCER) AND THE VALUE (FOLLOWERS)
    int duplicates = 0; // DUPLICATES FOUND IN THE DATA
    int n; //DATA SIZE
public:
    void read_csv(string filename)
    {
        FILE* file = freopen(filename.c_str(), "r", stdin); // Redirect stdin to the file
        if (file)
        {
            printf("File found.\n");
            int user, follows;
            char comma;
            while (scanf("%d %c %d", &user, &comma, &follows) != EOF)
                if(!checkDuplicates(twitterGraph[follows], user))
                    twitterGraph[follows].emplace_back(user);
            calculateFollowers();
            fclose(file);
        }
        else
        {
            printf("File not found.\n");
            exit(-1);
        }

    }
    void printAdjacencyList()
    {
        for(pair<int,vector<int>> x: twitterGraph)
        {
            for(int followers : x.second)
                printf("%d ", followers);
            printf("--> follows %d\n", x.first);
        }

    }
    void getDuplicates()
    {
        printf("There are %d duplicates in this data.\n", duplicates);
    }
    void printFollowersCount()
    {
        printf("Please enter n for TOP n EX: TOP 10 will list top 10 influencers.\n");
        string userInput;
        int number;
        for(int i = 0; i < 10; i++)
            printf("%d %d\n", followersCount[i].first, followersCount[i].second);
    }
    void heapSortFollowersCount()
    {
        n = followersCount.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(followersCount, n, i);

        // Heap sort
        for (int i = n - 1; i > 0; i--)
        {
            swap(followersCount[0], followersCount[i]);
            heapify(followersCount, i, 0);
        }
    }
private:
    bool checkDuplicates(vector<int> v, int key)
    {
        if(v.size())
        {
             for(int x : v)
                if(x == key)
                {
                    duplicates+=1;
                    return true; //FOUND DUPLICATE!
                }
        }
        return false;
    }
    void calculateFollowers()
    {
        for(pair<int,vector<int>> x : twitterGraph)
            followersCount.push_back({x.first,x.second.size()});
    }
    void heapify(vector<pair<int, int>>& arr, int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left].second < arr[largest].second)
            largest = left;

        if (right < n && arr[right].second < arr[largest].second)
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};



int main()
{
    TwitterFollowersAnalyzer analyzer;
    analyzer.read_csv("twitter.csv");
    //analyzer.getDuplicates();
    analyzer.heapSortFollowersCount();
    analyzer.printFollowersCount();
    //analyzer.printAdjacencyList();
    return 0;
}
