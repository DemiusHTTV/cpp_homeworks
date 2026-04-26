#pragma once

#include <exception>
#include <ostream>

template<class T>
class LineList;

class LineListException final : public std::exception {
public:
    const char* what() const noexcept override { return "LineList error"; }
};

template<class T>
class LineListElem {
    T data;
    LineListElem<T>* next;

public:
    LineListElem(const T& adata, LineListElem<T>* anext) : data(adata), next(anext) {}

    const T& getData() const { return data; }
    LineListElem<T>* getNext() { return next; }
    const LineListElem<T>* getNext() const { return next; }

    friend class LineList<T>;
};

template<class T>
class LineList {
    LineListElem<T>* start;
    LineListElem<T>* tail;

    LineList(const LineList&) = delete;
    LineList& operator=(const LineList&) = delete;

public:
    LineList() : start(nullptr), tail(nullptr) {}

    ~LineList() {
        if (!start) return;
        tail->next = nullptr; // break the ring
        while (start) {
            LineListElem<T>* temp = start->next;
            delete start;
            start = temp;
        }
        tail = nullptr;
    }

    LineListElem<T>* getStart() { return start; }
    LineListElem<T>* getTail() { return tail; }

    void insertFirst(const T& data) {
        if (!start) {
            start = new LineListElem<T>(data, nullptr);
            start->next = start;
            tail = start;
        } else {
            LineListElem<T>* oldStart = start;
            start = new LineListElem<T>(data, oldStart);
            tail->next = start;
        }
    }

    void deleteFirst() {
        if (!start) throw LineListException();

        if (start == tail) {
            delete start;
            start = nullptr;
            tail = nullptr;
            return;
        }

        LineListElem<T>* newStart = start->next;
        delete start;
        start = newStart;
        tail->next = start;
    }

    void insertAfter(LineListElem<T>* ptr, const T& data) {
        if (!ptr) return;
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
        if (ptr == tail) tail = ptr->next;
    }

    void deleteAfter(LineListElem<T>* ptr) {
        if (!ptr || !ptr->next) throw LineListException();

        LineListElem<T>* toDelete = ptr->next;
        if (toDelete == start) {
            deleteFirst();
            return;
        }

        ptr->next = toDelete->next;
        if (toDelete == tail) tail = ptr;
        delete toDelete;
    }

    template<class U>
    friend std::ostream& operator<<(std::ostream& out, const LineList<U>& list);
};

template<class T>
std::ostream& operator<<(std::ostream& out, const LineList<T>& list) {
    LineListElem<T>* ptr = list.start;
    if (!ptr) {
        out << "EMPTY";
        return out;
    }

    LineListElem<T>* first = ptr;
    do {
        out << ptr->getData() << ' ';
        ptr = ptr->getNext();
    } while (ptr && ptr != first);

    return out;
}
