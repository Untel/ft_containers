/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:02:40 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/23 13:45:40 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTNODE_HPP
# define RBTNODE_HPP 1

namespace ft {

    enum Color { RED_NODE, BLACK_NODE };

	template <class T>
    struct RBTNode
    {
        typedef T                   value_type;
        typedef T *                 pointer;
        typedef T &                 reference;
        typedef	RBTNode<T> *        node_ptr;

        pointer data;
       	node_ptr left;
        node_ptr right;
        node_ptr parent;
        Color color;
    
        // Constructor
        RBTNode(pointer el = NULL) :
            data(el), left(NULL), right(NULL), parent(NULL), color(RED_NODE)
        {};

		bool is_root() {
			return !parent;
		}
        bool is_left() {
            return (parent && parent->left == this);
        }
        bool is_right() {
            return (parent && parent->right == this);
        }

		node_ptr getNext() {
			if (this->right) {
				node_ptr el = right;
				while (el->left)
					el = el->left;
				return el;
			} else if (parent && is_left()) {
				return this->parent;
			} else if (parent && is_right()) {
				node_ptr el = this;
				while (el->is_right())
					el = el->parent;
				if (!el->parent)
					return (right);
				return el->parent; 
			} else {
				return right;
			}
		}

        void rotateLeft(node_ptr &root, node_ptr &pt, node_ptr sentry) {
            MDBG("Rotating left " << *root << " with " << *pt);
            node_ptr pt_right = pt->right;
        
            pt->right = pt_right->left;
        
            if (pt->right != sentry)
                pt->right->parent = pt;
        
            pt_right->parent = pt->parent;
        
            if (pt->parent == sentry)
                root = pt_right;
            else if (pt == pt->parent->left)
                pt->parent->left = pt_right;
            else
                pt->parent->right = pt_right;
            pt_right->left = pt;
            pt->parent = pt_right;
        }
        void rotateRight(node_ptr &root, node_ptr &pt, node_ptr sentry) {
            MDBG("Rotating right " << *root << " with " << *pt);
            node_ptr pt_left = pt->left;
        
            pt->left = pt_left->right;
        
            if (pt->left != sentry)
                pt->left->parent = pt;
        
            pt_left->parent = pt->parent;
        
            if (pt->parent == sentry)
                root = pt_left;
            else if (pt == pt->parent->left)
                pt->parent->left = pt_left;
            else
                pt->parent->right = pt_left;
        
            pt_left->right = pt;
            pt->parent = pt_left;
        }

        void fixViolation(node_ptr &root, node_ptr &pt, node_ptr &sentry) {
            node_ptr parent_pt = sentry;
            node_ptr grand_parent_pt = sentry;

            while (
                (pt != root) &&
                (pt->color != BLACK_NODE) &&
                (pt->parent->color == RED_NODE)
            ) {
				std::cout << RED << "ITER\n";
                parent_pt = pt->parent;
                grand_parent_pt = pt->parent->parent;
        
                /*  Case : A
                    Parent of pt is left child
                    of Grand-parent of pt */
                if (parent_pt == grand_parent_pt->left)
                {
        
                    node_ptr uncle_pt = grand_parent_pt->right;
        
                    /* Case : 1
                    The uncle of pt is also _RED
                    Only Recoloring requi_RED */
                    if (uncle_pt != sentry && uncle_pt->color == RED_NODE)
                    {
                        grand_parent_pt->color = RED_NODE;
                        parent_pt->color = BLACK_NODE;
                        uncle_pt->color = BLACK_NODE;
                        pt = grand_parent_pt;
                    }
        
                    else
                    {
                        /* Case : 2
                        pt is right child of its parent
                        Left-rotation required */
                        if (pt == parent_pt->right)
                        {
                            rotateLeft(root, parent_pt, sentry);
                            pt = parent_pt;
                            parent_pt = pt->parent;
                        }
        
                        /* Case : 3
                        pt is left child of its parent
                        Right-rotation required */
                        rotateRight(root, grand_parent_pt, sentry);
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
                    node_ptr uncle_pt = grand_parent_pt->left;
        
                    /*  Case : 1
                        The uncle of pt is also RED_NODE
                        Only Recoloring required */
                    if ((uncle_pt != sentry) && (uncle_pt->color == RED_NODE))
                    {
                        grand_parent_pt->color = RED_NODE;
                        parent_pt->color = BLACK_NODE;
                        uncle_pt->color = BLACK_NODE;
                        pt = grand_parent_pt;
                    }
                    else
                    {
                        /* Case : 2
                        pt is left child of its parent
                        Right-rotation required */
                        if (pt == parent_pt->left)
                        {
                            rotateRight(root, parent_pt, sentry);
                            pt = parent_pt;
                            parent_pt = pt->parent;
                        }
        
                        /* Case : 3
                        pt is right child of its parent
                        Left-rotation required */
                        rotateLeft(root, grand_parent_pt, sentry);
                        std::swap(parent_pt->color,
                                grand_parent_pt->color);
                        pt = parent_pt;
                    }
                }
            }

            root->color = BLACK_NODE;
        }

    };

    template <class T>
    std::ostream & operator << (std::ostream & o, RBTNode<T> const & n){
        o << "Node(" << *n.data << ")";
        o << " - L( " << n.left << " )" << " R( " << n.right << " )";
        o << " - P( " << n.parent << " )";
	    return o;
    }
}
#endif