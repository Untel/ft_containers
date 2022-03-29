/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:02:40 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/29 22:29:13 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTNODE_HPP
# define RBTNODE_HPP 1

namespace ft {

    enum Color { RED_NODE, BLACK_NODE };
    enum Childs { NO_CHILDS, CHILD_LEFT, CHILD_RIGHT, TWO_CHILDS };

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
        node_ptr sentry;
        Color color;
    
        // Constructor
        RBTNode(pointer el = NULL) :
            data(el), left(NULL), right(NULL), parent(NULL), sentry(NULL), color(RED_NODE)
        {};

        ~RBTNode(void) {
            std::cout << "Destroy" << std::endl;
        };

		bool is_root() {
			return parent->nil();
		}
        bool is_left() {
            return (parent->exist() && parent->left == this);
        }
        bool is_right() {
            return (parent->exist() && parent->right == this);
        }
        node_ptr grand_parent() {
            if (parent->exist())
                return (parent->parent);
            return sentry;
        }

        node_ptr oldest_left_ancestor() {
            node_ptr ancestor = this;
            while (ancestor->is_left() && !ancestor->parent->is_root())
                ancestor = ancestor->parent;
            return ancestor;
        }

        node_ptr oldest_right_ancestor() {
            node_ptr ancestor = this;
            while (ancestor->is_right())
                ancestor = ancestor->parent;
            return ancestor;
        }

        node_ptr oldest_side_ancestor() {
            return (is_left() ? oldest_left_ancestor() : oldest_right_ancestor());
        }

        bool nil() {
            return (this == sentry);
        }
        bool exist() {
            return !nil();
        }
        bool is_leaf() {
            return (right->nil() && left->nil());
        }
        bool has_one_childs() {
            return (
                !is_leaf() &&
                !has_two_childs()
            );
        }
        bool has_two_childs() {
            return (right->exist() && left->exist());
        }
        Childs has_childs() {
            if (is_leaf())
                return NO_CHILDS;
            if (left->exist() && right->exist())
                return TWO_CHILDS;
            if (left->exist())
                return CHILD_LEFT;
            return CHILD_RIGHT;
        }

        node_ptr get_uniq_child() {
            return (left->exist() ? left : right);
        }

		node_ptr getNext() {
            if (!right->nil()) {
                MDBG("Case 1 " << right << " | " << *right);

				node_ptr el = right;
				while (!el->left->nil())
					el = el->left;
				return el;
			} else if (!parent->nil() && is_left()) {
                MDBG("Case 2");

				return parent;
			} else if (!parent->nil() && is_right()) {
                MDBG("Case 3");

				node_ptr el = this;
				while (el->is_right())
					el = el->parent;
				if (!el->parent->nil())
					return (right);
				return el->parent; 
			} else {
				return right;
			}
		}

        node_ptr getPrev() {
            MDBG("Search prev of " << this);
            if (!left->nil()) {
				node_ptr el = left;
				while (!el->right->nil())
					el = el->right;
                MDBG("Case 1 " << el);
				return el;
			} else if (!parent->nil() && is_right()) {
                MDBG("Case 2 " << parent);
				return parent;
			} else if (!parent->nil() && is_left()) {
				node_ptr el = this;
				while (el->is_left())
					el = el->parent;
				if (!el->parent->nil())
					return (left);
                MDBG("Case 3 " << el);
				return el->parent; 
			} else {
                MDBG("Case 4 " << left);
                return left;
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
                    Only Recoloring required */
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
                        std::swap(parent_pt->color, grand_parent_pt->color);
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
                        std::swap(parent_pt->color, grand_parent_pt->color);
                        pt = parent_pt;
                    }
                }
            }
            root->color = BLACK_NODE;
        }

    };

    template <class T>
    std::ostream & operator << (std::ostream & o, RBTNode<T> const & n) {
        if (n.color == BLACK_NODE)
            o << BLACK;
        else
            o << RED;
        o << "Node(" << *n.data << ")";
        o << " - L( " << (n.left->data->first) << " )" << " R( " << (n.right->data->first) << " ) \n\n";
        if (n.parent &&
            n.parent->data &&
            n.parent->data->first
        ) {
            o << " - P( " << n.parent->data->first << " )";
        } else {
            o << YELLOW << " !! ERROR !!";
        }
        o << RESET;
	    return o;
    }
}
#endif