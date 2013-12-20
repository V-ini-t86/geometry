// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP
#define BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP


#include <string>

#include <boost/tuple/tuple.hpp>
#include <boost/geometry/strategies/side_info.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

namespace policies { namespace relate
{


// "tupled" to return intersection results together.
// Now with two, with some meta-programming and derivations it can also be three (or more)
template <typename Policy1, typename Policy2, typename CalculationType = void>
struct segments_tupled
{
    typedef boost::tuple
        <
            typename Policy1::return_type,
            typename Policy2::return_type
        > return_type;

    // Take segments of first policy, they should be equal
    typedef typename Policy1::segment_type1 segment_type1;
    typedef typename Policy1::segment_type2 segment_type2;

    typedef typename select_calculation_type
        <
            segment_type1,
            segment_type2,
            CalculationType
        >::type coordinate_type;

    // Get the same type, but at least a double
    typedef typename select_most_precise<coordinate_type, double>::type rtype;

    template <typename SegmentIntersectionInfo>
    static inline return_type segments_crosses(side_info const& sides,
                    SegmentIntersectionInfo const& sinfo,
                    segment_type1 const& s1, segment_type2 const& s2)
    {
        return boost::make_tuple
            (
                Policy1::segments_crosses(sides, sinfo, s1, s2),
                Policy2::segments_crosses(sides, sinfo, s1, s2)
            );
    }

    template <typename Segment1, typename Segment2, typename Ratio>
    static inline return_type segments_collinear(
        Segment1 const& segment1, Segment2 const& segment2,
        Ratio const& ra1, Ratio const& ra2, Ratio const& rb1, Ratio const& rb2)
    {
        return boost::make_tuple
            (
                Policy1::segments_collinear(segment1, segment2, ra1, ra2, rb1, rb2),
                Policy2::segments_collinear(segment1, segment2, ra1, ra2, rb1, rb2)
            );
    }

    static inline return_type degenerate(segment_type1 const& segment,
                bool a_degenerate)
    {
        return boost::make_tuple
            (
                Policy1::degenerate(segment, a_degenerate),
                Policy2::degenerate(segment, a_degenerate)
            );
    }

    static inline return_type disjoint()
    {
        return boost::make_tuple
            (
                Policy1::disjoint(),
                Policy2::disjoint()
            );
    }

    static inline return_type error(std::string const& msg)
    {
        return boost::make_tuple
            (
                Policy1::error(msg),
                Policy2::error(msg)
            );
    }

    static inline return_type collinear_disjoint()
    {
        return boost::make_tuple
            (
                Policy1::collinear_disjoint(),
                Policy2::collinear_disjoint()
            );
    }

};

}} // namespace policies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP
