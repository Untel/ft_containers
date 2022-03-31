/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:02:40 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/31 18:47:51 by adda-sil         ###   ########.fr       */
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
        typedef	RBTNode<const T> *  const_node_ptr;

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

        RBTNode(pointer el, node_ptr l, node_ptr r, node_ptr p, node_ptr s, Color c) :
            data(el), left(l), right(r), parent(p), sentry(s), color(c)
        {};
 
        RBTNode(RBTNode & n) :
            data(n.data), left(n.left), right(n.right), parent(n.parent), sentry(n.sentry), color(n.color)
        {};

        ~RBTNode(void) {};
// RBTNode<ft::pair<const int, foo<int> > > *
// binary_tree_iterator<const ft::pair<const int, foo<int> > >
        operator RBTNode<const value_type>(void) const {
            return (RBTNode<const value_type>(data, left, right, parent, sentry, color));
        }

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
            if (right->exist()) {
                //MDBG("Case 1 " << right << " | " << *right);

				node_ptr el = right;
				while (el->left->exist())
					el = el->left;
				return el;
			} else if (is_left()) {
				return parent;
			} else if (is_right()) {
				node_ptr el = this->parent;
				while (el->exist() && el->is_right())
					el = el->parent;
				if (el->nil())
					return (el->right);
				return el->parent; 
			}
            return right;
		}

        node_ptr getPrev() {
            //MDBG("Search prev of " << this);
            if (!left->nil()) {
				node_ptr el = left;
				while (!el->right->nil())
					el = el->right;
                //MDBG("Case 1 " << el);
				return el;
			} else if (!parent->nil() && is_right()) {
                //MDBG("Case 2 " << parent);
				return parent;
			} else if (!parent->nil() && is_left()) {
				node_ptr el = this;
				while (el->is_left())
					el = el->parent;
				if (!el->parent->nil())
					return (left);
                //MDBG("Case 3 " << el);
				return el->parent; 
			} else {
                //MDBG("Case 4 " << left);
                return left;
            }
        }

        void rotateLeft(void) {
            node_ptr right_node = right;
        
            right = right_node->left;
            if (right->exist())
                right->parent = this;
            right_node->parent = parent;
            if (is_root())
                sentry->parent = right_node;
            else if (this == parent->left)
                parent->left = right_node;
            else
                parent->right = right_node;
            right_node->left = this;
            parent = right_node;
        }
        void rotateRight(void) {
            node_ptr left_node = left;
        
            left = left_node->right;        
            if (left != sentry)
                left->parent = this;
            left_node->parent = parent;
            if (is_root())
                sentry->parent = left_node;
            else if (this == parent->left)
                parent->left = left_node;
            else
                parent->right = left_node;
            left_node->right = this;
            parent = left_node;
        }

        void fixViolation() {
            node_ptr node = this;
            node_ptr parent_node = sentry;
            node_ptr grand_parent_node = sentry;

            while (
                (!node->is_root()) &&
                (node->color != BLACK_NODE) &&
                (node->parent->color == RED_NODE)
            ) {
                parent_node = node->parent;
                grand_parent_node = node->grand_parent();
                if (parent_node == grand_parent_node->left) {
                    node_ptr uncle_pt = grand_parent_node->right;
                    if (uncle_pt->exist() && uncle_pt->color == RED_NODE) {
                        grand_parent_node->color = RED_NODE;
                        parent_node->color = BLACK_NODE;
                        uncle_pt->color = BLACK_NODE;
                        node = grand_parent_node;
                    } else {
                        if (node->is_right()) {
                            parent_node->rotateLeft();
                            node = parent_node;
                            parent_node = node->parent;
                        }
                        grand_parent_node->rotateRight();
                        std::swap(parent_node->color, grand_parent_node->color);
                        node = parent_node;
                    }
                } else {
                    node_ptr uncle_pt = grand_parent_node->left;
                    if (uncle_pt->exist() && (uncle_pt->color == RED_NODE)) {
                        grand_parent_node->color = RED_NODE;
                        parent_node->color = BLACK_NODE;
                        uncle_pt->color = BLACK_NODE;
                        node = grand_parent_node;
                    } else {
                        if (node == parent_node->left) {
                            parent_node->rotateRight();
                            node = parent_node;
                            parent_node = node->parent;
                        }
                        grand_parent_node->rotateLeft();
                        std::swap(parent_node->color, grand_parent_node->color);
                        node = parent_node;
                    }
                }
            }
        }
    };

    template <class T>
    std::ostream & operator << (std::ostream & o, RBTNode<T> const & n) {
        if (n.color == BLACK_NODE)
            o << BLACK;
        else
            o << RED;
        o << "Node(" << *n.data << ")";
        o << " - L( " << (n.left->data->first) << " )" << " R( " << (n.right->data->first) << " )";
        if (
            n.parent->exist() &&
            n.parent->data &&
            n.parent->data->first
        ) {
            o << " - P( " << n.parent->data->first << " )";
        } else {
            o << " - P(NIL)";

        }
        o << RESET;
	    return o;
    }
}
#endif