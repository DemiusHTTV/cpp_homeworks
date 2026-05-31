#ifndef LINELIST_CPP
#define LINELIST_CPP
#include "LineList.h"

template<class T>
LineListElem<T>::LineListElem(const T& adata, LineListElem<T>* anext) {
    data = adata;
    next = anext;
}

template<class T>
const T& LineListElem<T>::getData() const {
    return data;
}

template<class T>
LineListElem<T>* LineListElem<T>::getNext() {
    return next;
}


template<class T>
LineList<T>::LineList() {
    start = 0;
    tail = 0;
}

template<class T>
LineList<T>::~LineList() {
    if (start) {
        tail->next = 0;
        while (start) {
            LineListElem<T>* temp = start->next;
            delete start;
            start = temp;
        }
    }
}

template<class T>
LineListElem<T>* LineList<T>::getStart() {
    return start;
}

template<class T>
LineListElem<T>* LineList<T>::getTail() {
    return tail;
}

template<class T>
void LineList<T>::insertFirst(const T& data) {
    if (!start) {
        start = new LineListElem<T>(data, nullptr);
        start->next = start;
        tail = start;
    } else {
        LineListElem<T>* second = start;
        start = new LineListElem<T>(data, second);
        tail->next = start;
    }
}

template<class T>
void LineList<T>::deleteFirst() {
    if (start) {
        if (start == tail) {
            delete start;
            start = 0;
            tail = 0;
        } else {
            LineListElem<T>* temp = start->next;
            delete start;
            start = temp;
            tail->next = start;
        }
    } else {
        throw LineListException();
    }
}

template<class T>
void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data) {
    if (ptr) {
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
        if (ptr == tail) {
            tail = ptr->next;
        }
    }
}

template<class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr) {
    if (ptr && ptr->next) {
        LineListElem<T>* toDelete = ptr->next;
        if (toDelete == start) {
            deleteFirst();
            return;
        }
        ptr->next = toDelete->next;
        if (toDelete == tail) {
            tail = ptr;
        }
        delete toDelete;
    } else {
        throw LineListException();
    }
}

template<class T>
std::ostream& operator<<(std::ostream& out, LineList<T>& list) {
    LineListElem<T>* ptr = list.start;
    if (!ptr) {
        out << "EMPTY";
    } else {
        while (ptr) {
            out << ptr->getData() << " ";
            ptr = ptr->getNext();
        }
    }
    return out;
}

#endif