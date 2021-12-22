#pragma once

#include <list>
#include <memory>

namespace task2 {
template<typename T>
class List {
    struct Node {
        explicit Node(T data) : data_{std::move(data)} {}
        static std::shared_ptr<Node> create(T data, std::shared_ptr<Node> prev = {}, std::shared_ptr<Node> next = {}) {
            auto node = std::make_shared<Node>(std::move(data));
            Node::connect(prev, node);
            Node::connect(node, next);
            return node;
        }
        static void connect(std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
            if (a) {
                a->next_ = b;
            }
            if (b) {
                b->prev_ = std::weak_ptr{a};
            }
        }

        T data_;
        std::weak_ptr<Node> prev_;
        std::shared_ptr<Node> next_;
    };

    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

    public:
        explicit Iterator(std::shared_ptr<Node> node) : node_{std::move(node)} {}

        std::shared_ptr<Node> node() const { return node_; }

        T& operator*() const { return node_->data_; }
        T* operator->() const { return &(node_->data_); }

        Iterator& operator++() {
            node_ = node_->next_;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            node_ = node_->next_;
            return tmp;
        }
        Iterator& operator--() {
            node_ = node_->prev_.lock();
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            node_ = node_->prev_;
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return node_ == other.node_;
        }
        bool operator!=(const Iterator& other) const {
            return node_ != other.node_;
        }

    private:
        std::shared_ptr<Node> node_;
    };

public:
    Iterator begin() { return Iterator{begin_}; }
    Iterator end() { return Iterator{nullptr}; }

    void insert(Iterator it, T data) {
        if (!begin_ && !end_.lock()) {
            begin_ = Node::create(std::move(data));
            end_ = std::weak_ptr{begin_};
            return;
        }
        if (it == end()) {
            end_ = std::weak_ptr{Node::create(std::move(data), end_.lock())};
            return;
        }
        if (it == begin()) {
            begin_ = Node::create(std::move(data), {}, begin_);
            return;
        }
        Node::create(std::move(data), it.node(), it.node()->next_);
    }

    void remove(Iterator it) {
        if (!begin_ && !end_.lock()) {
            throw std::runtime_error{"removing from empty list"};
        }
        if (it == end()) {
            throw std::runtime_error{"removing from end of the list"};
        }
        if (it.node() == end_.lock()) {
            end_ = std::weak_ptr{end_.lock()->prev_};
        }
        if (it == begin()) {
            begin_ = begin_->next_;
        }
        auto prev = it.node()->prev_;
        auto next = it.node()->next_;
        if (prev.lock()) {
            prev.lock()->next_ = next;
        }
        if (next) {
            next->prev_ = prev;
        }
    }

    template<typename Comparator>
    void sort(Comparator comparator) {
        auto [_begin, _end] = sort_impl(begin_, std::move(comparator));
        begin_ = _begin;
        end_ = _end;
    }

private:
    template<typename Comparator>
    std::pair<std::shared_ptr<Node>, std::weak_ptr<Node>> sort_impl(std::shared_ptr<Node> head, Comparator comparator) {
        if (head == nullptr || head->next_ == nullptr) {
            return {begin_, end_};
        }

        auto pivot = split(head);

        sort_impl(head, comparator);
        sort_impl(pivot, comparator);

        return merge(std::move(head), std::move(pivot), std::move(comparator));
    }

    std::shared_ptr<Node> split(std::shared_ptr<Node> source) {
        std::shared_ptr<Node> fast = source->next_;
        std::shared_ptr<Node> slow = source;
        while (fast != nullptr) {
            fast = fast->next_;
            if (fast != nullptr) {
                fast = fast->next_;
                slow = slow->next_;
            }
        }
        auto result = slow->next_;
        slow->next_ = nullptr;
        return result;
    }

    template<typename Comparator>
    std::pair<std::shared_ptr<Node>, std::weak_ptr<Node>> merge(std::shared_ptr<Node> head, std::shared_ptr<Node> pivot, Comparator comparator) {
        std::shared_ptr<Node> _begin;
        std::weak_ptr<Node> _end;

        std::shared_ptr<Node> node;
        while (head != nullptr || pivot != nullptr) {
            if (!pivot || (head && comparator(head->data_, pivot->data_))) {
                Node::connect(node, head);
                node = head;
                head = head->next_;
            } else {
                Node::connect(node, pivot);
                node = pivot;
                pivot = pivot->next_;
            }
            if (!_begin) {
                _begin = node;
            }
            _end = std::weak_ptr{node};
        }

        return {_begin, _end};
    }

private:
    std::shared_ptr<Node> begin_;
    std::weak_ptr<Node> end_;
};
}// namespace task2
