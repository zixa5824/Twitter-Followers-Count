```
CSC 114 Algorithms Analysis and Design
```
# Algorithm’s Project

## Twitter Followers Project

## In this project, you are given a comma-separated file to represent some Twitter users and

the users they follow. The file name is “twitter.csv”. Each row represents a certain user’s id
and the id of another user he/she follows.

e.g.

```
1,2 //user with id = 1 follows the user with id = 2
2,5 //user with id = 2 follows the user with id = 5
3,5 //user with id = 3 follows the user with id = 5
1,6 //user with id = 1 follows the user with id = 6
```
## You are required to make a program that stores this data in a suitable data structure that

helps your program to retrieve the Top-influencer that has the highest number of followers,
when required, and then the next Top-influencer and so on.

Also, you have to support a complexity analysis illustration to your program’s algorithm in
any illustration form; a piece of paper, presentation slides, ... etc.

## As a bonus question, you may take a Twitter account id from the user and calculate its

closest group of Twitter users to recommend as a new friend. Closest means they have at
least a threshold number of Twitter accounts in common. One of your responsibilities in this
bonus task is to determine this threshold.

The attached dataset contains 2,420,766 different following states (edges) and around
81,000 different Twitter accounts.

# Twitter Followers

**Complexity Analysis:**

1. **read_csv** Method:
    - **Time Complexity:**
       - Reading the CSV file involves iterating through each line. The time complexity
          here is linear, O(n), where 'n' is the number of lines in the CSV file.
    - **Space Complexity:**
       - The space complexity is determined by the size of the **twitterGraph** and
          **followersCount** data structures, both of which grow based on the data in the CSV
          file. It's O(N + E), where 'N' is the number of unique Twitter users and 'E' is the
          total number of follower relationships.
2. **heapSortFollowersCount** Method:
    - **Time Complexity:**
       - The heap sort operation performs a max heap construction followed by 'n'
          removals (swaps and heapifications). It has a time complexity of O(n log n),
          where 'n' is the number of elements in **followersCount**.
    - **Space Complexity:**
       - The heap sort in-place method has a space complexity of O(1) as it sorts the
          elements in the same array ( **followersCount** ) without using additional space
          proportional to the input size.
3. **printFollowersCount** Method:
    - **Time Complexity:**
       - The loop to print the top 'n' influencers has a time complexity of O(n), where 'n'
          is the input provided by the user.
    - **Space Complexity:**
       - The space complexity is O(1) as there are no additional data structures created.


Overall:

- **Time Complexity:**
    - The dominant operations are the heap sort (O(n log n)) and reading the CSV file
       (O(n)). Thus, the overall time complexity is O(n log n) due to the sorting
       operation.
- **Space Complexity:**
    - The space complexity is primarily determined by the size of the **twitterGraph** and
       **followersCount** data structures, making it O(N + E).

This analysis provides an overview of the time and space complexities across the main
operations in the program.

I managed to achieve 5 seconds only on the execution of the code and that’s huge because the
data is too big.

# Bonus Task Complexity Analysis

I implemented Jaccard Similarity between the requested user and the whole graph with a user
input threshold.

**Creating Sets for Each User**

- **Time Complexity:** O(N * M)
    - N: Total number of users
    - M: Average number of followers per user


- **Explanation:**
    - For each user, we iterate through their list of followers to create a set of
       followers.
    - This involves traversing each user's follower list (which on average contains M
       followers) and inserting each follower into a set.
    - This step is repeated for each of the N users.

**Calculating Jaccard Similarity**

- **Time Complexity:** O(N^2 * K)
    - N: Total number of users
    - K: Average number of followers among users
- **Explanation:**
    - For each pair of users (there are N^2 pairs in total), we calculate the Jaccard
       similarity.
    - To compute Jaccard similarity between two users, we perform set operations
       (intersection and union).
    - These set operations involve comparing sets, which have an average size of K
       (average number of followers).
    - This step repeats for each pair of users.

**Overall Complexity:**

- The total time complexity can be approximated as O(N * M + N^2 * K).
- Space complexity involves the storage of user followers in sets, which is also O(N * M).


# Intuition

I implemented **adjacency list** for the twitter dataset so that I can deal with it as a graph. The
best implementation for this adjacency list is **unordered maps** with an integer as a **key** and an
**unordered set** as a **value.**

**Unordered maps** provide fast average lookup **O(1)** , insertion, and deletion times as it acts as a
hash table using a very good hash function that doesn’t in average produce many collisions.

**Unordered sets** are similar to unordered maps, but it stores unique keys rather than key-value
pairs. That’s why I used it to store followers as you can’t follow the same person twice in Twitter
(X), so it ignores the duplicates with **O(1)**.

If I didn’t include unordered sets we would have reached to a **O(n)** if we want to remove
duplicates from our data, if there are many ones. ( **This assumes that the hash function of the
unordered set provides a good distribution of keys, resulting in constant-time access on
average).**

**Heap sort** provide the best average case time O(n log(n)) and in-place sorting so O(1) space
complexity. That’s why I used it to be efficient in memory usage.

In **BONUS TASK,** Jaccard similarity is a suitable measure for recommending Twitter users
because it quantifies the similarity between sets. Users' follower lists can be represented as
sets, where the set elements are the followers of each user. I can set a threshold for similarity to
recommend users who share a certain percentage of followers. This threshold can be adjusted
based on the desired level of similarity.

For two sets, _A_ and _B_ , the Jaccard similarity coefficient _J_ ( _A_ , _B_ ) is calculated as:

_J_ ( _A_ , _B_ )=
∣𝐴∪𝐵∣
∣𝐴∩𝐵∣^

In this formula:

- | _A_ ∩ _B_ ∣ represents the cardinality (number of elements) of the intersection of sets _A_ and
    _B_.
- ∣ _A_ ∪ _B_ ∣ represents the cardinality of the union of sets _A_ and _B_.

The Jaccard similarity coefficient always ranges between 0 and 1, where:

- 0 indicates no intersection between sets (completely dissimilar).
- 1 indicates that the sets are identical (completely similar).




