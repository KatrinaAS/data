// Copyright (c) 2018-2020 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_MATH_NONNEGATIVE
#define DATA_MATH_NONNEGATIVE

#include <data/valid.hpp>
#include <data/math/ordered.hpp>

namespace data::math {
    
    template <typename R> struct nonnegative : interface::ordered<R> {
        R Value;
        
        explicit nonnegative(const R& n) : Value{n} {}
        nonnegative() : Value{} {}
        
        bool valid() {
            return data::valid(Value) && Value >= R(0);
        }
        
        operator R() const {
            return Value;
        }
        
        nonnegative operator+(const nonnegative& n) const {
            return Value + n.Value;
        }
        
        nonnegative operator*(const nonnegative& n) const {
            return Value * n.Value;
        }
        
        bool operator==(const nonnegative& n) const {
            return Value == n.Value;
        }
        
        bool operator!=(const nonnegative& n) const {
            return !operator==(n);
        }
        
        bool operator>(const nonnegative& n) const {
            return Value > n.Value;
        }
        
        bool operator>=(const nonnegative& n) const {
            return Value >= n.Value;
        }
        
        bool operator<(const nonnegative& n) const {
            return Value < n.Value;
        }
        
        bool operator<=(const nonnegative& n) const {
            return Value <= n.Value;
        }
    };
    
    template <typename R> struct nonzero {
        R Value;
        
        explicit nonzero(const R& n) : Value{n} {}
        nonzero() : Value{} {}
        
        bool valid() const {
            return data::valid(Value) && Value != R(0);
        }
        
        operator R() const {
            return Value;
        }
        
        nonzero operator*(const nonzero& n) const {
            return Value * n.Value;
        }
        
        R operator+(const R& n) const {
            return Value + n;
        }
        
        R operator*(const R& n) const {
            return Value * n;
        }
        
        bool operator==(const nonzero& n) const {
            return Value == n.Value;
        }
        
        bool operator!=(const nonzero& n) const {
            return !operator==(n);
        }
    };

}



#endif
