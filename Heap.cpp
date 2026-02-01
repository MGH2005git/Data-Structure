// Mobin Ghorbani 40332360
// December 3, 2025
#include <iostream>
#include <vector>
#include <algorithm> // swap

class MaxHeap {
    std::vector<int> heap;
public:

    void heapify(){
        int len = heap.size();
        if(len <= 1) return;
        for (int i = len / 2 - 1; i >= 0; --i) {
            sub_heapify(i);
        }
    }

    void sub_heapify(int root_index){
        int len = heap.size();
        if(root_index >= len) return;

        int left = 2 * root_index + 1;
        int right = 2 * root_index + 2;

        // Find which child is largest
        int largest = root_index;
        if(left < len && heap[left] > heap[largest])
            largest = left;
        if(right < len && heap[right] > heap[largest])
            largest = right;

        if(largest != root_index) {
            std::swap(heap[root_index], heap[largest]);
            sub_heapify(largest);
        }
    }

    void up_heapify(int index){
        int len = heap.size();
        if(len <= 1) return;
        if(index <= 0) return;
        int parent = (index - 1) / 2;
        if(heap[index] > heap[parent]){
            std::swap(heap[index], heap[parent]);
            up_heapify(parent);
        }
    }

    void down_heapify(int index){
        int len = heap.size();
        if(len <= 1) return;
        if(index >= len) return;

        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if(left < len && heap[left] > heap[largest])
            largest = left;
        if(right < len && heap[right] > heap[largest])
            largest = right;

        if (largest != index){
            std::swap(heap[largest], heap[index]);
            down_heapify(largest);
        }
    }

    void insert(int data){
        int len = heap.size();
        heap.push_back(data);
        if(len <= 0) return;
        up_heapify(len);
    }

    int get_max(void){
        if(heap.size() == 0) return 0;
        return heap[0];
    }

    void pop(){
        if(heap.size() == 0) return;
        int len = heap.size();
        std::swap(heap[0], heap[len - 1]);
        heap.pop_back();
        down_heapify(0);
    }

    // Helper methods for testing
    void print() {
        for (int num : heap) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int size() {
        return heap.size();
    }
};
