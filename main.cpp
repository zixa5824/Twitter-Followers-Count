//THIS CODE IS DONE BY MAHMOUD ESSAM SHARSHIRA 022023001
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace std::chrono;

class TwitterFollowersAnalyzer {
private:
    unordered_map<int, unordered_set<int>> twitterGraph;
    vector<pair<int, int>> followersCount;
    int n;
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
                twitterGraph[follows].insert(user);

            calculateFollowers();
            fclose(file);
            freopen("CON", "r", stdin);
        }
        else
        {
            printf("File not found.\n");
            exit(-1);
        }
    }

    void printAdjacencyList()
    {
        for (pair<int, unordered_set<int>> x : twitterGraph)
        {
            for (int followers : x.second)
                printf("%d ", followers);
            printf("--> follows %d\n", x.first);
        }
    }

    void getSize()
    {
        printf("%d\n", followersCount.size());
    }

    void printFollowersCount()
    {
        freopen("CON", "r", stdin);
        printf("Please enter n for TOP n (e.g., TOP 10 will list top 10 influencers): \n");
        /*int number;
        int numRead;
        while ((numRead = scanf("%d", &number)) != 1 || number <= 0 || number > followersCount.size()) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a valid number within range: ");
        }*/
        for (int i = 0; i < 10; i++)
            printf("%d %d\n", followersCount[i].first, followersCount[i].second);
    }


    void heapSortFollowersCount()
    {
        n = followersCount.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(followersCount, n, i);

        // Heap sort
        for (int i = n - 1; i > 0; i--) {
            swap(followersCount[0], followersCount[i]);
            heapify(followersCount, i, 0);
        }
    }

    /*void sortUsingSTL()
    {
        sort(followersCount.begin(), followersCount.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });
    }*/
    void recommendUsers(int userId, double threshold)
    {
        unordered_set<int> closestUsers = findClosestUsers(userId, threshold);

        printf("Recommendations for user %d with threshold %.3f:\n", userId, threshold);
        for (int user : closestUsers) {
            printf("%d\n", user);
        }
    }
private:
    void calculateFollowers()
    {
        for (pair<int, unordered_set<int>> x : twitterGraph)
            followersCount.emplace_back(x.first, x.second.size());
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

        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    double calculateJaccardSimilarity(unordered_set<int> setA, unordered_set<int> setB)
    {
        int intersection = 0;
        int unionSet = setA.size() + setB.size();

        for (int user : setA) {
            if (setB.find(user) != setB.end())
            {
                intersection++;
                unionSet--;
            }
        }

        if (unionSet == 0) return 0; // To handle the case of empty sets
        return (double)intersection / unionSet;
    }
    unordered_set<int> findClosestUsers(int userId, double threshold)
    {
        unordered_set<int> closestUsers;

        for (pair<int,unordered_set<int>> entry : twitterGraph)
        {
            if (entry.first == userId)
                continue; // Skip the same user
            double similarity = calculateJaccardSimilarity(twitterGraph[userId], entry.second);
            if (similarity >= threshold)
                closestUsers.insert(entry.first);
        }

        return closestUsers;
    }
};

int main() {
    auto start = high_resolution_clock::now();
    TwitterFollowersAnalyzer analyzer;
    analyzer.read_csv("twitter.csv");
    analyzer.heapSortFollowersCount();
    //analyzer.sortUsingSTL();
    analyzer.printFollowersCount();
    // analyzer.getSize();
    // analyzer.printAdjacencyList();
    analyzer.recommendUsers(214328887, 0.05);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    printf("Execution time: %d seconds\n",duration.count());
    return 0;
}
