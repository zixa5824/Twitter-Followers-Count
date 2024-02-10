import time
class MaxHeap:
    def __init__(self):
        self.heap = []

    def push(self, key, value):
        self.heap.append((key, value))
        self._heapify_up()

    def pop(self):
        if not self.heap:
            raise IndexError("pop from an empty heap")
        if len(self.heap) == 1:
            return self.heap.pop()[0]

        root_key, root_value = self.heap[0]
        self.heap[0] = self.heap.pop()
        self._heapify_down()
        return root_key

    def _heapify_up(self):
        current_index = len(self.heap) - 1
        while current_index > 0:
            parent_index = (current_index - 1) // 2
            if self.heap[parent_index][1] < self.heap[current_index][1]:
                self.heap[parent_index], self.heap[current_index] = self.heap[current_index], self.heap[parent_index]
                current_index = parent_index
            else:
                break

    def _heapify_down(self):
        current_index = 0
        while True:
            left_child_index = 2 * current_index + 1
            right_child_index = 2 * current_index + 2
            max_index = current_index

            if left_child_index < len(self.heap) and self.heap[left_child_index][1] > self.heap[max_index][1]:
                max_index = left_child_index

            if right_child_index < len(self.heap) and self.heap[right_child_index][1] > self.heap[max_index][1]:
                max_index = right_child_index

            if max_index != current_index:
                self.heap[current_index], self.heap[max_index] = self.heap[max_index], self.heap[current_index]
                current_index = max_index
            else:
                break

def Closest_Group(id,accounts,threshold):
    if id in accounts:
        target_acc_followers = accounts[id][1]
    else:
         raise ValueError("ID Not Found")
    target_dic_followers = {key:1 for key in target_acc_followers}
    close_group=[]
    for key,value in accounts.items():
        followers = value[1]
        cnt=0
        temp_dic=dict(target_dic_followers)
        for i in followers:
            if i in temp_dic:
                temp_dic[i] = temp_dic[i] + 1
                cnt +=1
            else:
                temp_dic[i] = 1
        if cnt >= threshold:
            close_group.append(key)
    return close_group

start_time = time.time()
file = open("twitter.csv", "r")
accounts = {}
for x in set(file):
    two_acc = x.split(",")
    first_acc, sec_acc = two_acc[0] , two_acc[1][:-1]
    if sec_acc in accounts :
      accounts[sec_acc][0] = accounts[sec_acc][0] + 1
      accounts[sec_acc][1].append(first_acc)
    else:
      l = [1,[first_acc]] 
      accounts[sec_acc] = l

max_heap = MaxHeap()

# Populate the max heap with the dictionary items
for key, value in accounts.items():
    max_heap.push(key, value[0])


#show_followers_ids = input("[^_^] The result is finished, the program will show you followers number for each accout. \n[!] Do you want to show followers IDs [N/y]? ")
# Pop elements from the max heap in descending order of values
#out_file = open("C:/Users/ahmed/OneDrive/Desktop/Desktop/MASTER/Analysis&Design of Algorithms/Project/Result.txt", "w")
cnt =0
while len(max_heap.heap) > 0 and cnt < 10:
    cnt+=1
    max_key = max_heap.pop()
    print(f"Account: {max_key}, Followers Number: {accounts[max_key][0]}")
    #out_file.write(f"Account: {max_key}, Followers Number: {accounts[max_key][0]}\n")
    #if show_followers_ids.lower().strip() == "y" or show_followers_ids.lower().strip() == "yes":
        #print(f"Followers IDs: {accounts[max_key][1]}")
        #out_file.write(f"Followers IDs: {accounts[max_key][1]}\n")
#my_id = input("[!] Enter your ID to recommend new friends: ")
print(Closest_Group('214328887',accounts,50))
end_time = time.time()
total_time = end_time - start_time
print(f"[!] The entire operation took just {total_time} seconds.")
file.close()
#out_file.close()

#Bouns Function






