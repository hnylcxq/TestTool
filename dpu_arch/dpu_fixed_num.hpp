#ifndef _FIXED_NUM_HPP
#define _FIXED_NUM_HPP
#include <cstdint>
#include <algorithm>


#ifdef ITBENCH
#ifdef WIN32
#include "itb_assert.h"
#else
#include <cassert>
#define ASSERT_ITB(A, B, ...) assert(A)
#endif
#define FP_ASSERT(A, B, ...) ASSERT_ITB(A, B, __VA_ARGS__)
#else
#define FP_ASSERT(A, B, ...)
#endif
#ifdef max
#undef max
#endif
template<typename T>
struct identity { typedef T type; };


template<class T>
T Clamp(T x, T min, T max)
{
    if (x > max)
        return max;
    if (x < min)
        return min;
    return x;
}




class fixed_num
{
public:
    using raw_type = int64_t;
    static const raw_type RAW_MASK = INT64_MAX;
    static const uint32_t RAW_VALID_BITS = sizeof(raw_type) * 8 - 1;
    /*
        @ For a given `signed` m.n format, using an m+n+1 bit container
        @ with n fractional bits:
        @ range from -(2^m) to 2^m - 2^(-n)
        @ the resolution is 2^(-n)
        @
        @ For a given `unsigned` m.n format, using an m+n bit container
        @ with n fractional bits:
        @ range from 0 to 2^m - 2^(-n)
        @ the resolution is 2^(-n)
    */

    fixed_num()
    {
        m_int_bits = 32;
        m_frac_bits = 32;
        m_is_signed = false;
        m_raw = 0;
    };
    fixed_num(const int& int_bits, const int& frac_bits,
        const bool& is_signed = true)
    {
        m_int_bits = int_bits;
        m_frac_bits = frac_bits;
        m_is_signed = is_signed;
        auto_set_vars_by_input();
    };
    template <typename T>
    fixed_num(const int& int_bits, const int& frac_bits,
        const bool& is_signed = true, T value = 0)
    {
        m_int_bits = int_bits;
        m_frac_bits = frac_bits;
        m_is_signed = is_signed;
        auto_set_vars_by_input();
        *this = value;
    };

    ~fixed_num() {};

    operator double() const
    {
        return m_double_dbg;
    };

    operator float() const
    {
        return (float)m_double_dbg;
    };

    operator raw_type() const
    {
        FP_ASSERT(0, ""); // should never use this
        return (raw_type)m_double_dbg;// lei just avoid warnning
    };

    template<typename T>
    fixed_num& operator=(const T& rhs)
    {
        this->update_raw((raw_type)rhs << m_frac_bits);
        return *this;
    };
    fixed_num& operator=(const fixed_num& rhs)
    {
        this->m_int_bits = rhs.get_int_bits();
        this->m_frac_bits = rhs.get_frac_bits();
        this->m_is_signed = rhs.get_is_signed();
        auto_set_vars_by_input();
        this->set_raw(rhs.get_raw());
        return *this;
    }

    fixed_num& operator=(const float& rhs)
    {
        raw_type v = (raw_type)((double)rhs * (1ull << m_frac_bits));
        // unsigned fixed number shouldn't accept negative value
        if (m_is_signed == false) FP_ASSERT(v >= 0, "Error: set negative to unsigned FIXED.");
        this->update_raw(v);
        return *this;
    };

    fixed_num& operator=(const double& rhs)
    {
        raw_type v = (raw_type)(rhs * (1ull << m_frac_bits));
        // unsigned fixed number shouldn't accept negative value
        if (m_is_signed == false) FP_ASSERT(v >= 0, "Error: set negative to unsigned FIXED.");
        this->update_raw(v);
        return *this;
    };
    template<typename T>
    fixed_num operator+(const T& rhs) const
    {
        int rhs_int_bits = bits_of_int_without_sign(int(rhs));
        fixed_num op_rhs(rhs_int_bits, m_frac_bits, true, rhs);
        return *this + op_rhs;
    };
    fixed_num operator+(const fixed_num& rhs) const
    {
        int int_bits_new = std::max(this->get_int_bits(), rhs.get_int_bits());
        int frac_bits_new = std::max(this->get_frac_bits(), rhs.get_frac_bits());
        bool out_is_signed = this->get_is_signed() || rhs.get_is_signed();
        fixed_num t(int_bits_new, frac_bits_new, out_is_signed);
        fixed_num op_lhs = *this;
        fixed_num op_rhs = rhs;
        op_lhs.convert(int_bits_new, frac_bits_new);
        op_rhs.convert(int_bits_new, frac_bits_new);

        raw_type v = op_lhs.raw() + op_rhs.raw();

        if (is_overflow(v))
        {
            t.convert(int_bits_new + 1, frac_bits_new);
        }
        t.update_raw(v);
        return t;
    };
    template<typename T>
    fixed_num operator-(const T& rhs) const
    {
        int rhs_int_bits = bits_of_int_without_sign(int(rhs));
        fixed_num op_rhs(rhs_int_bits, m_frac_bits, true, rhs);
        return *this - op_rhs;
    };
    fixed_num operator-(const fixed_num& rhs) const
    {
        int int_bits_new = std::max(this->get_int_bits(), rhs.get_int_bits());
        int frac_bits_new = std::max(this->get_frac_bits(), rhs.get_frac_bits());
        fixed_num op_lhs = *this;
        fixed_num op_rhs = rhs;
        op_lhs.convert(int_bits_new, frac_bits_new);
        op_rhs.convert(int_bits_new, frac_bits_new);
        raw_type v = op_lhs.raw() - op_rhs.raw();
        bool out_is_signed = m_is_signed || v < 0;
        fixed_num t(int_bits_new, frac_bits_new, out_is_signed);
        t.update_raw(v);
        return t;
    };
    template<typename T>
    fixed_num operator*(const T& rhs) const
    {
        int rhs_int_bits = bits_of_int_without_sign(int(rhs));
        fixed_num op_rhs(rhs_int_bits, m_frac_bits, true, rhs);
        return  *this * op_rhs;
    };
    fixed_num operator*(const fixed_num& rhs) const
    {
        bool is_res_signed =
            this->m_is_signed || rhs.get_is_signed();
        int int_bits_new = m_int_bits + rhs.get_int_bits();
        int frac_bits_new = m_frac_bits + rhs.get_frac_bits();
        fixed_num t(int_bits_new, frac_bits_new, is_res_signed);
        raw_type v = this->m_raw * rhs.raw();
        t.update_raw(v);
        return t;
    };
    template<typename T>
    fixed_num operator/(const T& rhs) const
    {
        int rhs_int_bits = bits_of_int_without_sign(int(rhs));
        fixed_num op_rhs(rhs_int_bits, m_frac_bits, true, rhs);
        return  *this / op_rhs;
    };
    fixed_num operator/(const fixed_num& rhs) const
    {
        bool is_res_signed =
            this->m_is_signed || rhs.get_is_signed();
        int int_bits_new = m_int_bits + rhs.get_frac_bits();
        int frac_bits_new = m_frac_bits + rhs.get_int_bits();
        fixed_num t(int_bits_new, frac_bits_new, is_res_signed);
        raw_type v = this->m_raw << rhs.get_bits();
        v /= rhs.raw();
        t.update_raw(v);
        return t;
    };
    template<typename T>
    bool operator>(const T& rhs) const
    {
        return *this > fixed_num(m_int_bits, m_frac_bits, m_is_signed, rhs);
    };
    bool operator>(const fixed_num& rhs) const
    {
        int new_int_bits = std::max(this->get_int_bits(), rhs.get_int_bits());
        int new_frac_bits = std::max(this->get_frac_bits(), rhs.get_frac_bits());
        fixed_num op_lhs = *this;
        fixed_num op_rhs = rhs;
        op_lhs.convert(new_int_bits, new_frac_bits);
        op_rhs.convert(new_int_bits, new_frac_bits);
        return op_lhs.raw() > op_rhs.raw();
    };
    template<typename T>
    bool operator<(const T& rhs) const
    {
        return *this < fixed_num(m_int_bits, m_frac_bits, m_is_signed, rhs);
    };
    bool operator<(const fixed_num& rhs) const
    {
        int new_int_bits = std::max(this->get_int_bits(), rhs.get_int_bits());
        int new_frac_bits = std::max(this->get_frac_bits(), rhs.get_frac_bits());
        fixed_num op_lhs = *this;
        fixed_num op_rhs = rhs;
        op_lhs.convert(new_int_bits, new_frac_bits);
        op_rhs.convert(new_int_bits, new_frac_bits);
        return op_lhs.raw() < op_rhs.raw();
    };
    template<typename T>
    bool operator>=(const T& rhs) const
    {
        return *this >= fixed_num(m_int_bits, m_frac_bits, m_is_signed, rhs);
    };
    bool operator>=(const fixed_num& rhs) const
    {
        int new_int_bits = std::max(this->get_int_bits(), rhs.get_int_bits());
        int new_frac_bits = std::max(this->get_frac_bits(), rhs.get_frac_bits());
        fixed_num op_lhs = *this;
        fixed_num op_rhs = rhs;
        op_lhs.convert(new_int_bits, new_frac_bits);
        op_rhs.convert(new_int_bits, new_frac_bits);
        return op_lhs.raw() >= op_rhs.raw();
    };
    template<typename T>
    bool operator<=(const T& rhs) const
    {
        return *this <= fixed_num(m_int_bits, m_frac_bits, m_is_signed, rhs);
    };
    bool operator<=(const fixed_num& rhs) const
    {
        int new_int_bits = std::max(this->get_int_bits(), rhs.get_int_bits());
        int new_frac_bits = std::max(this->get_frac_bits(), rhs.get_frac_bits());
        fixed_num op_lhs = *this;
        fixed_num op_rhs = rhs;
        op_lhs.convert(new_int_bits, new_frac_bits);
        op_rhs.convert(new_int_bits, new_frac_bits);
        return op_lhs.raw() <= op_rhs.raw();
    };
    template<typename T>
    bool operator==(const T& rhs) const
    {
        return *this == fixed_num(m_int_bits, m_frac_bits, m_is_signed, rhs);
    };
    bool operator==(const fixed_num& rhs) const
    {
        int new_int_bits = std::max(this->get_int_bits(), rhs.get_int_bits());
        int new_frac_bits = std::max(this->get_frac_bits(), rhs.get_frac_bits());
        fixed_num op_lhs = *this;
        fixed_num op_rhs = rhs;
        op_lhs.convert(new_int_bits, new_frac_bits);
        op_rhs.convert(new_int_bits, new_frac_bits);
        return op_lhs.raw() == op_rhs.raw();
    };

    fixed_num abs() const
    {
        fixed_num t = *this;
        raw_type v = std::abs(m_raw);
        t.update_raw(v);
        return t;
    };

    bool is_neg() const
    {
        return ((1ull << m_bits) & m_raw) > 0;
    };

    fixed_num create(const int32_t& value)
    {
        fixed_num t = *this;
        t = value;
        return t;
    };
    fixed_num create(const double& value)
    {
        fixed_num t = *this;
        t = value;
        return t;
    };
    fixed_num create_by_int() const
    {
        fixed_num t = *this;
        if (m_is_signed)
        {
            raw_type v =
                (raw_type)m_double_dbg * (1ull << m_frac_bits);
            t.update_raw(v);
        }
        else
        {
            t.update_raw(m_raw & (RAW_MASK << m_frac_bits));
        }
        return t;
    };
    fixed_num create_by_frac() const
    {
        fixed_num t = *this;
        if (m_is_signed)
        {
            raw_type v = m_raw - (raw_type)m_double_dbg * (1ull << m_frac_bits);
            t.update_raw(v);
        }
        else
        {
            t.update_raw(m_raw & ~(n_bits_mask(m_int_bits) << m_frac_bits));
        }
        return t;
    };

    void assign(const fixed_num& value,
        const bool& is_clamp = false, const bool& is_round = false, const bool& is_simple_round = false)
    {
        fixed_num t = value;
        t.convert(m_int_bits, m_frac_bits, m_is_signed, is_clamp, is_round, is_simple_round);
        *this = t;
    };

    void convert(
        const int& int_bits_new,
        const int& frac_bits_new,
        const int& is_signed_new = -1,
        const bool& is_clamp = false,
        const bool& is_round = false,
        const bool& is_simple_round = false)
    {
        if (is_signed_new != -1)
        {
            if (this->m_is_signed == true &&
                is_signed_new == 0 &&
                this->is_neg())
            {
                FP_ASSERT(0,
                    "current fixed_num is signed and the value is negative, can't convert to unsigned type! please check!");
            }
            else
            {
                m_is_signed = (bool)(is_signed_new);
            }
        }
        if (frac_bits_new < m_frac_bits)
        {
            int shift_bits = m_frac_bits - frac_bits_new;
            int round_delta = 0;
            if (is_round)
            {
                if (is_simple_round)
                {
                    round_delta = is_neg() ? 0 : (1 << (shift_bits - 1));
                }
                else
                    round_delta = is_neg() ? -(1 << (shift_bits - 1)) : (1 << (shift_bits - 1));
            }
            m_raw = (m_raw + round_delta) >> shift_bits;
        }
        else
        {
            uint32_t shift = frac_bits_new - m_frac_bits;
            m_raw <<= shift;
        }
        m_frac_bits = frac_bits_new;

        if (int_bits_new < m_int_bits)
        {
            raw_type new_max =
                (n_bits_mask(int_bits_new) << frac_bits_new) | n_bits_mask(frac_bits_new);
            raw_type new_min =
                m_is_signed ? ((-1 * (1ull << int_bits_new)) << m_frac_bits) : 0;

            if (m_raw > new_max || m_raw < new_min)
            {
                if (is_clamp)
                {
                    m_raw = Clamp(m_raw, new_min, new_max);
                }
                else
                {
                    FP_ASSERT(false,
                        "Precision loss when converting, \
                        set clamp/round flag if you need auto conversion!");
                }
            }
        }
        m_int_bits = int_bits_new;

        auto_set_vars_by_input();
        update_raw(m_raw);
    };

    void round_bits(const int& frac_round_bits)
    {
        int shift_bits = m_frac_bits - frac_round_bits;
        int round_delta = 1 << (shift_bits - 1);
        FP_ASSERT(shift_bits - 1 >= 0, "wrong round bit setting!");
        update_raw(((m_raw + round_delta) >> shift_bits) << shift_bits);
    };

    void set_raw(const raw_type& value)
    {
        raw_type v = 0;
        if ((value & (1ull << m_bits)) != 0)
        {
            update_raw(value | (RAW_MASK << m_bits));
        }
        else
        {
            update_raw(value & n_bits_mask(m_bits));
        }
    };

    raw_type get_raw() const
    {
        raw_type mask = m_is_signed ?
            n_bits_mask(m_bits + 1) :
            n_bits_mask(m_bits);
        return m_raw & mask;
    };
    uint32_t get_raw_dw() const
    {
        FP_ASSERT(m_bits <= 32, "Overflow");
        return get_raw() & 0xffffffff;
    };
    int get_int_bits() const
    {
        return m_int_bits;
    };
    int get_frac_bits() const
    {
        return m_frac_bits;
    };
    int get_bits() const
    {
        return m_bits;
    };
    bool get_is_signed() const
    {
        return m_is_signed;
    };

    void to_max_value()
    {
        this->update_raw(m_raw_max);
    }
    void to_min_value()
    {
        this->update_raw(m_raw_min);
    }
private:
    int m_int_bits = 0;
    int m_frac_bits = 0;
    int m_sint_bits = 0;
    int m_bits = 0;
    raw_type m_raw_max = 0;
    raw_type m_raw_min = 0;
    raw_type m_raw = 0;
    bool m_is_signed = true;
    double m_double_dbg = 0.0;

    void auto_set_vars_by_input()
    {
        //m_sint_bits = m_is_signed ? m_int_bits + 1 : m_int_bits; // todo: useless?
        //m_bits = m_sint_bits + m_frac_bits;
        m_bits = m_int_bits + m_frac_bits;
        FP_ASSERT(m_bits <= RAW_VALID_BITS, "Bits overflow!");
        m_raw_max = (n_bits_mask(m_int_bits) << m_frac_bits) | n_bits_mask(m_frac_bits);
        m_raw_min = m_is_signed ? (raw_type)((-1 * (1ull << m_int_bits)) << m_frac_bits) : 0;
    };

    raw_type n_bits_mask(int bits) const
    {
        return (1ull << bits) - 1;
    };

    bool is_overflow(const raw_type& value) const
    {
        if (value > m_raw_max || value < m_raw_min)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    void update_raw(const raw_type& value)
    {
        if (is_overflow(value)) FP_ASSERT(0, "overflow!");

        m_raw = value;

        m_double_dbg = (double)(m_raw) / (1ull << m_frac_bits);
    };

    raw_type raw() const
    {
        return m_raw;
    };

    static int bits_of_int_without_sign(const int& value)
    {
        int r = 1, v = value;
        while ((v >>= 1) != (v >= 0 ? 0 : -1))
        {
            r++;
        }
        return r;
    };
};

#endif // !_FIXED_NUM_HPP
