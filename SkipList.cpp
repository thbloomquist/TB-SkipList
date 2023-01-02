//
//  SkipList.cpp
//

#include "SkipList.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
// TODO: constructor
template<class T>
SkipList<T>::SkipList() {
    head = new Node<T>(T(), maxHeight);
    height = 1;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
// TODO: destructor
template<class T>
SkipList<T>::~SkipList() {
    makeEmpty();
    delete head;
};
#endif

/* **************************************************************** */

#if FIND || ALL
// TODO: find() method
template<class T>
bool SkipList<T>::find(const T &x) const {
    Node<T> *cNode = head;

    for (int i = height - 1; i >= 0; i--) {
        while (cNode->next[i] != nullptr && cNode->next[i]->data < x) {
            cNode = cNode->next[i];
        }
    }
    cNode = cNode->next[0];
    if (cNode != nullptr) {
        if (cNode->data == x) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
#endif

/* **************************************************************** */

#if INSERT || ALL
// TODO: insert() method
template<class T>
void SkipList<T>::insert(const T &x) {
    Node<T> *nNode = head;
    Node<T> *update[maxHeight];
    for (int i = height-1; i >= 0; i--) {
        while (nNode->next[i] != nullptr && nNode->next[i]->data < x) {
            nNode = nNode->next[i];
        }
        update[i] = nNode;
    }
        nNode = nNode->next[0];
        if(nNode != nullptr && nNode->data == x) {
            nNode->data = x;
        } else {
            int nLevel = randomLevel();
            if(nLevel > height) {
                for(int a = height; a < nLevel; a++) {
                    update[a] = head;
                }
                height = nLevel;
            }
            nNode = new Node<T>(x, nLevel);
            for(int i = 0; i <= nLevel-1; i++) {
                nNode->next[i] = update[i]->next[i];
                update[i]->next[i] = nNode;
            }
        }
}
#endif


/* **************************************************************** */

#if REMOVE || ALL
// TODO: remove() method
template <class T>
void SkipList<T>::remove(const T &x) {
    Node<T> *cNode = head;
    Node<T> *update[maxHeight];
    for (int i = height - 1; i >= 0; i--) {
        while (cNode->next[i] != nullptr && cNode->next[i]->data < x) {
            cNode = cNode->next[i];
        }
        update[i] = cNode;
    }
    cNode = cNode->next[0];
    if(cNode != nullptr && cNode->data == x) {
        for(int i = 0; i <= height-1; i++) {
            if(update[i]->next[i] != cNode) {
                break;
            }
            update[i]->next[i] = cNode->next[i];
        }
        delete cNode;
        cNode = head;
        while(height > 0 && head->next[height-1] == nullptr) {
            height--;
        }
    }
}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty() method
template <class T>
bool SkipList<T>::isEmpty() const {
    return head->next[0] == nullptr;
}
#endif

/* **************************************************************** */

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
template <class T>
void SkipList<T>::makeEmpty() {
    if(!isEmpty()) {
        Node<T> *cNode = head->next[0];
        while(head->next[0] != nullptr) {
            Node<T> *iNode = cNode->next[0];
            remove(cNode->data);
            cNode = iNode;
        }
        height = 1;
    }
}
#endif

/* **************************************************************** */

#if RANDOMLEVEL || ALL
// TODO: randomLevel() method
template <class T>
int SkipList<T>::randomLevel() {
    int level = 1;
    while(getRandomNumber() < 0.5 && level <= height && level < maxHeight) {
        level++;
    }
    return level;


}
#endif

/* **************************************************************** */



/* **************************************************************** */
// Do NOT modify anything below this line
/* **************************************************************** */

#ifndef BUILD_LIB
// random number generator
template <class T>
double SkipList<T>::getRandomNumber()
{
    static int i = 0;
    static double a[10] = {0.32945,0.15923,0.12982,0.16250,0.36537,0.64072,0.27597,0.83957,0.75531,0.22502};
    
    return a[(i++)%10];
}


// printList() method
template <class T>
void SkipList<T>::printList()
{
    Node<T> *n = head;
    
    if (isEmpty())
    {
        std::cout << "Empty List" << std::endl;
    } else {
        while(n->next[0] != nullptr)
        {
            n = n->next[0];
            // Print node data
            std::cout << "Node " << n->data << " height " << n->height << ": ";
            
            // Print levels
            for (int i=(n->height - 1); i >= 0; i--) {
                std::cout << "Level " << i << " -> ";
                if (n->next[i] != nullptr) {
                    std::cout << n->next[i]->data;
                } else {
                    std::cout << "nullptr";
                }
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
#endif

template class SkipList<int>;


