#include "expanding_search_range.hpp"


#include <iterator>
#include <ranges>
#include <stdexcept>

namespace ct {


class ExpandingSearchRange {
    Pos start;

    // this is here only to bound the range.
    // otherwise it would happily expand forever.
    int max_rings = 10;
public:

    class iterator;
    using const_iterator = iterator;

    constexpr explicit ExpandingSearchRange(int pos_x, int pos_y) : start(pos_x, pos_y) {}

    [[nodiscard]]
    iterator begin() const noexcept;
    [[nodiscard]]
    iterator end() const noexcept;
};


class ExpandingSearchRange::iterator {
    Pos start_ { 0, 0 };
    Pos curr_ { 0, 0 };
    int ring_ = 0;

    enum Direction {
        N = 0,
        W = 1,
        S = 2,
        E = 3,
        X = 4,
    };

    Direction direction_ = X;

public:

    using iterator_category = std::forward_iterator_tag;
    using value_type = Pos;
    using difference_type = std::ptrdiff_t;
    using pointer = const Pos*;
    using reference = const Pos&;


    iterator() = default;

    iterator(Pos start, Pos curr, int ring)
        : start_(start), curr_(curr), ring_(ring) {}


    reference operator*() const noexcept {
        return curr_;
    }

    pointer operator->() const noexcept {
        return &curr_;
    }

    iterator& operator++() noexcept {
        // Walk around the square of width ring about the center
        switch (direction_) {
            case W:
                --curr_.x;
                if (curr_.x == start_.x - ring_) {
                    // change direction when we reach the top-left corner
                    direction_ = S;
                }
                break;
            case S:
                --curr_.y;
                if (curr_.y == start_.y - ring_) {
                    // change direction when we reach the bottom-left corner
                    direction_ = E;
                }
                break;
            case E:
                ++curr_.x;
                if (curr_.x == start_.x + ring_) {
                    // change direction when we reach the bottom-right corner
                    direction_ = N;
                }
                break;
            case N:
                ++curr_.y;
                if (curr_.y == start_.y + ring_) {
                    // change direction when we reach the top-right corner
                    direction_ = W;
                } else if (curr_.y == start_.y) {
                    // special case for the N direction for when we
                    // return to the start_.y line, we instead move
                    // outwards on the next iteration.
                    direction_ = X;
                }
                break;
            case X:
                // Move out to the next ring, start moving north
                ++ring_;
                ++curr_.x;
                direction_ = N;
                break;
        }

        return *this;
    }

    iterator operator++(int) noexcept {
        iterator ret(*this);
        ++(*this);
        return ret;
    }

    friend bool operator==(const iterator& lhs, const iterator& rhs) noexcept {
        return lhs.curr_.x == rhs.curr_.x && lhs.curr_.y == rhs.curr_.y;
    }

    friend bool operator!=(const iterator& lhs, const iterator& rhs) noexcept {
        return !(lhs == rhs);
    }

};


inline ExpandingSearchRange::iterator ExpandingSearchRange::begin() const noexcept {
    return iterator(start, start, 0);
}

inline ExpandingSearchRange::iterator ExpandingSearchRange::end() const noexcept {
    return iterator(start, {start.x + max_rings, start.y}, max_rings);
}


} // namespace ct


ct::Pos ct::find_closest_signal_range(int dim_x, int dim_y, double detection_intensity, Pos start) {

    auto predicate = [detection_intensity](const Pos& pos) {
        return compute_signal_intensity(pos.x, pos.y) > detection_intensity;
    };

    ExpandingSearchRange range(start.x, start.y);
    auto closest_pos = std::ranges::find_if(range, predicate);

    if (closest_pos == range.end()) {
        throw std::runtime_error("No signal found");
    }

    return *closest_pos;
}
