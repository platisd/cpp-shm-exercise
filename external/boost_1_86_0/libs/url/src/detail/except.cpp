//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//


#include <boost/url/detail/config.hpp>
#include <boost/url/detail/except.hpp>
#include <boost/throw_exception.hpp>
#include <boost/system/system_error.hpp>
#include <new>
#include <stdexcept>

namespace boost {
namespace urls {
namespace detail {

void
throw_system_error(
    system::error_code const& ec,
    source_location const& loc)
{
    throw_exception(
        boost::system::system_error(ec), loc);
}

void
throw_errc(
    boost::system::errc::errc_t ev,
    source_location const& loc)
{
    throw_system_error(make_error_code(ev), loc);
}

void
throw_invalid_argument(
    source_location const& loc)
{
    throw_errc(boost::system::errc::invalid_argument, loc);
}

void
throw_length_error(
    source_location const& loc)
{
    throw_errc(boost::system::errc::value_too_large, loc);
}

} // detail
} // url
} // boost

