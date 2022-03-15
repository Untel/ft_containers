/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:46:43 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/14 16:21:33 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <stdexcept>
# include <cstdio>

namespace ft {

    enum Color { _RED, _BLACK };
    
    template <class T>
    struct Node
    {
        typedef T           value_type;
        typedef T *         pointer;
        typedef T &         reference;

        pointer data;
        Node * left;
        Node * right;
        Node * parent;
        bool color;
    
        // Constructor
        Node(pointer el = NULL)
            : data(el), left(NULL), parent(NULL), color(_RED)
        {};
    };
    
    // Class to represent _RED-_BLACK Tree
    template <class T>
    class RBTree {
        public:
            typedef ft::Node<T>                     value_type;
            typedef typename ft::Node<T> *          pointer;
            // Constructor
            RBTree() { root = NULL; }
            void insert(pointer pt) {            
                // Do a normal BST insert
                root = BSTInsert(root, pt);
                // fix _RED _BLACK Tree violations
                fixViolation(root, pt);
            }
            void inorder() { inorderHelper(root); }
            void levelOrder() { {  levelOrderHelper(root); } }

        private:
            pointer root;

        protected:
            void rotateLeft(pointer &root, pointer &pt) {
                pointer pt_right = pt->right;
            
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
            void rotateRight(pointer &root, pointer &pt) {
                pointer pt_left = pt->left;
            
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
            void fixViolation(pointer &root, pointer &pt) {
                pointer parent_pt = NULL;
                pointer grand_parent_pt = NULL;
            
                while ((pt != root) && (pt->color != _BLACK) &&
                    (pt->parent->color == _RED))
                {
            
                    parent_pt = pt->parent;
                    grand_parent_pt = pt->parent->parent;
            
                    /*  Case : A
                        Parent of pt is left child
                        of Grand-parent of pt */
                    if (parent_pt == grand_parent_pt->left)
                    {
            
                        pointer uncle_pt = grand_parent_pt->right;
            
                        /* Case : 1
                        The uncle of pt is also _RED
                        Only Recoloring requi_RED */
                        if (uncle_pt != NULL && uncle_pt->color == _RED)
                        {
                            grand_parent_pt->color = _RED;
                            parent_pt->color = _BLACK;
                            uncle_pt->color = _BLACK;
                            pt = grand_parent_pt;
                        }
            
                        else
                        {
                            /* Case : 2
                            pt is right child of its parent
                            Left-rotation requi_RED */
                            if (pt == parent_pt->right)
                            {
                                rotateLeft(root, parent_pt);
                                pt = parent_pt;
                                parent_pt = pt->parent;
                            }
            
                            /* Case : 3
                            pt is left child of its parent
                            Right-rotation requi_RED */
                            rotateRight(root, grand_parent_pt);
                            std::swap(parent_pt->color,
                                    grand_parent_pt->color);
                            pt = parent_pt;
                        }
                    }
            
                    /* Case : B
                    Parent of pt is right child
                    of Grand-parent of pt */
                    else
                    {
                        pointer uncle_pt = grand_parent_pt->left;
            
                        /*  Case : 1
                            The uncle of pt is also _RED
                            Only Recoloring requi_RED */
                        if ((uncle_pt != NULL) && (uncle_pt->color ==
                                                                _RED))
                        {
                            grand_parent_pt->color = _RED;
                            parent_pt->color = _BLACK;
                            uncle_pt->color = _BLACK;
                            pt = grand_parent_pt;
                        }
                        else
                        {
                            /* Case : 2
                            pt is left child of its parent
                            Right-rotation requi_RED */
                            if (pt == parent_pt->left)
                            {
                                rotateRight(root, parent_pt);
                                pt = parent_pt;
                                parent_pt = pt->parent;
                            }
            
                            /* Case : 3
                            pt is right child of its parent
                            Left-rotation requi_RED */
                            rotateLeft(root, grand_parent_pt);
                            std::swap(parent_pt->color,
                                    grand_parent_pt->color);
                            pt = parent_pt;
                        }
                    }
                }
            
                root->color = _BLACK;
            }
    };
    
    // A recursive function to do inorder traversal
    template <class T>
    void inorderHelper(ft::Node<T> *root)
    {
        if (root == NULL)
            return;
    
        inorderHelper(root->left);
        std::cout << *(root->data) << "  ";
        inorderHelper(root->right);
    }
    
    /* A utility function to insert
        a new node with given key
    in BST */
    template <class T>
    ft::Node<T>* BSTInsert(ft::Node<T>* root, ft::Node<T> *pt)
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
    void levelOrderHelper(ft::Node<T> *root)
    {
        if (root == NULL)
            return;
    
        std::queue<ft::Node<T> *> q;
        q.push(root);
    
        while (!q.empty())
        {
            ft::Node<T> *temp = q.front();
            std::cout << *(temp->data) << "  ";
            q.pop();
    
            if (temp->left != NULL)
                q.push(temp->left);
    
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }
}