//
// Created by Viktoria Erokhina on 30.04.17.
//


#include <iostream>
#include <string>
#include <cassert>
#include <math.h>
#include <algorithm>
#include "big_integer.h"

unsigned int *create_pointer(int capacity, unsigned int cnt) {
    unsigned int *new_pointer = new unsigned int[capacity + 1];
    new_pointer[0] = cnt;
    ++new_pointer;
    //std::cout << new_pointer << " " << capacity << std::endl;
    return new_pointer;
}

void del_pointer(unsigned int *pointer) {
    pointer--;
    delete []pointer;
}

void inc_refs(unsigned int *pointer) {
    ++pointer[-1];
}

void dec_refs(unsigned int *pointer) {
    --pointer[-1];
    if (pointer[-1] == 0) {
        del_pointer(pointer);
    }
}

big_integer::big_integer() {
    capacity = 1;
    value = 0LL;
}

void big_integer::ensure_capacity(int size) {
    if (size > capacity) {
        resize(size * 3);
    }
    if (4 * size < capacity) {
        resize(capacity >> 1);
    }
}

void big_integer::resize(int new_size) {
    //unsigned int *tmp = new unsigned int[new_size];
    unsigned int *tmp = create_pointer(new_size, 1);
    for (int i = 0; i < size; i++) {
        tmp[i] = digits[i];
    }
    for (int i = size; i < new_size; i++) {
        tmp[i] = 0;
    }
    dec_refs(digits);
    digits = tmp;
    capacity = new_size;
}

bool big_integer::is_ok(long long x) {
    return MIN <= x && x <= MAX;
}

std::pair <bool, long long> big_integer::is_relevant_string(std::string const &str, int cnt, int s) {
    if (str.size() - cnt > DIG_LEN)
        return std::make_pair(false, 0);
    else {
        long long num = 0;
        for (; cnt < (int)str.size(); ++cnt) {
            num = num * 10 + str[cnt] - '0';
        }
        num *= s;
        return std::make_pair(is_ok(num), num);
    }
}

big_integer::big_integer(std::string const &str) {
    int cnt = 0;
    if (str[cnt] == '-') {
        sign = -1;
        ++cnt;
    } else {
        sign = 1;
    }
    while (str[cnt] == '0') {
        cnt++;
    }
    std::pair <bool, long long> res = is_relevant_string(str, cnt, sign);
    if (res.first) {
        capacity = 1;
        value = res.second;
        return;
    }
    std::vector<int> digs;
    for (int i = cnt; i < (int)str.size(); ++i) {
        digs.push_back(str[i] - '0');
    }
    capacity = std::max((int)digs.size(), 2);
    digits = create_pointer(capacity, 1);
    for (int i = 0; i < capacity; ++i) {
        digits[i] = 0;
    }
    size = 0;
    while (true) {
        long long rem = 0;
        bool fl = true;
        for (size_t i = 0; i < digs.size(); ++i) {
            rem = (rem * 10) + digs[i];
            digs[i] = (int)(rem / MAX_VALUE);
            if (digs[i] != 0) {
                fl = false;
            }
            rem %= MAX_VALUE;
        }
        digits[size++] = (unsigned int)rem;
        if (fl) {
            break;
        }
    }
    ensure_capacity(size);
    remove_zeroes();
    if (size == 1 && digits[size - 1] == 0) {
        sign = 1;
    }
}

bool operator<(big_integer const &a, big_integer const &b) {
    if (a.capacity == 1 && b.capacity == 1) {
        return a.value < b.value;
    }
    if (a.capacity == 1) return b.sign == 1;
    if (b.capacity == 1) return a.sign == -1;
    if (a.sign != b.sign) {
        return a.sign < b.sign;
    }
    bool res = true;
    if (a.size != b.size) {
        res = a.size < b.size;
    } else {
        bool fl = true;
        for (int i = a.size - 1; i >= 0; i--) {
            if (a.digits[i] != b.digits[i]) {
                res = a.digits[i] < b.digits[i];
                fl = false;
                break;
            }
        }
        if (fl) {
            return false;
        }
    }
    return (a.sign < 0) == !res;
}

bool operator>(big_integer const &a, big_integer const &b) {
    return b < a;
}

bool operator<=(big_integer const &a, big_integer const &b) {
    return !(b < a);
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return !(a < b);
}

big_integer::big_integer(big_integer const &other) {
    sign = other.sign;
    size = other.size;
    capacity = other.capacity;
    if (capacity == 1) {
        value = other.value;
    } else {
       // digits = new unsigned int[capacity];
        digits = other.digits;
        inc_refs(digits);
    }
}

big_integer::~big_integer() {
    if (capacity > 1)
        dec_refs(digits);
}

big_integer::big_integer(int a) {
    capacity = 1;
    value = 1LL * a;
}


void big_integer::sw(big_integer& tmp) {
    std::swap(sign, tmp.sign);
    std::swap(digits, tmp.digits);
    std::swap(capacity, tmp.capacity);
    std::swap(size, tmp.size);
}

big_integer &big_integer::operator=(big_integer const &other) {
    big_integer tmp = big_integer(other);
    sw(tmp);
    return *this;
}

void big_integer::cancel_small(int new_capacity) {
    assert(new_capacity > 1);
    long long cur = value;
    if (cur < 0) {
        cur = -cur;
        sign = -1;
    } else {
        sign = 1;
    }
    capacity = new_capacity;
    //digits = new unsigned int[capacity];
    digits = create_pointer(capacity, 1);
    digits[0] = (unsigned int)(cur % MAX_VALUE);
    digits[1] = (unsigned int)(cur / MAX_VALUE);
    for (int i = 2; i < new_capacity; ++i) {
        digits[i] = 0;
    }
    size = 2;
    if (digits[1] == 0) {
        size = 1;
    }
}

void big_integer::make_copy() {
    if (digits[-1] == 1) return;
    unsigned int *pointer = create_pointer(capacity, 1);
    //std::cout << digits << " " << capacity << "?" << std::endl;
    for (int i = 0; i < capacity; ++i) {
        pointer[i] = digits[i];
    }
    dec_refs(digits);
    digits = pointer;
}

void big_integer::add_small(long long x) {
    long long carry = 0LL;
    for (int i = 0; i < size; ++i) {
        carry += (1LL * digits[i]);
        if (i == 0) carry += x;
        digits[i] = (unsigned int)(carry % MAX_VALUE);
        carry /= MAX_VALUE;
    }
    if (carry != 0) {
        digits[size++] = (unsigned int)carry;
    }
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    if (capacity == 1 && rhs.capacity == 1 && is_ok(value + rhs.value)) {
        value += rhs.value;
        return *this;
    }
    if (capacity == 1) {
        cancel_small(rhs.capacity + 2);
    }
    make_copy();
    if (rhs.capacity == 1) {
        if (sign * ((rhs.value < 0) ? -1 : 1) > 0) {
            ensure_capacity(size + 1);
            add_small(rhs.value);
            return *this;
        } else {
            long long x = rhs.value;
            sub_small((x < 0) ? -x : x);
            remove_zeroes();
            return *this;
        }
    }
    if (sign * rhs.sign > 0) {
        return add(rhs);
    } else {
        if (cmp_abs(*this, rhs) >= 0) {
            return sub(rhs);
        } else {
            big_integer tmp = rhs;
            tmp.make_copy();
            tmp.sub(*this);
            *this = tmp;
            return *this;
        }
    }
}

big_integer &big_integer::add(big_integer const &rhs) {
    int new_size = std::max(size, rhs.size) + 1;
    ensure_capacity(new_size);
    long long carry = 0LL;
    for (int i = 0; i < new_size; ++i) {
        long long cur_value = carry;
        if (i < size) {
            cur_value += 1LL * digits[i];
        }
        if (i < rhs.size) {
            cur_value += 1LL * rhs.digits[i];
        }
        digits[i] = (unsigned int)(cur_value % MAX_VALUE);
        carry = cur_value / MAX_VALUE;
    }
    update_size();
    if (size == 1 && digits[0] == 0) sign = 1;
    return (*this);
}

void big_integer::sub_small(long long x) {
    bool take_away = 0;
    for (int i = 0; i < size; ++i) {
        long long cur = 1LL * digits[i];
        if (i == 0) {
            cur -= x;
        }
        if (take_away) {
            --cur;
            take_away = 0;
        }
        if (cur < 0) {
            cur += MAX_VALUE;
            take_away = 1;
        }
        digits[i] = (unsigned int)cur;
    }
}

big_integer &big_integer::sub(big_integer const &rhs) {
    bool take_away = 0;
    for (int i = 0; i < size; ++i) {
        if (i >= rhs.size) {
            if (!take_away) {
                break;
            } else {
                if (digits[i] > 0) {
                    --digits[i];
                    break;
                } else {
                    digits[i] = (unsigned int)(MAX_VALUE - 1);
                }
            }
        } else {
            long long res = 1LL * digits[i] - 1LL * rhs.digits[i] - 1LL * take_away;
            if (res < 0) {
                res += MAX_VALUE;
                take_away = true;
            } else {
                take_away = false;
            }
            digits[i] = (unsigned int)res;
        }
    }
    update_size();
    if (size == 1 && digits[0] == 0) sign = 1;
    return *this;
}

void big_integer::remove_zeroes() {
    while (size > 1 && digits[size - 1] == 0) {
        --size;
    }
}

int cmp_abs(big_integer const& lhs, big_integer const& rhs) { // abs(lhs) < abs(rhs) -> -1, == 0
    if (lhs.capacity == 1 && rhs.capacity == 1) {
        if (lhs.value == rhs.value) return 0;
        if (std::abs(lhs.value) < std::abs(rhs.value)) return -1;
        return 1;
    }
    if (lhs.capacity == 1) return -1;
    if (rhs.capacity == 1) return 1;
    if (lhs.size != rhs.size) {
        if (lhs.size < rhs.size) {
            return -1;
        } else {
            return 1;
        }
    }
    for (int i = lhs.size - 1; i >= 0; --i) {
        if (lhs.digits[i] < rhs.digits[i]) {
            return -1;
        } else if (lhs.digits[i] > rhs.digits[i]) {
            return 1;
        }
    }
    return 0;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    if (capacity == 1 && rhs.capacity == 1 && is_ok(value - rhs.value)) {
        value -= rhs.value;
        return *this;
    }
    if (capacity == 1) {
        cancel_small(rhs.capacity + 2);
    }
    make_copy();
    if (rhs.capacity == 1) {
        if (sign * ((rhs.value < 0) ? -1 : 1) > 0) {
            long long x = rhs.value;
            sub_small((x < 0) ? -x : x);
            remove_zeroes();
            return *this;
        } else {
            ensure_capacity(size + 1);
            add_small(rhs.value);
            return *this;
        }
    }
    if (sign * rhs.sign < 0) {
        return add(rhs);
    } else {
        if (cmp_abs(*this, rhs) >= 0) {
            return sub(rhs);
        } else {
            big_integer tmp = rhs;
            tmp.make_copy();
            tmp.sub(*this);
            *this = tmp;
            sign ^= (-2);
            return *this;
        }
    }
}

big_integer big_integer::operator+() const {
    big_integer tmp = *this;
    return tmp;
}

big_integer big_integer::operator-() const {
    big_integer tmp = *this;
    if (tmp.capacity == 1) {
        tmp.value = -tmp.value;
        return tmp;
    }
    tmp.make_copy();
    if (size == 1 && digits[0] == 0) return tmp;
    tmp.sign ^= (-2);
    return tmp;
}

void big_integer::update_size() {
    remove_zeroes();
    ensure_capacity(size);
}

big_integer big_integer::operator~() const {
    big_integer tmp = *this;
    if (tmp.capacity == 1) {
        tmp.value = -tmp.value - 1;
        return tmp;
    }
    tmp.make_copy();
    ++tmp;
    tmp.sign ^= (-2);
    tmp.update_size();
    return tmp;
}

big_integer &big_integer::operator++() {
    (*this) += ONE;
    return *this;
}

big_integer big_integer::operator++(int) {
    big_integer tmp = *this;
    (*this) += ONE;
    return tmp;
}

big_integer &big_integer::operator--() {
    (*this) -= ONE;
    return *this;
}

big_integer big_integer::operator--(int) {
    big_integer tmp = *this;
    (*this) -= ONE;
    return tmp;
}

void big_integer::shift_left(int k) {
    if (capacity == 1) {
        if (value == 0LL) return;
        if (k <= 31) {
            value <<= k;
            if (is_ok(value)) return;
            else cancel_small(3);
        }
    }
    make_copy();
    int blocks = k / POWER;
    k %= POWER;
    ensure_capacity(size + blocks + 1);
    unsigned int tmp = 0;
    for (int i = size - 1; i >= 0; --i) {
        tmp = digits[i];
        digits[i] = 0;
        digits[i + blocks + 1] |= (tmp >> (POWER - k));
        digits[i + blocks] |=  ((tmp & ((1U << (POWER - k)) - 1)) << k);
    }
    size += blocks + 1;
    update_size();
}

void big_integer::shift_right(int k) {
    if (capacity == 1) {
        value >>= k;
        return;
    }
    make_copy();
    int blocks = k / POWER;
    k %= POWER;
    bool dec_one = ((digits[0] & ((1 << k) - 1)) != 0);
    digits[0] >>= k;
    for (int i = 1; i < size; ++i) {
        digits[i - 1] |= (digits[i] & ((1 << k) - 1)) << (POWER - k);
    }
    if (!dec_one) {
        int till = std::min(blocks, size);
        for (int i = 0; i < till; ++i) {
            if (digits[i] != 0) {
                dec_one = true;
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        if (i + blocks < size) {
            digits[i] = digits[i + blocks];
        } else {
            digits[i] = 0;
        }
    }
    if ((sign < 0) && (dec_one)) {
        --(*this);
    }
    update_size();
}

std::string to_string(big_integer const &a) {
    if (a.capacity == 1) {
        return std::to_string(a.value);
    }
    int lst = a.size - 1;
    while (lst > 0 && a.digits[lst] == 0) {
        --lst;
    }
    int size0 = 2 + (lst + 1) * big_integer::DIGITS_IN_ONE;
    unsigned int *tmp = new unsigned int[lst + 1];
    for (int i = 0; i <= lst; ++i) {
        tmp[i] = a.digits[i];
    }

    char *str = new char[size0];
    for (int i = 0; i < size0; ++i) {
        str[i] = 0;
    }
    int ind = 0;
    while (true) {
        bool got_zero = true;
        long long cur = 0LL;
        for (int i = lst; i >= 0; --i) {
            cur = cur * big_integer::MAX_VALUE + tmp[i];
            tmp[i] = (unsigned int)(cur / 10LL);
            cur %= 10LL;
            if (tmp[i] != 0LL) {
                got_zero = false;
            }
        }
        str[ind++] = (char)(cur + '0');
        if (got_zero) {
            break;
        }
        while (lst > 0 && a.digits[lst] == 0) {
            --lst;
        }
    }

    if (a.sign < 0) {
        str[ind++] = '-';
    }
    int le = 0;
    int ri = ind - 1;
    while (le < ri) {
        std::swap(str[le++], str[ri--]);
    }
    std::string answer = std::string(str);
    delete[] str;
    delete[] tmp;
    return answer;
}

bool operator==(big_integer const& a, big_integer const& b) {
    if (a.capacity == 1 && b.capacity == 1) return a.value == b.value;
    if (a.capacity == 1) {
        if (b.size == 1 && b.digits[0] == std::abs(a.value)) {
            if ((b.sign == 1 && a.value >= 0) || (b.sign == -1 && a.value <= 0)) return true;
            return false;
        }
        return false;
    }
    if (b.capacity == 1) {
        if (a.size == 1 && a.digits[0] == std::abs(b.value)) {
            if ((a.sign == 1 && b.value >= 0) || (a.sign == -1 && b.value <= 0)) return true;
            return false;
        }
        return false;
    }
    if (a.sign != b.sign || a.size != b.size) {
        return false;
    }
    return cmp_abs(a, b) == 0;
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return !(a == b);
}

big_integer operator+(big_integer a, big_integer const& b) {
    a += b;
    return a;
}
big_integer operator-(big_integer a, big_integer const& b) {
    a -= b;
    return a;
}

big_integer big_integer::ONE = 1;

void big_integer::mul_small(long long x) {
    if (x < 0) sign *= -1, x = -x;
    long long carry = 0;
    for (int i = 0; i < size; i++) {
        long long res = digits[i] * x + carry;
        digits[i] = (unsigned int) (res % MAX_VALUE);
        carry = res / MAX_VALUE;
    }
    while (carry != 0) {
        digits[size++] = (unsigned int) (carry % MAX_VALUE);
        carry /= MAX_VALUE;
    }
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    if (capacity == 1 && rhs.capacity == 1) {
        value *= rhs.value;
        if (!is_ok(value)) cancel_small(3);
        return *this;
    }
    if (capacity == 1) cancel_small(3);
    if (rhs.capacity == 1) {
        ensure_capacity(size + 2);
        make_copy();
        mul_small(rhs.value);
        return *this;
    }
    sign *= rhs.sign;
    int max_size = size + rhs.size + 5;
    //ensure_capacity(max_size);
    //unsigned int *tmp = new unsigned int[capacity];
    unsigned int *tmp = create_pointer(max_size, 1);
    for (int i = 0; i < max_size; ++i) {
        tmp[i] = 0;
    }
    long long cur = 0LL;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < rhs.size; ++j) {
            cur = (1LL * digits[i]) * rhs.digits[j] + tmp[i + j];
            tmp[i + j] = (unsigned int)(cur & (MAX_VALUE - 1));
            cur >>= (1LL * POWER);
            if (cur != 0LL) {
                int nxt_index = i + j + 1;
                tmp[nxt_index] += cur;
                while (tmp[nxt_index] >= MAX_VALUE) {
                    tmp[nxt_index++] -= MAX_VALUE;
                    ++tmp[nxt_index];
                }
            }
        }
    }
    dec_refs(digits);
    digits = tmp;
    capacity = max_size;
    size += rhs.size;
    update_size();
    if (size == 1 && digits[size - 1] == 0) {
        sign = 1;
    }
    return *this;
}

void big_integer::div_small(long long x) {
    if (x < 0) sign *= -1, x = -x;
    long long carry = 0;
    for (int i = size - 1; i >= 0; --i) {
        long long res = (carry << 31LL) + digits[i];
        digits[i] = (unsigned int) (res / x);
        carry = res % x;
    }
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    if (rhs == 0) {
        *this = rhs;
    }
    if (cmp_abs(*this, rhs) < 0) {
        *this = 0;
    }
    if (*this == 0) {
        return *this;
    }

    if (capacity == 1 && rhs.capacity == 1) {
        value /= rhs.value;
        if (!is_ok(value)) cancel_small(3);
        return *this;
    }
    if (rhs.capacity == 1) {
        make_copy();
        div_small(rhs.value);
        remove_zeroes();
        return *this;
    }

    make_copy();
    int sign0 = sign * rhs.sign;
    big_integer rhs_copy = rhs;
    rhs_copy.make_copy();
    int tmp_size = size - rhs.size + 5;
    unsigned int *tmp = create_pointer(tmp_size, 1);
    for (int i = 0; i < tmp_size; ++i) {
        tmp[i] = 0;
    }
    long long next, res, XY;
    double ABC;
    sign = rhs_copy.sign = 1;
    int was_sz = size;
    rhs_copy <<= (POWER * (size - rhs.size));
    for (int i = size - 1; i >= rhs.size - 1; --i) {
        ABC = 1LL * digits[i] * MAX_VALUE; // B
        XY = 1LL * rhs_copy.digits[i] * MAX_VALUE; // X
        if (i > 0) {
            ABC += digits[i - 1]; // C
            XY += rhs_copy.digits[i - 1]; // Y
        }
        if (i + 1 < size) {
            ABC += ((double)digits[i + 1]) * MAX_VALUE * MAX_VALUE; //A
        }

        ABC /= XY + 1;
        res = (long long)(ABC - 1e-9);

        tmp[i - rhs.size + 1] = (unsigned int)res;
        next = 0;

        for (int j = i - rhs.size + 1; j <= i; j++) {
            next += digits[j] - rhs_copy.digits[j] * res;
            XY = next % MAX_VALUE;
            next /= MAX_VALUE;
            if (XY < 0) {
                XY += MAX_VALUE;
                next--;
            }
            digits[j] = (unsigned int)XY;
        }
        if (next) {
            digits[i + 1] += next;
        }
        while ((size > 1) && (digits[size - 1] == 0)) {
            --size;
        }
        int iters = 0;
        while (*this >= rhs_copy && iters < 2) { //check
            ++iters;
            ++tmp[i - rhs.size + 1]; // increase cur digit
            next = 0LL;
            for (int j = i - rhs.size + 1; j <= i; j++) {
                next += (long long)digits[j] - rhs_copy.digits[j];
                XY = next;
                next = 0;
                while (XY < 0) {
                    XY += MAX_VALUE;
                    next--;
                }
                digits[j] = (unsigned int)XY;
            }
            if (next) {
                digits[i + 1] += next;
            }
            remove_zeroes();
        }
        for (int j = std::max(i - rhs_copy.size, 0); j < i; j++) {
            rhs_copy.digits[j] = rhs_copy.digits[j + 1];
        }
        rhs_copy.digits[i] = 0;
        rhs_copy.size--;
    }
    dec_refs(digits);
    digits = tmp;
    capacity = tmp_size;
    sign = sign0;
    size = was_sz - rhs.size + 1;
    update_size();
    return *this;

}

big_integer &big_integer::operator<<=(int rhs) {
    if (rhs < 0) {
        shift_right(-rhs);
    } else {
        shift_left(rhs);
    }
    return *this;
}

big_integer &big_integer::operator>>=(int rhs) {
    if (rhs < 0) {
        shift_left(-rhs);
    } else {
        shift_right(rhs);
    }
    return *this;
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    big_integer ths = *this;
    big_integer tmp = ths / rhs;
    big_integer mult = tmp * rhs;
    tmp = ths - mult;
    *this = tmp;
    return *this;
}

void big_integer::and_small(long long x) {
    long long y = std::abs(x);
    long long a = y % MAX_VALUE;
    long long b = y / MAX_VALUE;
    if (x < 0) {
        a ^= (MAX_VALUE - 1);
        b ^= (MAX_VALUE - 1);
    }
    digits[0] &= a;
    digits[1] &= b;
    for (int i = 2; i < size; i++) {
        digits[i] = 0;
    }
}

big_integer &big_integer::operator&=(big_integer const &rhs) {
    if (capacity == 1 && rhs.capacity == 1) {
        value &= rhs.value;
        return *this;
    }
    if (capacity == 1) cancel_small(3);
    make_copy();
    if (rhs.capacity == 1) {
        and_small(rhs.value);
        remove_zeroes();
        return *this;
    }

    if (capacity < rhs.capacity) {
        ensure_capacity(rhs.capacity + 2);
    }
    if (sign < 0) {
        ++(*this);
        for (int i = 0; i < capacity; i++) {
            digits[i] ^= (unsigned int) (MAX_VALUE - 1LL);
        }
        sign = -1;
    }

    long long cur = 0LL;
    long long carry = 1LL;
    int i;
    for (i = 0; i < rhs.capacity; i++) {
        if (rhs.sign > 0) {
            digits[i] &= rhs.digits[i];
        } else {
            cur = (rhs.digits[i] ^ (unsigned int)(MAX_VALUE - 1LL)) + carry;
            carry = 0;
            if (cur == MAX_VALUE) {
                cur -= MAX_VALUE;
                carry = 1;
            }
            digits[i] &= cur;
        }
    }
    for (; i < capacity; i++) {
        if (rhs.sign > 0) {
            digits[i] = 0;
        } else {
            cur = ((unsigned int)(MAX_VALUE - 1)) + carry;
            carry = 0;
            if (cur == MAX_VALUE) {
                cur -= MAX_VALUE;
                carry = 1;
            }
            digits[i] &= cur;
        }
    }

    if (sign < 0 && rhs.sign < 0) {
        for (i = 0; i < capacity; i++) {
            digits[i] ^= (unsigned int)(MAX_VALUE - 1);
        }
        --(*this);
        sign = -1;
    } else {
        sign = 1;
    }
    size = capacity;
    update_size();
    return *this;
}

void big_integer::or_small(long long x) {
    long long y = std::abs(x);
    long long a = y % MAX_VALUE;
    long long b = y / MAX_VALUE;
    if (x < 0) {
        a ^= (MAX_VALUE - 1);
        b ^= (MAX_VALUE - 1);
    }
    digits[0] |= a;
    digits[1] |= b;
}

big_integer &big_integer::operator|=(const big_integer &rhs) {
    if (capacity == 1 && rhs.capacity == 1) {
        value |= rhs.value;
        return *this;
    }
    if (capacity == 1) cancel_small(3);
    make_copy();
    if (rhs.capacity == 1) {
        or_small(rhs.value);
        remove_zeroes();
        return *this;
    }

    if (capacity < rhs.capacity) {
        ensure_capacity(rhs.capacity + 2);
    }
    if (sign < 0) {
        ++(*this);
        for (int i = 0; i < capacity; i++) {
            digits[i] ^= (unsigned int)(MAX_VALUE - 1);
        }
    }

    int i = 0;
    long long next = 0;
    int overflow = 1;
    for (; i < rhs.capacity; i++) {
        if (rhs.sign > 0) {
            digits[i] |= rhs.digits[i];
        } else {
            next = (rhs.digits[i] ^ (unsigned int)(MAX_VALUE - 1)) + overflow;
            overflow = 0;
            if (next == MAX_VALUE) {
                next -= MAX_VALUE;
                overflow = 1;
            }
            digits[i] |= next;
        }
    }
    for (; i < capacity; i++) {
        if (rhs.sign > 0) {
            digits[i] |= 0;
        } else {
            next = (0 ^ (unsigned int)(MAX_VALUE - 1)) + overflow;
            overflow = 0;
            if (next == MAX_VALUE) {
                next -= MAX_VALUE;
                overflow = 1;
            }
            digits[i] |= next;
        }
    }

    if ((sign < 0) || (rhs.sign < 0)) {
        sign = -1;
        for (i = 0; i < capacity; i++) {
            digits[i] ^= (unsigned int)(MAX_VALUE - 1);
        }
        --(*this);
    }
    size = capacity;
    update_size();
    return *this;
}

void big_integer::xor_small(long long x) {
    long long y = std::abs(x);
    long long a = y % MAX_VALUE;
    long long b = y / MAX_VALUE;
    if (x < 0) {
        a ^= (MAX_VALUE - 1);
        b ^= (MAX_VALUE - 1);
    }
    digits[0] ^= a;
    digits[1] ^= b;
}

big_integer &big_integer::operator^=(big_integer const &rhs) {
    if (capacity == 1 && rhs.capacity == 1) {
        value ^= rhs.value;
        return *this;
    }
    if (capacity == 1) cancel_small(3);
    make_copy();
    if (rhs.capacity == 1) {
        xor_small(rhs.value);
        remove_zeroes();
        return *this;
    }

    if (capacity < rhs.capacity) {
        ensure_capacity(rhs.capacity + 2);
    }
    if (sign < 0) {
        ++(*this);
        for (int i = 0; i < capacity; i++) {
            digits[i] ^= (unsigned int)(MAX_VALUE - 1LL);
        }
    }

    long long cur = 0LL;
    long long carry = cur + 1LL;
    int i;
    for (i = 0; i < rhs.capacity; i++) {
        if (rhs.sign > 0) {
            digits[i] ^= rhs.digits[i];
        } else {
            cur = (rhs.digits[i] ^ (unsigned int)(MAX_VALUE - 1LL)) + carry;
            carry = 0;
            if (cur == MAX_VALUE) {
                cur -= MAX_VALUE;
                carry = 1;
            }
            digits[i] ^= cur;
        }
    }
    for (; i < capacity; i++) {
        if (rhs.sign < 0) {
            cur = (unsigned int)(MAX_VALUE - 1) + carry;
            carry = 0;
            if (cur == MAX_VALUE) {
                cur -= MAX_VALUE;
                carry = 1;
            }
            digits[i] ^= cur;
        }
    }

    if ((sign < 0) ^ (rhs.sign < 0)) {
        for (i = 0; i < capacity; i++) {
            digits[i] ^= (unsigned int)(MAX_VALUE - 1);
        }
        sign = -1;
        --(*this);
    } else {
        sign = 1;
    }
    size = capacity;
    update_size();
    return *this;
}

big_integer operator*(big_integer a, big_integer const& b) {
    a *= b;
    return a;
}


big_integer operator/(big_integer a, big_integer const& b) {
    a /= b;
    return a;
}
big_integer operator%(big_integer a, big_integer const& b) {
     a %= b;
    return a;
}

big_integer operator<<(big_integer a, int b) {
    a <<= b;
    return a;
}
big_integer operator>>(big_integer a, int b) {
    a >>= b;
    return a;
}

std::ostream& operator<<(std::ostream& out, big_integer const& c) {
    out << to_string(c);
    return out;
}

big_integer operator&(big_integer a, big_integer const& b) {
    a &= b;
    return a;
}

big_integer operator|(big_integer a, big_integer const& b) {
    a |= b;
    return a;
}

big_integer operator^(big_integer a, big_integer const& b) {
    a ^= b;
    return a;
}