// Copyright 2025 The OnePointer Authors.
//

#pragma once

#include "cppenumflag.hpp"

#include <ranges>
#include <utility>


namespace plugin {
namespace util {

class TimeTag {
public:
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

    static TimeTag* parse_time( const std::string tflag );

    TimeTag() = default;
    TimeTag( const std::string tflag );
    TimeTag( const uint8_t hours, const uint8_t minutes, const uint8_t seconds = 0 );
    TimeTag( const uint8_t year, const uint8_t month, const uint8_t day );
    TimeTag( const uint8_t year, const uint8_t month, const uint8_t day
           , const uint8_t hours, const uint8_t minutes, const uint8_t seconds = 0 );

    virtual operator std::string() const;

    TimeTag& operator+=( const TimeTag& another );
    
    static uint8_t plus_month( const uint8_t lhs, const uint8_t rhs, TimeTag& initial = *new TimeTag() );
    static uint8_t plus_day( const uint8_t lhs, const uint8_t rhs, TimeTag& initial = *new TimeTag() );
    static uint8_t plus_hours( const uint8_t lhs, const uint8_t rhs, TimeTag& initial = *new TimeTag() );
    static uint8_t plus_minutes( const uint8_t lhs, const uint8_t rhs, TimeTag& initial = *new TimeTag() );
    static uint8_t plus_seconds( const uint8_t lhs, const uint8_t rhs, TimeTag& initial = *new TimeTag() );

    static TimeTag operator+( const TimeTag& lhs, const TimeTag& rhs );
};


namespace time {




TimeTag* now_date();
TimeTag* now_time();
TimeTag* now();


} // namespace time


} // namespace util
} // namespace plugin
