/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:02:40 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/03 19:21:53 by adda-sil         ###   ########.fr       */
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
			return this == sentry->parent;
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

        void transplant(node_ptr with) {
            MDBG("Transplanting " << *with);
            if (parent->nil()) {
                MDBG("2 " << *parent->right);
                sentry->parent = with;
            }  else if (this == parent->left) {
                MDBG("3 " << *parent->right);
                parent->left = with;
            } else {
                MDBG("4 " << *parent->right);
                parent->right = with;
            }
            MDBG("Assign par " << *parent);

            //In fact, we shall exploit the ability to assign to v.p when v point to nil.
            // NO, because our NIL.parent == root in our case
            // if (with->exist())
            with->parent = parent;
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

        // page 324, 17/31
        void remove() {
            MDBG("Start, sentry is " << *sentry);
            node_ptr y = this;
            node_ptr x;
            Color origin = color;
            if (left->nil()) {
                x = right;
                transplant(right);
            } else if (right->nil()) {
                x = left;
                transplant(left);
            } else {
                y = right->min_subtree();
                MDBG("Min subtree " << *y);
                origin = y->color;
                x = y->right;
                MDBG("2, sentry is " << *sentry);
                if (y->parent == this) {
                    MDBG("y parent == this " << *y);
                    x->parent = y;
                }
                else if (y->exist()) {
                    MDBG("3, sentry is " << *sentry);
                    MDBG("y parent != this " << *y);
                    y->transplant(y->right);
                    MDBG("after transpl" << *y);
                    MDBG("4, sentry is " << *sentry);
                    
                    y->right = right;
                    y->right->parent = y;
                    MDBG("27 " << *y);
                    MDBG("30" << *y->right);
                    MDBG("5, sentry is " << *sentry);
                }
                transplant(y);
                y->left = left;
                y->left->parent = y;
                y->color = color;

                MDBG("Y is " << *y);
                MDBG("X is " << *x);
            }
            if (origin == BLACK_NODE)
                fixDelete(x);
            MDBG("End, sentry is " << *sentry);
        }

        void fixDelete(node_ptr x) {
            if (x->nil())
                return ;
            while (!x->is_root() && x->color == BLACK_NODE) {
                if (x == x->parent->left) {
                    node_ptr w = x->parent->right;
                    if (w->color == RED_NODE) {
                        w->color = BLACK_NODE;
                        x->parent->color = RED_NODE;
                        x->parent->rotateLeft();
                        w = x->parent->right;
                    }
                    if (w->left->color == BLACK_NODE && w->right->color == BLACK_NODE) {
                        w->color = RED_NODE;
                        x = x->parent;
                    } else {
                        if (x->right->color == BLACK_NODE) {
                            w->left->color = BLACK_NODE;
                            w->color = RED_NODE;
                            w->rotateRight();
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK_NODE;
                        w->right->color = BLACK_NODE;
                        x->parent->rotateLeft();
                        x = sentry->parent;
                    }
                }
                else {
                    node_ptr w = x->parent->left;
                    if (w->color == RED_NODE) {
                        w->color = BLACK_NODE;
                        x->parent->color = RED_NODE;
                        x->parent->rotateLeft();
                        w = x->parent->right;
                    }
                    if (w->left->color == BLACK_NODE && w->right->color == BLACK_NODE) {
                        w->color = RED_NODE;
                        x = x->parent;
                    } else {
                        if (x->right->color == BLACK_NODE) {
                            w->left->color = BLACK_NODE;
                            w->color = RED_NODE;
                            w->rotateRight();
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK_NODE;
                        w->right->color = BLACK_NODE;
                        x->parent->rotateLeft();
                        x = sentry->parent;
                    }
                }
            }
            x->color = BLACK_NODE;
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