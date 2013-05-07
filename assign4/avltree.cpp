#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "../assign3/list.h"
using namespace std;
template <typename T> class AVL
{
public:
    class TreeNode
    {
    public:
        T item;
        TreeNode* left;
        TreeNode* right;
        int height;

        TreeNode(T item)
        {
            this->item = item;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }
    };

    TreeNode* root;
    int size;

    AVL() : root(NULL), size(0) {}
    ~AVL() { this->clear(); }

    int get_height(TreeNode* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        else
        {
            return node->height;
        }
    }

    TreeNode* set_height(TreeNode * node)
    {
        int left = this->get_height(node->left);
        int right = this->get_height(node->right);
        node->height = (std::max(left, right)) + 1;
        return node;
    }

    T get_item(TreeNode* node)
    {
        if (node == NULL)
        {
            return "NULL";
        }
        else
        {
            return node->item;
        }
    }
    void clear()
    {
        if (this->root != NULL)
        {
            this->binary_clear(this->root);
        }
        this->root = NULL;
        this->size = 0;
    }

    void insert(const T item)
    {
        if (this->find(item))
            return;
        if (this->size == 0)
        {
            this->root = new TreeNode(item);
            this->size++;
        }
        else
        {
            this->root = this->binary_insert(this->root, item);
        }
    }

    void remove(const T item)
    {
        if (!this->size == 0)
        {
            this->root = binary_remove(this->root, item);
        }
    }

    bool find(const T item)
    {
        if (this->root != NULL)
        {
            return this->binary_find(this->root, item);
        }
        return false;
    }

std::string print (std::string sort_order)
  {
    
    if (this->size == 0) 
    {
        return ""; 
    }
    List<TreeNode*> current_level;
    List<TreeNode*> next_level;
    List<TreeNode*> temp;
    List<std::string> ordered;
    current_level.push_front(this->root);
  
    while (!current_level.empty())
    {
        TreeNode *node = current_level.pop_front(); 
        if (node != NULL)
        {
            stringstream ss;
            ss << " " << node->item << "(" << node->height << ")"; 
            ordered.push_back(ss.str());
            if (node->left != NULL)
                next_level.push_front(node->left);
            if (node->right != NULL)
                next_level.push_front(node->right);
        }
        if (current_level.empty())
        {
            temp = current_level;
            current_level = next_level;
            next_level = temp;
        }
    }
    ordered.sort(sort_order);
    std::stringstream done;
    while (!ordered.empty())
    {
        done << ordered.pop_front() << std::endl;
    }
    std::string s = done.str();
    return s;
  }

  std::string print ()
  {
    std::stringstream ss;
    if (this->size == 0) 
    {
        string s = ss.str();
        return s; 
    }
    ss << endl << "level 0:";

    List<TreeNode*> current_level;
    List<TreeNode*> next_level;
    List<TreeNode*> temp;
    current_level.push_front(this->root);
  
    int i = 0;
    int printed = 0;
    while (!current_level.empty())
    {
        TreeNode  *node = current_level.pop_front(); 
        if (node != NULL)
        {
            ss << " " << node->item << "(" << node->height << ")"; 
            printed++;
            if (node->left != NULL)
              next_level.push_front(node->left); 
            if (node->right != NULL)
              next_level.push_front(node->right);
        }
        if ((printed >= 8) && (!current_level.empty()) && (i <= root->height))
        {
            ss << endl;
            ss << "level " << i << ":";
            printed = 0;
        }
        if (current_level.empty())
        {
            if ((!next_level.empty()) && (i < root->height))
            {
                ss << endl;
                ss << "level " << ++i << ":";
                printed = 0;
            }
            temp = current_level;
            current_level = next_level;
            next_level = temp;
        }
    }

    std::string s = ss.str();
    return s;
  }

private:
    TreeNode* single_right_rotate(TreeNode* node)
    {
        TreeNode* ptr = node->left;
        node->left = ptr->right;
        ptr->right = node;
        node = set_height(node);
        ptr = set_height(ptr);
        return ptr;
    }

    TreeNode* single_left_rotate(TreeNode* node)
    {
        TreeNode* ptr = node->right;
        node->right = ptr->left;
        ptr->left = node;
        node = set_height(node);
        ptr = set_height(ptr);
        return ptr;
    }

    TreeNode* double_right_rotate(TreeNode* node)
    {
        node->left = single_left_rotate(node->left);
        node = single_right_rotate(node);
        return node;
    }

    TreeNode* double_left_rotate(TreeNode* node)
    {
        node->right = single_right_rotate(node->right);
        node = single_left_rotate(node);
        return node;
    }

    TreeNode* binary_insert(TreeNode* node, T item)
    {
        if (node == NULL)
        {
            this->size++;
            return new TreeNode(item);
        }
        else if (node->item == item)
        {
            return node;
        }
        else if (node->item < item)
        {
            node->right = this->binary_insert(node->right, item);
        }
        else
        {
            node->left = this->binary_insert(node->left, item);
        }
        node = this->set_height(node);
        node = this->balance(node);
        return node;
    }

    TreeNode* balance(TreeNode* node)
    {
        if (this->get_height(node->left) - this->get_height(node->right) > 1)
        {
            node = this->balance_right(node);
        }
        else if (this->get_height(node->right) - this->get_height(node->left) > 1)
        {
            node = this->balance_left(node);
        }
        return node;
    }

    TreeNode* balance_left(TreeNode * node)
    {
        if ((this->get_height(node->right->left)) > (this->get_height(node->right->right)))
        {
            node = this->double_left_rotate(node);
        }
        else
        {
            node = this->single_left_rotate(node);
        }
        return node;
    }
    TreeNode* balance_right(TreeNode* node)
    {
        if ((this->get_height(node->left->right)) > (this->get_height(node->left->left)))
        {
            node = this->double_right_rotate(node);
            return node;
        }
        else
        {
            node = this->single_right_rotate(node);
            return node;
        }
    }

    TreeNode* binary_remove(TreeNode* node, T item)
    {
        if (node == NULL)
        {
            return NULL;
        }
        if (node->item == item)
        {
            if (this->get_height(node) == 1)
            {
                delete node;
                this->size--;
                return NULL;
            }
            else if ((node->right == NULL) && (node->left != NULL))
            {
                this->size--;
                TreeNode * temp = node;
                node = node->left;
                delete (temp);
                return node;
            }
            else if ((node->left == NULL) && (node->right != NULL))
            {
                this->size--;
                TreeNode * temp = node;
                node = node->right;
                delete (temp);
                return node;
            }
            else if ((node->left != NULL) && (node->right != NULL))
            {
                T temp = this->find_min(node->right);
                node->item = temp;
                node->right = this->binary_remove(node->right, temp);
            }
        }
        else if (node->item < item)
        {
            node->right = this->binary_remove(node->right, item);
        }
        else if (node->item >= item)
        {
            node->left = this->binary_remove(node->left, item);
        }
        node = this->set_height(node);
        node = this->balance(node);
        return node;
    }

    T find_min(TreeNode* node)
    {
        if (node->left == NULL)
        {
            return node->item;
        }
        else
        {
            return this->find_min(node->left);
        }
    }

    bool binary_find(TreeNode* node, T item)
    {
        if (node == NULL)
        {
            return false;
        }
        if (item < node->item)
        {
            return this->binary_find(node->left, item);
        }
        else if (item > node->item)
        {
            return this->binary_find(node->right, item);
        }
        return true;
    }

    void binary_clear(TreeNode * node)
    {
        if (node->left != NULL)
        {
            this->binary_clear(node->left);
        }
        if (node->right != NULL)
        {
            this->binary_clear(node->right);
        }
        delete node;
    }


    

};

int main()
{
    AVL<std::string> tree;
    std::string line;
    std::ifstream myfile ("words.dat");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            if (line != "")
                tree.insert(line);
        }
        myfile.close();
    }

    std::cout << " ITEM (HEIGHT) - ASCENDING ORDER" << std::endl << std::endl;
    std::string output = tree.print("asc");
    std::cout << output << std::endl << std::endl;
    std::cout << " ITEM (HEIGHT) - DESCENDING ORDER" << std::endl << std::endl;
    output = tree.print("desc");
    std::cout << output << std::endl << std::endl;
    std::ifstream myfile2 ("remove.dat");
    if (myfile2.is_open())
    {
        while ( myfile2.good() )
        {
            getline (myfile2,line);
            if (line != "")
                tree.remove(line);
        }
        myfile2.close();
    }
    std::cout << " ITEM (HEIGHT) - ASCENDING ORDER" << std::endl << std::endl;
    output = tree.print("asc");
    std::cout << output << std::endl << std::endl;
    std::cout << " ITEM (HEIGHT) - DESCENDING ORDER" << std::endl << std::endl;
    output = tree.print("desc");
    std::cout << output << std::endl << std::endl;
    std::cout << " NODAL HIEARCHY" << std::endl << std::endl;
    output = tree.print();
    std::cout << output << std::endl << std::endl;
    return 0;
}