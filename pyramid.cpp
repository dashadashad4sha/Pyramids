#include <vector>
#include <print>  // 23
#include <iostream>
#include <optional>

using namespace std;

// indexation from 0
template <typename Item>
struct PriorityQueue
{
    vector<Item> queueBody;

    // size of the pyramid (n in Skiene)
    size_t size() const
    {
        return queueBody.size();
    }

    // returns true if the pyramid is empty, false otherwise
    bool empty() const
    {
        return queueBody.empty();
    }

    // swap elements in pyramid
    void swapElements(size_t index1, size_t index2) {
        swap(queueBody[index1], queueBody[index2]);
    }

    // parent's index if index is not 0, nullopt otherwise
    std::optional<size_t> pq_parent(size_t index) const
    {
        if (index == 0 or index >= queueBody.size())
            return nullopt;
        return (index - 1) / 2;
    }

    // left child
    size_t pq_young_child(size_t index) const
    {
        return index * 2 + 1;
    }

    // right child
    size_t pq_old_child(size_t index) const
    {
        return index * 2 + 2;
    }

    // sorting
    void bubble_up(size_t index)
    {
        auto parent_index = pq_parent(index);
        if (parent_index.has_value() && queueBody[parent_index.value()] > queueBody[index])
        {
            swapElements(index, parent_index.value());
            bubble_up(parent_index.value());
        }
    }

    void bubble_up_no_reqursion(size_t index)
    {
        while (index > 0)
        {
            size_t parent_index = (index - 1) / 2;
            if (queueBody[parent_index] <= queueBody[index])
                break;
            swapElements(index, parent_index);
            index = parent_index;
        }
    }

    // inser element
    void pq_insert(Item element)
    {
        // there is no need to check for excess size due to using vector
        queueBody.push_back(element);
        // no stack overflowed version
        // queueBody.bubble_up(queueBody.size() - 1);
        bubble_up_no_reqursion(queueBody.size() - 1);
    }

    // reqursion algorythm
    void bubble_down(size_t index)
    {
        size_t c = pq_young_child(index);
        size_t min_index = index;

        for (size_t i = 0; i <= 1; i++)
        {
            if ((c + i) < queueBody.size())
            {
                if (queueBody[min_index] > queueBody[c + i])
                    min_index = c + i;
            }
        }
        if (min_index != index)
        {
            swapElements(index, min_index);
            bubble_down(min_index);
        }
    }

    // no reqursion algorythm
    void bubble_down_no_reqursion(size_t index)
    {
        while (index < queueBody.size())
        {
            size_t min_index = index;
            size_t c = pq_young_child(index);

            for (size_t i = 0; i <= 1; i++)
            {
                if ((c + i) < queueBody.size())
                {
                    if (queueBody[min_index] > queueBody[c + i])
                        min_index = c + i;
                }
            }
            if (min_index == index)
                break;

            swapElements(index, min_index);
            index = min_index;
        }
    }


    void make_heap_fast(vector<Item> elements)
    {
        queueBody = elements;
        for (int i = queueBody.size() / 2 - 1; i >= 0; i--)
        {
            // bubble_down(i);
            bubble_down_no_reqursion(i);
        }
    }

    // pretty print pyramid
    void print()
    {
        size_t i = 0, power = 0;

        println("\nPyramid:");
        while (i < queueBody.size())
        {
            for (size_t j = 0; j < pow(2, power) && i < queueBody.size(); ++j)
            {
                cout << queueBody[i] << " ";
                i++;
            }
            println();
            power++;
        }
    }
};

void demo_pyramid()
{
    PriorityQueue<int> pq;

    pq.pq_insert(10);
    pq.pq_insert(5);
    pq.pq_insert(15);
    pq.pq_insert(3);
    pq.pq_insert(7);
    pq.pq_insert(6);
    pq.pq_insert(2);
    pq.pq_insert(4);
    pq.pq_insert(14);
    pq.pq_insert(16);

    pq.print();

    PriorityQueue<int> fast;
    fast.make_heap_fast({ 4, 5, 7, 5, 2, 1, 4, 8, 12, 11, 10, 4 });
    fast.print();

}


int main()
{
    demo_pyramid();
    return 0;
}