/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:46:43 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/07 17:19:55 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <stdexcept>
# include <cstdio>

namespace ft {

    enum Color { RED, BLACK };
    
    template <class T>
    struct Node
    {
        typedef T           value_type;

        value_type data;
        bool color;
        Node *left, *right, *parent;
    
        // Constructor
        Node(value_type el)
            : data(el), left(NULL), parent(NULL), color(RED)
        {};
    };
    
    // Class to represent Red-Black Tree
    template <class T>
    class RBTree
    {
        typedef typename Node<T>           value_type;

        public:
            // Constructor
            RBTree() { root = NULL; }
            void insert(const value_type *pt) {            
                // Do a normal BST insert
                root = BSTInsert(root, pt);
                // fix Red Black Tree violations
                fixViolation(root, pt);
            }
            void inorder() { inorderHelper(root); }
            void levelOrder() { {  levelOrderHelper(root); } }

        private:
            value_type *root;

        protected:
            void rotateLeft(value_type *&root, value_type *&pt) {
                value_type *pt_right = pt->right;
            
                pt->right = pt_right->left;
            
                if (pt->right != NULL)
                    pt->right->parent = pt;
            
                pt_right->parent = pt->parent;
            
                if (pt->parent == NULL)
                    root = pt_right;
            
                else if (pt == pt->parent->left)
                    pt->parent->left = pt_right;
            
                else
                    pt->parent->right = pt_right;
            
                pt_right->left = pt;
                pt->parent = pt_right;
            }
            void rotateRight(value_type *&root, value_type *&pt) {
                value_type *pt_left = pt->left;
            
                pt->left = pt_left->right;
            
                if (pt->left != NULL)
                    pt->left->parent = pt;
            
                pt_left->parent = pt->parent;
            
                if (pt->parent == NULL)
                    root = pt_left;
            
                else if (pt == pt->parent->left)
                    pt->parent->left = pt_left;
            
                else
                    pt->parent->right = pt_left;
            
                pt_left->right = pt;
                pt->parent = pt_left;
            }
            void fixViolation(value_type *&root, value_type *&pt) {
                value_type *parent_pt = NULL;
                value_type *grand_parent_pt = NULL;
            
                while ((pt != root) && (pt->color != BLACK) &&
                    (pt->parent->color == RED))
                {
            
                    parent_pt = pt->parent;
                    grand_parent_pt = pt->parent->parent;
            
                    /*  Case : A
                        Parent of pt is left child
                        of Grand-parent of pt */
                    if (parent_pt == grand_parent_pt->left)
                    {
            
                        value_type *uncle_pt = grand_parent_pt->right;
            
                        /* Case : 1
                        The uncle of pt is also red
                        Only Recoloring required */
                        if (uncle_pt != NULL && uncle_pt->color == RED)
                        {
                            grand_parent_pt->color = RED;
                            parent_pt->color = BLACK;
                            uncle_pt->color = BLACK;
                            pt = grand_parent_pt;
                        }
            
                        else
                        {
                            /* Case : 2
                            pt is right child of its parent
                            Left-rotation required */
                            if (pt == parent_pt->right)
                            {
                                rotateLeft(root, parent_pt);
                                pt = parent_pt;
                                parent_pt = pt->parent;
                            }
            
                            /* Case : 3
                            pt is left child of its parent
                            Right-rotation required */
                            rotateRight(root, grand_parent_pt);
                            swap(parent_pt->color,
                                    grand_parent_pt->color);
                            pt = parent_pt;
                        }
                    }
            
                    /* Case : B
                    Parent of pt is right child
                    of Grand-parent of pt */
                    else
                    {
                        value_type *uncle_pt = grand_parent_pt->left;
            
                        /*  Case : 1
                            The uncle of pt is also red
                            Only Recoloring required */
                        if ((uncle_pt != NULL) && (uncle_pt->color ==
                                                                RED))
                        {
                            grand_parent_pt->color = RED;
                            parent_pt->color = BLACK;
                            uncle_pt->color = BLACK;
                            pt = grand_parent_pt;
                        }
                        else
                        {
                            /* Case : 2
                            pt is left child of its parent
                            Right-rotation required */
                            if (pt == parent_pt->left)
                            {
                                rotateRight(root, parent_pt);
                                pt = parent_pt;
                                parent_pt = pt->parent;
                            }
            
                            /* Case : 3
                            pt is right child of its parent
                            Left-rotation required */
                            rotateLeft(root, grand_parent_pt);
                            swap(parent_pt->color,
                                    grand_parent_pt->color);
                            pt = parent_pt;
                        }
                    }
                }
            
                root->color = BLACK;
            }
    };
    
    // A recursive function to do inorder traversal
    template <class T>
    void inorderHelper(Node<T> *root)
    {
        if (root == NULL)
            return;
    
        inorderHelper(root->left);
        std::cout << root->data << "  ";
        inorderHelper(root->right);
    }
    
    /* A utility function to insert
        a new node with given key
    in BST */
    template <class T>
    Node<T>* BSTInsert(Node<T>* root, Node<T> *pt)
    {
        /* If the tree is empty, return a new node */
        if (root == NULL)
        return pt;
    
        /* Otherwise, recur down the tree */
        if (pt->data < root->data)
        {
            root->left  = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }
    
        /* return the (unchanged) node povalue_typeer */
        return root;
    }
    
    // Utility function to do level order traversal
    template <class T>
    void levelOrderHelper(Node<T> *root)
    {
        if (root == NULL)
            return;
    
        std::queue<Node<T> *> q;
        q.push(root);
    
        while (!q.empty())
        {
            Node *temp = q.front();
            std::cout << temp->data << "  ";
            q.pop();
    
            if (temp->left != NULL)
                q.push(temp->left);
    
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }
}