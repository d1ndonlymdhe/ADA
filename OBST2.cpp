#include <iostream>
#include <vector>
#include <climits>
using namespace std;
typedef pair<int, int> node;
class BSTnode
{
public:
    int value;
    BSTnode *left = NULL;
    BSTnode *right = NULL;

    BSTnode(int value) { this->value = value; }
    BSTnode(int children[], int children_size)
    {
        if (children_size > 0)
        {
            value = children[0];
            for (int i = 1; i < children_size; i++)
            {
                this->addChild(new BSTnode(children[i]));
            }
        }
    }
    BSTnode(vector<int> children)
    {
        if (children.size() > 0)
        {
            value = children[0];
            for (int i = 1; i < children.size(); i++)
            {
                this->addChild(new BSTnode(children[i]));
            }
        }
    }
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
        if (this->left)
        {
            return this->left->getMin();
        }
        else
        {
            return this;
        }
    }
    // dont copy
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
        BSTnode *node = search(v);
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
            }
        }
    }
    void preorder()
    {
        cout << this->value << endl;
        if (this->left)
        {
            this->left->preorder();
        }
        if (this->right)
        {
            this->right->preorder();
        }
    }
    void inorder()
    {
        if (this->left)
        {
            this->left->inorder();
        }
        cout << this->value << endl;
        if (this->right)
        {
            this->right->inorder();
        }
    }
    void postorder()
    {
        if (this->left)
        {
            this->left->postorder();
        }
        if (this->right)
        {
            this->right->postorder();
        }
        cout << this->value << endl;
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
    // dont copy
    BSTnode *getSibling(BSTnode *n)
    {
        if (n)
        {
            if (n == this)
            {
                return NULL;
            }
            BSTnode *parent = this->getParent(n);
            if (parent)
            {
                if (parent->left == n)
                {
                    return parent->right;
                }
                return parent->left;
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

int vectorSum(vector<int> freq, int i, int j)
{
    int sum = 0;
    for (int k = i; k <= j; k++)
    {
        sum += freq[k];
    }
    return sum;
}

bool vectorHas(vector<int> v, int n)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == n)
        {
            return true;
        }
    }
    return false;
}

vector<int> vectorRev(vector<int> v)
{
    vector<int> rev;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        rev.push_back(v[i]);
    }
    return rev;
}

int min_cost(vector<int> freq)
{
    int n = freq.size();
    vector<vector<int>> cost(freq.size(), vector<int>(freq.size(), 0));

    for (int i = 0; i < n; i++)
        cost[i][i] = freq[i];
    for (int i = 1; i < n; i++)
    {
        int start = 0;
        for (int end = i; end < n; end++)
        {
            int sum = vectorSum(freq, start, end);
            cost[start][end] = INT_MAX;
            for (int r = start; r <= end; r++)
            {
                int left = r == start ? 0 : cost[start][r - 1];
                int right = r == end ? 0 : cost[r + 1][end];
                int total = sum + left + right;
                if (total < cost[start][end])
                {
                    cost[start][end] = total;
                }
            }
            start++;
        }
    }
    return cost[0][n - 1];
}

BSTnode *getBST(vector<int> keys, vector<vector<node>> cost, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }
    int idx = cost[start][end].second;
    BSTnode *root = new BSTnode(keys[idx]);
    BSTnode *left = getBST(keys, cost, start, idx - 1);
    BSTnode *right = getBST(keys, cost, idx + 1, end);
    root->left = left;
    root->right = right;
    return root;
}

BSTnode *min_cost_tree(vector<int> freq, vector<int> keys)
{
    vector<vector<node>> cost(freq.size(), vector<node>(freq.size(), node(0, 0)));
    vector<int> included = {};
    for (int i = 0; i < freq.size(); i++)
    {
        cost[i][i] = node(freq[i], i);
    }

    int n = freq.size();
    for (int i = 1; i < n; i++)
    {
        int start = 0;
        for (int end = i; end < n; end++)
        {
            int sum = vectorSum(freq, start, end);
            cost[start][end] = node(INT_MAX, 0);
            for (int r = start; r <= end; r++)
            {
                int left = r == start ? 0 : cost[start][r - 1].first;
                int right = r == end ? 0 : cost[r + 1][end].first;
                int total = sum + left + right;
                if (total < cost[start][end].first)
                {
                    cost[start][end] = node(total, r);
                }
            }
            start++;
        }
    }

    BSTnode *head = getBST(keys, cost, 0, n - 1);

    return head;
}

int main()
{
    vector<int> freq = {4, 2, 6, 3};
    vector<vector<int>> cost(freq.size(), vector<int>(freq.size(), 0));
    vector<int> root;
    vector<int> keys = {10, 20, 30, 40};
    for (int i = 0; i < freq.size(); i++)
    {
        cost[i][i] = freq[i];
    }
    // cout << min_cost(freq) << endl;
    BSTnode *head = min_cost_tree(freq, keys);
    return 0;
}
