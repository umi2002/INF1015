#ifndef ITER_DROPWHILE_H_
#define ITER_DROPWHILE_H_

#include "filter.hpp"
#include "internal/iterator_wrapper.hpp"
#include "internal/iterbase.hpp"

#include <functional>
#include <iterator>
#include <utility>

namespace iter
{
    namespace impl
    {
        template< typename FilterFunc, typename Container >
        class Dropper;

        using DropWhileFn = IterToolFnOptionalBindFirst< Dropper, BoolTester >;
    }

    constexpr impl::DropWhileFn dropwhile {};
}

template< typename FilterFunc, typename Container >
class iter::impl::Dropper
{
private:
    Container          container_;
    mutable FilterFunc filter_func_;

    friend DropWhileFn;

    Dropper(FilterFunc filter_func, Container&& container) :
        container_(std::forward< Container >(container)),
        filter_func_(filter_func)
    { }

public:
    Dropper(Dropper&&) = default;

    template< typename ContainerT >
    class Iterator
    {
    private:
        template< typename >
        friend class Iterator;
        using Holder = DerefHolder< iterator_deref< ContainerT > >;
        IteratorWrapper< ContainerT > sub_iter_;
        IteratorWrapper< ContainerT > sub_end_;
        Holder                        item_;
        FilterFunc*                   filter_func_;

        void inc_sub_iter()
        {
            ++sub_iter_;
            if (sub_iter_ != sub_end_)
            {
                item_.reset(*sub_iter_);
            }
        }

        //skip all values for which the predicate is true
        void skip_passes()
        {
            while (sub_iter_ != sub_end_
                   && std::invoke(*filter_func_, item_.get()))
            {
                inc_sub_iter();
            }
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = iterator_traits_deref< ContainerT >;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type*;
        using reference         = value_type&;

        Iterator(IteratorWrapper< ContainerT >&& sub_iter,
                 IteratorWrapper< ContainerT >&& sub_end,
                 FilterFunc&                     filter_func) :
            sub_iter_ {std::move(sub_iter)},
            sub_end_ {std::move(sub_end)},
            filter_func_(&filter_func)
        {
            if (sub_iter_ != sub_end_)
            {
                item_.reset(*sub_iter_);
            }
            skip_passes();
        }

        typename Holder::reference operator*()
        {
            return item_.get();
        }

        typename Holder::pointer operator->()
        {
            return item_.get_ptr();
        }

        Iterator& operator++()
        {
            inc_sub_iter();
            return *this;
        }

        Iterator operator++(int)
        {
            auto ret = *this;
            ++*this;
            return ret;
        }

        template< typename T >
        bool operator!=(const Iterator< T >& other) const
        {
            return sub_iter_ != other.sub_iter_;
        }

        template< typename T >
        bool operator==(const Iterator< T >& other) const
        {
            return !(*this != other);
        }
    };

    Iterator< Container > begin()
    {
        return {get_begin(container_), get_end(container_), filter_func_};
    }

    Iterator< Container > end()
    {
        return {get_end(container_), get_end(container_), filter_func_};
    }

    Iterator< AsConst< Container > > begin() const
    {
        return {get_begin(std::as_const(container_)),
                get_end(std::as_const(container_)),
                filter_func_};
    }

    Iterator< AsConst< Container > > end() const
    {
        return {get_end(std::as_const(container_)),
                get_end(std::as_const(container_)),
                filter_func_};
    }
};

#endif
