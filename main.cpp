#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace::std;
// ALL FUNCTION AND CLASS NAMES ARE ADAPTED FROM WIKIPEDIA OF IDA*
class Node
{
public:
    string state = "";
    Node * parent;
};
int distance(int m, int n) // finds distance between two cells
{
    if(n == 21) // E
        return 0;
    int diff = abs(m - n);
    if(diff == 4 && m % 2 == 0)
        return 2;
    return 4 - abs(diff - 4);
}
int hue(Node * node) // heuristic function: Manhattan Distance
{
    string s = node->state;
    int dis = 0; // Manhattan distance
    int n = 0; // actual digit
    for(int i = 0; i <= 2; i++)
    {
        n = s[i] - '0';
        dis += distance(i + 1, n);
    }
    n = s[3] - '0';
    dis += distance(8, n);
    if(s[4] != 'E')
    {
        n = s[4] - '0';
        if(n % 2 == 0)
            dis += 1;
        else
            dis += 2;
    }
    n = s[5] - '0';
    dis += distance(4, n);
    for(int i = 6; i <= 8; i++)
    {
        n = s[i] - '0';
        dis += distance(13 - i, n);
    }
    return dis;
}
int h(Node * node) // heuristic function: number of misplaced tiles; this heuristic function is implemented only to compare to slide's example
{
    int dis = 0;
    string s = node->state;
    if(s[0] != '1')
        dis++;
    if(s[1] != '2')
        dis++;
    if(s[2] != '3')
        dis++;
    if(s[3] != '8')
        dis++;
    if(s[5] != '4')
        dis++;
    if(s[6] != '7')
        dis++;
    if(s[7] != '6')
        dis++;
    if(s[8] != '5')
        dis++;
    return dis;
}
int is_goal(Node * node) // returns 1 if the node is a goal
{
    return node->state == "1238E4765";
    //       1 2 3
    // GOAL: 8 E 4
    //       7 6 5
}
Node* create_child(Node* node, string str) // returns a new child node with str state
{
    Node * child;
    child = new Node[1];
    child->parent = node;
    child->state = str;
    return child;
}
vector<Node*> successors(Node * node, vector<Node*> path) // returns the successors of the node
{
    string str = node->state;
    vector<Node*> succ;
    if(str[0] == 'E')
    {
    // case #1
        // O X -
        // - - -
        // - - -
        swap(str[0], str[1]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // O - -
        // X - -
        // - - -
        swap(str[0], str[3]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[1] == 'E')
    {
    // case #1
        // X O -
        // - - -
        // - - -
        swap(str[1], str[0]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - O X
        // - - -
        // - - -
        swap(str[1], str[2]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #3
        // - O -
        // - X -
        // - - -
        swap(str[1], str[4]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[2] == 'E')
    {
    // case #1
        // - X O
        // - - -
        // - - -
        swap(str[2], str[1]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - - O
        // - - X
        // - - -
        swap(str[2], str[5]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[3] == 'E')
    {
    // case #1
        // X - -
        // O - -
        // - - -
        swap(str[3], str[0]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - - -
        // O X -
        // - - -
        swap(str[3], str[4]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #3
        // - - -
        // O - -
        // X - -
        swap(str[3], str[6]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[4] == 'E')
    {
    // case #1
        // - X -
        // - O -
        // - - -
        swap(str[4], str[1]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - - -
        // X O -
        // - - -
        swap(str[4], str[3]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #3
        // - - -
        // - O X
        // - - -
        swap(str[4], str[5]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #4
        // - - -
        // - O -
        // - X -
        swap(str[4], str[7]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[5] == 'E')
    {
    // case #1
        // - - X
        // - - O
        // - - -
        swap(str[5], str[2]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - - -
        // - X O
        // - - -
        swap(str[5], str[4]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #3
        // - - -
        // - - O
        // - - X
        swap(str[5], str[8]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[6] == 'E')
    {
    // case #1
        // - - -
        // X - -
        // O - -
        swap(str[6], str[3]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - - -
        // - - -
        // O X -
        swap(str[6], str[7]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[7] == 'E')
    {
    // case #1
        // - - -
        // - X -
        // - O -
        swap(str[7], str[4]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - - -
        // - - -
        // X O -
        swap(str[7], str[6]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #3
        // - - -
        // - - -
        // - O X
        swap(str[7], str[8]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    else if(str[8] == 'E')
    {
    // case #1
        // - - -
        // - - X
        // - - O
        swap(str[8], str[5]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
        str = node->state;
    // case #2
        // - - -
        // - - -
        // - X O
        swap(str[8], str[7]);
        if(node->parent == nullptr || str != node->parent->state)
        {
            Node * child = create_child(node, str);
            vector<Node*>::iterator i;
            for( i = succ.begin(); i != succ.end(); i++)
            {
                if(hue(*i) > hue(child))
                    break;
            }
            succ.insert(i, child);
        }
    }
    return succ;
}
int IDA(vector<Node*> * path, int g, int bound)
{
    Node * node = (*path).back();
    int f = g + hue(node); // f(n) = g(n) + h(n)
    if(f > bound) // exceeds the limit
        return f;
    if(is_goal(node) == 1)
        return -1; // -1 means FOUND
    int min_value = 2147483647; // max possible value
    vector<Node*> v = successors(node, *path);
    for(vector<Node*>::iterator succ = v.begin(); succ != v.end(); succ++)
    {
        if(!(std::find((*path).begin(), (*path).end(), *succ) != (*path).end()))
        {
            (*path).push_back(*succ);
            int t = IDA( path, g + 1, bound);
            if(t == -1) // t is FOUND
                return -1;
            if(t < min_value)
                min_value = t;
            (*path).pop_back();
        }
    }
    return min_value;
}
int main()
{
    // create the root node
    Node * root;
    root = new Node[1];
    root->parent = nullptr;
    // get the initial state
    for(int i = 1; i <= 9; i++)
    {
        string cell = "";
        cin >> cell;
        root->state += cell;
    }
    int bound = hue(root);
    vector<Node*> * path;
    path = new vector<Node*>[1];
    (*path).push_back(root);
    int t = 0; // answer
    while(true)
    {
        t = IDA(path, 0, bound);
        if( t == -1) // FOUND
            break;
        bound = t; // update the bound
    }
    cout << bound;
}
