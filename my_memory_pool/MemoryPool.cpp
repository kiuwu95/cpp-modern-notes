#include<iostream>
#include<vector>
#include<cassert>
#include<chrono>
#include<utility>
//算法
static inline std::size_t align_up(size_t n, size_t align) {
    return (n + (align - 1)) & ~(align - 1);
}

class MemoryPool {
private:
    size_t blocks_size;//小块内存的大小
    size_t blocks_per_page;//一页内存有多少块小块内存
    std::vector<void*> m_pages;//页的vector
    //空闲小块内存链表
    struct Node {
        Node* next;
    };
    Node* free_list;
    //将小块内存大小设定为能运行的正常值
    size_t adjust_block_size(const size_t& size) {
        if (size < sizeof(void*)) {
            return align_up(sizeof(void*), alignof(void*));
        }
        return align_up(size, alignof(void*));
    }
    //每次向系统申请一页内存，并把这一页内存的切成很多小块并把它们挂到空闲链表中
    void expand() {
        size_t pages_bytes = blocks_per_page * blocks_size;
        char* p = static_cast<char*>(::operator new[](pages_bytes));
        m_pages.push_back(p);

        for (int i = 0;i < blocks_per_page;i++) {
            char* add_blk = p + i * blocks_size;
            Node* add_node = reinterpret_cast<Node*>(add_blk);

            add_node->next = free_list;
            free_list = add_node;
        }
    }
public:
    //分配一小块内存
    void* allocate() {
        if (!free_list) {
            expand();
        }
        Node* head = free_list;
        free_list = head->next;
        return head;
    }
    //回收内存，归还小块内存，插入链表头部
    void deallocate(void* p) {
        if (!p)return;

        Node* head = static_cast<Node*>(p);
        head->next = free_list;
        free_list = head;
    }

    size_t BlocksSize() {
        return blocks_size;
    }
    size_t BlockPagesSize() {
        return blocks_per_page;
    }

    //析构时释放内存页
    ~MemoryPool() {
        for (auto& it : m_pages) {
            ::operator delete[](it);
        }
    }

    explicit MemoryPool(const size_t& block_size, const size_t& block_per_page = 1024) :blocks_per_page(block_per_page),
        free_list(nullptr), blocks_size(adjust_block_size(block_size)) {
    }

};

struct test {
    int x, y, z;

    static void* operator new(size_t n);
    static void operator delete(void* p) noexcept;
};

MemoryPool mp(8, 2048);
void* test::operator new(size_t n) {
    return mp.allocate();
}

void test::operator delete(void* p) noexcept {
    return mp.deallocate(p);
}

int main() {
    std::vector<test*> v;
    v.reserve(10000);

    auto before = std::chrono::system_clock::now();
    for (int i = 0;i < 10000;i++) {
        test* t = new test{ 1,2,3 };
        v.emplace_back(std::move(t));
    }

    for (auto it : v) {
        delete it;
    }
    auto after = std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(after - before);
    std::cout << duration.count() << "ms" << std::endl;
}