// Copyright (c) 2019-2020 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_TOOLS_PRIORITY_QUEUE
#define DATA_TOOLS_PRIORITY_QUEUE

#include <data/functional/tree.hpp>
#include <data/tools/linked_stack.hpp>
#include <data/tools/linked_tree.hpp>
#include <data/math/ordered.hpp>
    
namespace data::tool {

    template <typename element>
    concept prioritized = requires (const element &a, const element &b) {
        {a <= b} -> implicitly_convertible_to<bool>;
    };
    
    template <functional::tree tree, typename element = element_of<tree>>
    requires prioritized<element>
    struct priority_queue {
        
        size_t size () const;
        bool empty () const;
        
        priority_queue ();
        priority_queue (const element &e);
        
        template<typename ... P>
        priority_queue (const element &a, const element &b, P... p);
        
        bool valid () const;
        
        const element &first () const;
        priority_queue rest () const;
        
        priority_queue insert (const element &elem) const;
        
        template <typename list> requires sequence<list, element>
        priority_queue insert (list l) const;
        
        template <typename list> requires sequence<list, element> 
        priority_queue (list l);

        template <data::sequence X> requires std::equality_comparable_with<element, data::element_of<X>>
        bool operator == (const X &x) const {
            return sequence_equal (*this, x);
        }

        tree Tree;
        priority_queue (tree t) : Tree {t} {}

        static tree merge (const tree &left, const tree right) {
            if (left.empty ())
                return right;
            if (right.empty ())
                return left;
            if (left.root () <= right.root ())
                return tree {left.root (), left.left (), merge (left.right (), right)};
            else
                return tree {right.root (), right.left (), merge (left, right.right ())};
        }
    };
    
    template <functional::tree tree, typename element = element_of<tree>> 
    priority_queue<tree, element> inline operator << (const priority_queue<tree, element> p, const element &elem) {
        return p.insert (elem);
    }

    template <functional::tree tree, typename element = element_of<tree>>
    priority_queue<tree, element> inline operator <<= (priority_queue<tree, element> &p, const element &elem) {
        return p = p.insert (elem);
    }
    
    template <functional::tree tree, typename element = element_of<tree>>
    bool inline operator == (const priority_queue<tree, element> a, const priority_queue<tree, element> b) {
        if (data::empty (a) && data::empty (b)) return true;
        if (data::empty (a) || data::empty (b)) return false;
        if (a.first () != b.first ()) return false;
        return a.rest () == b.rest ();
    }
    
    template <functional::tree tree, typename element> requires prioritized<element>
    size_t inline priority_queue<tree, element>::size () const {
        return data::size (Tree);
    }
    
    template <functional::tree tree, typename element> requires prioritized<element>
    bool inline priority_queue<tree, element>::empty () const {
        return data::empty (Tree);
    }
    
    template <functional::tree tree, typename element> requires prioritized<element>
    inline priority_queue<tree, element>::priority_queue () : Tree {} {}
    
    template <functional::tree tree, typename element> requires prioritized<element>
    inline priority_queue<tree, element>::priority_queue (const element &e) : priority_queue {priority_queue {}.insert (e)} {}
    
    template <functional::tree tree, typename element> requires prioritized<element>
    template <typename ... P>
    priority_queue<tree, element>::priority_queue (const element &a, const element &b, P... p) :
        priority_queue {priority_queue {b, p...}.insert (a)} {}
    
    template <functional::tree tree, typename element> requires prioritized<element>
    const element inline &priority_queue<tree, element>::first () const {
        return Tree.root ();
    }
    
    template <functional::tree tree, typename element> requires prioritized<element>
    priority_queue<tree, element> priority_queue<tree, element>::rest () const {
        if (empty ()) return *this;
        return {merge (Tree.left (), Tree.right ())};
    }
    
    template <functional::tree tree, typename element> requires prioritized<element>
    priority_queue<tree, element> inline priority_queue<tree, element>::insert (const element &elem) const {
        return {merge (tree {elem}, Tree)};
    }
    
    template <functional::tree tree, typename element> requires prioritized<element>
    template <typename list> requires sequence<list, element>
    priority_queue<tree, element> priority_queue<tree, element>::insert (list l) const {
        if (l.empty ()) return *this;
        return insert (l.first ()).insert (l.rest ());
    }
    
    template <functional::tree tree, typename element> requires prioritized<element>
    template <typename list> requires sequence<list, element> 
    inline priority_queue<tree, element>::priority_queue (list l) : priority_queue {priority_queue {}.insert (l)} {}
    
    template <functional::tree tree, typename element> requires prioritized<element>
    bool inline priority_queue<tree, element>::valid () const {
        return Tree.valid ();
    }
    
}

#endif
