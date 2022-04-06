/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:02:40 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:20:15 by adda-sil         ###   ########.fr       */
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
			return parent == sentry;
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

        node_ptr min_subtree() {
            if (nil())
                return this;
            node_ptr l = this;
            while (l->left->exist())
                l = l->left;
            return l;
        }

        node_ptr max_subtree() {
            if (nil())
                return this;
            node_ptr r = this;
            while (r->right->exist())
                r = r->right;
            return r;
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
				node_ptr el = right;
				while (el->left->exist())
					el = el->left;
				return el;
			} else if (is_left()) {
				return parent;
			} else if (is_right()) {
				node_ptr el = parent;
				while (el->exist() && el->is_right())
					el = el->parent;
				if (el->nil())
					return (el->right);
				return el->parent; 
			}
            return right;
		}

        node_ptr getPrev() {
            if (left->exist()) {
				node_ptr el = left;
				while (el->right->exist())
					el = el->right;
				return el;
			} else if (is_right()) {
				return parent;
			} else if (is_left()) {
				node_ptr el = parent;
				while (el->exist() && el->is_left())
					el = el->parent;
				if (el->nil())
					return (el->left);
				return el->parent; 
			}
            return left;
        }
    };

    #ifdef DEBUG
        template <class T>
        std::ostream & operator << (std::ostream & o, RBTNode<T> const & n) {
            if (n.color == BLACK_NODE)
                o << BLACK;
            else
                o << RED;
            o << "Node(" << *n.data << ")";
            o << " - L( " << (n.left->data->first) << " )" << " R( " << (n.right->data->first) << " )";
            o << RESET;
            return o;
        }
    #endif
}
#endif