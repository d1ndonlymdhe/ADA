#include <iostream>
#include <vector>
#include "gettime.h"

using namespace std;

class BSTnode
{
public:
    int value;
    BSTnode *left = NULL;
    BSTnode *right = NULL;

    BSTnode(int value) { this->value = value; }

    void addChild(int v)
    {
        BSTnode *child = new BSTnode(v);
        addChild(child);
    }
    void addChild(BSTnode *child)
    {
        if (child)
        {
            if (child->value == this->value)
            {
                return;
            }
            if (child->value < this->value)
            {
                if (this->left)
                {
                    this->left->addChild(child);
                }
                else
                {
                    this->left = child;
                }
            }
            else
            {
                if (this->right)
                {
                    this->right->addChild(child);
                }
                else
                {
                    this->right = child;
                }
            }
        }
    }
    BSTnode *getMin()
    {
        if (this->left != NULL)
        {
            return this->left->getMin();
        }
        else
        {
            return this;
        }
    }
    BSTnode *getMax()
    {
        if (this->right)
        {
            return this->right->getMax();
        }
        else
        {
            return this;
        }
    }
    void deleteChild(int v)
    {
        BSTnode *node = search_iter(v);
        BSTnode *parent = getParent(node);
        if (node && parent)
        {
            // node is leaf
            if (node->left == NULL && node->right == NULL)
            {
                if (parent->right == node)
                {
                    parent->right = NULL;
                }
                else
                {
                    parent->left = NULL;
                }
                free(node);
                return;
            }
            // node has both left and right
            if (node->left != NULL && node->right != NULL)
            {
                BSTnode *minNode = node->right->getMin();
                BSTnode *minParent = this->getParent(minNode);
                if (minParent->left == minNode)
                {
                    minParent->left = NULL;
                }
                else
                {
                    minParent->right = NULL;
                }
                BSTnode *nodeRight = node->right == minNode ? NULL : node->right;
                BSTnode *nodeLeft = node->left == minNode ? NULL : node->left;
                if (parent->right == node)
                {
                    parent->right = NULL;
                }
                else
                {
                    parent->left = NULL;
                }
                minNode->addChild(nodeRight);
                minNode->addChild(nodeLeft);
                parent->addChild(minNode);
                free(node);
                return;
            }
            // node has only one child
            if (node->left == NULL || node->right == NULL)
            {
                BSTnode *nodeChild = node->left ? node->left : node->right;
                if (parent->right == node)
                {
                    parent->right = NULL;
                }
                else
                {
                    parent->left = NULL;
                }
                parent->addChild(nodeChild);
                free(node);
                return;
            }
        }
    }

    BSTnode *getParent(BSTnode *n)
    {
        if (n)
        {
            if (n == this)
            {
                return NULL;
            }
            if (this->left == n || this->right == n)
            {
                return this;
            }
            if (this->left)
            {
                BSTnode *checkLeft = this->left->getParent(n);
                if (checkLeft)
                {
                    return checkLeft;
                }
            }
            if (this->right)
            {
                BSTnode *checkRight = this->right->getParent(n);
                if (checkRight)
                {
                    return checkRight;
                }
            }
        }
        return NULL;
    }

    BSTnode *search(int v)
    {
        if (this->value == v)
        {
            return this;
        }
        if (v > this->value)
        {
            if (this->right)
            {
                BSTnode *rSearch = this->right->search(v);

                return rSearch;
            }
        }
        if (v < this->value)
        {
            if (this->left)
            {
                BSTnode *lSearch = this->left->search(v);

                return lSearch;
            }
        }
        return NULL;
    }

    BSTnode *search_iter(int v)
    {
        BSTnode *current = this;
        while (current != NULL)
        {
            if (current->value == v)
            {
                return current;
            }
            if (v > current->value)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return NULL;
    }

    int size(int initSize = 0)
    {
        int s = initSize + 1;
        if (this->left)
        {
            s = this->left->size(s);
        }
        if (this->right)
        {
            s = this->right->size(s);
        }
        return s;
    }
};

int main()
{
    vector<int> sizes;
    int start_size = 1000000;
    int increment = 500000;
    sizes.push_back(start_size);
    // srand(time(NULL));
    for (size_t i = 0; i < 4; i++)
    {
        sizes.push_back(sizes.back() + increment);
    }
    // insert random values
    for (size_t i = 0; i < sizes.size(); i++)
    {
        int size = sizes[i];
        BSTnode *root = new BSTnode(rand());
        long long time = getTime([&]()
                                 {
                                     for (size_t i = 0; i < size; i++)
                                     {
                                         root->addChild(rand());
                                     } });
        cout << "BST insert " << size << " nodes: " << time << "ns" << endl;
        time = getTime([&]()
                       {
                           for (size_t i = 0; i < size; i++)
                           {
                               root->search(rand());
                           } });
        cout << "BST search recursive " << size << " nodes: " << time << "ns" << endl;
        time = getTime([&]()
                       {
                           for (size_t i = 0; i < size; i++)
                           {
                               root->search_iter(rand());
                           } });
        cout << "BST search iter " << size << " nodes: " << time << "ns" << endl;
        time = getTime([&]()
                       {
                           for (size_t i = 0; i < size; i++)
                           {
                               root->deleteChild(rand());
                           } });
        cout << "BST delete " << size << " nodes: " << time << "ns" << endl;

        cout << "----------" << endl;
    }
}